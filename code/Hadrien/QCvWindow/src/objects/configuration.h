#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QDebug>
#include <QLabel>
#include <QFileDialog>
#include <QInputDialog>
#include <QString>
#include <QMap>

#include <opencv2/opencv.hpp>

#include "../classes/eventzone.h"
#include "../config/constant.h"

namespace Ui {
	class MainWindow;
}

class Configuration : public QWidget
{
		Q_OBJECT
	public:
		Configuration(Ui::MainWindow *_ui, QWidget *parent = 0);
		~Configuration();

		bool setCurrentTab(int i);
		bool setCamera(bool check = true);
		bool reset();

		bool open();
		bool save();
		bool saveas();

		void displayMask(QPainter& painter);

		// ========================================

		QString name;
		QString path;
		int current_tab;

		bool freeze;
		MDMA::calibration calibration_status;
		QVector<QPoint> user_mask;

		bool running;
		bool changed;
		QMap<QString, EventZone> zones;

		// ========================================

		int cameraPort;
		cv::VideoCapture camera;
		cv::Mat current_frame;

		// ========================================

		Ui::MainWindow *ui;
};


#endif // CONFIGURATION_H
