#ifndef WIDGET_H
#define WIDGET_H

#include <QApplication>
#include <QWidget>

#include <opencv2/opencv.hpp>

#include "../evenement.h"
#include "log.h"
#include "mycamerawindow.h"

class MaFenetre : public QWidget
{
public:
    explicit MaFenetre(QWidget *parent = 0);
    ~MaFenetre();
    
protected:
    Evenement* even;
    Log* log;
    MyCameraWindow* mainWin;
    CvCapture * camera;
};

#endif // WIDGET_H
