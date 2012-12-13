#include "mainwindow.h"

#include <QPixmap>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    xn::ScriptNode scriptNode;
    XnStatus rc = m_rContext.InitFromXmlFile("Sample-Tracking.xml", scriptNode);
    if (rc != XN_STATUS_OK)
    {
        printf("Couldn't initialize: %s\n", xnGetStatusString(rc));
        exit(1);
    }
    ht = new HandTracker(m_rContext);
    label = new QLabel(this);
    label->setFixedSize(640,480);
    ht->Init();
    ht->Run();
    setFixedSize(640,480);
    startTimer(25);
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
