#include "zoneeditor.h"
#include "ui_zoneeditor.h"

ZoneEditor::ZoneEditor(EventZone& _evz, QWidget *parent) :
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
	ui->spinBox_axex_1->setValue(evz.signal[MDMA::EVENT_X][0]);
	ui->spinBox_axex_2->setValue(evz.signal[MDMA::EVENT_X][1]);
	ui->spinBox_axex_3->setValue(evz.signal[MDMA::EVENT_X][2]);
	ui->comboBox_axey_0->setCurrentIndex(MDMA::is_midi(evz.active[MDMA::EVENT_Y])?evz.active[MDMA::EVENT_Y]:MDMA::GOTO_TAB1);
	ui->spinBox_axey_1->setValue(evz.signal[MDMA::EVENT_Y][0]);
	ui->spinBox_axey_2->setValue(evz.signal[MDMA::EVENT_Y][1]);
	ui->spinBox_axey_3->setValue(evz.signal[MDMA::EVENT_Y][2]);

	ui->comboBox_enter->setCurrentIndex(evz.active[MDMA::ENTER]);
	ui->spinBox_enter_1->setValue(evz.signal[MDMA::ENTER][0]);
	ui->spinBox_enter_2->setValue(evz.signal[MDMA::ENTER][1]);
	ui->spinBox_enter_3->setValue(evz.signal[MDMA::ENTER][2]);
	ui->comboBox_exit->setCurrentIndex(evz.active[MDMA::EXIT]);
	ui->spinBox_exit_1->setValue(evz.signal[MDMA::EXIT][0]);
	ui->spinBox_exit_2->setValue(evz.signal[MDMA::EXIT][1]);
	ui->spinBox_exit_3->setValue(evz.signal[MDMA::EXIT][2]);
	ui->comboBox_open->setCurrentIndex(evz.active[MDMA::OPEN]);
	ui->spinBox_open_1->setValue(evz.signal[MDMA::OPEN][0]);
	ui->spinBox_open_2->setValue(evz.signal[MDMA::OPEN][1]);
	ui->spinBox_open_3->setValue(evz.signal[MDMA::OPEN][2]);
	ui->comboBox_close->setCurrentIndex(evz.active[MDMA::CLOSE]);
	ui->spinBox_close_1->setValue(evz.signal[MDMA::CLOSE][0]);
	ui->spinBox_close_2->setValue(evz.signal[MDMA::CLOSE][1]);
	ui->spinBox_close_3->setValue(evz.signal[MDMA::CLOSE][2]);
	ui->comboBox_shock->setCurrentIndex(evz.active[MDMA::SHOCK]);
	ui->spinBox_shock_1->setValue(evz.signal[MDMA::SHOCK][0]);
	ui->spinBox_shock_2->setValue(evz.signal[MDMA::SHOCK][1]);
	ui->spinBox_shock_3->setValue(evz.signal[MDMA::SHOCK][2]);

	ui->comboBox_in->setCurrentIndex(evz.active[MDMA::IN]);
	ui->spinBox_in_1->setValue(evz.signal[MDMA::IN][0]);
	ui->spinBox_in_2->setValue(evz.signal[MDMA::IN][1]);
	ui->spinBox_in_3->setValue(evz.signal[MDMA::IN][2]);
	ui->comboBox_out->setCurrentIndex(evz.active[MDMA::OUT]);
	ui->spinBox_out_1->setValue(evz.signal[MDMA::OUT][0]);
	ui->spinBox_out_2->setValue(evz.signal[MDMA::OUT][1]);
	ui->spinBox_out_3->setValue(evz.signal[MDMA::OUT][2]);
}

ZoneEditor::~ZoneEditor()
{
	delete ui;
}

// ========================================================================================

