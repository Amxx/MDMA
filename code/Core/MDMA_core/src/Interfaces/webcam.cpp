#include "webcam.h"

#include <QDebug>

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







WebCam::WebCam(void* pVoid)
{
	int* pInt = static_cast<int*>(pVoid);
	camera.open( (pInt) ? *pInt : 0 );
	if(!camera.isOpened()) throw MDMA::DEVICE_NOT_DETECTED;
	pts.insert(0, Pointer());
	pts.insert(1, Pointer());
}

WebCam::~WebCam()
{
	if(camera.isOpened()) camera.release();
}


void WebCam::calibrate()
{
	throw "Webcam::Calibrate not implemented yet";
}

bool WebCam::isCalibrated()
{
	throw "Webcam::isCalibrated not implemented yet";
}

void WebCam::update()
{
	if(camera.isOpened())
		camera >> current_frame;
}

QImage WebCam::getImage()
{
	return mat2qimage(current_frame);
}

QMap<int,Pointer> WebCam::getPointers()
{
	return pts;
}
