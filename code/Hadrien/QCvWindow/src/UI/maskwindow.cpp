#include "maskwindow.h"
#include "ui_maskwindow.h"

MaskWindow::MaskWindow(Configuration& _config, QWidget *parent) :
	QDialog(parent),
	config(_config),
	ui(new Ui::MaskWindow)
{
	ui->setupUi(this);
	if(!config.user_mask.empty()) ui->pushButton->setText("Reconfigure mask");
	QObject::connect(&timer, SIGNAL(timeout()),this,SLOT(set_number()));
}

MaskWindow::~MaskWindow()
{
	delete ui;
}

void MaskWindow::closeEvent()
{
	reject();
}

// ===============================================================================================================================

void MaskWindow::on_pushButton_next_clicked()
{
	if(config.user_mask.empty())
		QMessageBox::critical(this, "Mask isn't set", "The mask must be set in order to go to the next step");
	else
		accept();
}

void MaskWindow::on_pushButton_cancel_clicked()
{
	reject();
}

void MaskWindow::on_pushButton_clicked()
{
	timer.start(1000);
	config.freeze = false;
	config.user_mask.clear();
	ui->pushButton->setDisabled(true);
	ui->pushButton_cancel->setDisabled(true);
	ui->pushButton_next->setDisabled(true);
	ui->lcdNumber->display(5);
}

void MaskWindow::set_number()
{
	switch(ui->lcdNumber->intValue())
	{
		case 0:
			timer.stop();
			config.freeze = true;
			ui->pushButton->setDisabled(false);
			ui->pushButton_cancel->setDisabled(false);
			ui->pushButton_next->setDisabled(false);
			ui->pushButton->setText("Reconfigure mask");
			break;
		default:
			ui->lcdNumber->display(ui->lcdNumber->intValue() - 1);
			break;
	}

}
