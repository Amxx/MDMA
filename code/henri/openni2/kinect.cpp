#include "kinect.h"

#include <cassert>

#define MAX_DEPTH 10000

const bool m_showdepth = true;

//---------------------------------------------------------------------------
// Method Definitions
//---------------------------------------------------------------------------
Kinect::Kinect(HandDescriptor &_left, HandDescriptor &_right) :
    h_left(_left),
    h_right(_right)
{
    m_imagecamera = NULL;
    m_imagedepth = NULL;
    m_HandTracker = NULL;
}

Kinect::~Kinect()
{
    if(m_imagecamera)
        delete m_imagecamera;
    if(m_imagedepth)
        delete m_imagedepth;
    if(m_HandTracker)
        delete m_HandTracker;
    nite::NiTE::shutdown();
    m_colorStream.stop();
    m_colorStream.destroy();
    m_device.close();
    openni::OpenNI::shutdown();
}

openni::Status Kinect::Init()
{
    openni::OpenNI::initialize();
    puts("Open device");
    openni::Status rc = m_device.open(openni::ANY_DEVICE);
	if (rc != openni::STATUS_OK)
	{
		printf("Open Device failed:\n%s\n", openni::OpenNI::getExtendedError());
		return rc;
    }
    openni::ImageRegistrationMode irm = m_device.getImageRegistrationMode();
    printf("Registration Mode: %i\n",irm);
    if(irm == openni::IMAGE_REGISTRATION_OFF && m_device.isImageRegistrationModeSupported(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR))
    {
        puts("Set Registration on");
        m_device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);
    }
    puts("Get color stream");
    rc = m_colorStream.create(m_device, openni::SENSOR_COLOR);
	if (rc == openni::STATUS_OK)
	{
		rc = m_colorStream.start();
		if (rc != openni::STATUS_OK)
		{
            printf("\tCouldn't start color stream:\n%s\n", openni::OpenNI::getExtendedError());
			m_colorStream.destroy();
		}
	}
	else
	{
        printf("\tCouldn't find color stream:\n%s\n", openni::OpenNI::getExtendedError());
	}

    if (!m_colorStream.isValid())
	{
        printf("\tNo valid streams. Exiting\n");
		openni::OpenNI::shutdown();
        return openni::STATUS_ERROR;
	}
    openni::VideoMode colorVideoMode;

    colorVideoMode = m_colorStream.getVideoMode();

    m_width = colorVideoMode.getResolutionX();
    m_height = colorVideoMode.getResolutionY();

    puts("NiTE init");
    nite::NiTE::initialize();
    m_HandTracker = new nite::HandTracker;
    puts("NiTE track create");
    if (m_HandTracker->create(&m_device) != nite::STATUS_OK)
    {
        return openni::STATUS_ERROR;
	}
    puts("NiTE start gesture");
	m_HandTracker->startGestureDetection(nite::GESTURE_WAVE);
	m_HandTracker->startGestureDetection(nite::GESTURE_CLICK);

    return openni::STATUS_OK;
}

openni::Status Kinect::Run()
{
    m_imagecamera = new QImage(m_width,m_height,QImage::Format_RGB888);
    m_imagedepth = new QImage(m_width,m_height,QImage::Format_RGB888);

    return openni::STATUS_OK;
}

openni::Status Kinect::Update()
{
    nite::HandTrackerFrameRef handFrame;
	nite::Status rc = m_HandTracker->readFrame(&handFrame);
	if (rc != nite::STATUS_OK)
	{
		printf("GetNextData failed\n");
        return openni::STATUS_ERROR;
	}

    m_depthFrame = handFrame.getDepthFrame();

    m_colorStream.readFrame(&m_colorFrame);
    *m_imagecamera = QImage((const uchar*)m_colorFrame.getData(), m_width, m_height, QImage::Format_RGB888);

    const nite::Array<nite::GestureData>& gestures = handFrame.getGestures();
	for (int i = 0; i < gestures.getSize(); ++i)
	{
        if (gestures[i].isComplete())
		{
			const nite::Point3f& position = gestures[i].getCurrentPosition();
            printf("Gesture %d at (%f,%f,%f)\n", gestures[i].getType(), position.x, position.y, position.z);

			nite::HandId newId;
            m_HandTracker->startHandTracking(gestures[i].getCurrentPosition(), &newId);
		}
	}

	const nite::Array<nite::HandData>& hands= handFrame.getHands();
	for (int i = 0; i < hands.getSize(); ++i)
	{
		const nite::HandData& user = hands[i];

		if (!user.isTracking())
		{
			printf("Lost hand %d\n", user.getId());
			nite::HandId id = user.getId();
			m_history.erase(m_history.find(id));
		}
		else
		{
            if (user.isNew())
			{
				printf("Found hand %d\n", user.getId());
                Hand h;
                h.pos = user.getPosition();
                m_history[user.getId()] = h;
                this->calibrateOn(user.getId());
                puts("Done");
			}
            m_history[user.getId()].pos = user.getPosition();
            this->areaOf(user.getId());
		}
	}
	
	
    //Set left/right hands
    int i = 0;
    for(HandHistory::iterator it = m_history.begin(); it != m_history.end() && i < 2; ++it, ++i)
    {
        nite::Point3f	point = it->second.pos;
        m_HandTracker->convertHandCoordinatesToDepth(point.x,point.y,point.z,&(point.x),&(point.y));
        point.x = 640 - point.x;
        if(i==0)
            h_left.updatePos(point.x, point.y, false);
        if(i==1)
            h_right.updatePos(point.x, point.y, false);

    }
    //Display Hand positions
    for(HandHistory::iterator it = m_history.begin(); it != m_history.end() ; ++it)
    {
        nite::Point3f	point = it->second.pos;
        m_HandTracker->convertHandCoordinatesToDepth(point.x,point.y,point.z,&(point.x),&(point.y));
        point.x = 640 - point.x;
        point.y += 20;
        QRgb value = qRgb(255,255,255);
        if(it->second.area / it->second.calibration < THRESHOLD)
            value = qRgb(0,255,255);
        for (int y = 0; y < 5; ++y)
        {
                for (int x = 0; x < 5; ++x)
                {
                        m_imagecamera->setPixel(x+point.x, y+point.y, value);
                }
        }
    }
    return openni::STATUS_OK;
}

