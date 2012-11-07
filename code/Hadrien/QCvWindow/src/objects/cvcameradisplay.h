#ifndef CVCAMERADISPLAY_H
#define CVCAMERADISPLAY_H

#include <QDebug>
#include <QObject>

#include <opencv2/opencv.hpp>

#include "../classes/configuration.h"

class cvCameraDisplay : public QObject
{
		Q_OBJECT
	public:
		explicit cvCameraDisplay(configuration* _config, QObject *parent = 0);
		~cvCameraDisplay();

	protected:
		void timerEvent(QTimerEvent*);

	private:
		configuration* config;
};

QImage mat2qimage(const cv::Mat& mat);

#endif // CVCAMERADISPLAY_H
