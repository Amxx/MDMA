#include "zoneeditor.h"
#include "ui_zoneeditor.h"

#include <QDebug>

ZoneEditor::ZoneEditor(Zone& zn, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ZoneEditor),
	_zn(zn)
{
	ui->setupUi(this);

	ui->lineEdit_name->setText(_zn._name);
	ui->comboBox_tab->setCurrentIndex(_zn._tab);
	ui->tabWidget_type->setCurrentIndex(_zn._type);

	ui->comboBox_axex_0->setCurrentIndex(MDMA::isMidi(_zn[MDMA::EVENT_X].type)?_zn[MDMA::EVENT_X].type:MDMA::GOTO_TAB1);
	ui->spinBox_axex_1->setValue(_zn[MDMA::EVENT_X].signal[0]);
	ui->spinBox_axex_2->setValue(_zn[MDMA::EVENT_X].signal[1]);
	ui->spinBox_axex_3->setValue(_zn[MDMA::EVENT_X].signal[2]);
	ui->radioButton_variable_1_1->setChecked(_zn[MDMA::EVENT_X].variable == 1);
	ui->radioButton_variable_1_2->setChecked(_zn[MDMA::EVENT_X].variable == 2);

	ui->comboBox_axey_0->setCurrentIndex(MDMA::isMidi(_zn[MDMA::EVENT_Y].type)?_zn[MDMA::EVENT_Y].type:MDMA::GOTO_TAB1);
	ui->spinBox_axey_1->setValue(_zn[MDMA::EVENT_Y].signal[0]);
	ui->spinBox_axey_2->setValue(_zn[MDMA::EVENT_Y].signal[1]);
	ui->spinBox_axey_3->setValue(_zn[MDMA::EVENT_Y].signal[2]);
	ui->radioButton_variable_2_1->setChecked(_zn[MDMA::EVENT_Y].variable == 1);
	ui->radioButton_variable_2_2->setChecked(_zn[MDMA::EVENT_Y].variable == 2);

	ui->comboBox_enter->setCurrentIndex(_zn[MDMA::ENTER].type);
	ui->spinBox_enter_1->setValue(_zn[MDMA::ENTER].signal[0]);
	ui->spinBox_enter_2->setValue(_zn[MDMA::ENTER].signal[1]);
	ui->spinBox_enter_3->setValue(_zn[MDMA::ENTER].signal[2]);
	ui->comboBox_exit->setCurrentIndex(_zn[MDMA::EXIT].type);
	ui->spinBox_exit_1->setValue(_zn[MDMA::EXIT].signal[0]);
	ui->spinBox_exit_2->setValue(_zn[MDMA::EXIT].signal[1]);
	ui->spinBox_exit_3->setValue(_zn[MDMA::EXIT].signal[2]);
	ui->comboBox_open->setCurrentIndex(_zn[MDMA::OPEN].type);
	ui->spinBox_open_1->setValue(_zn[MDMA::OPEN].signal[0]);
	ui->spinBox_open_2->setValue(_zn[MDMA::OPEN].signal[1]);
	ui->spinBox_open_3->setValue(_zn[MDMA::OPEN].signal[2]);
	ui->comboBox_close->setCurrentIndex(_zn[MDMA::CLOSE].type);
	ui->spinBox_close_1->setValue(_zn[MDMA::CLOSE].signal[0]);
	ui->spinBox_close_2->setValue(_zn[MDMA::CLOSE].signal[1]);
	ui->spinBox_close_3->setValue(_zn[MDMA::CLOSE].signal[2]);
	ui->comboBox_shock->setCurrentIndex(_zn[MDMA::SHOCK].type);
	ui->spinBox_shock_1->setValue(_zn[MDMA::SHOCK].signal[0]);
	ui->spinBox_shock_2->setValue(_zn[MDMA::SHOCK].signal[1]);
	ui->spinBox_shock_3->setValue(_zn[MDMA::SHOCK].signal[2]);

	ui->comboBox_in->setCurrentIndex(_zn[MDMA::IN].type);
	ui->spinBox_in_1->setValue(_zn[MDMA::IN].signal[0]);
	ui->spinBox_in_2->setValue(_zn[MDMA::IN].signal[1]);
	ui->spinBox_in_3->setValue(_zn[MDMA::IN].signal[2]);
	ui->comboBox_out->setCurrentIndex(_zn[MDMA::OUT].type);
	ui->spinBox_out_1->setValue(_zn[MDMA::OUT].signal[0]);
	ui->spinBox_out_2->setValue(_zn[MDMA::OUT].signal[1]);
	ui->spinBox_out_3->setValue(_zn[MDMA::OUT].signal[2]);
}

