#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QDebug>
#include <QObject>

#include <opencv2/opencv.hpp>

#include "configuration.h"
#include "../config/constant.h"

class cameraManager : public QObject
{
		Q_OBJECT
	public:
		cameraManager(configuration& _config, QObject *parent = 0);
		~cameraManager();

	protected:
		void timerEvent(QTimerEvent*);

	private:
		configuration& config;
		void display(cv::Mat frame);
};

QImage mat2qimage(const cv::Mat& mat);

#endif // CAMERAMANAGER_H
