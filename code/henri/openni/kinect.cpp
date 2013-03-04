#include "kinect.h"

#include <cassert>

using namespace xn;
using namespace cv;


//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define LENGTHOF(arr)			(sizeof(arr)/sizeof(arr[0]))
#define FOR_ALL(arr, action)	{for(unsigned int i = 0; i < LENGTHOF(arr); ++i){action(arr[i])}}

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
XnListT<Kinect*>	Kinect::sm_Instances;


//---------------------------------------------------------------------------
// Hooks
//---------------------------------------------------------------------------
void Kinect::Gesture_Recognized(  xn::GestureGenerator&	/*generator*/,
                                       const XnChar*			strGesture,
                                       const XnPoint3D*		/*pIDPosition*/,
                                       const XnPoint3D*		pEndPosition,
                                       void*					pCookie)
{
    printf("Gesture recognized: %s\n", strGesture);

    Kinect*	pThis = static_cast<Kinect*>(pCookie);
    if(sm_Instances.Find(pThis) == sm_Instances.End())
    {
        printf("Dead Kinect: skipped!\n");
        return;
    }

    pThis->m_HandsGenerator.StartTracking(*pEndPosition);
}

void Kinect::Hand_Create(	xn::HandsGenerator& /*generator*/,
                                XnUserID			nId,
                                const XnPoint3D*	pPosition,
                                XnFloat				/*fTime*/,
                                void*				pCookie)
{
    printf("New Hand: %d @ (%f,%f,%f)\n", nId, pPosition->X, pPosition->Y, pPosition->Z);

    Kinect*	pThis = static_cast<Kinect*>(pCookie);
    if(sm_Instances.Find(pThis) == sm_Instances.End())
    {
        printf("Dead Kinect: skipped!\n");
        return;
    }
    Hand h;
    h.pos = *pPosition;
    pThis->m_History[nId] = h;
    pThis->calibrateOn(nId);
}

void Kinect::Hand_Update(	xn::HandsGenerator& /*generator*/,
                                XnUserID			nId,
                                const XnPoint3D*	pPosition,
                                XnFloat				/*fTime*/,
                                void*				pCookie)
{
    Kinect*	pThis = static_cast<Kinect*>(pCookie);
    if(sm_Instances.Find(pThis) == sm_Instances.End())
    {
        printf("Dead Kinect: skipped!\n");
        return;
    }

    // Add to this user's hands history
    HandHistory::Iterator it = pThis->m_History.Find(nId);
    if (it == pThis->m_History.End())
    {
        printf("Dead hand update: skipped!\n");
        return;
    }
    it->Value().pos = *pPosition;
    pThis->areaOf(nId);
    //pThis->calibrateOn(nId);
    //printf("%d: (%f,%f,%f) [%f]\n", nId, pPosition->X, pPosition->Y, pPosition->Z, fTime);
}

void Kinect::Hand_Destroy(	xn::HandsGenerator& /*generator*/,
                                XnUserID			nId,
                                XnFloat				/*fTime*/,
                                void*				pCookie)
{
    printf("Lost Hand: %d\n", nId);

    Kinect*	pThis = static_cast<Kinect*>(pCookie);
    if(sm_Instances.Find(pThis) == sm_Instances.End())
    {
        printf("Dead Kinect: skipped!\n");
        return;
    }

    // Remove this user from hands history
    pThis->m_History.Remove(nId);
}


//---------------------------------------------------------------------------
// Method Definitions
//---------------------------------------------------------------------------
Kinect::Kinect(HandDescriptor &_left, HandDescriptor &_right) :
    h_left(_left),
    h_right(_right)
{
   // Track all living instances (to protect against calling dead pointers in the Gesture/Hand Generator hooks)
    XnStatus rc = sm_Instances.AddLast(this);
    if (rc != XN_STATUS_OK)
    {
        printf("Unable to add NiKinect instance to the list.\n");
        exit(1);
    }
    m_imagecamera = NULL;
    m_imagedepth = NULL;

    m_treshold = 80;
}

