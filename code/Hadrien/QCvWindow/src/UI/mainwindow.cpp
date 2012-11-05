#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 *	###############################################################################################
 *  #                                        Constructors                                         #
 *	###############################################################################################
 */

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	camera = new cv::VideoCapture(0);
	//assert(camera->isOpened());

	displayer = new cvCameraDisplay(ui->label_display, camera, this);
/*
	zone_pixmax = new QPixmap(100, 100);
	zone_painter = new QPainter(zone_pixmax);
	ui->label_zone->setPixmap((*zone_pixmax));
*/
	ui->statusbar->showMessage("Ready");
}

void MainWindow::mousePressEvent(QMouseEvent* ev)
{
	int x = ev->x()-ui->label_display->x();
	int y = ev->y()-ui->label_display->y()-ui->menubar->size().height();
	if(x>=0 && x<=640 && y>=0 && y<=480)
		display_clic(x, y);
}

MainWindow::~MainWindow()
{
	delete ui;
	delete displayer;
}

/*
 *	###############################################################################################
 *  #                                      Ui Private Slots                                       #
 *	###############################################################################################
 */

void MainWindow::on_pushButton_configure_pressed()
{
	configwindow configW;
	configW.exec();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
	qApp->aboutQt();
}

void MainWindow::on_pushButton_run_clicked()
{
	if(ui->pushButton_run->text() == "Run")
	{
		ui->pushButton_run->setText("Stop");
		ui_disable(true);
		ui->statusbar->showMessage("Running");
	}
	else
	{
		ui->pushButton_run->setText("Run");
		ui_disable(false);
		ui->statusbar->showMessage("Ready");
	}
}

/*
 *	###############################################################################################
 *  #                                     Ui Private Methodes                                     #
 *	###############################################################################################
 */

void MainWindow::display_clic(int x, int y)
{
	qDebug() << "[display_clic] x" << x << "y" << y;
	//zone_painter->drawPoint(x, y);
}

void MainWindow::ui_disable(bool b)
{
	ui->comboBox_tab->setDisabled(b);
	ui->pushButton_calibrate->setDisabled(b);
	ui->pushButton_configure->setDisabled(b);
	ui->pushButton_delete->setDisabled(b);
	ui->pushButton_deleteAll->setDisabled(b);
	ui->pushButton_edit->setDisabled(b);
}
