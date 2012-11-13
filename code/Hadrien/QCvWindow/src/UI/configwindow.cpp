#include "configwindow.h"
#include "ui_configwindow.h"

ConfigWindow::ConfigWindow(midiManager &_midi, configuration &_config, QWidget *parent) :
	midi(_midi),
	config(_config),
	QDialog(parent),
	ui(new Ui::ConfigWindow)
{
	ui->setupUi(this);
	refreshPorts();
}

ConfigWindow::~ConfigWindow()
{
	delete ui;
}


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
	qDebug() << midi.getPortCount() << "midi port available";
	for(int i=0; i<midi.getPortCount(); i++)
	{
		ui->comboBox_midi->addItem(QString(midi.getPortName(i).c_str()));
		qDebug() << "\t" << i << " : " << midi.getPortName(i).c_str();
	}
}
