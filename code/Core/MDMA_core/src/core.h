#ifndef CORE_H
#define CORE_H

#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QSettings>
#include <QTimer>


#include "Classes/configuration.h"
#include "Interfaces/interface.h"
#include "Interfaces/kinect.h"
#include "Interfaces/mouse.h"
#include "Interfaces/webcam.h"
#include "Utils/define.h"


class Core : public QObject
{
	Q_OBJECT

	public:
		Core();
		~Core();
		void init();

		static Core& getCore()
		{
			static Core mycore;
			return mycore;
		}

		void setUi(QWidget* mw);
		QWidget* Ui();

		void run();
		bool exit();

		bool setDevice(MDMA::device dev, void* pVoid = NULL);
		void releaseDevice();

	public slots:
		void refresh();

	signals:
		void refreshed();
		void setStatus(QString, int = 0);

	public:
		Configuration cfg;
		Interface* itf;

	private:
		QTimer tmr;
		QWidget* ui;
		bool running;

};



#endif // CORE_H