void ZoneEditor::on_buttonBox_accepted()
{

	evz.name = ui->lineEdit_name->text();
	evz.P1 = QPoint(ui->lineEdit_x1->text().toInt(), ui->lineEdit_y1->text().toInt());
	evz.P2 = QPoint(ui->lineEdit_x2->text().toInt(), ui->lineEdit_y2->text().toInt());
	evz.tab = ui->comboBox_tab->currentIndex();

	evz.type = MDMA::type(ui->tabWidget_type->currentIndex());

	evz.active[MDMA::EVENT_X] = (MDMA::active) (ui->comboBox_axex_0->currentIndex());
	if(!MDMA::is_midi(evz.active[MDMA::EVENT_X])) evz.active[MDMA::EVENT_X] = MDMA::NOTHING;
	evz.signal[MDMA::EVENT_X][0] = ui->spinBox_axex_1->value();
	evz.signal[MDMA::EVENT_X][1] = ui->spinBox_axex_2->value();
	evz.signal[MDMA::EVENT_X][2] = ui->spinBox_axex_3->value();
	evz.active[MDMA::EVENT_Y] = (MDMA::active) (ui->comboBox_axey_0->currentIndex());
	if(!MDMA::is_midi(evz.active[MDMA::EVENT_Y])) evz.active[MDMA::EVENT_Y] = MDMA::NOTHING;
	evz.signal[MDMA::EVENT_Y][0] = ui->spinBox_axey_1->value();
	evz.signal[MDMA::EVENT_Y][1] = ui->spinBox_axey_2->value();
	evz.signal[MDMA::EVENT_Y][2] = ui->spinBox_axey_3->value();

	evz.active[MDMA::ENTER] = (MDMA::active) ui->comboBox_enter->currentIndex();
	evz.signal[MDMA::ENTER][0] = ui->spinBox_enter_1->value();
	evz.signal[MDMA::ENTER][1] = ui->spinBox_enter_2->value();
	evz.signal[MDMA::ENTER][2] = ui->spinBox_enter_3->value();
	evz.active[MDMA::EXIT] = (MDMA::active) ui->comboBox_exit->currentIndex();
	evz.signal[MDMA::EXIT][0] = ui->spinBox_exit_1->value();
	evz.signal[MDMA::EXIT][1] = ui->spinBox_exit_2->value();
	evz.signal[MDMA::EXIT][2] = ui->spinBox_exit_3->value();
	evz.active[MDMA::OPEN] = (MDMA::active) ui->comboBox_open->currentIndex();
	evz.signal[MDMA::OPEN][0] = ui->spinBox_open_1->value();
	evz.signal[MDMA::OPEN][1] = ui->spinBox_open_2->value();
	evz.signal[MDMA::OPEN][2] = ui->spinBox_open_3->value();
	evz.active[MDMA::CLOSE] = (MDMA::active) ui->comboBox_close->currentIndex();
	evz.signal[MDMA::CLOSE][0] = ui->spinBox_close_1->value();
	evz.signal[MDMA::CLOSE][1] = ui->spinBox_close_2->value();
	evz.signal[MDMA::CLOSE][2] = ui->spinBox_close_3->value();
	evz.active[MDMA::SHOCK] = (MDMA::active) ui->comboBox_shock->currentIndex();
	evz.signal[MDMA::SHOCK][0] = ui->spinBox_shock_1->value();
	evz.signal[MDMA::SHOCK][1] = ui->spinBox_shock_2->value();
	evz.signal[MDMA::SHOCK][2] = ui->spinBox_shock_3->value();

	evz.active[MDMA::IN] = (MDMA::active) ui->comboBox_in->currentIndex();
	evz.signal[MDMA::IN][0] = ui->spinBox_in_1->value();
	evz.signal[MDMA::IN][1] = ui->spinBox_in_2->value();
	evz.signal[MDMA::IN][2] = ui->spinBox_in_3->value();
	evz.active[MDMA::OUT] = (MDMA::active) ui->comboBox_out->currentIndex();
	evz.signal[MDMA::OUT][0] = ui->spinBox_out_1->value();
	evz.signal[MDMA::OUT][1] = ui->spinBox_out_2->value();
	evz.signal[MDMA::OUT][2] = ui->spinBox_out_3->value();

	accept();
}

// ========================================================================================


void ZoneEditor::on_comboBox_axex_0_currentIndexChanged(int index)
{
	ui->spinBox_axex_1->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_axex_2->setDisabled(MDMA::is_midi((MDMA::active) index) < 2);
	ui->spinBox_axex_3->setDisabled(MDMA::is_midi((MDMA::active) index) < 3);

	ui->spinBox_axex_2->setValue((MDMA::is_midi((MDMA::active) index) == 1)?64:0);
	ui->spinBox_axex_3->setValue((MDMA::is_midi((MDMA::active) index) == 2)?64:0);
}

void ZoneEditor::on_comboBox_axey_0_currentIndexChanged(int index)
{
	ui->spinBox_axey_1->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_axey_2->setDisabled(MDMA::is_midi((MDMA::active) index) < 2);
	ui->spinBox_axey_3->setDisabled(MDMA::is_midi((MDMA::active) index) < 3);

	ui->spinBox_axey_2->setValue((MDMA::is_midi((MDMA::active) index) == 1)?64:0);
	ui->spinBox_axey_3->setValue((MDMA::is_midi((MDMA::active) index) == 2)?64:0);
}

// ========================================================================================

void ZoneEditor::on_comboBox_enter_currentIndexChanged(int index)
{
	ui->spinBox_enter_1->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_enter_2->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_enter_3->setDisabled(MDMA::is_midi((MDMA::active) index) < 2);
}

void ZoneEditor::on_comboBox_exit_currentIndexChanged(int index)
{
	ui->spinBox_exit_1->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_exit_2->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_exit_3->setDisabled(MDMA::is_midi((MDMA::active) index) < 2);
}

void ZoneEditor::on_comboBox_open_currentIndexChanged(int index)
{
	ui->spinBox_open_1->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_open_2->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_open_3->setDisabled(MDMA::is_midi((MDMA::active) index) < 2);
}

void ZoneEditor::on_comboBox_close_currentIndexChanged(int index)
{
	ui->spinBox_close_1->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_close_2->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_close_3->setDisabled(MDMA::is_midi((MDMA::active) index) < 2);
}

void ZoneEditor::on_comboBox_shock_currentIndexChanged(int index)
{
	ui->spinBox_shock_1->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_shock_2->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_shock_3->setDisabled(MDMA::is_midi((MDMA::active) index) < 2);
}


void ZoneEditor::on_comboBox_in_currentIndexChanged(int index)
{
	ui->spinBox_in_1->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_in_2->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_in_3->setDisabled(MDMA::is_midi((MDMA::active) index) < 2);
}

void ZoneEditor::on_comboBox_out_currentIndexChanged(int index)
{
	ui->spinBox_out_1->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_out_2->setDisabled(MDMA::is_midi((MDMA::active) index) < 1);
	ui->spinBox_out_3->setDisabled(MDMA::is_midi((MDMA::active) index) < 2);
}