Kinect::~Kinect()
{
    // Remove the current instance from living instances list
    XnListT<Kinect*>::ConstIterator it = sm_Instances.Find(this);
    assert(it != sm_Instances.End());
    sm_Instances.Remove(it);
    if(m_imagecamera)
        delete m_imagecamera;
    if(m_imagedepth)
        delete m_imagedepth;
}

XnStatus Kinect::Init()
{
    xn::ScriptNode scriptNode;
    XnStatus rc = m_rContext.InitFromXmlFile("Sample-Tracking.xml", scriptNode);
    if (rc != XN_STATUS_OK)
    {
        printf("Couldn't initialize: %s\n", xnGetStatusString(rc));
        return rc;
    }

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

    rc = m_DepthGenerator.Create(m_rContext);
    if (rc != XN_STATUS_OK)
    {
        printf("Unable to create ImageGenerator.");
        return rc;
    }

    rc = m_ImageGenerator.Create(m_rContext);
    if (rc != XN_STATUS_OK)
    {
        printf("Unable to create ImageGenerator.");
        return rc;
    }

    // Register callbacks
    // Using this as cookie
    XnCallbackHandle	chandle;
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

    return XN_STATUS_OK;
}

XnStatus Kinect::Run()
{
    //ADD_ALL_GESTURES;

    XnStatus	rc = m_rContext.StartGeneratingAll();
    if (rc != XN_STATUS_OK)
    {
        printf("Unable to start generating.");
        return rc;
    }

    ADD_ALL_GESTURES;

    m_DepthGenerator.GetMetaData(m_DepthMD);

    m_imagecamera = new QImage(1280,480,QImage::Format_RGB888);

    return XN_STATUS_OK;
}

XnStatus Kinect::Update()
{
    m_imagecamera->fill(Qt::black);
    XnStatus rc = m_rContext.WaitAnyUpdateAll();
    if (rc != XN_STATUS_OK)
    {
        printf("Read failed: %s\n", xnGetStatusString(rc));
        return rc;
    }
    m_ImageGenerator.GetMetaData(m_ImageMD);
    // draw image frame to texture
    const XnRGB24Pixel* pImageRow = m_ImageMD.RGB24Data();
    QRgb value;
    for (XnUInt y = 0; y < m_ImageMD.YRes(); ++y)
    {
        const XnRGB24Pixel* pImage = pImageRow;
        for (XnUInt x = 0; x < m_ImageMD.XRes(); ++x, ++pImage)
        {
            value = qRgb(pImage->nRed, pImage->nGreen, pImage->nBlue);
            m_imagecamera->setPixel(x, y, value);
        }
        pImageRow += m_ImageMD.XRes();
    }
    //Set left/right hands
    int i = 0;
    for(HandHistory::Iterator it = m_History.Begin(); it != m_History.End() && i < 2; ++it, ++i)
    {
        XnPoint3D	point = it->Value().pos;
        m_DepthGenerator.ConvertRealWorldToProjective(1, &point, &point);
        point.X = 640 - point.X;
        if(i==0)
            h_left.updatePos(point.X, point.Y, false);
        if(i==1)
            h_right.updatePos(point.X, point.Y, false);

    }
    //Display Hand positions
    for(HandHistory::Iterator it = m_History.Begin(); it != m_History.End() ; ++it)
    {
        XnPoint3D	point = it->Value().pos;
        m_DepthGenerator.ConvertRealWorldToProjective(1, &point, &point);
        point.X = 640 - point.X;
        point.Y += 20;
        value = qRgb(255,255,255);
        if(it->Value().area / it->Value().calibration < TRESHOLD)
            value = qRgb(0,255,255);
        for (XnUInt y = 0; y < 5; ++y)
        {
                for (XnUInt x = 0; x < 5; ++x)
                {
                        m_imagecamera->setPixel(x+point.X, y+point.Y, value);
                }
        }
    }
    return rc;
}

