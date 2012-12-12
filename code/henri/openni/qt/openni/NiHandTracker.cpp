/****************************************************************************
*                                                                           *
*  OpenNI 1.x Alpha                                                         *
*  Copyright (C) 2011 PrimeSense Ltd.                                       *
*                                                                           *
*  This file is part of OpenNI.                                             *
*                                                                           *
*  OpenNI is free software: you can redistribute it and/or modify           *
*  it under the terms of the GNU Lesser General Public License as published *
*  by the Free Software Foundation, either version 3 of the License, or     *
*  (at your option) any later version.                                      *
*                                                                           *
*  OpenNI is distributed in the hope that it will be useful,                *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             *
*  GNU Lesser General Public License for more details.                      *
*                                                                           *
*  You should have received a copy of the GNU Lesser General Public License *
*  along with OpenNI. If not, see <http://www.gnu.org/licenses/>.           *
*                                                                           *
****************************************************************************/
//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "NiHandTracker.h"
#include <cassert>


using namespace xn;


//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define LENGTHOF(arr)			(sizeof(arr)/sizeof(arr[0]))
#define FOR_ALL(arr, action)	{for(int i = 0; i < LENGTHOF(arr); ++i){action(arr[i])}}

#define ADD_GESTURE(name)		{if(m_GestureGenerator.AddGesture(name, NULL) != XN_STATUS_OK){printf("Unable to add gesture"); exit(1);}}
#define REMOVE_GESTURE(name)	{if(m_GestureGenerator.RemoveGesture(name) != XN_STATUS_OK){printf("Unable to remove gesture"); exit(1);}}

#define ADD_ALL_GESTURES		FOR_ALL(cGestures, ADD_GESTURE)
#define REMOVE_ALL_GESTURES		FOR_ALL(cGestures, REMOVE_GESTURE)


//---------------------------------------------------------------------------
// Consts
//---------------------------------------------------------------------------
// Gestures to track
static const char			cClickStr[] = "Click";
static const char			cWaveStr[] = "Wave";
static const char* const	cGestures[] =
{
	cClickStr,
	cWaveStr
};

//---------------------------------------------------------------------------
// Statics
//---------------------------------------------------------------------------
XnListT<HandTracker*>	HandTracker::sm_Instances;


//---------------------------------------------------------------------------
// Hooks
//---------------------------------------------------------------------------
void XN_CALLBACK_TYPE HandTracker::Gesture_Recognized(	xn::GestureGenerator&	/*generator*/, 
														const XnChar*			strGesture, 
														const XnPoint3D*		/*pIDPosition*/, 
														const XnPoint3D*		pEndPosition, 
														void*					pCookie)
{
	printf("Gesture recognized: %s\n", strGesture);

	HandTracker*	pThis = static_cast<HandTracker*>(pCookie);
	if(sm_Instances.Find(pThis) == sm_Instances.End())
	{
		printf("Dead HandTracker: skipped!\n");
		return;
	}

	pThis->m_HandsGenerator.StartTracking(*pEndPosition);
}

void XN_CALLBACK_TYPE HandTracker::Hand_Create(	xn::HandsGenerator& /*generator*/, 
												XnUserID			nId, 
												const XnPoint3D*	pPosition, 
												XnFloat				/*fTime*/, 
												void*				pCookie)
{
	printf("New Hand: %d @ (%f,%f,%f)\n", nId, pPosition->X, pPosition->Y, pPosition->Z);

	HandTracker*	pThis = static_cast<HandTracker*>(pCookie);
	if(sm_Instances.Find(pThis) == sm_Instances.End())
	{
		printf("Dead HandTracker: skipped!\n");
		return;
	}

	pThis->m_History[nId].Push(*pPosition);
}

void XN_CALLBACK_TYPE HandTracker::Hand_Update(	xn::HandsGenerator& /*generator*/, 
												XnUserID			nId, 
												const XnPoint3D*	pPosition, 
												XnFloat				fTime, 
												void*				pCookie)
{
	HandTracker*	pThis = static_cast<HandTracker*>(pCookie);
	if(sm_Instances.Find(pThis) == sm_Instances.End())
	{
		printf("Dead HandTracker: skipped!\n");
		return;
	}

	// Add to this user's hands history
	TrailHistory::Iterator it = pThis->m_History.Find(nId);
	if (it == pThis->m_History.End())
	{
		printf("Dead hand update: skipped!\n");
		return;
	}
	printf("%d: (%f,%f,%f) [%f]\n", nId, pPosition->X, pPosition->Y, pPosition->Z, fTime);
	it->Value().Push(*pPosition);
}

