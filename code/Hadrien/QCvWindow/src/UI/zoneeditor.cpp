#include "zoneeditor.h"
#include "ui_zoneeditor.h"

zoneEditor::zoneEditor(eventZone& _evz, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::zoneEditor),
	evz(_evz)
{
	ui->setupUi(this);

	ui->lineEdit_name->setText(evz.name);
	ui->lineEdit_x1->setText(QString::number(evz.P1.x()));
	ui->lineEdit_y1->setText(QString::number(evz.P1.y()));
	ui->lineEdit_x2->setText(QString::number(evz.P2.x()));
	ui->lineEdit_y2->setText(QString::number(evz.P2.y()));
	ui->comboBox_tab->setCurrentIndex(evz.tab);

	ui->tabWidget_type->setCurrentIndex(evz.type);

	ui->comboBox_axex_0->setCurrentIndex(MDMA::is_midi(evz.active[MDMA::EVENT_X])?evz.active[MDMA::EVENT_X]:MDMA::GOTO_TAB1);
	ui->spinBox_axex_1->setValue(evz.signal[MDMA::EVENT_X][0] & 15);
	ui->spinBox_axex_2->setValue(evz.signal[MDMA::EVENT_X][1] & 127);
	ui->comboBox_axey_0->setCurrentIndex(MDMA::is_midi(evz.active[MDMA::EVENT_Y])?evz.active[MDMA::EVENT_Y]:MDMA::GOTO_TAB1);
	ui->spinBox_axey_1->setValue(evz.signal[MDMA::EVENT_Y][0] & 15);
	ui->spinBox_axey_2->setValue(evz.signal[MDMA::EVENT_Y][1] & 127);

	ui->comboBox_enter->setCurrentIndex(evz.active[MDMA::ENTER]);
	ui->spinBox_enter_1->setValue(evz.signal[MDMA::ENTER][0] & 15);
	ui->spinBox_enter_2->setValue(evz.signal[MDMA::ENTER][1] & 127);
	ui->spinBox_enter_3->setValue(evz.signal[MDMA::ENTER][2] & 127);
	ui->comboBox_exit->setCurrentIndex(evz.active[MDMA::EXIT]);
	ui->spinBox_exit_1->setValue(evz.signal[MDMA::EXIT][0] & 15);
	ui->spinBox_exit_2->setValue(evz.signal[MDMA::EXIT][1] & 127);
	ui->spinBox_exit_3->setValue(evz.signal[MDMA::EXIT][2] & 127);
	ui->comboBox_open->setCurrentIndex(evz.active[MDMA::OPEN]);
	ui->spinBox_open_1->setValue(evz.signal[MDMA::OPEN][0] & 15);
	ui->spinBox_open_2->setValue(evz.signal[MDMA::OPEN][1] & 127);
	ui->spinBox_open_3->setValue(evz.signal[MDMA::OPEN][2] & 127);
	ui->comboBox_close->setCurrentIndex(evz.active[MDMA::CLOSE]);
	ui->spinBox_close_1->setValue(evz.signal[MDMA::CLOSE][0] & 15);
	ui->spinBox_close_2->setValue(evz.signal[MDMA::CLOSE][1] & 127);
	ui->spinBox_close_3->setValue(evz.signal[MDMA::CLOSE][2] & 127);
	ui->comboBox_shock->setCurrentIndex(evz.active[MDMA::SHOCK]);
	ui->spinBox_shock_1->setValue(evz.signal[MDMA::SHOCK][0] & 15);
	ui->spinBox_shock_2->setValue(evz.signal[MDMA::SHOCK][1] & 127);
	ui->spinBox_shock_3->setValue(evz.signal[MDMA::SHOCK][2] & 127);
}

zoneEditor::~zoneEditor()
{
	delete ui;
}

// ========================================================================================

