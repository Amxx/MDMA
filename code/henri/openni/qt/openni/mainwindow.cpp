#include "mainwindow.h"

#include <QPixmap>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ht()
{
    label = new QLabel(this);
    label->setFixedSize(640,480);
    ht.Init();
    ht.Run();
    setFixedSize(640,480);
    startTimer(25);
}

MainWindow::~MainWindow()
{
    delete label;
}

void MainWindow::timerEvent(QTimerEvent *)
{
    ht.Update();
    label->setPixmap(QPixmap::fromImage(ht.getCamera()));
}
