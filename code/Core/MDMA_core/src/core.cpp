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
 * #									SLOTS										#
 * ##################################################################################
 */


void Core::start()
{
	// ============
	running = true;
}

void Core::stop()
{
	// ============
	running = false;
}

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
 * #								Config Management								#
 * ##################################################################################

/*
 * ##################################################################################
 * #										TAB										#
 * ##################################################################################
 */

void Core::setTab(int t)
{
	cfg._tab  = t;
	emit tabChanged(t);
}
int Core::getTab()
{
	return cfg._tab;
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



