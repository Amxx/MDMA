#include "handopenwindow.h"
#include "ui_handopenwindow.h"

HandOpenWindow::HandOpenWindow(Configuration& _config, QWidget *parent) :
	QDialog(parent),
	config(_config),
	ui(new Ui::HandOpenWindow)
{
	ui->setupUi(this);
	QObject::connect(&timer, SIGNAL(timeout()),this,SLOT(set_number()));
}

HandOpenWindow::~HandOpenWindow()
{
	delete ui;
}

void HandOpenWindow::closeEvent(QCloseEvent* ev)
{
	reject();
}

// ===============================================================================================================================

void HandOpenWindow::on_pushButton_next_clicked()
{
	/*
	if(config.user_mask.empty())
		QMessageBox::critical(this, "Mask isn't set", "The mask must be set in order to go to the next step");
	else
	*/
	accept();
}

void HandOpenWindow::on_pushButton_cancel_clicked()
{
	reject();
}

void HandOpenWindow::on_pushButton_clicked()
{
	timer.start(1000);
	config.freeze = false;
	ui->pushButton->setDisabled(true);
	ui->pushButton_cancel->setDisabled(true);
	ui->pushButton_next->setDisabled(true);
	ui->lcdNumber->display(5);
}

void HandOpenWindow::set_number()
{
	switch(ui->lcdNumber->intValue())
	{
		case 0:
			timer.stop();
			ui->pushButton->setDisabled(false);
			ui->pushButton_cancel->setDisabled(false);
			ui->pushButton_next->setDisabled(false);
			break;
		default:
			ui->lcdNumber->display(ui->lcdNumber->intValue() - 1);
			break;
	}

}
