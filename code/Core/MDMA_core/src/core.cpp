#include "core.h"

/*
 * ##################################################################################
 * #								CONSTRUCTORS									#
 * ##################################################################################
 */

Core::Core() :
	cfg(),
	itf(NULL),
	ui(NULL),
	running(false)
{
}

Core::~Core()
{
	if(itf) delete itf;
}

void Core::init()
{
	if(setDevice(MDMA::Kinect))
	{
		QMessageBox::information(0, "Welcome to MDMA", "Connection with Kinect established");
	}
	else if(setDevice(MDMA::WebCam))
	{
		QMessageBox::information(0, "Welcome to MDMA", "Connection with WebCam established");
	}
	else if(setDevice(MDMA::Mouse))
	{
		QMessageBox::critical(0, "Input error", "No video device has been detected");
	}
}

/*
 * ##################################################################################
 * #									METHODES									#
 * ##################################################################################
 */

void Core::setUi(QWidget* mw)
{
	ui = mw;
}
QWidget* Core::Ui()
{
	return ui;
}
void Core::setTab(int t)
{
	cfg._tab  = t;
	emit tabChanged(t);
}
int Core::getTab()
{
	return cfg._tab;
}
void Core::run()
{
	// ============
	qDebug() << "run";
	// ============
}
bool Core::exit()
{
	if(cfg._edit)
		switch(QMessageBox::question(0, "Changed have been made to the configuration", "Would you like to save changes ?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save))
		{
			case QMessageBox::Save:
				return save();
				break;
			case QMessageBox::Discard:
				return true;
				break;
			case QMessageBox::Cancel:
				return false;
				break;
			default:
				break;
		}
	return true;
}

/*
 * ##################################################################################
 * #								CONFIG MANAGEMENT								#
 * ##################################################################################
*/

bool Core::reset()
{
	if(cfg._edit)
		switch(QMessageBox::question(0, "Changed have been made to the configuration", "Would you like to save changes ?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save))
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
	cfg.clear();
	cfg._file = "";
	cfg._tab = 0;
	cfg._edit = false;
	return true;
}

bool Core::load()
{
	if(reset())
	{
		cfg._file = QFileDialog::getOpenFileName(0, "Open file", QDir::homePath(), "MDMA configuration (*.mdma);;All file (*)", 0, 0);
		if(cfg._file == "") return false;

		Configuration::initConfiguration();
		QSettings file(cfg._file, QSettings::IniFormat);
		cfg << file.value("Configuration", qVariantFromValue(Configuration())).value<Configuration>();
		emit reconstruct();
		return true;
	}
	return false;
}

bool Core::save()
{
	if(cfg._file == "")
	{
		cfg._file = QFileDialog::getSaveFileName(0, "Save file", QDir::homePath()+"/new_config.mdma", "MDMA configuration (*.mdma);;All file (*)", 0, 0);
		if(cfg._file == "") return false;
	}

	Configuration::initConfiguration();
	QSettings file(cfg._file, QSettings::IniFormat);
	file.setValue("Configuration", qVariantFromValue(cfg));
	file.sync();

	cfg._edit = false;
	return true;
}
bool Core::saveas()
{
	QString new_path = QFileDialog::getSaveFileName(0, "Save file as", (cfg._file == "")?(QDir::homePath()+"/new_config.mdma"):cfg._file, "MDMA configuration (*.mdma);;All file (*)", 0, 0);
	if(new_path == "") return false;

	cfg._file = new_path;
	save();
	return true;
}

/*
 * ##################################################################################
 * #									SLOTS										#
 * ##################################################################################
 */

void Core::refresh()
{
	if(itf)
	{
		itf->update();

		if(running)
		{
			QMap<int,Pointer> pts = itf->getPointers();
			QList<Signal> sgns;
			for(Zone& zn : cfg)
				sgns << zn.update(pts);
			for(Signal s : sgns)
				switch(s.type)
				{
					case MDMA::NOTE_OFF:
					case MDMA::NOTE_ON:
					case MDMA::POLYFONIC_AFTERTOUCH:
					case MDMA::CONTROL_CHANGE:
					case MDMA::PROGRAM_CHANGE:
					case MDMA::CHANNEL_AFTERTOUCH:
					case MDMA::PITCH_BENDING:
					{
						break;
					}
					case MDMA::GOTO_TAB1:
						setTab(0);
						break;
					case MDMA::GOTO_TAB2:
						setTab(1);
						break;
					case MDMA::GOTO_TAB3:
						setTab(2);
						break;
					case MDMA::NOTHING:
						break;
				}
		}

		emit refreshed();
	}
}

/*
 * ##################################################################################
 * #								DEVICES MANAGEMENT								#
 * ##################################################################################
 */

bool Core::setDevice(MDMA::device dev, void* pVoid)
{
	tmr.stop();
	if(itf) delete itf;
	try
	{
		switch(dev)
		{
			case MDMA::Kinect:
				itf = new Kinect(pVoid);
				qDebug() << "Connection established to Kinect";
				break;
			case MDMA::Mouse:
				itf = new Mouse(pVoid);
				qDebug() << "Connection established to Mouse";
				break;
			case MDMA::WebCam:
				itf = new WebCam(pVoid);
				qDebug() << "Connection established to WebCam";
				break;
		}
		connect(&tmr, SIGNAL(timeout()), this, SLOT(refresh()));
		tmr.start(40);
		return true;
	}
	catch(MDMA::exn e)
	{
		itf = NULL;
		return false;
	}
}

void Core::releaseDevice()
{
	delete itf;
	itf = NULL;
}



