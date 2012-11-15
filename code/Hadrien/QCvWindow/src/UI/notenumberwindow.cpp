#include "notenumberwindow.h"
#include "ui_notenumberwindow.h"

NoteNumberWindow::NoteNumberWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NoteNumberWindow)
{
	ui->setupUi(this);
	update();
}

NoteNumberWindow::~NoteNumberWindow()
{
	delete ui;
}

void NoteNumberWindow::on_note_currentIndexChanged()
{
	update();
}

void NoteNumberWindow::on_octave_currentIndexChanged()
{
	update();
}

void NoteNumberWindow::update()
{
	int value = ui->note->currentIndex() + ui->octave->currentIndex() * 12;
	ui->display->setText((value > 127)?"Not a valid note":QString::number(value));

}
