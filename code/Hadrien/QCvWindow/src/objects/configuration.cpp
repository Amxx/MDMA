#include "configuration.h"
#include "ui_mainwindow.h"

Configuration::Configuration(Ui::MainWindow *_ui, QWidget* parent) :
	QWidget(parent),
	name("Unamed configuration"),
	path(""),
	current_tab(0),
	freeze(false),
	calibration_status(MDMA::NOT_CALIBRATED),
	running(false),
	changed(false),
	cameraPort(0),
	ui(_ui)
{
	setCamera();
}

Configuration::~Configuration()
{
}

// =========================================================================================================

void Configuration::setCurrentTab(int i)
{
	current_tab = i;
	ui->comboBox_tab->setCurrentIndex(i);
}


bool Configuration::setCamera(bool check)
{
	camera.open(cameraPort);
	bool ok = check;
	while(ok && !camera.isOpened())
	{
		cameraPort = QInputDialog::getInt(this, "Couldn't open camera", "Please select camera port", cameraPort, -2147483647, 2147483647, 1, &ok);
		camera.open(cameraPort);
	}
	return !check || ok;
}

bool Configuration::reset()
{
	if(changed && !save()) return false;

	name = "unamed configuration";
	path = "";
	current_tab = 0;
	freeze = false;
	running = false;
	changed = false;
	zones.clear();
	cameraPort = 0;
	ui->comboBox_tab->setCurrentIndex(0);
	ui->treeWidget_list->clear();
	return true;
}

// =========================================================================================================

bool Configuration::open()
{
	if(changed && !save()) return false;
	QString file = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "MDMA configuration (*.mdma);;All file (*)", 0, QFILEDIALOGOPTION);
	QFileInfo file_info(file);

	qDebug() << "path : " << file_info.filePath();
	qDebug() << "file name " << file_info.fileName();

	return true;
}

bool Configuration::save()
{
	if(changed)
	{
		if(path == "") path = QFileDialog::getSaveFileName(this, "Save file", QDir::homePath()+"/new_config.mdma", "MDMA configuration (*.mdma);;All file (*)", 0, QFILEDIALOGOPTION);
		if(path == "") return false;

		name = QFileInfo(path).fileName();

		// save

		changed = false;
		return true;
	}
	return false;
}

bool Configuration::saveas()
{
	QString new_path = QFileDialog::getSaveFileName(this, "Save file as", (path == "")?(QDir::homePath()+"/new_config.mdma"):path, "MDMA configuration (*.mdma);;All file (*)", 0, QFILEDIALOGOPTION);
	if(new_path == "") return false;

	path = new_path;
	name = QFileInfo(new_path).fileName();

	// save

	changed = false;
	return true;
}


// =========================================================================================================

void Configuration::displayMask(QPainter& painter)
{
	painter.setPen(QPen(QBrush(MDMA::mask_color), 1, Qt::SolidLine, Qt::RoundCap));
	painter.setBrush(QBrush(MDMA::mask_color));
	QPolygon poly;
	for(QPoint& p : user_mask.toList()) poly << p;
	painter.drawPolygon(poly);
}
