#include "configuration.h"
#include "ui_mainwindow.h"

configuration::configuration(Ui::MainWindow *_ui) :
	ui(_ui)
{
	cameraPort = 0;
	camera = new cv::VideoCapture(cameraPort);
}


int configuration::current_tab()
{
	return ui->comboBox_tab->currentIndex();
}
