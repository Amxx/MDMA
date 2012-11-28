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
	camera_manager(handtracking, this),
	handtracking(Configuration::config().left_hand, Configuration::config().right_hand),
	midi_manager(),
	zone_manager(this)
{
	Configuration::config().initialize(ui);

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

	switch(Configuration::config().calibration_status)
	{
		case MDMA::NOT_CALIBRATED:
		case MDMA::CALIBRATED:
			if(!Configuration::config().running && x>=0 && x<=640 && y>=0 && y<=480)
				switch(ev->button())
				{
					case Qt::LeftButton:
						zone_manager.set_zone(QPoint(x, y));
						break;
					case Qt::RightButton:
						zone_manager.reset_clic();
						break;
					default:
						break;
				}
			break;

		case MDMA::MASK_DRAW:
			if(!Configuration::config().running)
			{
				x = std::max(0, std::min(x,640));
				y = std::max(0, std::min(y,480));
				switch(ev->button())
				{
					case Qt::LeftButton:
						Configuration::config().user_mask.push_back(QPoint(x, y));
						break;
					case Qt::RightButton:
						if(!Configuration::config().user_mask.empty()) Configuration::config().user_mask.pop_back();
						break;
					default:
						break;
				}
			}
		case MDMA::HANDS_CLOSED:
		case MDMA::HANDS_OPEN:
			break;

	}
}

