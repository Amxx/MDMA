#include "cameramanager.h"
#include "ui_mainwindow.h"

CameraManager::CameraManager(HandTracking& _handtracking, QObject *parent) :
	QObject(parent),
	handtracking(_handtracking)
{
	startTimer(40);
}

CameraManager::~CameraManager()
{
}

void CameraManager::timerEvent(QTimerEvent*)
{
	if(Configuration::config().camera.isOpened() && !Configuration::config().freeze)
	{
		Configuration::config().camera >> Configuration::config().current_frame;
		if(Configuration::config().flip) cv::flip(Configuration::config().current_frame, Configuration::config().current_frame, 1);

		display();

		if(Configuration::config().running)
		{
			if(Configuration::config().track_mouse)
			{
				QPoint cursor  = Configuration::config().main->mapFromGlobal(QCursor::pos()) - Configuration::config().ui->label_camera->pos();
				int x = std::min(std::max(cursor.x(), 0), 640);
				int y = std::min(std::max(cursor.y() - Configuration::config().ui->menubar->size().height(), 0), 480);

				qDebug() << x << y << (QApplication::mouseButtons() == Qt::NoButton);

				Configuration::config().mouse_hand.updatePos(x, y, QApplication::mouseButtons() == Qt::NoButton);
			}
			if(Configuration::config().track_image)
			{
				handtracking.Track(Configuration::config().current_frame);
			}
			emit track_updated();
		}
	}
}

void CameraManager::display()
{
	Configuration::config().ui->label_camera->setPixmap(QPixmap::fromImage(mat2qimage(Configuration::config().current_frame)));
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
