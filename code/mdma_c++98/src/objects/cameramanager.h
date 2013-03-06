#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QDebug>
#include <QObject>

#include <opencv2/opencv.hpp>
#include "../classes/handtracking.h"
#include "../classes/kinect.h"
#include "../config/constant.h"

#define KINECT_DEVICE      -1

class CameraManager : public QObject
{
		Q_OBJECT
	public:
        CameraManager(HandDescriptor&, HandDescriptor&, QObject *parent = 0);
		~CameraManager();
        bool canDoCalibration();
        MDMA::calibration isCalibrated();
        bool calibrate();
        bool existsKinect();
        bool setCamera(int i = KINECT_DEVICE);
        void Init();

	protected:
		void timerEvent(QTimerEvent*);

	signals:
		void track_updated();

	private:
        int cameraPort;
        cv::VideoCapture camera;
        Kinect kinect;
        HandTracking handtracking;
        void display();
        bool useKinect;
        MDMA::calibration calibration_status;
};

QImage mat2qimage(const cv::Mat& mat);

#endif // CAMERAMANAGER_H