ZoneEditor::~ZoneEditor()
{
	delete ui;
}

// ========================================================================================

void ZoneEditor::on_pushButton_apply_clicked()
{

	_zn._name = ui->lineEdit_name->text();
	_zn._tab = ui->comboBox_tab->currentIndex();
	_zn._type = MDMA::type(ui->tabWidget_type->currentIndex());

	_zn[MDMA::EVENT_X].type = (MDMA::signal) (ui->comboBox_axex_0->currentIndex());
	if(!MDMA::isMidi(_zn[MDMA::EVENT_X].type)) _zn[MDMA::EVENT_X].type = MDMA::NOTHING;
	_zn[MDMA::EVENT_X].signal[0] = ui->spinBox_axex_1->value();
	_zn[MDMA::EVENT_X].signal[1] = ui->spinBox_axex_2->value();
	_zn[MDMA::EVENT_X].signal[2] = ui->spinBox_axex_3->value();
	_zn[MDMA::EVENT_X].variable = ui->radioButton_variable_1_1->isChecked()?1:2;

	_zn[MDMA::EVENT_Y].type = (MDMA::signal) (ui->comboBox_axey_0->currentIndex());
	if(!MDMA::isMidi(_zn[MDMA::EVENT_Y].type)) _zn[MDMA::EVENT_Y].type = MDMA::NOTHING;
	_zn[MDMA::EVENT_Y].signal[0] = ui->spinBox_axey_1->value();
	_zn[MDMA::EVENT_Y].signal[1] = ui->spinBox_axey_2->value();
	_zn[MDMA::EVENT_Y].signal[2] = ui->spinBox_axey_3->value();
	_zn[MDMA::EVENT_Y].variable = ui->radioButton_variable_2_1->isChecked()?1:2;

	_zn[MDMA::ENTER].type = (MDMA::signal) ui->comboBox_enter->currentIndex();
	_zn[MDMA::ENTER].signal[0] = ui->spinBox_enter_1->value();
	_zn[MDMA::ENTER].signal[1] = ui->spinBox_enter_2->value();
	_zn[MDMA::ENTER].signal[2] = ui->spinBox_enter_3->value();
	_zn[MDMA::EXIT].type = (MDMA::signal) ui->comboBox_exit->currentIndex();
	_zn[MDMA::EXIT].signal[0] = ui->spinBox_exit_1->value();
	_zn[MDMA::EXIT].signal[1] = ui->spinBox_exit_2->value();
	_zn[MDMA::EXIT].signal[2] = ui->spinBox_exit_3->value();
	_zn[MDMA::OPEN].type = (MDMA::signal) ui->comboBox_open->currentIndex();
	_zn[MDMA::OPEN].signal[0] = ui->spinBox_open_1->value();
	_zn[MDMA::OPEN].signal[1] = ui->spinBox_open_2->value();
	_zn[MDMA::OPEN].signal[2] = ui->spinBox_open_3->value();
	_zn[MDMA::CLOSE].type = (MDMA::signal) ui->comboBox_close->currentIndex();
	_zn[MDMA::CLOSE].signal[0] = ui->spinBox_close_1->value();
	_zn[MDMA::CLOSE].signal[1] = ui->spinBox_close_2->value();
	_zn[MDMA::CLOSE].signal[2] = ui->spinBox_close_3->value();
	_zn[MDMA::SHOCK].type = (MDMA::signal) ui->comboBox_shock->currentIndex();
	_zn[MDMA::SHOCK].signal[0] = ui->spinBox_shock_1->value();
	_zn[MDMA::SHOCK].signal[1] = ui->spinBox_shock_2->value();
	_zn[MDMA::SHOCK].signal[2] = ui->spinBox_shock_3->value();

	_zn[MDMA::IN].type = (MDMA::signal) ui->comboBox_in->currentIndex();
	_zn[MDMA::IN].signal[0] = ui->spinBox_in_1->value();
	_zn[MDMA::IN].signal[1] = ui->spinBox_in_2->value();
	_zn[MDMA::IN].signal[2] = ui->spinBox_in_3->value();
	_zn[MDMA::OUT].type = (MDMA::signal) ui->comboBox_out->currentIndex();
	_zn[MDMA::OUT].signal[0] = ui->spinBox_out_1->value();
	_zn[MDMA::OUT].signal[1] = ui->spinBox_out_2->value();
	_zn[MDMA::OUT].signal[2] = ui->spinBox_out_3->value();

	accept();
}

