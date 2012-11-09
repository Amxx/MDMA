#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 *	###############################################################################################
 *  #                                        Constructors                                         #
 *	###############################################################################################
 */

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	config(ui, this),
	camera_manager(config, this),
	zone_manager(config, this)
{
	ui->setupUi(this);
	ui->statusbar->showMessage("Ready");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent* ev)
{
	int x = ev->x()-ui->label_camera->x();
	int y = ev->y()-ui->label_camera->y()-ui->menubar->size().height();

	if(!config.running && x>=0 && x<=640 && y>=0 && y<=480)
		switch(ev->button())
		{
			case Qt::LeftButton:
				zone_manager.clic(QPoint(x, y));
				break;
			case Qt::RightButton:
				zone_manager.reset_clic();
				break;
			default:
				break;
		}
}

void MainWindow::closeEvent(QCloseEvent* ev)
{
	if(config.changed)
	{
		switch(QMessageBox::question(this, "Changed have been made to the configuration", "Would you like to save changes made to \""+config.name+"\" before closing ?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel))
		{
			case QMessageBox::Yes:
				if(config.save())
					ev->accept();
				else
					ev->ignore();
				break;
			case QMessageBox::No:
				ev->accept();
				break;
			default:
				ev->ignore();
				break;
		}
	}
	else
		ev->accept();
}

/*
 *	###############################################################################################
 *  #                                      Ui Private Slots                                       #
 *	###############################################################################################
 */

void MainWindow::on_actionNew_triggered()
{
	if(!config.running)
	{
		config.reset();
		setWindowTitle("MDMA - Motion Detection Midi Interface - "+config.name);
	}
}

void MainWindow::on_actionOpen_triggered()
{
	if(!config.running)
	{
		config.open();
		setWindowTitle("MDMA - Motion Detection Midi Interface - "+config.name);
	}
}

void MainWindow::on_actionSave_triggered()
{
	if(!config.running)
	{
		config.save();
		setWindowTitle("MDMA - Motion Detection Midi Interface - "+config.name);
	}
}

void MainWindow::on_actionSave_As_triggered()
{
	if(!config.running)
	{
		config.saveas();
		setWindowTitle("MDMA - Motion Detection Midi Interface - "+config.name);
	}
}

void MainWindow::on_actionAbout_MDMA_triggered()
{
	if(!config.running)
	{
	}
}

void MainWindow::on_actionAbout_Qt_triggered()
{
	if(!config.running)
	{
		qApp->aboutQt();
	}
}

void MainWindow::on_pushButton_run_clicked()
{
	if(config.running)
	{
		config.running = false;
		ui_disable(false);
		ui->pushButton_run->setText("Run");
		ui->statusbar->showMessage("Ready");
	}
	else
	{
		config.running = true;
		zone_manager.reset_clic();
		ui_disable(true);
		ui->pushButton_run->setText("Stop");
		ui->statusbar->showMessage("Running");
	}
}

void MainWindow::on_pushButton_configure_pressed()
{
	configwindow configW;
	configW.exec();
}

void MainWindow::on_pushButton_edit_clicked()
{
	if(ui->treeWidget_list->currentItem() != NULL)
	{
		QString name = ui->treeWidget_list->currentItem()->text(0);
		eventZone& evz = config.zones[name];
		zoneEditor popup(evz);

		if(popup.exec())
		{
			if(name != evz.name)
			{
				eventZone evz_t(config.zones[name]);
				config.zones.remove(name);
				config.zones.insert(evz_t.name, evz_t);
			}

			ui->treeWidget_list->currentItem()->setText(0, evz.name);
			ui->treeWidget_list->currentItem()->setText(1, MDMA::type_to_string(evz.type));
			ui->treeWidget_list->currentItem()->setText(2, QString::number(evz.tab + 1));

			config.changed = true;
		}
	}
}


void MainWindow::on_pushButton_delete_clicked()
{
	if(ui->treeWidget_list->currentItem() != NULL)
	{
		config.zones.erase(config.zones.find(ui->treeWidget_list->currentItem()->text(0)));
		delete ui->treeWidget_list->currentItem();
		config.changed = true;
	}
}


void MainWindow::on_pushButton_deleteAll_clicked()
{
	if(QMessageBox::question(this, "Delete all", "Are you sure ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
	{
		ui->treeWidget_list->clear();
		config.zones.clear();
		config.changed = true;
	}
}

void MainWindow::on_comboBox_tab_currentIndexChanged(int index)
{
	config.current_tab = index;
	config.changed = true;
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

