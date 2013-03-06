#include "handopenwindow.h"
#include "ui_handopenwindow.h"

HandOpenWindow::HandOpenWindow(cv::Mat& mat, QWidget *parent) :
	QDialog(parent),
    ui(new Ui::HandOpenWindow),
    mat(mat)
{
	ui->setupUi(this);
	QObject::connect(&timer, SIGNAL(timeout()),this,SLOT(set_number()));
}

HandOpenWindow::~HandOpenWindow()
{
	delete ui;
}

void HandOpenWindow::closeEvent()
{
	reject();
}

// ===============================================================================================================================

void HandOpenWindow::on_pushButton_next_clicked()
{

    if(mat.empty())
		QMessageBox::critical(this, "", "");
	else
		accept();
}

void HandOpenWindow::on_pushButton_cancel_clicked()
{
	reject();
}

void HandOpenWindow::on_pushButton_clicked()
{
	timer.start(1000);
	Configuration::config().freeze = false;
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
            mat = Configuration::config().current_frame.clone();
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
