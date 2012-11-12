#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QDebug>
#include <QLabel>
#include <QFileDialog>
#include <QString>
#include <QMap>

#include <opencv2/opencv.hpp>

#include "../classes/eventzone.h"
#include "../config/constant.h"

namespace Ui {
	class MainWindow;
}

class configuration : public QWidget
{
		Q_OBJECT
	public:
		configuration(Ui::MainWindow *_ui, QWidget *parent = 0);
		~configuration();

		bool reset();
		bool open();
		bool save();
		bool saveas();

		// ========================================

		QString name;
		QString path;
		int current_tab;

		MDMA::calibration calibration_status;
		QVector<QPoint> user_mask;

		bool running;
		bool changed;
		QMap<QString, eventZone> zones;

		// ========================================

		int cameraPort;
		cv::VideoCapture camera;

		// ========================================

		Ui::MainWindow *ui;
};

//Q_DECLARE_METATYPE(configuration);



#endif // CONFIGURATION_H
