#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>

#include <opencv2/opencv.hpp>

#include "configwindow.h"
#include "../classes/configuration.h"
#include "../objects/cvcameradisplay.h"
#include "../objects/zonedisplay.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT
		
	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		void mousePressEvent(QMouseEvent* ev);

	private slots:
		void on_pushButton_configure_pressed();
		void on_actionAbout_Qt_triggered();
		void on_pushButton_run_clicked();

		void on_pushButton_delete_clicked();

		void on_pushButton_deleteAll_clicked();

		void on_pushButton_edit_clicked();

	private:
		void ui_disable(bool b = true);

		Ui::MainWindow *ui;

		configuration * config;
		cvCameraDisplay* cameraDisplayer;
		zoneDisplay* zoneDisplayer;
};

#endif // MAINWINDOW_H
