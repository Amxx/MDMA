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

	config = new configuration(ui);
	cameraDisplayer = new cvCameraDisplay(config, this);
	zoneDisplayer = new zoneDisplay(config, this);

	ui->statusbar->showMessage("Ready");
}

void MainWindow::mousePressEvent(QMouseEvent* ev)
{
	switch(ev->button())
	{
		case Qt::LeftButton:
		{
			int x = ev->x()-ui->label_camera->x();
			int y = ev->y()-ui->label_camera->y()-ui->menubar->size().height();
			if(x>=0 && x<=640 && y>=0 && y<=480)
			{
				zoneDisplayer->clic(QPoint(x, y));
			}
			break;
		}
		default:
			break;
	}
}

MainWindow::~MainWindow()
{
	delete ui;
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


void MainWindow::on_pushButton_edit_clicked()
{
	if(ui->treeWidget_list->currentItem() != NULL)
	{
		QString name = ui->treeWidget_list->currentItem()->text(0);
		eventZone evz = config->zones[name];
		zoneEditor popup(&evz);

		if(popup.exec())
		{
//			delete config->zones.find(name);
//			config->zones.insert(evz.name, evz);

//			ui->treeWidget_list->currentItem()->setText(0, evz.name);
//			ui->treeWidget_list->currentItem()->setText(1, MDMA::type_to_string(evz.type));
//			ui->treeWidget_list->currentItem()->setText(2, QString::number(evz.tab));
		}
	}
}


void MainWindow::on_pushButton_delete_clicked()
{
	if(ui->treeWidget_list->currentItem() != NULL)
	{
		config->zones.erase(config->zones.find(ui->treeWidget_list->currentItem()->text(0)));
		delete ui->treeWidget_list->currentItem();
	}
}


void MainWindow::on_pushButton_deleteAll_clicked()
{
	if(QMessageBox::question(this, "Delete all", "Are you sure ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
	{
		ui->treeWidget_list->clear();
		config->zones.clear();
	}
}


/*
 *	###############################################################################################
 *  #                                     Ui Private Methodes                                     #
 *	###############################################################################################
 */

void MainWindow::ui_disable(bool b)
{
	ui->comboBox_tab->setDisabled(b);
	ui->pushButton_calibrate->setDisabled(b);
	ui->pushButton_configure->setDisabled(b);
	ui->pushButton_delete->setDisabled(b);
	ui->pushButton_deleteAll->setDisabled(b);
	ui->pushButton_edit->setDisabled(b);
}
