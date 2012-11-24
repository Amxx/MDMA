#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QDebug>
#include <QObject>

#include <opencv2/opencv.hpp>

#include "configuration.h"
#include "../classes/handtracking.h"
#include "../config/constant.h"

class CameraManager : public QObject
{
		Q_OBJECT
	public:
		CameraManager(Configuration& _config, HandTracking & _handtracking, QObject *parent = 0);
		~CameraManager();

	protected:
		void timerEvent(QTimerEvent*);

	signals:
		void track_updated();

	private:
		Configuration& config;
		HandTracking& handtracking;
		void display();
};

QImage mat2qimage(const cv::Mat& mat);

#endif // CAMERAMANAGER_H
