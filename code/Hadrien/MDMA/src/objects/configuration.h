#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QDebug>
#include <QLabel>
#include <QFileDialog>
#include <QInputDialog>
#include <QList>
#include <QMessageBox>
#include <QSettings>
#include <QString>
#include <QMap>

#include <opencv2/opencv.hpp>

#include "../classes/eventzone.h"
#include "../classes/handdescriptor.h"
#include "../classes/subconfig.h"
#include "../config/constant.h"

namespace Ui {
	class MainWindow;
	class SecondWindow;
}

class Configuration : public QWidget
{
		Q_OBJECT

		Configuration();
		~Configuration();

	public:
		static Configuration& config()
		{
			static Configuration myconfig;   // Instantiated when this function is called
			return myconfig;
		}
		void initialize(QWidget *_main, Ui::MainWindow *_ui);

		// ----------------------------------------------------------
		// Methode
		// ----------------------------------------------------------

		void setCurrentTab(int i);
		bool setCamera(bool force = false);
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

		bool flip_display;
		bool flip_zones;
		bool freeze;
		bool running;
		bool changed;
		MDMA::calibration calibration_status;
		QList<QPoint> user_mask;
		cv::Mat close_calib;
		cv::Mat open_calib;

		bool track_hand;
		bool track_mouse;

		HandDescriptor left_hand;
		HandDescriptor right_hand;
		HandDescriptor mouse_hand;

		// ----------------------------------------------------------

		int cameraPort;
		cv::VideoCapture camera;
		cv::Mat current_frame;

		// ----------------------------------------------------------

		QWidget *main;
		Ui::MainWindow *ui;

		Ui::SecondWindow *second_display;

};


#endif // CONFIGURATION_H