void ZoneEditor::on_pushButton_cancel_clicked()
{
	reject();
}

void ZoneEditor::on_pushButton_delete_clicked()
{
	done(-1);
}

// ========================================================================================


void ZoneEditor::on_comboBox_axex_0_currentIndexChanged(int index)
{

	ui->spinBox_axex_1->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_axex_2->setDisabled((MDMA::isMidi((MDMA::signal) index) < 1)); // || evz.variable[0][0]);
	ui->spinBox_axex_3->setDisabled((MDMA::isMidi((MDMA::signal) index) < 2)); // || evz.variable[0][1]);

}

void ZoneEditor::on_comboBox_axey_0_currentIndexChanged(int index)
{
	ui->spinBox_axey_1->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_axey_2->setDisabled((MDMA::isMidi((MDMA::signal) index) < 1)); // || evz.variable[1][0]);
	ui->spinBox_axey_3->setDisabled((MDMA::isMidi((MDMA::signal) index) < 2)); // || evz.variable[1][1]);
}

// ========================================================================================

void ZoneEditor::on_comboBox_enter_currentIndexChanged(int index)
{
	ui->spinBox_enter_1->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_enter_2->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_enter_3->setDisabled(MDMA::isMidi((MDMA::signal) index) < 2);
}

void ZoneEditor::on_comboBox_exit_currentIndexChanged(int index)
{
	ui->spinBox_exit_1->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_exit_2->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_exit_3->setDisabled(MDMA::isMidi((MDMA::signal) index) < 2);
}

void ZoneEditor::on_comboBox_open_currentIndexChanged(int index)
{
	ui->spinBox_open_1->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_open_2->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_open_3->setDisabled(MDMA::isMidi((MDMA::signal) index) < 2);
}

void ZoneEditor::on_comboBox_close_currentIndexChanged(int index)
{
	ui->spinBox_close_1->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_close_2->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_close_3->setDisabled(MDMA::isMidi((MDMA::signal) index) < 2);
}

void ZoneEditor::on_comboBox_shock_currentIndexChanged(int index)
{
	ui->spinBox_shock_1->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_shock_2->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_shock_3->setDisabled(MDMA::isMidi((MDMA::signal) index) < 2);
}


void ZoneEditor::on_comboBox_in_currentIndexChanged(int index)
{
	ui->spinBox_in_1->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_in_2->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_in_3->setDisabled(MDMA::isMidi((MDMA::signal) index) < 2);
}

void ZoneEditor::on_comboBox_out_currentIndexChanged(int index)
{
	ui->spinBox_out_1->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_out_2->setDisabled(MDMA::isMidi((MDMA::signal) index) < 1);
	ui->spinBox_out_3->setDisabled(MDMA::isMidi((MDMA::signal) index) < 2);
}


void ZoneEditor::on_noteHelp_clicked()
{
//	NoteNumberWindow* noteWindow = new NoteNumberWindow(this);
//	noteWindow->show();
}






int EditZone(Zone& zn, QWidget* parent)
{
	return ZoneEditor(zn, parent).exec();
}

