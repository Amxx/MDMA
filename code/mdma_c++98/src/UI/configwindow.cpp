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
	ui->checkBox_flip_display->setChecked(Configuration::config().flip_display);
	ui->checkBox_flip_zones->setChecked(Configuration::config().flip_zones);
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
#ifdef __WINDOWS_MM__
	bool ok;
	QString name = QInputDialog::getText(this, "[This option is currently disabled for Windows user] Create a new MIDI port", "Port name", QLineEdit::Normal, "MDMA", &ok);
#else //__WINDOWS_MM__
	bool ok;
	QString name = QInputDialog::getText(this, "Create a new MIDI port", "Port name", QLineEdit::Normal, "MDMA", &ok);
	if(ok && name != "")
	{
		midi.createPort(name);
		on_pushButton_midi_refresh_clicked();
	}
#endif //NOT __WINDOWS_MM__
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
	if(!refreshing && index != int(midi.getPortCount()))
	{
		midi.changePort(index);
		on_pushButton_midi_refresh_clicked();
	}
}



void ConfigWindow::on_checkBox_flip_display_clicked()
{
	Configuration::config().flip_display = ui->checkBox_flip_display->isChecked();
}
void ConfigWindow::on_checkBox_flip_zones_clicked()
{
	Configuration::config().flip_zones = ui->checkBox_flip_zones->isChecked();
}



void ConfigWindow::on_pushButton_device_clicked()
{
    Configuration::config().calibration_status = MDMA::NOT_CALIBRATED;

    bool ok = true;
    bool success = false;
    do {
        int i = QInputDialog::getInt(0, "Camera selection", "Please select camera device number\n\t0 for default camera\n\t-1 for Kinect", 0, -1, 2147483647, 1, &ok);
        if(ok)
        {
            success = Configuration::config().camera_manager.setCamera(i);
            QString msg;
            if(i == -1 && !success)
                msg = "Connection with Kinect failed";
            else if(!success)
                msg = "Connection with the camera failed";
            if(!success)
                QMessageBox::information(this, "Connection failed", msg);
        }
    }
    while(ok && !success);

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




void ConfigWindow::on_pushButton_dualdisplay_clicked()
{
	if(Configuration::config().second_display == 0)
	{

		SecondWindow *sw = new SecondWindow(Configuration::config().main);
		sw->show();

		Configuration::config().second_display = sw->ui;
	}
}
