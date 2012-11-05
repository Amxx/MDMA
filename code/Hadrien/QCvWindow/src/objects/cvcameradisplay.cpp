#include "cvcameradisplay.h"

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

cvCameraDisplay::cvCameraDisplay(QLabel* _displayLabel, cv::VideoCapture* _camera, QObject *parent) :
	QObject(parent),
	displayLabel(_displayLabel),
	camera(_camera)
{
	startTimer(25);
}

void cvCameraDisplay::timerEvent(QTimerEvent*)
{
	cv::Mat frame;
	(*camera) >> frame;
	cv::flip(frame, frame, 1);
	displayLabel->setPixmap(QPixmap::fromImage(mat2qimage(frame)));
	//displayLabel->setPixmap(QPixmap::fromImage(IplImage2QImage(cvQueryFrame(camera))));
}