void Kinect::areaOf(nite::HandId nId)
{
    HandHistory::iterator it = this->m_history.find(nId);
    if (it == this->m_history.end())
    {
        printf("Dead hand area: skipped!\n");
        return;
    }
    nite::Point3f   handPos = it->second.pos;

    const int XRES =    m_width;
    const int YRES =    m_height;

    cv::Mat depthRaw(YRES, XRES, CV_16UC1);
    cv::Mat depthShow(YRES, XRES, CV_8UC1);

    /* Definition de la région d'intérêt */
    nite::Point3f rectangle[3];
    rectangle[0].x  =   handPos.x-ROI_OFFSET+it->second.offset;
    rectangle[0].y  =   handPos.y-ROI_OFFSET+it->second.offset;
    rectangle[0].z  =   handPos.z;
    rectangle[1].x  =   handPos.x+ROI_OFFSET-it->second.offset;
    rectangle[1].y  =   handPos.y+ROI_OFFSET-it->second.offset;
    rectangle[1].z  =   handPos.z;
    rectangle[2]    =   handPos;

    for(int i = 0 ; i < 3 ; ++i)
        m_HandTracker->convertHandCoordinatesToDepth(rectangle[i].x,rectangle[i].y,rectangle[i].z,&(rectangle[i].x),&(rectangle[i].y));

    cv::Rect dim(cv::Point(0,0),cv::Size(XRES,YRES));
    cv::Rect roi = cv::Rect(cv::Point(rectangle[0].x,rectangle[0].y),cv::Point(rectangle[1].x,rectangle[1].y));
    roi &= dim;

    /* Calcul de l'image binaire de la main */
    memcpy(depthRaw.data, m_depthFrame.getData(), XRES*YRES*2);
    const float DEPTH_SCALE_FACTOR = 255./4096.;
    depthRaw.convertTo(depthShow, CV_8U, DEPTH_SCALE_FACTOR);

    cv::Mat handCpy(depthShow, roi);
    cv::Mat handMat = handCpy.clone();
    //Threshold
    handMat = (handMat > (handPos.z * DEPTH_SCALE_FACTOR - 5)) & (handMat < (handPos.z * DEPTH_SCALE_FACTOR + 5));
    //Filtre median pour supprimer les inpuretés
    cv::medianBlur(handMat, handMat, 5);

    /* Calcul de la surface */
    int count = cv::countNonZero(handMat);

    const float smallconst = 1E-9;
    //printf("c\t%i\t%f\n", r<0.68,r);

    //Dessin
    QRgb value;
    const openni::DepthPixel* depthMap = (const openni::DepthPixel*)m_depthFrame.getData();
    for (int y = 0; y < YRES; ++y)
    {
        const openni::DepthPixel* pImage = depthMap;
        for (int x = 0; x < XRES; ++x, ++pImage)
        {
            if(((y >= roi.y && y < roi.y+roi.height) && (x == roi.x || x == roi.x+roi.width-1)) || ((y == roi.y || y == roi.y+roi.height-1) && (x >= roi.x && x < roi.x+roi.width)))
                value = qRgb(255,0,0);
            else if(abs(*pImage - handPos.z) * DEPTH_SCALE_FACTOR < 5 )
                value = qRgb(255,255,255);
            else
                value = 0;
            m_imagedepth->setPixel(x, y, value);
        }
        depthMap += XRES;
    }
    const float r = (count*smallconst)*(handPos.z*handPos.z)/it->second.calibration;
    //Display Hand positions
    for(int i = 0 ; i < 3 ; ++i)
    {
        nite::Point3f	point = rectangle[i];
        //point.x = 640 - point.x;
        value = 255 << (i*8);
        if(r < THRESHOLD)
            value ^= -1;
        for (int y = 0; y < 5; ++y)
        {
                for (int x = 0; x < 5; ++x)
                {
                        m_imagedepth->setPixel((x+point.x), y+point.y, value);
                }
        }
    }
    it->second.area = (count*smallconst)*(handPos.z*handPos.z);
    return;

}

