#include "configwindow.h"
#include "ui_configwindow.h"

ConfigWindow::ConfigWindow(MidiManager &_midi, QWidget *parent) :
	QDialog(parent),
	midi(_midi),
	ui(new Ui::ConfigWindow)
{
	ui->setupUi(this);
	ui->checkBox_flip->setChecked(Configuration::config().flip);
	refreshPorts();
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
		refreshPorts();
	}
}

void ConfigWindow::refreshPorts()
{
	ui->comboBox_midi->clear();
	for(unsigned int i=0; i<midi.getPortCount(); i++)
		ui->comboBox_midi->addItem(QString(midi.getPortName(i).c_str()));
}


void ConfigWindow::on_checkBox_flip_clicked()
{
	Configuration::config().flip = ui->checkBox_flip->isChecked();
}


