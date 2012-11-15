#include "configuration.h"
#include "ui_mainwindow.h"

Configuration::Configuration(Ui::MainWindow *_ui, QWidget* parent) :
	QWidget(parent),
	freeze(false),
	running(false),
	changed(false),
	calibration_status(MDMA::NOT_CALIBRATED),
	cameraPort(0),
	ui(_ui)
{
	//setCamera();
}

Configuration::~Configuration()
{
}

// =========================================================================================================

void Configuration::setCurrentTab(int i)
{
	data.current_tab = i;
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

// =========================================================================================================

bool Configuration::reset()
{
	if(changed)
		switch(QMessageBox::question(this, "Changed have been made to the configuration", "Would you like to save changes made to \""+data.name+"\" before closing ?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save))
		{
			case QMessageBox::Save:
				if(!save()) return false;
				break;

			default:
				return false;
				break;
		}

	data.name = "New configuration";
	data.path = "";
	data.current_tab = 0;
	data.zones.clear();
	freeze = false;
	running = false;
	changed = false;
	cameraPort = 0;
	ui->comboBox_tab->setCurrentIndex(0);
	ui->treeWidget_list->clear();
	return true;
}

bool Configuration::open()
{
	if(changed)
		switch(QMessageBox::question(this, "Changed have been made to the configuration", "Would you like to save changes made to \""+data.name+"\" before closing ?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save))
		{
			case QMessageBox::Save:
				if(!save()) return false;
				break;

			default:
				return false;
				break;
		}

	QString open_path = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "MDMA configuration (*.mdma);;All file (*)", 0, QFILEDIALOGOPTION);

	if(open_path == "") return false;

	SubConfig::initSubConfig();
	QSettings file(open_path, QSettings::IniFormat);
	data = file.value("SubConfig", qVariantFromValue(SubConfig())).value<SubConfig>();
	ui->treeWidget_list->clear();
	for(EventZone& evz : data.zones)
		ui->treeWidget_list->addTopLevelItem(new QTreeWidgetItem(QStringList() << evz.name << MDMA::type_to_string(evz.type) << QString::number(evz.tab+1)));
	ui->comboBox_tab->setCurrentIndex(data.current_tab);
	changed = false;

	return true;
}

bool Configuration::save()
{
	if(data.path == "")
	{
		data.path = QFileDialog::getSaveFileName(this, "Save file", QDir::homePath()+"/new_config.mdma", "MDMA configuration (*.mdma);;All file (*)", 0, QFILEDIALOGOPTION);
		if(data.path == "") return false;
	}

	data.name = QFileInfo(data.path).fileName();

	SubConfig::initSubConfig();
	QSettings file(data.path, QSettings::IniFormat);
	file.setValue("SubConfig", qVariantFromValue(data));
	file.sync();

	changed = false;
	return true;
}

bool Configuration::saveas()
{
	QString new_path = QFileDialog::getSaveFileName(this, "Save file as", (data.path == "")?(QDir::homePath()+"/new_config.mdma"):data.path, "MDMA configuration (*.mdma);;All file (*)", 0, QFILEDIALOGOPTION);
	if(new_path == "") return false;

	data.path = new_path;
	data.name = QFileInfo(new_path).fileName();

	SubConfig::initSubConfig();
	QSettings file(data.path, QSettings::IniFormat);
	file.setValue("SubConfig", qVariantFromValue(data));
	file.sync();

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

