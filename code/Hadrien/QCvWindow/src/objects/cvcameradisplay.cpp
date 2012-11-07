#include "cvcameradisplay.h"
#include "ui_mainwindow.h"

cvCameraDisplay::cvCameraDisplay(configuration* _config, QObject *parent) :
	QObject(parent),
	config(_config)
{
	startTimer(40);
}

cvCameraDisplay::~cvCameraDisplay()
{
}

void cvCameraDisplay::timerEvent(QTimerEvent*)
{
	cv::Mat frame;
	*config->camera >> frame;
	cv::flip(frame, frame, 1);
	config->ui->label_camera->setPixmap(QPixmap::fromImage(mat2qimage(frame)));
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
