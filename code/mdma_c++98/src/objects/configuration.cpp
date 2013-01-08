#include "configuration.h"
#include "ui_mainwindow.h"
#include "ui_secondwindow.h"

Configuration::Configuration() :
	flip_display(true),
	flip_zones(false),
	freeze(false),
	running(false),
	changed(false),
	calibration_status(MDMA::NOT_CALIBRATED),
	track_hand(true),
	track_mouse(false),
	left_hand(0, 0, MDMA::LEFT),
	right_hand(0, 0, MDMA::RIGHT),
	mouse_hand(0, 0, MDMA::MOUSE),
	cameraPort(0)
{
}

Configuration::~Configuration()
{
}

void Configuration::initialize(QWidget *_main, Ui::MainWindow *_ui)
{
	main = _main;
	ui = _ui;

	camera.open(cameraPort);
	setCamera();
}

// =========================================================================================================

void Configuration::setCurrentTab(int i)
{
	data.current_tab = i;
	ui->comboBox_tab->setCurrentIndex(i);
}


bool Configuration::setCamera(bool force)
{
	bool run = !force;
	bool ok = true;
	while(ok && !(run && camera.isOpened()))
	{
		run = true;
		cameraPort = QInputDialog::getInt(0, "Camera selection", "Please select camera device number", cameraPort, 0, 2147483647, 1, &ok);
		if(camera.isOpened()) camera.release();
		camera.open(cameraPort);
	}
	return ok;
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
			case QMessageBox::Discard:
				break;
			case QMessageBox::Cancel:
				return false;
				break;
			default:
				break;
		}

	data.version = MDMA::VERSION;
	data.name = "New configuration";
	data.path = "";
	data.current_tab = 0;
	data.zones.clear();
	freeze = false;
	running = false;
	track_hand = true;
	track_mouse = false;
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

			case QMessageBox::Discard:
				break;

			default:
				return false;
				break;
		}

	QString open_path = QFileDialog::getOpenFileName(0, "Open file", QDir::homePath(), "MDMA configuration (*.mdma);;All file (*)", 0, QFILEDIALOGOPTION);
	if(open_path == "") return false;

	SubConfig::initSubConfig();
	QSettings file(open_path, QSettings::IniFormat);
	data = file.value("SubConfig", qVariantFromValue(SubConfig())).value<SubConfig>();

	ui->treeWidget_list->clear();
	changed = false;

	if(data.version != MDMA::VERSION)
	{
		QMessageBox::information(0, "Depreciated configuration file", "The configuration you tried to load does not match the current verion of MDMA");
		reset();
		return false;
	}

    //for(EventZone& evz : data.zones)
    //	ui->treeWidget_list->addTopLevelItem(new QTreeWidgetItem(QStringList() << evz.name << MDMA::type_to_string(evz.type) << QString::number(evz.tab+1)));
    for(QMap<QString, EventZone>::Iterator it = data.zones.begin() ; it != data.zones.end() ; ++it)
        ui->treeWidget_list->addTopLevelItem(new QTreeWidgetItem(QStringList() << it->name << MDMA::type_to_string(it->type) << QString::number(it->tab+1)));
    ui->comboBox_tab->setCurrentIndex(data.current_tab);


	return true;
}

bool Configuration::save()
{
	if(data.path == "")
	{
		data.path = QFileDialog::getSaveFileName(0, "Save file", QDir::homePath()+"/new_config.mdma", "MDMA configuration (*.mdma);;All file (*)", 0, QFILEDIALOGOPTION);
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
	QString new_path = QFileDialog::getSaveFileName(0, "Save file as", (data.path == "")?(QDir::homePath()+"/new_config.mdma"):data.path, "MDMA configuration (*.mdma);;All file (*)", 0, QFILEDIALOGOPTION);
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
    //for(QPoint& p : user_mask) poly << p;
    for(QList<QPoint>::Iterator it = user_mask.begin() ; it != user_mask.end() ; ++it) poly << *it;
    painter.drawPolygon(poly);
}

