#include "kinect.h"

#include <cassert>

//---------------------------------------------------------------------------
// Method Definitions
//---------------------------------------------------------------------------
Kinect::Kinect(HandDescriptor &_left, HandDescriptor &_right) :
    h_left(_left),
    h_right(_right)
{
    m_imagecamera = NULL;
    m_imagedepth = NULL;

    m_treshold = 80;
}

Kinect::~Kinect()
{
    if(m_imagecamera)
        delete m_imagecamera;
    if(m_imagedepth)
        delete m_imagedepth;
}

openni::Status Kinect::Init()
{
    openni::OpenNI::initialize();

	openni::Status rc = m_device.open(openni::ANY_DEVICE);
	if (rc != openni::STATUS_OK)
	{
		printf("Open Device failed:\n%s\n", openni::OpenNI::getExtendedError());
		return rc;
	}
	rc = m_depthStream.create(device, openni::SENSOR_DEPTH);
	if (rc == openni::STATUS_OK)
	{
		rc = m_depthStream.start();
		if (rc != openni::STATUS_OK)
		{
			printf("SimpleViewer: Couldn't start depth stream:\n%s\n", openni::OpenNI::getExtendedError());
			m_depthStream.destroy();
		}
	}
	else
	{
		printf("SimpleViewer: Couldn't find depth stream:\n%s\n", openni::OpenNI::getExtendedError());
	}

	rc = m_colorStream.create(device, openni::SENSOR_COLOR);
	if (rc == openni::STATUS_OK)
	{
		rc = m_colorStream.start();
		if (rc != openni::STATUS_OK)
		{
			printf("SimpleViewer: Couldn't start color stream:\n%s\n", openni::OpenNI::getExtendedError());
			m_colorStream.destroy();
		}
	}
	else
	{
		printf("SimpleViewer: Couldn't find color stream:\n%s\n", openni::OpenNI::getExtendedError());
	}

	if (!m_depthStream.isValid() || !m_colorStream.isValid())
	{
		printf("SimpleViewer: No valid streams. Exiting\n");
		openni::OpenNI::shutdown();
        return openni::STATUS_ERROR;
	}
    openni::VideoMode depthVideoMode;
    openni::VideoMode colorVideoMode;

    depthVideoMode = m_depthStream.getVideoMode();
    colorVideoMode = m_colorStream.getVideoMode();

    int depthWidth = depthVideoMode.getResolutionX();
    int depthHeight = depthVideoMode.getResolutionY();
    int colorWidth = colorVideoMode.getResolutionX();
    int colorHeight = colorVideoMode.getResolutionY();

    if (depthWidth == colorWidth &&
        depthHeight == colorHeight)
    {
        m_width = depthWidth;
        m_height = depthHeight;
    }
    else
    {
        printf("Error - expect color and depth to be in same resolution: D: %dx%d, C: %dx%d\n",
            depthWidth, depthHeight,
            colorWidth, colorHeight);
        return openni::STATUS_ERROR;
    }

	nite::NiTE::initialize();

	if (m_HandTracker->create(&m_device) != nite::STATUS_OK)
	{
		return openni::STATUS_ERROR;
	}

	m_HandTracker->startGestureDetection(nite::GESTURE_WAVE);
	m_HandTracker->startGestureDetection(nite::GESTURE_CLICK);

    return openni::STATUS_OK;
}

openni::Status Kinect::Run()
{
    m_imagecamera = new QImage(m_width,m_height,QImage::Format_RGB888);

    return openni::STATUS_OK;
}

