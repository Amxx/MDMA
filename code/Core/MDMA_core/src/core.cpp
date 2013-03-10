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
		emit setStatus("Connection with Kinect established", 5000);
		//QMessageBox::information(0, "Welcome to MDMA", "Connection with Kinect established");
	}
	else if(setDevice(MDMA::WebCam))
	{
		emit setStatus("Connection with Webcam established", 5000);
		//QMessageBox::information(0, "Welcome to MDMA", "Connection with WebCam established");
	}
	else if(setDevice(MDMA::Mouse))
	{
		emit setStatus("No video device has been detected", 5000);
		//QMessageBox::critical(0, "Input error", "No video device has been detected");
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
void Core::run()
{
	// ============
	qDebug() << "run";
	// ============
}
bool Core::exit()
{
	if(cfg.isEdited())
		switch(QMessageBox::question(0, "Changed have been made to the configuration", "Would you like to save changes ?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save))
		{
			case QMessageBox::Save:
				return cfg.save();
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
						cfg.setTab(0);
						break;
					case MDMA::GOTO_TAB2:
						cfg.setTab(1);
						break;
					case MDMA::GOTO_TAB3:
						cfg.setTab(2);
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
				break;
			case MDMA::Mouse:
				itf = new Mouse(pVoid);
				break;
			case MDMA::WebCam:
				itf = new WebCam(pVoid);
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



