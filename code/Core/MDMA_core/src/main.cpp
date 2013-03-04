#include <QApplication>


#include "core.h"
#include "src/UI/mainwindow.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	try
	{
		MainWindow mainwindow;
		mainwindow.init();
		appCore().init();

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
