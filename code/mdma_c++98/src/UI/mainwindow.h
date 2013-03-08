#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>

#include <opencv2/opencv.hpp>

#include "configwindow.h"
#include "handclosewindow.h"
#include "handopenwindow.h"
#include "maskwindow.h"
#include "../classes/handtracking.h"
#include "../objects/configuration.h"
#include "../objects/cameramanager.h"
#include "../objects/eventmanager.h"
#include "../objects/midimanager.h"
#include "../objects/zonemanager.h"

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
		void closeEvent(QCloseEvent* ev);

	private slots:
		void on_actionNew_triggered();
		void on_actionOpen_triggered();
		void on_actionSave_triggered();
		void on_actionSave_As_triggered();
		void on_actionAbout_Qt_triggered();

		void on_pushButton_run_clicked();
		void on_pushButton_calibrate_clicked();
		void on_pushButton_configure_clicked();
		void on_pushButton_delete_clicked();
		void on_pushButton_deleteAll_clicked();
		void on_pushButton_edit_clicked();
		void on_comboBox_tab_currentIndexChanged(int index);
		void on_actionAbout_MDMA_triggered();


	private:
		void ui_disable(bool b = true, bool all = false);

		Ui::MainWindow *ui;

        EventManager event_manager;
		MidiManager midi_manager;
		ZoneManager zone_manager;

};

#endif // MAINWINDOW_H
