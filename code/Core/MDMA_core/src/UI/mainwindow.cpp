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
	connect(&appCore(), SIGNAL(setStatus(QString,int)), ui->statusBar, SLOT(showMessage(QString,int)));
	connect(&appCore().cfg, SIGNAL(reconstruct()), this, SLOT(reconstruct()));
}

/*
 * ##################################################################################
 * #									EVENTS										#
 * ##################################################################################
 */

void MainWindow::closeEvent(QCloseEvent *e)
{
	if(appCore().exit())
		e->accept();
	else
		e->ignore();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	switch(e->button())
	{
		case Qt::LeftButton:
		{
			Zone zn(QRect(ui->display->mapFromGlobal(e->globalPos()), QSize(5, 5)), appCore().cfg.getTab());
			zd = new ZoneDrager(appCore().cfg.insertZone(zn), ui->centralWidget);
			zd->mousePressEvent(e, true);
			break;
		}
		case Qt::MidButton:
			appCore().cfg.setTab((appCore().cfg.getTab()+1)%3);
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

void MainWindow::reconstruct()
{
	for(Zone& z : appCore().cfg)
		new ZoneDrager(z, ui->centralWidget);
	appCore().cfg.edited(false);
}

/*
 * ##################################################################################
 * #								PRIVATE SLOTS									#
 * ##################################################################################
 */

void MainWindow::on_actionNew_triggered()
{
	appCore().cfg.reset();
}

void MainWindow::on_actionOpen_triggered()
{
	appCore().cfg.load();
}

void MainWindow::on_actionSave_triggered()
{
	appCore().cfg.save();
}

void MainWindow::on_actionSave_as_triggered()
{
	appCore().cfg.saveas();
}

void MainWindow::on_actionAbout_MDMA_triggered()
{
	qApp->aboutQt();
}