void MainWindow::closeEvent(QCloseEvent* ev)
{
	if(Configuration::config().changed)
	{
		switch(QMessageBox::question(this, "Changed have been made to the configuration", "Would you like to save changes made to \""+Configuration::config().data.name+"\" before closing ?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save))
		{
			case QMessageBox::Save:
				if(Configuration::config().save())
					ev->accept();
				else
					ev->ignore();
				break;
			case QMessageBox::Discard:
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
	if(!Configuration::config().running)
	{
		Configuration::config().reset();
		setWindowTitle("MDMA - Motion Detection Midi Interface - "+Configuration::config().data.name);
	}
}

void MainWindow::on_actionOpen_triggered()
{
	if(!Configuration::config().running)
	{
		Configuration::config().open();
		setWindowTitle("MDMA - Motion Detection Midi Interface - "+Configuration::config().data.name);
	}
}

void MainWindow::on_actionSave_triggered()
{
	if(!Configuration::config().running)
	{
		Configuration::config().save();
		setWindowTitle("MDMA - Motion Detection Midi Interface - "+Configuration::config().data.name);
	}
}

void MainWindow::on_actionSave_As_triggered()
{
	if(!Configuration::config().running)
	{
		Configuration::config().saveas();
		setWindowTitle("MDMA - Motion Detection Midi Interface - "+Configuration::config().data.name);
	}
}

void MainWindow::on_actionAbout_MDMA_triggered()
{
	if(!Configuration::config().running)
	{

		handtracking.hadriencalib(Configuration::config().current_frame.clone());

	}
}

void MainWindow::on_actionAbout_Qt_triggered()
{
	if(!Configuration::config().running) qApp->aboutQt();
}

void MainWindow::on_pushButton_run_clicked()
{
	if(Configuration::config().calibration_status != MDMA::CALIBRATED)
	{
		QMessageBox::information(this, "Setup isn't configured", "This setup hasn't been configured yet, please run the configuration window before running");
		return;
	}

	if(Configuration::config().running)
	{
		Configuration::config().running = false;
		ui_disable(false);
		ui->pushButton_run->setText("Run");
		ui->statusbar->showMessage("Ready");
	}
	else
	{
		Configuration::config().running = true;
		zone_manager.reset_clic();
		ui_disable(true);
		ui->pushButton_run->setText("Stop");
		ui->statusbar->showMessage("Running");
	}
}

void MainWindow::on_pushButton_calibrate_clicked()
{
	QEventLoop loop;
	zone_manager.reset_clic();
	ui_disable(true, true);

	// -------------------------------------------------------

	Configuration::config().calibration_status = MDMA::MASK_DRAW;

	MaskWindow mask_window(0);
	mask_window.show();
	connect(&mask_window, SIGNAL(finished(int)), &loop, SLOT(quit()));
	loop.exec();

	Configuration::config().freeze = false;

	// -------------------------------------------------------

	if(mask_window.result() == QDialog::Rejected)
	{
		Configuration::config().calibration_status = MDMA::NOT_CALIBRATED;
		ui_disable(false, true);
		ui->pushButton_calibrate->setText("Calibrate");
		return;
	}

	// -------------------------------------------------------

	Configuration::config().calibration_status = MDMA::HANDS_CLOSED;

	HandCloseWindow handclose_window(0);
	handclose_window.show();
	connect(&handclose_window, SIGNAL(finished(int)), &loop, SLOT(quit()));
	loop.exec();

	// -------------------------------------------------------

	if(handclose_window.result() == QDialog::Rejected)
	{
		Configuration::config().calibration_status = MDMA::NOT_CALIBRATED;
		ui_disable(false, true);
		ui->pushButton_calibrate->setText("Calibrate");
		return;
	}

	// -------------------------------------------------------

	Configuration::config().calibration_status = MDMA::HANDS_OPEN;

	HandOpenWindow handopen_window(0);
	handopen_window.show();
	connect(&handopen_window, SIGNAL(finished(int)), &loop, SLOT(quit()));
	loop.exec();

	// -------------------------------------------------------

	if(handopen_window.result() == QDialog::Rejected)
	{
		Configuration::config().calibration_status = MDMA::NOT_CALIBRATED;
		ui_disable(false, true);
		ui->pushButton_calibrate->setText("Calibrate");
		return;
	}

	// -------------------------------------------------------

	try
	{
		handtracking.Calibrate(Configuration::config().close_calib, MDMA::zone_leftclose, MDMA::zone_rightclose,
							   Configuration::config().open_calib, MDMA::zone_leftopen, MDMA::zone_rightopen,
							   Configuration::config().user_mask);
		Configuration::config().calibration_status = MDMA::CALIBRATED;
		ui->pushButton_calibrate->setText("Recalibrate");
		QMessageBox::information(this, "Calibration succesfull", "Calibration succesfull, run is now available");
	}
	catch(std::exception& e)
	{
		Configuration::config().calibration_status = MDMA::NOT_CALIBRATED;
		ui->pushButton_calibrate->setText("Calibrate");
		QMessageBox::critical(this, "Calibration unsuccesfull", "Calibration failled due to lack of contrast");
	}
	// -------------------------------------------------------
	ui_disable(false, true);
}


void MainWindow::on_pushButton_configure_clicked()
{
	ConfigWindow config_window(midi_manager, 0);
	config_window.exec();
	ui_disable(false, true);
}


void MainWindow::on_pushButton_edit_clicked()
{
	if(ui->treeWidget_list->currentItem() != NULL)
	{
		QString name = ui->treeWidget_list->currentItem()->text(0);
		EventZone& evz = Configuration::config().data.zones[name];
		ZoneEditor popup(evz);

		if(popup.exec())
		{
			if(name != evz.name)
			{
				EventZone evz_t(evz);
				Configuration::config().data.zones.insert(evz_t.name, evz_t);
			}

			ui->treeWidget_list->currentItem()->setText(0, evz.name);
			ui->treeWidget_list->currentItem()->setText(1, MDMA::type_to_string(evz.type));
			ui->treeWidget_list->currentItem()->setText(2, QString::number(evz.tab + 1));

			if(name != evz.name) Configuration::config().data.zones.remove(name);

			Configuration::config().changed = true;
		}
	}
}


void MainWindow::on_pushButton_delete_clicked()
{
	if(ui->treeWidget_list->currentItem() != NULL)
	{
		Configuration::config().changed = true;
		Configuration::config().data.zones.erase(Configuration::config().data.zones.find(ui->treeWidget_list->currentItem()->text(0)));
		delete ui->treeWidget_list->currentItem();
	}
}


void MainWindow::on_pushButton_deleteAll_clicked()
{
	if(QMessageBox::question(this, "Delete all", "Are you sure ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
	{
		Configuration::config().changed = true;
		Configuration::config().data.zones.clear();
		ui->treeWidget_list->clear();
	}
}

void MainWindow::on_comboBox_tab_currentIndexChanged(int index)
{
	Configuration::config().changed = true;
	Configuration::config().data.current_tab = index;
}

/*
 *	###############################################################################################
 *  #                                     Ui Private Methodes                                     #
 *	###############################################################################################
 */

void MainWindow::ui_disable(bool b, bool all)
{
	ui->menubar->setDisabled(b);
	ui->comboBox_tab->setDisabled(b);
	ui->pushButton_calibrate->setDisabled(b);
	ui->pushButton_configure->setDisabled(b);
	ui->pushButton_delete->setDisabled(b);
	ui->pushButton_deleteAll->setDisabled(b);
	ui->pushButton_edit->setDisabled(b);
	if(all) ui->pushButton_run->setDisabled(b);
}

