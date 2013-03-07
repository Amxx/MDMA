#include <QApplication>


#include "core.h"
#include "src/UI/mainwindow.h"



#include "Classes/pointer.h"



int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	try
	{
		/*
		MainWindow mainwindow;
		mainwindow.init();
		appCore().init();
		*/

		TriPointHist ph;
		ph.update(QPoint(1,0));
		ph.update(QPoint(0,1));
		TriPoint p = ph.previous() - ph.current();
		qDebug() << p.x() << p.y() << p.z();

		return app.exec();
	}
	catch(char const* error)
	{
		qDebug() << "========================================";
		qDebug() << "           Exception catched            ";
		qDebug() << "========================================";
		qDebug() << error;
		app.exit(1);
	}
}
