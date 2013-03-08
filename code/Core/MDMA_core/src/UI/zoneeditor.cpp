#include "zoneeditor.h"
#include "ui_zoneeditor.h"

#include <QDebug>

ZoneEditor::ZoneEditor(Zone* evz, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ZoneEditor),
	evz(evz)
{
	ui->setupUi(this);

	ui->lineEdit_name->setText(evz->_name);
	ui->comboBox_tab->setCurrentIndex(evz->_tab);
	ui->tabWidget_type->setCurrentIndex(evz->_type);

	ui->comboBox_axex_0->setCurrentIndex(MDMA::isMidi((*evz)[MDMA::EVENT_X].type)?(*evz)[MDMA::EVENT_X].type:MDMA::GOTO_TAB1);
	ui->spinBox_axex_1->setValue((*evz)[MDMA::EVENT_X].signal[0]);
	ui->spinBox_axex_2->setValue((*evz)[MDMA::EVENT_X].signal[1]);
	ui->spinBox_axex_3->setValue((*evz)[MDMA::EVENT_X].signal[2]);
	ui->radioButton_variable_1_1->setChecked((*evz)[MDMA::EVENT_X].variable == 1);
	ui->radioButton_variable_1_2->setChecked((*evz)[MDMA::EVENT_X].variable == 2);

	ui->comboBox_axey_0->setCurrentIndex(MDMA::isMidi((*evz)[MDMA::EVENT_Y].type)?(*evz)[MDMA::EVENT_Y].type:MDMA::GOTO_TAB1);
	ui->spinBox_axey_1->setValue((*evz)[MDMA::EVENT_Y].signal[0]);
	ui->spinBox_axey_2->setValue((*evz)[MDMA::EVENT_Y].signal[1]);
	ui->spinBox_axey_3->setValue((*evz)[MDMA::EVENT_Y].signal[2]);
	ui->radioButton_variable_2_1->setChecked((*evz)[MDMA::EVENT_Y].variable == 1);
	ui->radioButton_variable_2_2->setChecked((*evz)[MDMA::EVENT_Y].variable == 2);

	ui->comboBox_enter->setCurrentIndex((*evz)[MDMA::ENTER].type);
	ui->spinBox_enter_1->setValue((*evz)[MDMA::ENTER].signal[0]);
	ui->spinBox_enter_2->setValue((*evz)[MDMA::ENTER].signal[1]);
	ui->spinBox_enter_3->setValue((*evz)[MDMA::ENTER].signal[2]);
	ui->comboBox_exit->setCurrentIndex((*evz)[MDMA::EXIT].type);
	ui->spinBox_exit_1->setValue((*evz)[MDMA::EXIT].signal[0]);
	ui->spinBox_exit_2->setValue((*evz)[MDMA::EXIT].signal[1]);
	ui->spinBox_exit_3->setValue((*evz)[MDMA::EXIT].signal[2]);
	ui->comboBox_open->setCurrentIndex((*evz)[MDMA::OPEN].type);
	ui->spinBox_open_1->setValue((*evz)[MDMA::OPEN].signal[0]);
	ui->spinBox_open_2->setValue((*evz)[MDMA::OPEN].signal[1]);
	ui->spinBox_open_3->setValue((*evz)[MDMA::OPEN].signal[2]);
	ui->comboBox_close->setCurrentIndex((*evz)[MDMA::CLOSE].type);
	ui->spinBox_close_1->setValue((*evz)[MDMA::CLOSE].signal[0]);
	ui->spinBox_close_2->setValue((*evz)[MDMA::CLOSE].signal[1]);
	ui->spinBox_close_3->setValue((*evz)[MDMA::CLOSE].signal[2]);
	ui->comboBox_shock->setCurrentIndex((*evz)[MDMA::SHOCK].type);
	ui->spinBox_shock_1->setValue((*evz)[MDMA::SHOCK].signal[0]);
	ui->spinBox_shock_2->setValue((*evz)[MDMA::SHOCK].signal[1]);
	ui->spinBox_shock_3->setValue((*evz)[MDMA::SHOCK].signal[2]);

	ui->comboBox_in->setCurrentIndex((*evz)[MDMA::IN].type);
	ui->spinBox_in_1->setValue((*evz)[MDMA::IN].signal[0]);
	ui->spinBox_in_2->setValue((*evz)[MDMA::IN].signal[1]);
	ui->spinBox_in_3->setValue((*evz)[MDMA::IN].signal[2]);
	ui->comboBox_out->setCurrentIndex((*evz)[MDMA::OUT].type);
	ui->spinBox_out_1->setValue((*evz)[MDMA::OUT].signal[0]);
	ui->spinBox_out_2->setValue((*evz)[MDMA::OUT].signal[1]);
	ui->spinBox_out_3->setValue((*evz)[MDMA::OUT].signal[2]);
}

