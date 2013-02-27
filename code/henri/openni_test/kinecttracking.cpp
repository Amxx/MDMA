#include "kinecttracking.h"

#include <stdio.h>

//-----------------------------------------------------------------------------
// Callbacks
//-----------------------------------------------------------------------------

// Callback for when the focus is in progress
void XN_CALLBACK_TYPE SessionProgress(const XnChar* strFocus, const XnPoint3D& ptFocusPoint, XnFloat fProgress, void* UserCxt)
{
	printf("Session progress (%6.2f,%6.2f,%6.2f) - %6.2f [%s]\n", ptFocusPoint.X, ptFocusPoint.Y, ptFocusPoint.Z, fProgress,  strFocus);
}
// callback for session start
void XN_CALLBACK_TYPE SessionStart(const XnPoint3D& ptFocusPoint, void* UserCxt)
{
	printf("Session started. Please wave (%6.2f,%6.2f,%6.2f)...\n", ptFocusPoint.X, ptFocusPoint.Y, ptFocusPoint.Z);
}
// Callback for session end
void XN_CALLBACK_TYPE SessionEnd(void* UserCxt)
{
	printf("Session ended. Please perform focus gesture to start session\n");
}
// Callback for wave detection
void XN_CALLBACK_TYPE OnWaveCB(void* cxt)
{
	printf("Wave!\n");
}
// callback for a new position of any hand
void XN_CALLBACK_TYPE OnPointUpdate(const XnVHandPointContext* pContext, void* cxt)
{
	printf("%d: (%f,%f,%f) [%f]\n", pContext->nID, pContext->ptPosition.X, pContext->ptPosition.Y, pContext->ptPosition.Z, pContext->fTime);
}


KinectTracking::KinectTracking() {
	pSessionGenerator = NULL;
}

KinectTracking::~KinectTracking() {
	if(pSessionGenerator)
		delete pSessionGenerator;
}
XnBool KinectTracking::fileExists(const char *fn)
{
	XnBool exists;
	xnOSDoesFileExist(fn, &exists);
	return exists;
}

int KinectTracking::wait() {
	// Main loop
	while (!xnOSWasKeyboardHit())
	{
		context.WaitAnyUpdateAll();
		((XnVSessionManager*)pSessionGenerator)->Update(&context);
	}
	return 0;
}

// this sample can run either as a regular sample, or as a client for multi-process (remote mode)
int KinectTracking::init()
{
	if(pSessionGenerator)
		return 1;
	
	const char *fn = NULL;
	if      (fileExists(SAMPLE_XML_FILE)) fn = SAMPLE_XML_FILE;
	else if (fileExists(SAMPLE_XML_FILE_LOCAL)) fn = SAMPLE_XML_FILE_LOCAL;
	else {
		printf("Could not find '%s' nor '%s'. Aborting.\n" , SAMPLE_XML_FILE, SAMPLE_XML_FILE_LOCAL);
		return XN_STATUS_ERROR;
	}
	XnStatus rc = context.InitFromXmlFile(fn, scriptNode);
	if (rc != XN_STATUS_OK)
	{
		printf("Couldn't initialize: %s\n", xnGetStatusString(rc));
		return 1;
	}

	// Create the Session Manager
	pSessionGenerator = new XnVSessionManager();
	rc = ((XnVSessionManager*)pSessionGenerator)->Initialize(&context, "Click", "RaiseHand");
	if (rc != XN_STATUS_OK)
	{
		printf("Session Manager couldn't initialize: %s\n", xnGetStatusString(rc));
		delete pSessionGenerator;
		return 1;
	}

	// Initialization done. Start generating
	context.StartGeneratingAll();

	// Register session callbacks
	pSessionGenerator->RegisterSession(NULL, &SessionStart, &SessionEnd, &SessionProgress);

	// init & register wave control
	wc.RegisterWave(NULL, OnWaveCB);
	wc.RegisterPointUpdate(NULL, OnPointUpdate);
	pSessionGenerator->AddListener(&wc);

	printf("Please perform focus gesture to start session\n");
	printf("Hit any key to exit\n");

	return 0;
}
