#include <QApplication>

#include "UI/mainwindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	MainWindow newWindow;
	newWindow.show();

	return app.exec();
}
