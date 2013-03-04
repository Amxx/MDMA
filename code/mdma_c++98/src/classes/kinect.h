#ifndef KINECT_H
#define KINECT_H

#include <QImage>

#include <XnCppWrapper.h>
#include <XnHashT.h>

#include <opencv2/opencv.hpp>

#include "handdescriptor.h"

#define XRES        640
#define YRES        480
#define ROI_OFFSET  100

#define THRESHOLD    0.72

class Kinect
{
public:
    Kinect(HandDescriptor &_left, HandDescriptor &_right);
    ~Kinect();

    XnStatus Init();
    XnStatus Run();
    XnStatus Update();

    QImage getCamera();

    HandDescriptor& h_left;
    HandDescriptor& h_right;

    //const TrailHistory&	GetHistory()	const	{return m_History;}

private:
    typedef struct {
        XnPoint3D pos;
        float area;
        float calibration;
        float offset;
    } Hand;

    typedef XnHashT<XnUserID, Hand> HandHistory;

    // OpenNI Gesture and Hands Generator callbacks
    static void Gesture_Recognized(xn::GestureGenerator&	generator,
                                const XnChar*			strGesture,
                                const XnPoint3D*		pIDPosition,
                                const XnPoint3D*		pEndPosition,
                                void*					pCookie);
    static void Gesture_Process(xn::GestureGenerator&	/*generator*/,
                                const XnChar*			/*strGesture*/,
                                const XnPoint3D*		/*pPosition*/,
                                XnFloat					/*fProgress*/,
                                void*					/*pCookie*/)	{}
    static void Hand_Create(	xn::HandsGenerator& generator,
                                XnUserID			nId,
                                const XnPoint3D*	pPosition,
                                XnFloat				fTime,
                                void*				pCookie);
    static void Hand_Update(    xn::HandsGenerator& generator,
                                XnUserID			nId,
                                const XnPoint3D*	pPosition,
                                XnFloat             fTime,
                                void*				pCookie);
    static void Hand_Destroy(	xn::HandsGenerator& generator,
                                XnUserID			nId,
                                XnFloat				fTime,
                                void*				pCookie);

    void calibrateOn(XnUserID	nId);
    void areaOf(XnUserID		nId);

    xn::Context				m_rContext;
    HandHistory             m_History;
    xn::GestureGenerator	m_GestureGenerator;
    xn::HandsGenerator		m_HandsGenerator;
    xn::ImageGenerator      m_ImageGenerator;
    xn::DepthGenerator      m_DepthGenerator;
    xn::ImageMetaData       m_ImageMD;
    xn::DepthMetaData       m_DepthMD;

    QImage*                 m_imagecamera;
    QImage*                 m_imagedepth;

    static XnListT<Kinect*>	sm_Instances;	// Living instances of the class

private:
    Kinect(const Kinect&);
    void operator=(const Kinect&);
};

#endif // KINECT_H