void Kinect::calibrateOn(nite::HandId nId)
{
    HandHistory::iterator it = this->m_history.find(nId);
    if (it == this->m_history.end())
    {
        printf("Dead hand area: skipped!\n");
        return;
    }
    nite::Point3f   handPos = it->second.pos;

    const int XRES =    m_width;
    const int YRES =    m_height;

    cv::Mat depthRaw(YRES, XRES, CV_16UC1);
    cv::Mat depthShow(YRES, XRES, CV_8UC1);

    /* Definition de la région d'intérêt */
    nite::Point3f rectangle[3];
    rectangle[0].x  =   handPos.x-ROI_OFFSET;
    rectangle[0].y  =   handPos.y-ROI_OFFSET;
    rectangle[0].z  =   handPos.z;
    rectangle[1].x  =   handPos.x+ROI_OFFSET;
    rectangle[1].y  =   handPos.y+ROI_OFFSET;
    rectangle[1].z  =   handPos.z;
    rectangle[2]    =   handPos;

    for(int i = 0 ; i < 3 ; ++i)
        m_HandTracker->convertHandCoordinatesToDepth(rectangle[i].x,rectangle[i].y,rectangle[i].z,&(rectangle[i].x),&(rectangle[i].y));

    cv::Rect dim(cv::Point(0,0),cv::Size(XRES,YRES));
    cv::Rect roi = cv::Rect(cv::Point(rectangle[0].x,rectangle[0].y),cv::Point(rectangle[1].x,rectangle[1].y));
    roi &= dim;
    /* Calcul de l'image binaire de la main */
    memcpy(depthRaw.data, m_depthFrame.getData(), XRES*YRES*2);
    const float DEPTH_SCALE_FACTOR = 255./4096.;
    depthRaw.convertTo(depthShow, CV_8U, DEPTH_SCALE_FACTOR);

    cv::Mat handCpy(depthShow, roi);
    cv::Mat handMat = handCpy.clone();
    //Threshold
    cv::Mat inf = handMat < (handPos.z * DEPTH_SCALE_FACTOR + 5);
    cv::Mat sup = handMat > (handPos.z * DEPTH_SCALE_FACTOR - 5);
    handMat = sup & inf;
    //Filtre median pour supprimer les inpuretés
    cv::medianBlur(handMat, handMat, 5);

    /* Calcul de la surface */
    //Ajustement du ROI
    int k;
    for(k = 0; k < handMat.rows && cv::countNonZero(handMat.row(k)) == 0 ; ++k);
    //printf("%i\n",k)
    assert(k < roi.width/2);
    it->second.offset = k*2*ROI_OFFSET/roi.width;

    cv::Rect roi2=cv::Rect(cv::Point(k, k), cv::Point(roi.width-k, roi.height-k));
    cv::Mat handMat2 = handMat(roi2);

    int count = cv::countNonZero(handMat2);

    const float smallconst = 1E-9;
    printf("calibration of %i=%f\n", nId, (count*smallconst)*(handPos.z*handPos.z));
    it->second.calibration = (count*smallconst)*(handPos.z*handPos.z);
    /*//Dessin
    QRgb value;
    const openni::DepthPixel* depthMap = (const openni::DepthPixel*)m_depthFrame.getData();
    for (int y = 0; y < YRES; ++y)
    {
        const openni::DepthPixel* pImage = depthMap;
        for (int x = 0; x < XRES; ++x, ++pImage)
        {
            if(((y >= roi.y && y < roi.y+roi.height) && (x == roi.x || x == roi.x+roi.width-1)) || ((y == roi.y || y == roi.y+roi.height-1) && (x >= roi.x && x < roi.x+roi.width)))
                value = qRgb(255,0,0);
            else if(abs(*pImage - handPos.z) < m_treshold)
                value = qRgb(255,255,255);
            else
                value = qRgb(0,0,0);
            m_imagecamera->setPixel(1279-x, y, value);
        }
        depthMap += XRES;
    }
    const float r = (count*smallconst)*(handPos.z*handPos.z)/it->second.calibration;
    //Display Hand positions
    for(int i = 0 ; i < 3 ; ++i)
    {
        nite::Point3f	point = rectangle[i];
        //point.x = 640 - point.x;
        value = 255 << (i*8);
        if(r < TRESHOLD)
            value ^= -1;
        for (int y = 0; y < 5; ++y)
        {
                for (int x = 0; x < 5; ++x)
                {
                        m_imagecamera->setPixel(1279-(x+point.x), y+point.y, value);
                }
        }
    }*/
}

QImage Kinect::getCamera()
{
    if(!m_showdepth)
        return m_imagecamera->mirrored(true, false);
    return m_imagedepth->mirrored(true, false);
}
