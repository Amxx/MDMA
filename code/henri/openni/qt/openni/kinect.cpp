#include "kinect.h"

#include <cassert>

using namespace xn;


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

    pThis->calibrateOn(*pPosition);

    pThis->m_History[nId] = *pPosition;
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
    TrailHistory::Iterator it = pThis->m_History.Find(nId);
    if (it == pThis->m_History.End())
    {
        printf("Dead hand update: skipped!\n");
        return;
    }
    pThis->calibrateOn(*pPosition);
    it->Value() = *pPosition;
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

    m_treshold = 30;
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

    m_imagecamera = new QImage(m_DepthMD.FullXRes(),m_DepthMD.FullYRes(),QImage::Format_RGB888);

    return XN_STATUS_OK;
}

XnStatus Kinect::Update()
{
    XnStatus rc = m_rContext.WaitAnyUpdateAll();
    if (rc != XN_STATUS_OK)
    {
        printf("Read failed: %s\n", xnGetStatusString(rc));
        return rc;
    }
    /*m_ImageGenerator.GetMetaData(m_ImageMD);
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
    for(TrailHistory::Iterator it = m_History.Begin(); it != m_History.End() && i < 2; ++it, ++i)
    {
        XnPoint3D	point = it->Value();
        m_DepthGenerator.ConvertRealWorldToProjective(1, &point, &point);
        point.X *= 640; point.Y *= 480;
        point.X /= m_ImageMD.XRes(); point.Y /= m_ImageMD.YRes();
        point.X = 640 - point.X;
        if(i==0)
            h_left.updatePos(point.X, point.Y, false);
        if(i==1)
            h_right.updatePos(point.X, point.Y, false);

    }
    //Display Hand positions
    for(TrailHistory::Iterator it = m_History.Begin(); it != m_History.End() ; ++it)
    {
        XnPoint3D	point = it->Value();
        m_DepthGenerator.ConvertRealWorldToProjective(1, &point, &point);
        point.X *= 640; point.Y *= 480;
        point.X /= m_ImageMD.XRes(); point.Y /= m_ImageMD.YRes();
        point.X = 640 - point.X;
        value = qRgb(255,255,255);

        for (XnUInt y = 0; y < 5; ++y)
        {
                for (XnUInt x = 0; x < 5; ++x)
                {
                        m_imagecamera->setPixel(x+point.X, y+point.Y, value);
                }
        }
    }*/
    return rc;
}

void Kinect::calibrateOn(XnPoint3D  handPos)
{
    const XnFloat dimx = 300;
    const XnFloat dimy = 300;

    rectangle[0].X  =   handPos.X-dimx/2;
    rectangle[0].Y  =   handPos.Y-dimy/2;
    rectangle[0].Z  =   handPos.Z;
    rectangle[1].X  =   handPos.X+dimx/2;
    rectangle[1].Y  =   handPos.Y+dimy/2;
    rectangle[1].Z  =   handPos.Z;
    rectangle[2]    =   handPos;

    m_DepthGenerator.ConvertRealWorldToProjective(3, rectangle, rectangle);
    m_DepthGenerator.GetMetaData(m_DepthMD);

    for(int i = 0 ; i < 3 ; ++i)
    {
        rectangle[i].X *= 640 / m_DepthMD.XRes();
        rectangle[i].Y *= 480 / m_DepthMD.YRes();
    }

    const XnUInt xmin   = std::min(rectangle[0].X,rectangle[1].X);
    const XnUInt ymin   = std::min(rectangle[0].Y,rectangle[1].Y);
    const XnUInt xmax   = std::max(rectangle[0].X,rectangle[1].X);
    const XnUInt ymax   = std::max(rectangle[0].Y,rectangle[1].Y);

    const XnDepthPixel* depthMap = m_DepthGenerator.GetDepthMap();
    depthMap += m_DepthMD.XRes() * ymin;

    int count = 0;
    for (XnUInt y = ymin; y < ymax; ++y)
    {
        const XnDepthPixel* pImage = depthMap;
        pImage += xmin;
        for (XnUInt x = xmin; x < xmax; ++x, ++pImage)
        {
            if(abs(*pImage - handPos.Z) < m_treshold)
                count++;
        }
        depthMap += m_DepthMD.XRes();
    }
    const float smallconst = 1E-9;
    printf("c=%f\n", (count*smallconst)*(handPos.Z*handPos.Z));

    //Dessin
    QRgb value;
    depthMap = m_DepthGenerator.GetDepthMap();
    for (XnUInt y = 0; y < m_DepthMD.YRes(); ++y)
    {
        const XnDepthPixel* pImage = depthMap;
        for (XnUInt x = 0; x < m_DepthMD.XRes(); ++x, ++pImage)
        {
            if(((y >= ymin && y < ymax) && (x == xmin || x == xmax-1)) || ((y == ymin || y == ymax-1) && (x >= xmin && x < xmax)))
                value = qRgb(255,0,0);
            else if(abs(*pImage - handPos.Z) < m_treshold)
                value = qRgb(255,255,255);
            else
                value = qRgb(0,0,0);
            m_imagecamera->setPixel(x, y, value);
        }
        depthMap += m_DepthMD.XRes();
    }
    //Display Hand positions
    rectangle[0].X  =   handPos.X-dimx/2;
    rectangle[0].Y  =   handPos.Y-dimy/2;
    rectangle[0].Z  =   handPos.Z;
    rectangle[1].X  =   handPos.X+dimx/2;
    rectangle[1].Y  =   handPos.Y+dimy/2;
    rectangle[1].Z  =   handPos.Z;
    rectangle[2]    =   handPos;
    for(int i = 0 ; i < 3 ; ++i)
    {
        XnPoint3D	point = rectangle[i];
        m_DepthGenerator.ConvertRealWorldToProjective(1, &point, &point);
        point.X *= 640; point.Y *= 480;
        point.X /= m_DepthMD.XRes(); point.Y /= m_DepthMD.YRes();
        //point.X = 640 - point.X;
        value = 255 << (i*8);

        for (XnUInt y = 0; y < 5; ++y)
        {
                for (XnUInt x = 0; x < 5; ++x)
                {
                        m_imagecamera->setPixel(x+point.X, y+point.Y, value);
                }
        }
    }
}

QImage Kinect::getCamera()
{
    return m_imagecamera->mirrored(false, false);
}