void Kinect::areaOf(XnUserID nId)
{
    HandHistory::Iterator it = this->m_History.Find(nId);
    if (it == this->m_History.End())
    {
        printf("Dead hand area: skipped!\n");
        return;
    }
    XnPoint3D   handPos = it->Value().pos;
    Mat depthRaw(YRES, XRES, CV_16UC1);
    Mat depthShow(YRES, XRES, CV_8UC1);

    /* Definition de la région d'intérêt */
    Rect dim(Point(0,0),Size(XRES,YRES));
    Rect roi;

    rectangle[0].X  =   handPos.X-ROI_OFFSET+it->Value().offset;
    rectangle[0].Y  =   handPos.Y-ROI_OFFSET+it->Value().offset;
    rectangle[0].Z  =   handPos.Z;
    rectangle[1].X  =   handPos.X+ROI_OFFSET-it->Value().offset;
    rectangle[1].Y  =   handPos.Y+ROI_OFFSET-it->Value().offset;
    rectangle[1].Z  =   handPos.Z;
    rectangle[2]    =   handPos;

    m_DepthGenerator.ConvertRealWorldToProjective(3, rectangle, rectangle);

    roi=Rect(Point(rectangle[0].X,rectangle[0].Y),Point(rectangle[1].X,rectangle[1].Y));
    roi &= dim;

    /* Calcul de l'image binaire de la main */
    memcpy(depthRaw.data, m_DepthGenerator.GetDepthMap(), XRES*YRES*2);
    const float DEPTH_SCALE_FACTOR = 255./4096.;
    depthRaw.convertTo(depthShow, CV_8U, DEPTH_SCALE_FACTOR);

    Mat handCpy(depthShow, roi);
    Mat handMat = handCpy.clone();
    //Treshold
    handMat = (handMat > (handPos.Z * DEPTH_SCALE_FACTOR - 5)) & (handMat < (handPos.Z * DEPTH_SCALE_FACTOR + 5));
    //Filtre median pour supprimer les inpuretés
    medianBlur(handMat, handMat, 5);

    /* Calcul de la surface */
    int count = countNonZero(handMat);

    const float smallconst = 1E-9;
    const float r = (count*smallconst)*(handPos.Z*handPos.Z)/it->Value().calibration;
    printf("c\t%f\n",r);

    //Dessin
    QRgb value;
    const XnDepthPixel* depthMap = m_DepthGenerator.GetDepthMap();
    for (int y = 0; y < YRES; ++y)
    {
        const XnDepthPixel* pImage = depthMap;
        for (int x = 0; x < XRES; ++x, ++pImage)
        {
            if(((y >= roi.y && y < roi.y+roi.height) && (x == roi.x || x == roi.x+roi.width-1)) || ((y == roi.y || y == roi.y+roi.height-1) && (x >= roi.x && x < roi.x+roi.width)))
                value = qRgb(255,0,0);
            else if(abs(*pImage - handPos.Z) < m_treshold)
                value = qRgb(255,255,255);
            else
                value = m_imagecamera->pixel(1279-x, y);
            m_imagecamera->setPixel(1279-x, y, value);
        }
        depthMap += XRES;
    }
    //Display Hand positions
    for(int i = 0 ; i < 3 ; ++i)
    {
        XnPoint3D	point = rectangle[i];
        //point.X = 640 - point.X;
        value = 255 << (i*8);
        if(r < TRESHOLD)
            value ^= -1;
        for (int y = 0; y < 5; ++y)
        {
                for (int x = 0; x < 5; ++x)
                {
                        m_imagecamera->setPixel(1279-(x+point.X), y+point.Y, value);
                }
        }
    }
    it->Value().area = (count*smallconst)*(handPos.Z*handPos.Z);
    return;

}