void zoneEditor::on_buttonBox_accepted()
{

	evz.name = ui->lineEdit_name->text();
	evz.P1 = QPoint(ui->lineEdit_x1->text().toInt(), ui->lineEdit_y1->text().toInt());
	evz.P2 = QPoint(ui->lineEdit_x2->text().toInt(), ui->lineEdit_y2->text().toInt());
	evz.tab = ui->comboBox_tab->currentIndex();

	evz.type = MDMA::type(ui->tabWidget_type->currentIndex());

	evz.active[MDMA::EVENT_X] = (MDMA::active) (ui->comboBox_axex_0->currentIndex());
	if(!MDMA::is_midi(evz.active[MDMA::EVENT_X])) evz.active[MDMA::EVENT_X] = MDMA::NOTHING;
	evz.signal[MDMA::EVENT_X][0] = ((MDMA::is_midi(evz.active[MDMA::EVENT_X]))?evz.active[MDMA::EVENT_X]<<4:0) | ui->spinBox_axex_1->value();
	evz.signal[MDMA::EVENT_X][1] = 128 | ui->spinBox_axex_2->value();
	evz.active[MDMA::EVENT_Y] = (MDMA::active) (ui->comboBox_axey_0->currentIndex());
	if(!MDMA::is_midi(evz.active[MDMA::EVENT_Y])) evz.active[MDMA::EVENT_Y] = MDMA::NOTHING;
	evz.signal[MDMA::EVENT_Y][0] = ((MDMA::is_midi(evz.active[MDMA::EVENT_Y]))?evz.active[MDMA::EVENT_Y]<<4:0) | ui->spinBox_axey_1->value();
	evz.signal[MDMA::EVENT_Y][1] = 128 | ui->spinBox_axey_2->value();

	evz.active[MDMA::ENTER] = (MDMA::active) ui->comboBox_enter->currentIndex();
	evz.signal[MDMA::ENTER][0] = ((MDMA::is_midi(evz.active[MDMA::ENTER]))?evz.active[MDMA::ENTER]<<4:0) | ui->spinBox_enter_1->value();
	evz.signal[MDMA::ENTER][1] = 128 | ui->spinBox_enter_2->value();
	evz.signal[MDMA::ENTER][2] = 128 | ui->spinBox_enter_3->value();
	evz.active[MDMA::EXIT] = (MDMA::active) ui->comboBox_exit->currentIndex();
	evz.signal[MDMA::EXIT][0] = ((MDMA::is_midi(evz.active[MDMA::EXIT]))?evz.active[MDMA::EXIT]<<4:0) | ui->spinBox_exit_1->value();
	evz.signal[MDMA::EXIT][1] = 128 | ui->spinBox_exit_2->value();
	evz.signal[MDMA::EXIT][2] = 128 | ui->spinBox_exit_3->value();
	evz.active[MDMA::OPEN] = (MDMA::active) ui->comboBox_open->currentIndex();
	evz.signal[MDMA::OPEN][0] = ((MDMA::is_midi(evz.active[MDMA::OPEN]))?evz.active[MDMA::OPEN]<<4:0) | ui->spinBox_open_1->value();
	evz.signal[MDMA::OPEN][1] = 128 | ui->spinBox_open_2->value();
	evz.signal[MDMA::OPEN][2] = 128 | ui->spinBox_open_3->value();
	evz.active[MDMA::CLOSE] = (MDMA::active) ui->comboBox_close->currentIndex();
	evz.signal[MDMA::CLOSE][0] = ((MDMA::is_midi(evz.active[MDMA::CLOSE]))?evz.active[MDMA::CLOSE]<<4:0) | ui->spinBox_close_1->value();
	evz.signal[MDMA::CLOSE][1] = 128 | ui->spinBox_close_2->value();
	evz.signal[MDMA::CLOSE][2] = 128 | ui->spinBox_close_3->value();
	evz.active[MDMA::SHOCK] = (MDMA::active) ui->comboBox_shock->currentIndex();
	evz.signal[MDMA::SHOCK][0] = ((MDMA::is_midi(evz.active[MDMA::SHOCK]))?evz.active[MDMA::SHOCK]<<4:0) | ui->spinBox_shock_1->value();
	evz.signal[MDMA::SHOCK][1] = 128 | ui->spinBox_shock_2->value();
	evz.signal[MDMA::SHOCK][2] = 128 | ui->spinBox_shock_3->value();

	accept();
}

