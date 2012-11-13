#include "configuration.h"
#include "ui_mainwindow.h"

configuration::configuration(Ui::MainWindow *_ui, QWidget* parent) :
	QWidget(parent),
	name("Unamed configuration"),
	path(""),
	current_tab(0),
	calibration_status(MDMA::NOT_CALIBRATED),
	running(false),
	changed(false),
	cameraPort(0),
	camera(cameraPort),
	ui(_ui)
{
	assert(camera.isOpened());
}

configuration::~configuration()
{
}

bool configuration::reset()
{
	if(changed && !save()) return false;

	name = "unamed configuration";
	path = "";
	current_tab = 0;
	running = false;
	changed = false;
	cameraPort = 0;
	ui->comboBox_tab->setCurrentIndex(0);
	return true;
}

bool configuration::open()
{
	if(changed && !save()) return false;
	QString file = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "*.mdma", 0, QFILEDIALOGOPTION);
	QFileInfo file_info(file);

	qDebug() << "path : " << file_info.filePath();
	qDebug() << "file name " << file_info.fileName();

	return true;
}

bool configuration::save()
{
	if(changed)
	{
		if(path == "") path = QFileDialog::getSaveFileName(this, "Save file", QDir::homePath()+"/new_config.mdma", "*.mdma", 0, QFILEDIALOGOPTION);
		if(path == "") return false;

		name = QFileInfo(path).fileName();

		// save

		changed = false;
		return true;
	}
	return false;
}

bool configuration::saveas()
{
	QString new_path = QFileDialog::getSaveFileName(this, "Save file as", (path == "")?(QDir::homePath()+"/new_config.mdma"):path, "*.mdma", 0, QFILEDIALOGOPTION);
	if(new_path == "") return false;

	path = new_path;
	name = QFileInfo(new_path).fileName();

	// save

	changed = false;
	return true;
}

