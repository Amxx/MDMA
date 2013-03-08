#include "core.h"

/*
 * ##################################################################################
 * #								CONSTRUCTORS									#
 * ##################################################################################
 */

Core::Core() :
	cfg(NULL),
	itf(NULL),
	ui(NULL),
	running(false)
{
}

Core::~Core()
{
	if(cfg) delete cfg;
	if(itf) delete itf;
}

void Core::init()
{
	cfg = new Configuration;
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
	running = true;

}

void Core::stop()
{
	running = false;
}

void Core::refresh()
{
	if(cfg && itf)
	{
		itf->update();

		if(running)
		{
			QMap<int,Pointer> pts = itf->getPointers();
			for(Zone* zn : *cfg)
			{
//				zn.update(pts);
//				zn.display();
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



