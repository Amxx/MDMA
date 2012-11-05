#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QLayout>
#include <QMainWindow>
#include <QMouseEvent>

#include <QPainter>

#include <opencv2/opencv.hpp>

#include "configwindow.h"
#include "../objects/cvcameradisplay.h"

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

	private:
		void display_clic(int x, int y);
		void ui_disable(bool b = true);

		Ui::MainWindow *ui;
		cv::VideoCapture* camera;
		cvCameraDisplay* displayer;

		//QPainter* zone_painter;
		//QPixmap* zone_pixmax;
};

#endif // MAINWINDOW_H
