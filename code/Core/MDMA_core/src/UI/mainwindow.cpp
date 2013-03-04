#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../core.h"


/*
 * ##################################################################################
 * #								CONSTRUCTORS									#
 * ##################################################################################
 */

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	appCore().setUi(NULL);
	delete ui;
}

void MainWindow::init()
{
	show();
	appCore().setUi(this);
	connect(&appCore(), SIGNAL(refreshed()), this, SLOT(refreshImage()));
}

/*
 * ##################################################################################
 * #									EVENTS										#
 * ##################################################################################
 */


/*
void MainWindow::closeEvent(QCloseEvent* ev)
{
}
*/

/*
 * ##################################################################################
 * #									SLOTS										#
 * ##################################################################################
 */


void MainWindow::refreshImage()
{
	if(appCore().itf && appCore().cfg)
	{
		this->ui->display->setPixmap(QPixmap::fromImage(appCore().itf->getImage()));
		//for(Zone& zn : *appCore().cfg)
		//	zn.display();
	}
}