openni::Status Kinect::Update()
{
    nite::HandTrackerFrameRef handFrame;
	nite::Status rc = m_HandTracker->readFrame(&handFrame);
	if (rc != nite::STATUS_OK)
	{
		printf("GetNextData failed\n");
		return;
	}

    m_depthFrame = handFrame.getDepthFrame();

	/*if (m_pTexMap == NULL)
	{
		// Texture map init
		m_nTexMapX = MIN_CHUNKS_SIZE(depthFrame.getVideoMode().getResolutionX(), TEXTURE_SIZE);
		m_nTexMapY = MIN_CHUNKS_SIZE(depthFrame.getVideoMode().getResolutionY(), TEXTURE_SIZE);
		m_pTexMap = new openni::RGB888Pixel[m_nTexMapX * m_nTexMapY];
	}


	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, GL_WIN_SIZE_X, GL_WIN_SIZE_Y, 0, -1.0, 1.0);
	*/
    m_colorStream.readFrame(&m_colorFrame);
    m_imagecamera->loadFromData(m_colorFrame.getData(),sizeof(openni::RGB888Pixel)*m_width*m_height);
	
	/*if (depthFrame.isValid())
	{
		const openni::DepthPixel* pDepth = (const openni::DepthPixel*)depthFrame.getData();
		int width = depthFrame.getWidth();
		int height = depthFrame.getHeight();
		// Calculate the accumulative histogram (the yellow display...)
		memset(m_pDepthHist, 0, MAX_DEPTH*sizeof(float));
		int restOfRow = depthFrame.getStrideInBytes() / sizeof(openni::DepthPixel) - width;

		unsigned int nNumberOfPoints = 0;
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x, ++pDepth)
			{
				if (*pDepth != 0)
				{
					m_pDepthHist[*pDepth]++;
					nNumberOfPoints++;
				}
			}
			pDepth += restOfRow;
		}
		for (int nIndex=1; nIndex<MAX_DEPTH; nIndex++)
		{
			m_pDepthHist[nIndex] += m_pDepthHist[nIndex-1];
		}
		if (nNumberOfPoints)
		{
			for (int nIndex=1; nIndex<MAX_DEPTH; nIndex++)
			{
				m_pDepthHist[nIndex] = (unsigned int)(256 * (1.0f - (m_pDepthHist[nIndex] / nNumberOfPoints)));
			}
		}
	}

	memset(m_pTexMap, 0, m_nTexMapX*m_nTexMapY*sizeof(openni::RGB888Pixel));

	float factor[3] = {1, 1, 1};
	// check if we need to draw depth frame to texture
	if (depthFrame.isValid() && g_drawDepth)
	{
		const openni::DepthPixel* pDepthRow = (const openni::DepthPixel*)depthFrame.getData();
		openni::RGB888Pixel* pTexRow = m_pTexMap + depthFrame.getCropOriginY() * m_nTexMapX;
		int rowSize = depthFrame.getStrideInBytes() / sizeof(openni::DepthPixel);

		for (int y = 0; y < depthFrame.getHeight(); ++y)
		{
			const openni::DepthPixel* pDepth = pDepthRow;
			openni::RGB888Pixel* pTex = pTexRow + depthFrame.getCropOriginX();

			for (int x = 0; x < depthFrame.getWidth(); ++x, ++pDepth, ++pTex)
			{
				if (*pDepth != 0)
				{
					factor[0] = Colors[colorCount][0];
					factor[1] = Colors[colorCount][1];
					factor[2] = Colors[colorCount][2];

					int nHistValue = m_pDepthHist[*pDepth];
					pTex->r = nHistValue*factor[0];
					pTex->g = nHistValue*factor[1];
					pTex->b = nHistValue*factor[2];

					factor[0] = factor[1] = factor[2] = 1;
				}
			}

			pDepthRow += rowSize;
			pTexRow += m_nTexMapX;
		}
	}

	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_nTexMapX, m_nTexMapY, 0, GL_RGB, GL_UNSIGNED_BYTE, m_pTexMap);

	// Display the OpenGL texture map
	glColor4f(1,1,1,1);

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

	g_nXRes = depthFrame.getVideoMode().getResolutionX();
	g_nYRes = depthFrame.getVideoMode().getResolutionY();

	// upper left
	glTexCoord2f(0, 0);
	glVertex2f(0, 0);
	// upper right
	glTexCoord2f((float)g_nXRes/(float)m_nTexMapX, 0);
	glVertex2f(GL_WIN_SIZE_X, 0);
	// bottom right
	glTexCoord2f((float)g_nXRes/(float)m_nTexMapX, (float)g_nYRes/(float)m_nTexMapY);
	glVertex2f(GL_WIN_SIZE_X, GL_WIN_SIZE_Y);
	// bottom left
	glTexCoord2f(0, (float)g_nYRes/(float)m_nTexMapY);
	glVertex2f(0, GL_WIN_SIZE_Y);

	glEnd();
	glDisable(GL_TEXTURE_2D);
*/
	const nite::Array<nite::GestureData>& gestures = handFrame.getGestures();
	for (int i = 0; i < gestures.getSize(); ++i)
	{
		if (gestures[i].isComplete())
		{
			const nite::Point3f& position = gestures[i].getCurrentPosition();
            printf("Gesture %d at (%f,%f,%f)\n", gestures[i].getType(), position.x, position.y, position.z);

			nite::HandId newId;
			m_pHandTracker->startHandTracking(gestures[i].getCurrentPosition(), &newId);
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
			Hand h;
			if (user.isNew())
			{
				printf("Found hand %d\n", user.getId());
				h.calibration = 7;
				//Calibration
			}
			h.pos = user.getPosition();
			//h.area = ...
		}
	}
	
	
    //Set left/right hands
    /*int i = 0;
    for(HandHistory::Iterator it = m_History.Begin(); it != m_History.End() && i < 2; ++it, ++i)
    {
        XnPoint3D	point = it->Value().pos;
        m_DepthGenerator.ConvertRealWorldToProjective(1, &point, &point);
        point.x = 640 - point.x;
        if(i==0)
            h_left.updatePos(point.x, point.y, false);
        if(i==1)
            h_right.updatePos(point.x, point.y, false);

    }
    //Display Hand positions
    for(HandHistory::Iterator it = m_History.Begin(); it != m_History.End() ; ++it)
    {
        XnPoint3D	point = it->Value().pos;
        m_DepthGenerator.ConvertRealWorldToProjective(1, &point, &point);
        point.x = 640 - point.x;
        point.y += 20;
        value = qRgb(255,255,255);
        if(it->Value().area / it->Value().calibration < TRESHOLD)
            value = qRgb(0,255,255);
        for (XnUInt y = 0; y < 5; ++y)
        {
                for (XnUInt x = 0; x < 5; ++x)
                {
                        m_imagecamera->setPixel(x+point.x, y+point.y, value);
                }
        }
    }*/
    return rc;
}

