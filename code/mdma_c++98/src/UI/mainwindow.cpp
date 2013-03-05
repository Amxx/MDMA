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
    event_manager(this),
    midi_manager(),
	zone_manager(this)
{
	ui->setupUi(this);
	ui->statusbar->showMessage("Ready");
	show();

	Configuration::config().initialize(this, ui);
    QObject::connect(&Configuration::config().camera_manager, SIGNAL(track_updated()), &event_manager, SLOT(detection()));
	QObject::connect(&event_manager, SIGNAL(sendMidi(MDMA::signal)), &midi_manager, SLOT(sendMessage(MDMA::signal)));
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
		QMessageBox::information(0, "Not available", "Feature soon to be added");
	}
}

void MainWindow::on_actionAbout_Qt_triggered()
{
	if(!Configuration::config().running) qApp->aboutQt();
}

void MainWindow::on_pushButton_run_clicked()
{

	if(Configuration::config().calibration_status != MDMA::CALIBRATED && Configuration::config().track_hand)
	{
		QMessageBox::information(this, "Calibration requested", "Calibration is needed to run image tracking, please run the calibration window before running");
		return;
	}
	if(!Configuration::config().track_hand && !Configuration::config().track_mouse)
	{
		QMessageBox::information(this, "Tracking disabled", "No tracking is enable at this time, please enable some tracking in the configuration window");
		return;
	}


	if(Configuration::config().running)
	{
		Configuration::config().running = false;
		ui_disable(false);
		ui->pushButton_run->setText("Run");
		ui->statusbar->showMessage("Ready");

        //for(EventZone& evz : Configuration::config().data.zones)
        for(QMap<QString, EventZone>::Iterator it = Configuration::config().data.zones.begin() ; it != Configuration::config().data.zones.end() ; ++it)
        {
            it->is_active[0] = false;
            it->is_active[1] = false;
            it->is_active[2] = false;
            it->emph_display = false;
		}
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
    if(!Configuration::config().camera_manager.canDoCalibration())
        return;
    QEventLoop loop;
	zone_manager.reset_clic();
	ui_disable(true, true);

	MDMA::calibration old_calib = Configuration::config().calibration_status;

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
		//Configuration::config().calibration_status = MDMA::NOT_CALIBRATED;
		Configuration::config().calibration_status = old_calib;

		ui_disable(false, true);
		//ui->pushButton_calibrate->setText("Calibrate");
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
        Configuration::config().handtracking.Calibrate(Configuration::config().close_calib, MDMA::zone_leftclose, MDMA::zone_rightclose,
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
		QMessageBox::critical(this, "Calibration unsuccesfull", "Calibration failed due to lack of contrast");
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

			EventZone evz_t(evz);
			Configuration::config().data.zones.remove(name);

			if(Configuration::config().data.zones.find(evz_t.name) != Configuration::config().data.zones.end())
			{
				int i = 0;
				while(Configuration::config().data.zones.find(evz_t.name+"_"+QString::number(i)) != Configuration::config().data.zones.end()) i++;
				evz_t.name+=("_"+QString::number(i));
			}
			Configuration::config().data.zones.insert(evz_t.name, evz_t);

			ui->treeWidget_list->currentItem()->setText(0, evz_t.name);
			ui->treeWidget_list->currentItem()->setText(1, MDMA::type_to_string(evz_t.type));
			ui->treeWidget_list->currentItem()->setText(2, QString::number(evz_t.tab + 1));

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
	ui->pushButton_calibrate->setDisabled(b || !Configuration::config().track_hand);
	ui->pushButton_configure->setDisabled(b);
	ui->pushButton_delete->setDisabled(b);
	ui->pushButton_deleteAll->setDisabled(b);
	ui->pushButton_edit->setDisabled(b);
	if(all) ui->pushButton_run->setDisabled(b);
}

