#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QDebug>
#include <QLabel>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QSettings>
#include <QString>
#include <QMap>

#include <opencv2/opencv.hpp>

#include "../classes/eventzone.h"
#include "../classes/subconfig.h"
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

		// ----------------------------------------------------------
		// Methode
		// ----------------------------------------------------------

		void setCurrentTab(int i);
		bool setCamera(bool check = true);
		bool reset();

		bool open();
		bool save();
		bool saveas();

		void displayMask(QPainter& painter);

		// ----------------------------------------------------------
		// Variables
		// ----------------------------------------------------------

		SubConfig data;

		// ----------------------------------------------------------

		bool freeze;
		bool running;
		bool changed;
		MDMA::calibration calibration_status;
		QVector<QPoint> user_mask;

		// ----------------------------------------------------------

		int cameraPort;
		cv::VideoCapture camera;
		cv::Mat current_frame;

		// ----------------------------------------------------------

		Ui::MainWindow *ui;
};


#endif // CONFIGURATION_H
