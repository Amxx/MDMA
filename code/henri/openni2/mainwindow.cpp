#include "mainwindow.h"

#include <QPixmap>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    l(0,0),
    r(0,0)
{
    ht = new Kinect(l,r);
    label = new QLabel(this);
    label->setFixedSize(640,480);
    puts("Init");
    int rc = ht->Init();
    if(rc != 0)
    {
        printf("pouet\n");
        exit(0);
    }
    ht->Run();
    setFixedSize(640,480);
    startTimer(40);
}

MainWindow::~MainWindow()
{
    delete ht;
    delete label;
}

void MainWindow::timerEvent(QTimerEvent *)
{
    ht->Update();
    label->setPixmap(QPixmap::fromImage(ht->getCamera()));
}
