#include "cameramanager.h"
#include "configuration.h"
#include "ui_mainwindow.h"
#include "ui_secondwindow.h"

CameraManager::CameraManager(HandTracking& _handtracking, QObject *parent) :
	QObject(parent),
    kinect(_handtracking.h_left, _handtracking.h_right),
	handtracking(_handtracking)
{

}

CameraManager::~CameraManager()
{
}

void CameraManager::Init()
{
    if(!setCamera(-1))
        setCamera(0);
    startTimer(40);
}

bool CameraManager::canDoCalibration()
{
    return !useKinect;
}

bool CameraManager::existsKinect()
{
    if(useKinect)
        return true;
    int rc = kinect.Init();
    return rc == 0;
}

bool CameraManager::setCamera(int i)
{
    cameraPort = i;
    if(camera.isOpened()) camera.release();
    if(i==KINECT_DEVICE)
    {
        int rc = kinect.Init();
        if(rc == 0)
        {
            rc = kinect.Run();
        }
        if((useKinect = (rc == 0)))
            Configuration::config().calibration_status = MDMA::CALIBRATED;
        return useKinect;
    }

    return  camera.open(cameraPort);
}

void CameraManager::timerEvent(QTimerEvent*)
{
    if(useKinect)
    {
        int rc = kinect.Update(Configuration::config().flip_display);
        if(rc != 0)
        {
            useKinect = false;
            return;
        }
        Configuration::config().ui->label_camera->setPixmap(QPixmap::fromImage(kinect.getCamera().mirrored(Configuration::config().flip_display,false)));
        if(Configuration::config().running)
        {
            if(Configuration::config().track_mouse)
            {
                QPoint cursor  = Configuration::config().main->mapFromGlobal(QCursor::pos()) - Configuration::config().ui->label_camera->pos();
                int x = std::min(std::max(cursor.x(), 0), 640);
                int y = std::min(std::max(cursor.y() - Configuration::config().ui->menubar->size().height(), 0), 480);
                Configuration::config().mouse_hand.updatePos(x, y, QApplication::mouseButtons() == Qt::NoButton);
            }
            emit track_updated();
        }
    }
    else if(camera.isOpened() && !Configuration::config().freeze)
	{
        camera >> Configuration::config().current_frame;


		if(Configuration::config().flip_display) cv::flip(Configuration::config().current_frame, Configuration::config().current_frame, 1);


		display();

		if(Configuration::config().running)
		{
			if(Configuration::config().track_mouse)
			{
				QPoint cursor  = Configuration::config().main->mapFromGlobal(QCursor::pos()) - Configuration::config().ui->label_camera->pos();
				int x = std::min(std::max(cursor.x(), 0), 640);
				int y = std::min(std::max(cursor.y() - Configuration::config().ui->menubar->size().height(), 0), 480);
				Configuration::config().mouse_hand.updatePos(x, y, QApplication::mouseButtons() == Qt::NoButton);
			}
			if(Configuration::config().track_hand)
			{
				handtracking.Track(Configuration::config().current_frame);
			}
			emit track_updated();
		}
	}
}

void CameraManager::display()
{
	QImage img = mat2qimage(Configuration::config().current_frame);

	Configuration::config().ui->label_camera->setPixmap(QPixmap::fromImage(img));

	if(Configuration::config().second_display)
		Configuration::config().second_display->label_camera->setPixmap((QPixmap::fromImage((Configuration::config().flip_display)?img.mirrored(true,false):img)));

	/*
	cv::Mat frame;
	Configuration::config().current_frame.copyTo(frame);

	if(Configuration::config().second_display)
		Configuration::config().second_display->display->setPixmap(QPixmap::fromImage(mat2qimage(frame)));

	if(Configuration::config().flip_display)
		cv::flip(frame, frame, 1);
	*/
}



QImage mat2qimage(const cv::Mat& mat)
{
	if(mat.type()==CV_8UC1)
	{
		QVector<QRgb> colorTable;
		for (int i=0; i<256; i++)
			colorTable.push_back(qRgb(i,i,i));
		const uchar *qImageBuffer = (const uchar*)mat.data;
		QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
		img.setColorTable(colorTable);
		return img;
	}
	if(mat.type()==CV_8UC3)
	{
		const uchar *qImageBuffer = (const uchar*)mat.data;
		QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return img.rgbSwapped();
	}
	else
	{
		return QImage();
	}
}
