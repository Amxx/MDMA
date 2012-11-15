#include "handclosewindow.h"
#include "ui_handclosewindow.h"

HandCloseWindow::HandCloseWindow(Configuration& _config, QWidget *parent) :
	QDialog(parent),
	config(_config),
	ui(new Ui::HandCloseWindow)
{
	ui->setupUi(this);
	QObject::connect(&timer, SIGNAL(timeout()),this,SLOT(set_number()));
}

HandCloseWindow::~HandCloseWindow()
{
	delete ui;
}

void HandCloseWindow::closeEvent()
{
	reject();
}

// ===============================================================================================================================

void HandCloseWindow::on_pushButton_next_clicked()
{
	/*
	if(config.user_mask.empty())
		QMessageBox::critical(this, "Mask isn't set", "The mask must be set in order to go to the next step");
	else
	*/
	accept();
}

void HandCloseWindow::on_pushButton_cancel_clicked()
{
	reject();
}

void HandCloseWindow::on_pushButton_clicked()
{
	timer.start(1000);
	config.freeze = false;
	ui->pushButton->setDisabled(true);
	ui->pushButton_cancel->setDisabled(true);
	ui->pushButton_next->setDisabled(true);
	ui->lcdNumber->display(5);
}

void HandCloseWindow::set_number()
{
	switch(ui->lcdNumber->intValue())
	{
		case 0:
			timer.stop();
			ui->pushButton->setDisabled(false);
			ui->pushButton_cancel->setDisabled(false);
			ui->pushButton_next->setDisabled(false);
			on_pushButton_next_clicked();
			break;
		default:
			ui->lcdNumber->display(ui->lcdNumber->intValue() - 1);
			break;
	}

}
