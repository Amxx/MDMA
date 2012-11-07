#include "zoneeditor.h"
#include "ui_zoneeditor.h"

zoneEditor::zoneEditor(eventZone* _evz, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::zoneEditor),
	evz(_evz)
{
	ui->setupUi(this);

	ui->lineEdit_name->setText(evz->name);

	ui->lineEdit_x1->setText(QString::number(evz->P1.x()));
	ui->lineEdit_y1->setText(QString::number(evz->P1.y()));
	ui->lineEdit_x2->setText(QString::number(evz->P2.x()));
	ui->lineEdit_y2->setText(QString::number(evz->P2.y()));

	ui->comboBox_tab->setCurrentIndex(evz->tab);

	ui->tabWidget_type->setCurrentIndex(evz->type);

	ui->comboBox_axes->setCurrentIndex(evz->axes);
	on_comboBox_axes_currentIndexChanged(evz->axes);
}

zoneEditor::~zoneEditor()
{
	delete ui;
}





void zoneEditor::on_comboBox_axes_currentIndexChanged(int index)
{
	switch(index)
	{
		case MDMA::AXE_X:
			ui->lineEdit_axex_1->setDisabled(false);
			ui->lineEdit_axex_2->setDisabled(false);
			ui->lineEdit_axey_1->setDisabled(true);
			ui->lineEdit_axey_2->setDisabled(true);
			break;
		case MDMA::AXE_Y:
			ui->lineEdit_axex_1->setDisabled(true);
			ui->lineEdit_axex_2->setDisabled(true);
			ui->lineEdit_axey_1->setDisabled(false);
			ui->lineEdit_axey_2->setDisabled(false);
			break;
		case MDMA::AXE_XY:
			ui->lineEdit_axex_1->setDisabled(false);
			ui->lineEdit_axex_2->setDisabled(false);
			ui->lineEdit_axey_1->setDisabled(false);
			ui->lineEdit_axey_2->setDisabled(false);
			break;

	}
}

void zoneEditor::on_buttonBox_accepted()
{

	evz->name = ui->lineEdit_name->text();
	evz->P1 = QPoint(ui->lineEdit_x1->text().toInt(), ui->lineEdit_y1->text().toInt());
	evz->P2 = QPoint(ui->lineEdit_x2->text().toInt(), ui->lineEdit_y2->text().toInt());
	evz->tab = ui->comboBox_tab->currentIndex();

	evz->type = MDMA::type(ui->tabWidget_type->currentIndex());
	evz->axes = MDMA::axes(ui->comboBox_axes->currentIndex());

//	char events[7][3];

	accept();
}
