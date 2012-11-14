#include "cameramanager.h"
#include "ui_mainwindow.h"

CameraManager::CameraManager(Configuration& _config, QObject *parent) :
	QObject(parent),
	config(_config)
{
	startTimer(40);
}

CameraManager::~CameraManager()
{
}

void CameraManager::timerEvent(QTimerEvent*)
{
	if(config.camera.isOpened() && !config.freeze)
	{
		config.camera >> config.current_frame;
		cv::flip(config.current_frame, config.current_frame, 1);

		display();
	}
}

void CameraManager::display()
{
	config.ui->label_camera->setPixmap(QPixmap::fromImage(mat2qimage(config.current_frame)));
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
