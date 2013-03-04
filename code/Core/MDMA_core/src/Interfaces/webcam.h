#ifndef WEBCAM_H
#define WEBCAM_H

#include <opencv2/opencv.hpp>

#include "interface.h"
#include "../Utils/define.h"


class WebCam : public Interface
{
	public:
		WebCam(void* = NULL);
		~WebCam();

		MDMA::device type() { return MDMA::WebCam; }

		void calibrate();
		bool isCalibrated();

		void update();
		QImage getImage();
		QMap<int,Pointer> getPointers();


	private:
		int cameraPort;
		cv::VideoCapture camera;
		cv::Mat current_frame;

		QMap<int,Pointer> pts;

};

#endif // WEBCAM_H
