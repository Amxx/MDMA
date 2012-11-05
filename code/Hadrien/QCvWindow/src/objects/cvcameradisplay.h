#ifndef CVCAMERADISPLAY_H
#define CVCAMERADISPLAY_H

#include <QObject>
#include <QLabel>

#include <opencv2/opencv.hpp>

class cvCameraDisplay : public QObject
{
		Q_OBJECT
	public:
		explicit cvCameraDisplay(QLabel* _displayLabel, cv::VideoCapture* _camera = 0, QObject *parent = 0);

	protected:
		void timerEvent(QTimerEvent*);

	private:
		QLabel* displayLabel;
		cv::VideoCapture* camera;
};

#endif // CVCAMERADISPLAY_H
