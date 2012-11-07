#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QLabel>
#include <QString>
#include <QMap>

#include <opencv2/opencv.hpp>

#include "eventzone.h"

namespace Ui {
	class MainWindow;
}

class configuration
{
	public:
		explicit configuration(Ui::MainWindow *_ui);
		~configuration();

		configuration Load(QString path);
		void Save(QString path);

		int current_tab();

		// ========================================

		QString name;
		QString file;

		// ========================================

		int cameraPort;
		cv::VideoCapture* camera;

		// ========================================

		bool changed;
		QMap<QString, eventZone> zones;

		// ========================================

		Ui::MainWindow *ui;
};



#endif // CONFIGURATION_H