ZoneEditor::~ZoneEditor()
{
	delete ui;
}

// ========================================================================================

void ZoneEditor::on_pushButton_apply_clicked()
{

	evz->_name = ui->lineEdit_name->text();
	evz->_tab = ui->comboBox_tab->currentIndex();
	evz->_type = MDMA::type(ui->tabWidget_type->currentIndex());

	(*evz)[MDMA::EVENT_X].type = (MDMA::signal) (ui->comboBox_axex_0->currentIndex());
	if(!MDMA::isMidi((*evz)[MDMA::EVENT_X].type)) (*evz)[MDMA::EVENT_X].type = MDMA::NOTHING;
	(*evz)[MDMA::EVENT_X].signal[0] = ui->spinBox_axex_1->value();
	(*evz)[MDMA::EVENT_X].signal[1] = ui->spinBox_axex_2->value();
	(*evz)[MDMA::EVENT_X].signal[2] = ui->spinBox_axex_3->value();
	(*evz)[MDMA::EVENT_X].variable = ui->radioButton_variable_1_1->isChecked()?1:2;

	(*evz)[MDMA::EVENT_Y].type = (MDMA::signal) (ui->comboBox_axey_0->currentIndex());
	if(!MDMA::isMidi((*evz)[MDMA::EVENT_Y].type)) (*evz)[MDMA::EVENT_Y].type = MDMA::NOTHING;
	(*evz)[MDMA::EVENT_Y].signal[0] = ui->spinBox_axey_1->value();
	(*evz)[MDMA::EVENT_Y].signal[1] = ui->spinBox_axey_2->value();
	(*evz)[MDMA::EVENT_Y].signal[2] = ui->spinBox_axey_3->value();
	(*evz)[MDMA::EVENT_Y].variable = ui->radioButton_variable_2_1->isChecked()?1:2;

	(*evz)[MDMA::ENTER].type = (MDMA::signal) ui->comboBox_enter->currentIndex();
	(*evz)[MDMA::ENTER].signal[0] = ui->spinBox_enter_1->value();
	(*evz)[MDMA::ENTER].signal[1] = ui->spinBox_enter_2->value();
	(*evz)[MDMA::ENTER].signal[2] = ui->spinBox_enter_3->value();
	(*evz)[MDMA::EXIT].type = (MDMA::signal) ui->comboBox_exit->currentIndex();
	(*evz)[MDMA::EXIT].signal[0] = ui->spinBox_exit_1->value();
	(*evz)[MDMA::EXIT].signal[1] = ui->spinBox_exit_2->value();
	(*evz)[MDMA::EXIT].signal[2] = ui->spinBox_exit_3->value();
	(*evz)[MDMA::OPEN].type = (MDMA::signal) ui->comboBox_open->currentIndex();
	(*evz)[MDMA::OPEN].signal[0] = ui->spinBox_open_1->value();
	(*evz)[MDMA::OPEN].signal[1] = ui->spinBox_open_2->value();
	(*evz)[MDMA::OPEN].signal[2] = ui->spinBox_open_3->value();
	(*evz)[MDMA::CLOSE].type = (MDMA::signal) ui->comboBox_close->currentIndex();
	(*evz)[MDMA::CLOSE].signal[0] = ui->spinBox_close_1->value();
	(*evz)[MDMA::CLOSE].signal[1] = ui->spinBox_close_2->value();
	(*evz)[MDMA::CLOSE].signal[2] = ui->spinBox_close_3->value();
	(*evz)[MDMA::SHOCK].type = (MDMA::signal) ui->comboBox_shock->currentIndex();
	(*evz)[MDMA::SHOCK].signal[0] = ui->spinBox_shock_1->value();
	(*evz)[MDMA::SHOCK].signal[1] = ui->spinBox_shock_2->value();
	(*evz)[MDMA::SHOCK].signal[2] = ui->spinBox_shock_3->value();

	(*evz)[MDMA::IN].type = (MDMA::signal) ui->comboBox_in->currentIndex();
	(*evz)[MDMA::IN].signal[0] = ui->spinBox_in_1->value();
	(*evz)[MDMA::IN].signal[1] = ui->spinBox_in_2->value();
	(*evz)[MDMA::IN].signal[2] = ui->spinBox_in_3->value();
	(*evz)[MDMA::OUT].type = (MDMA::signal) ui->comboBox_out->currentIndex();
	(*evz)[MDMA::OUT].signal[0] = ui->spinBox_out_1->value();
	(*evz)[MDMA::OUT].signal[1] = ui->spinBox_out_2->value();
	(*evz)[MDMA::OUT].signal[2] = ui->spinBox_out_3->value();

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






int EditZone(Zone* evz, QWidget* parent)
{
	return ZoneEditor(evz, parent).exec();
}