void Kinect::calibrateOn(XnUserID nId)
{
    HandHistory::Iterator it = this->m_History.Find(nId);
    if (it == this->m_History.End())
    {
        printf("Dead hand calibration: skipped!\n");
        return;
    }
    XnPoint3D   handPos = it->Value().pos;

    Mat depthRaw(YRES, XRES, CV_16UC1);
    Mat depthShow(YRES, XRES, CV_8UC1);

    /* Definition de la région d'intérêt */
    Rect dim(Point(0,0),Size(XRES,YRES));
    Rect roi;

    rectangle[0].X  =   handPos.X-ROI_OFFSET;
    rectangle[0].Y  =   handPos.Y-ROI_OFFSET;
    rectangle[0].Z  =   handPos.Z;
    rectangle[1].X  =   handPos.X+ROI_OFFSET;
    rectangle[1].Y  =   handPos.Y+ROI_OFFSET;
    rectangle[1].Z  =   handPos.Z;
    rectangle[2]    =   handPos;

    m_DepthGenerator.ConvertRealWorldToProjective(3, rectangle, rectangle);

    roi=Rect(Point(rectangle[0].X,rectangle[0].Y),Point(rectangle[1].X,rectangle[1].Y));
    roi &= dim;

    /* Calcul de l'image binaire de la main */
    memcpy(depthRaw.data, m_DepthGenerator.GetDepthMap(), XRES*YRES*2);
    const float DEPTH_SCALE_FACTOR = 255./4096.;
    depthRaw.convertTo(depthShow, CV_8U, DEPTH_SCALE_FACTOR);

    Mat handCpy(depthShow, roi);
    Mat handMat = handCpy.clone();
    //Treshold
    handMat = (handMat > (handPos.Z * DEPTH_SCALE_FACTOR - 5)) & (handMat < (handPos.Z * DEPTH_SCALE_FACTOR + 5));
    //Filtre median pour supprimer les inpuretés
    medianBlur(handMat, handMat, 5);

    /* Calcul de la surface */
    //Ajustement du ROI
    int k;
    for(k = 0; k < handMat.rows && countNonZero(handMat.row(k)) == 0 ; ++k);
    //printf("%i\n",k)
    assert(k < roi.width/2);
    it->Value().offset = k*2*ROI_OFFSET/roi.width;

    Rect roi2=Rect(Point(k, k), Point(roi.width-k, roi.height-k));
    Mat handMat2 = handMat(roi2);

    int count = countNonZero(handMat2);
    const float smallconst = 1E-9;
    printf("calibration of %i=%f\n", nId, (count*smallconst)*(handPos.Z*handPos.Z));
    it->Value().calibration = (count*smallconst)*(handPos.Z*handPos.Z);
    //Dessin
    roi.x += k; roi.y += k;
    roi.width -= k; roi.height -= k;
    QRgb value;
    const XnDepthPixel* depthMap = m_DepthGenerator.GetDepthMap();
    for (int y = 0; y < YRES; ++y)
    {
        const XnDepthPixel* pImage = depthMap;
        for (int x = 0; x < XRES; ++x, ++pImage)
        {
            if(((y >= roi.y && y < roi.y+roi.height) && (x == roi.x || x == roi.x+roi.width-1)) || ((y == roi.y || y == roi.y+roi.height-1) && (x >= roi.x && x < roi.x+roi.width)))
                value = qRgb(255,0,0);
            else if(abs(*pImage - handPos.Z) < m_treshold)
                value = qRgb(255,255,255);
            else
                value = qRgb(0,0,0);
            m_imagecamera->setPixel(1279-x, y, value);
        }
        depthMap += XRES;
    }

    //Display Hand positions
    for(int i = 0 ; i < 3 ; ++i)
    {
        XnPoint3D	point = rectangle[i];
        //point.X = 640 - point.X;
        value = 255 << (i*8);

        for (int y = 0; y < 5; ++y)
        {
                for (int x = 0; x < 5; ++x)
                {
                        m_imagecamera->setPixel(1279-(x+point.X), y+point.Y, value);
                }
        }
    }
}

QImage Kinect::getCamera()
{
    return m_imagecamera->mirrored(true, false);
}