// ========================================================================================


void zoneEditor::on_comboBox_axex_0_currentIndexChanged(int index)
{
	if(MDMA::is_midi((MDMA::active) index))
	{
		ui->spinBox_axex_1->setDisabled(false);
		ui->spinBox_axex_2->setDisabled(false);
	}
	else
	{
		ui->spinBox_axex_1->setDisabled(true);
		ui->spinBox_axex_2->setDisabled(true);
	}
}

void zoneEditor::on_comboBox_axey_0_currentIndexChanged(int index)
{
	if(MDMA::is_midi((MDMA::active) index))
	{
		ui->spinBox_axey_1->setDisabled(false);
		ui->spinBox_axey_2->setDisabled(false);
	}
	else
	{
		ui->spinBox_axey_1->setDisabled(true);
		ui->spinBox_axey_2->setDisabled(true);
	}
}

// ========================================================================================

void zoneEditor::on_comboBox_enter_currentIndexChanged(int index)
{
	if(MDMA::is_midi((MDMA::active) index))
	{
		ui->spinBox_enter_1->setDisabled(false);
		ui->spinBox_enter_2->setDisabled(false);
		ui->spinBox_enter_3->setDisabled(false);
	}
	else
	{
		ui->spinBox_enter_1->setDisabled(true);
		ui->spinBox_enter_2->setDisabled(true);
		ui->spinBox_enter_3->setDisabled(true);
	}
}

void zoneEditor::on_comboBox_exit_currentIndexChanged(int index)
{
	if(MDMA::is_midi((MDMA::active) index))
	{
		ui->spinBox_exit_1->setDisabled(false);
		ui->spinBox_exit_2->setDisabled(false);
		ui->spinBox_exit_3->setDisabled(false);
	}
	else
	{
		ui->spinBox_exit_1->setDisabled(true);
		ui->spinBox_exit_2->setDisabled(true);
		ui->spinBox_exit_3->setDisabled(true);
	}
}

void zoneEditor::on_comboBox_open_currentIndexChanged(int index)
{
	if(MDMA::is_midi((MDMA::active) index))
	{
		ui->spinBox_open_1->setDisabled(false);
		ui->spinBox_open_2->setDisabled(false);
		ui->spinBox_open_3->setDisabled(false);
	}
	else
	{
		ui->spinBox_open_1->setDisabled(true);
		ui->spinBox_open_2->setDisabled(true);
		ui->spinBox_open_3->setDisabled(true);
	}
}

void zoneEditor::on_comboBox_close_currentIndexChanged(int index)
{
	if(MDMA::is_midi((MDMA::active) index))
	{
		ui->spinBox_close_1->setDisabled(false);
		ui->spinBox_close_2->setDisabled(false);
		ui->spinBox_close_3->setDisabled(false);
	}
	else
	{
		ui->spinBox_close_1->setDisabled(true);
		ui->spinBox_close_2->setDisabled(true);
		ui->spinBox_close_3->setDisabled(true);
	}
}

void zoneEditor::on_comboBox_shock_currentIndexChanged(int index)
{
	if(MDMA::is_midi((MDMA::active) index))
	{
		ui->spinBox_shock_1->setDisabled(false);
		ui->spinBox_shock_2->setDisabled(false);
		ui->spinBox_shock_3->setDisabled(false);
	}
	else
	{
		ui->spinBox_shock_1->setDisabled(true);
		ui->spinBox_shock_2->setDisabled(true);
		ui->spinBox_shock_3->setDisabled(true);
	}
}

