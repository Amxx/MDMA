#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "kinect.h"
#include "handdescriptor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void timerEvent(QTimerEvent*);
    
private:
    QLabel* label;
    Kinect* ht;
    HandDescriptor l,r;
};

#endif // MAINWINDOW_H