void XN_CALLBACK_TYPE HandTracker::Hand_Destroy(	xn::HandsGenerator& /*generator*/, 
													XnUserID			nId, 
													XnFloat				/*fTime*/, 
													void*				pCookie)
{
	printf("Lost Hand: %d\n", nId);

	HandTracker*	pThis = static_cast<HandTracker*>(pCookie);
	if(sm_Instances.Find(pThis) == sm_Instances.End())
	{
		printf("Dead HandTracker: skipped!\n");
		return;
	}

	// Remove this user from hands history
	pThis->m_History.Remove(nId);
}


//---------------------------------------------------------------------------
// Method Definitions
//---------------------------------------------------------------------------
HandTracker::HandTracker() 
{
	// Track all living instances (to protect against calling dead pointers in the Gesture/Hand Generator hooks)
    XnStatus rc = m_rContext.InitFromXmlFile("Sample-Tracking.xml", m_scriptNode);
	if (rc != XN_STATUS_OK)
	{
		printf("Couldn't initialize: %s\n", xnGetStatusString(rc));
		exit(1);
	}
	rc = sm_Instances.AddLast(this);
	if (rc != XN_STATUS_OK)
	{
		printf("Unable to add NiHandTracker instance to the list.");
		exit(1);
    }
    m_imagecamera = NULL;
}

HandTracker::~HandTracker()
{
	// Remove the current instance from living instances list
	XnListT<HandTracker*>::ConstIterator it = sm_Instances.Find(this);
	assert(it != sm_Instances.End());
	sm_Instances.Remove(it);
    if(m_imagecamera)
        delete m_imagecamera;
}

XnStatus HandTracker::Init()
{            
	XnStatus			rc;
	XnCallbackHandle	chandle;

	// Create generators
	rc = m_GestureGenerator.Create(m_rContext);
	if (rc != XN_STATUS_OK)
	{
		printf("Unable to create GestureGenerator.");
		return rc;
	}

	rc = m_HandsGenerator.Create(m_rContext);
	if (rc != XN_STATUS_OK)
	{
		printf("Unable to create HandsGenerator.");
		return rc;
	}

	// Register callbacks
	// Using this as cookie
	rc = m_GestureGenerator.RegisterGestureCallbacks(Gesture_Recognized, Gesture_Process, this, chandle);
	if (rc != XN_STATUS_OK)
	{
		printf("Unable to register gesture callbacks.");
		return rc;
	}

    rc = m_HandsGenerator.RegisterHandCallbacks(Hand_Create, Hand_Update, Hand_Destroy, this, chandle);
    if (rc != XN_STATUS_OK)
    {
        printf("Unable to register hand callbacks.");
        return rc;
    }

    rc = m_ImageGenerator.Create(m_rContext);
    if (rc != XN_STATUS_OK)
    {
        printf("Unable to create ImageGenerator.");
        return rc;
    }

    return XN_STATUS_OK;
}

XnStatus HandTracker::Run()
{
	//ADD_ALL_GESTURES;

	XnStatus	rc = m_rContext.StartGeneratingAll();
	if (rc != XN_STATUS_OK)
	{
		printf("Unable to start generating.");
		return rc;
	}

	ADD_ALL_GESTURES;

    m_ImageGenerator.GetMetaData(m_IimageMD);

    m_imagecamera = new QImage(m_IimageMD.FullXRes(),m_IimageMD.FullYRes(),QImage::Format_RGB888);


	return XN_STATUS_OK;
}

XnStatus HandTracker::Update()
{
	XnStatus rc = m_rContext.WaitAnyUpdateAll();
	if (rc != XN_STATUS_OK)
	{
		printf("Read failed: %s\n", xnGetStatusString(rc));
		return rc;
	}
    m_ImageGenerator.GetMetaData(m_IimageMD);
    // draw image frame to texture
    const XnRGB24Pixel* pImageRow = m_IimageMD.RGB24Data();
    QRgb value;
    for (XnUInt y = 0; y < m_IimageMD.YRes(); ++y)
    {
            const XnRGB24Pixel* pImage = pImageRow;
            for (XnUInt x = 0; x < m_IimageMD.XRes(); ++x, ++pImage)
            {
                    value = qRgb(pImage->nRed, pImage->nGreen, pImage->nBlue);
                    m_imagecamera->setPixel(x, y, value);
            }
            pImageRow += m_IimageMD.XRes();
    }
	return rc;
}

QImage HandTracker::getCamera()
{
    return *m_imagecamera;
}
