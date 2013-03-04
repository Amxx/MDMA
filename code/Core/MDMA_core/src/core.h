#ifndef CORE_H
#define CORE_H

#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QObject>
#include <QTimer>

#include "Classes/configuration.h"
#include "Interfaces/interface.h"
#include "Interfaces/kinect.h"
#include "Interfaces/mouse.h"
#include "Interfaces/webcam.h"
#include "Utils/define.h"
#include "UI/mainwindow.h"


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
		

		void start();
		void stop();
//		void exit(int retcode = 0);

		bool setDevice(MDMA::device dev, void* pVoid = NULL);
		void releaseDevice();

		void setUi(MainWindow* mw) { ui = mw; }
		MainWindow* Ui() { return ui; }



	public slots:
		void refresh();

	signals:
		void refreshed();


	public:
		Configuration* cfg;
		Interface* itf;
	private:
		QTimer tmr;
		MainWindow* ui;
		bool running;

};



#endif // CORE_H