void Kinect::areaOf(nite::HandId nId)
{
    HandHistory::Iterator it = this->m_History.Find(nId);
    if (it == this->m_History.End())
    {
        printf("Dead hand area: skipped!\n");
        return;
    }
    nite::Point3f   handPos = it->Value().pos;

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

    //m_DepthGenerator.ConvertRealWorldToProjective(3, rectangle, rectangle);

    cv::Rect dim(cv::Point(0,0),cv::Size(XRES,YRES));
    cv::Rect roi = cv::Rect(cv::Point(rectangle[0].x,rectangle[0].y),cv::Point(rectangle[1].x,rectangle[1].y));
    roi &= dim;

    /* Calcul de l'image binaire de la main */
    memcpy(depthRaw.data, m_depthFrame.getData(), XRES*YRES*2);
    const float DEPTH_SCALE_FACTOR = 255./4096.;
    depthRaw.convertTo(depthShow, CV_8U, DEPTH_SCALE_FACTOR);

    Mat handCpy(depthShow, roi);
    Mat handMat = handCpy.clone();
    //Treshold
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
            else if(abs(*pImage - handPos.Z) < m_treshold)
                value = qRgb(255,255,255);
            else
                value = qRgb(0,0,0);
            m_imagecamera->setPixel(1279-x, y, value);
        }
        depthMap += XRES;
    }
    const float r = (count*smallconst)*(handPos.z*handPos.z)/it->Value().calibration;
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
    }
    it->Value().area = (count*smallconst)*(handPos.z*handPos.z);
    return;

}

void Kinect::calibrateOn(nite::HandId nId)
{
    HandHistory::Iterator it = this->m_History.Find(nId);
    if (it == this->m_History.End())
    {
        printf("Dead hand area: skipped!\n");
        return;
    }
    nite::Point3f   handPos = it->Value().pos;

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

    //m_DepthGenerator.ConvertRealWorldToProjective(3, rectangle, rectangle);

    cv::Rect dim(cv::Point(0,0),cv::Size(XRES,YRES));
    cv::Rect roi = cv::Rect(cv::Point(rectangle[0].x,rectangle[0].y),cv::Point(rectangle[1].x,rectangle[1].y));
    roi &= dim;

    /* Calcul de l'image binaire de la main */
    memcpy(depthRaw.data, m_depthFrame.getData(), XRES*YRES*2);
    const float DEPTH_SCALE_FACTOR = 255./4096.;
    depthRaw.convertTo(depthShow, CV_8U, DEPTH_SCALE_FACTOR);

    Mat handCpy(depthShow, roi);
    Mat handMat = handCpy.clone();
    //Treshold
    handMat = (handMat > (handPos.z * DEPTH_SCALE_FACTOR - 5)) & (handMat < (handPos.z * DEPTH_SCALE_FACTOR + 5));
    //Filtre median pour supprimer les inpuretés
    cv::medianBlur(handMat, handMat, 5);

    /* Calcul de la surface */
    int count = cv::countNonZero(handMat);

    const float smallconst = 1E-9;
    printf("calibration of %i=%f\n", nId, (count*smallconst)*(handPos.Z*handPos.Z));
    it->Value().calibration = (count*smallconst)*(handPos.Z*handPos.Z);
    //Dessin
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
            else if(abs(*pImage - handPos.Z) < m_treshold)
                value = qRgb(255,255,255);
            else
                value = qRgb(0,0,0);
            m_imagecamera->setPixel(1279-x, y, value);
        }
        depthMap += XRES;
    }
    const float r = (count*smallconst)*(handPos.z*handPos.z)/it->Value().calibration;
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
    }
}

QImage Kinect::getCamera()
{
    return m_imagecamera->mirrored(true, false);
}
