#include "configwindow.h"
#include "ui_configwindow.h"

ConfigWindow::ConfigWindow(MidiManager &_midi, Configuration &_config, QWidget *parent) :
	QDialog(parent),
	midi(_midi),
	config(_config),
	ui(new Ui::ConfigWindow)
{
	ui->setupUi(this);
	refreshPorts();
}

ConfigWindow::~ConfigWindow()
{
	delete ui;
}

void ConfigWindow::closeEvent()
{
	reject();
}

// ===============================================================================================================================

void ConfigWindow::on_pushButton_cancel_clicked()
{
	reject();
}

void ConfigWindow::on_pushButton_next_clicked()
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
		refreshPorts();
	}
}

void ConfigWindow::refreshPorts()
{
	ui->comboBox_midi->clear();
	for(unsigned int i=0; i<midi.getPortCount(); i++)
		ui->comboBox_midi->addItem(QString(midi.getPortName(i).c_str()));
}

