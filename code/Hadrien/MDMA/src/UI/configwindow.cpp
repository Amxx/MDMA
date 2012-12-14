#include "configwindow.h"
#include "ui_configwindow.h"
#include "ui_mainwindow.h"

ConfigWindow::ConfigWindow(MidiManager &_midi, QWidget *parent) :
	QDialog(parent),
	refreshing(false),
	midi(_midi),
	ui(new Ui::ConfigWindow)
{
	ui->setupUi(this);
	ui->checkBox_flip->setChecked(Configuration::config().flip);
	ui->pushButton_hand_track->setText(Configuration::config().track_hand?"Disable hand tracking":"Enable hand tracking");
	ui->pushButton_mouse_track->setText(Configuration::config().track_mouse?"Disable mouse tracking":"Enable mouse tracking");

	on_pushButton_midi_refresh_clicked();
}

ConfigWindow::~ConfigWindow()
{
	delete ui;
}

void ConfigWindow::closeEvent()
{
	accept();
}

// ===============================================================================================================================

void ConfigWindow::on_pushButton_ok_clicked()
{
	accept();
}

// ===============================================================================================================================

void ConfigWindow::on_pushButton_midi_clicked()
{
	bool ok;
	QString name = QInputDialog::getText(this, "Create a new midi port", "Port name", QLineEdit::Normal, "MDMA", &ok);
	if(ok && name != "")
	{
		midi.createPort(name);
		on_pushButton_midi_refresh_clicked();
	}
}


void ConfigWindow::on_pushButton_midi_refresh_clicked()
{
	refreshing = true;

	ui->comboBox_midi->clear();
	unsigned int nbPorts = midi.getPortCount();
	for(unsigned int i=0; i<nbPorts; i++)
		ui->comboBox_midi->addItem(QString(midi.getPortName(i).c_str()));

	if(midi.current_port != -1) {
		ui->comboBox_midi->setCurrentIndex(midi.current_port);
	}
	else {
		ui->comboBox_midi->addItem(QString(midi.MIDIPortName.c_str()));
		ui->comboBox_midi->setCurrentIndex(nbPorts);
	}

	refreshing = false;
}

void ConfigWindow::on_comboBox_midi_currentIndexChanged(int index)
{
	if(!refreshing && index != midi.getPortCount())
	{
		midi.changePort(index);
		on_pushButton_midi_refresh_clicked();
	}
}





void ConfigWindow::on_checkBox_flip_clicked()
{
	Configuration::config().flip = ui->checkBox_flip->isChecked();
}




void ConfigWindow::on_pushButton_device_clicked()
{
	Configuration::config().setCamera(true);

	Configuration::config().calibration_status = MDMA::NOT_CALIBRATED;
	Configuration::config().ui->pushButton_calibrate->setText("Calibrate");
}

void ConfigWindow::on_pushButton_hand_track_clicked()
{
	if(Configuration::config().track_hand)
	{
		Configuration::config().track_hand = false;
		ui->pushButton_hand_track->setText("Enable hand tracking");
		Configuration::config().ui->pushButton_calibrate->setDisabled(true);
	}
	else
	{
		Configuration::config().track_hand = true;
		ui->pushButton_hand_track->setText("Disable hand tracking");
		Configuration::config().ui->pushButton_calibrate->setDisabled(false);
	}
}

void ConfigWindow::on_pushButton_mouse_track_clicked()
{
	if(Configuration::config().track_mouse)
	{
		Configuration::config().track_mouse = false;
		ui->pushButton_mouse_track->setText("Enable mouse tracking");
	}
	else
	{
		Configuration::config().track_mouse = true;
		ui->pushButton_mouse_track->setText("Disable mouse tracking");
	}
}

