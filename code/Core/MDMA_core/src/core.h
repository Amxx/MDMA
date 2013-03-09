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
// #include "UI/mainwindow.h"


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
/*
		bool reset();
		bool load();
		bool save();
		bool saveas();
*/
		void setTab(int t);
		int getTab();

		bool setDevice(MDMA::device dev, void* pVoid = NULL);
		void releaseDevice();

		void setUi(QWidget* mw) { ui = mw; }
		QWidget* Ui() { return ui; }



	public slots:
		void refresh();

	signals:
		void refreshed();
		void tabChanged(int);


	public:
		Configuration cfg;
		Interface* itf;

	private:
		QTimer tmr;
		QWidget* ui;
		bool running;

};



#endif // CORE_H
