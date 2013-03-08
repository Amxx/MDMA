#include "mainwindow.h"
#include "ui_mainwindow.h"

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
	appCore().setUi(ui->display);
	connect(&appCore(), SIGNAL(refreshed()), this, SLOT(refreshImage()));
}

/*
 * ##################################################################################
 * #									EVENTS										#
 * ##################################################################################
 */


void MainWindow::mousePressEvent(QMouseEvent *e)
{
	switch(e->button())
	{
		case Qt::LeftButton:
		{
			zd = new ZoneDrager( new Zone(QRect(ui->display->mapFromGlobal(e->globalPos()), QSize(5, 5)), appCore().cfg->getTab()), ui->centralWidget );
			zd->mousePressEventHot(e);
			break;
		}
		case Qt::RightButton:
			appCore().cfg->setTab((appCore().cfg->getTab()+1)%3);
			break;
		default:
			break;
	}
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
	if ( e->buttons() & Qt::LeftButton ) zd->mouseMoveEvent(e);
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
	if ( e->button() & Qt::LeftButton ) zd->mouseReleaseEvent(e);
}

/*
 * ##################################################################################
 * #									SLOTS										#
 * ##################################################################################
 */


void MainWindow::refreshImage()
{
	this->ui->display->setPixmap(QPixmap::fromImage(appCore().itf->getImage()));
}
