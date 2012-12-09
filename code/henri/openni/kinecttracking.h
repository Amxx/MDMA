#ifndef KINECT_TRACKING
#define KINECT_TRACKING

// OpenNI headers
#include <XnOpenNI.h>
// NITE headers
#include <XnVSessionManager.h>
#include <XnVWaveDetector.h>

// xml to initialize OpenNI
#define SAMPLE_XML_FILE "Sample-Tracking.xml"
#define SAMPLE_XML_FILE_LOCAL "Sample-Tracking.xml"

class KinectTracking{
public:
	KinectTracking();
	~KinectTracking();
	
	int init();
	int wait();
	
private:
	xn::Context context;
	xn::ScriptNode scriptNode;
	XnVSessionGenerator* pSessionGenerator;
	XnVWaveDetector wc;
	
	XnBool fileExists(const char *fn);
};

#endif //KINECT_TRACKING
