#ifndef MYCAMERAWINDOW_H_
#define MYCAMERAWINDOW_H_
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
// On reconnait ici notre Widget personnalisé
#include "qopencvwidget.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "stdio.h"
#include <iostream>
#include <cstdio>


using namespace std;
using namespace cv;


class MyCameraWindow : public QWidget
{
    Q_OBJECT
    private:
        QOpenCVWidget *cvwidget;
        // Cet objet permet de traiter le flux de la camera
        CvCapture *camera;

    public:
        // Le constructeur reçoit l'objet cam pour gerer le flux video
        MyCameraWindow(CvCapture *cam, QWidget *parent=0);
    protected:
        // c'est dans cette methode qu'on affichera l'image provenant de l'objet camera
        void timerEvent(QTimerEvent*);
};
#endif /*MYCAMERAWINDOW_H_*/
