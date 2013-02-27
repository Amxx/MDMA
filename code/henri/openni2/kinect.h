#ifndef KINECT_H
#define KINECT_H

#include <QImage>

#include <NiTE.h>

#include <opencv2/opencv.hpp>

#include "handdescriptor.h"

#define ROI_OFFSET  100

#define TRESHOLD    0.68

class Kinect
{
public:
    Kinect(HandDescriptor &_left, HandDescriptor &_right);
    ~Kinect();

    openni::Status Init();
    openni::Status Run();
    openni::Status Update();

    QImage getCamera();

    HandDescriptor& h_left;
    HandDescriptor& h_right;

    //const TrailHistory&	GetHistory()	const	{return m_History;}

private:
    typedef struct {
        nite::Point3f pos;
        float area;
        float calibration;
    } Hand;
	
	typedef std::map<int,Hand>	HandHistory;

    void calibrateOn(nite::HandId   nId);
    void areaOf(nite::HandId		nId);
	
	openni::Device			m_device;
	openni::VideoFrameRef	m_depthFrame;
	openni::VideoFrameRef	m_colorFrame;
	
	openni::VideoStream		m_depthStream;
	openni::VideoStream		m_colorStream;

    int			m_width;
    int			m_height;
	
    nite::HandTracker* 		m_HandTracker;
	
	HandHistory				m_history;

    QImage*                 m_imagecamera;
    QImage*                 m_imagedepth;

    int                     m_treshold;
    nite::Point3f           m_rectangle[3];

private:
    Kinect(const Kinect&);
    void operator=(const Kinect&);
};

#endif // KINECT_H
