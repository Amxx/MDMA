#include "mycamerawindow.h"

MyCameraWindow::MyCameraWindow(CvCapture *cam, QWidget *parent) : QWidget(parent) {

    // On recupere l'objet permettant d'acceder aux images prises par la camera
    // comme attribut de la classe
    camera = cam;


    QVBoxLayout *layout = new QVBoxLayout;

    // Création de notre beau widget
    cvwidget = new QOpenCVWidget(this);
    layout->addWidget(cvwidget);
    //layout->addWidget(btnFaceDetection);
    setLayout(layout);
    resize(500, 400);
    // Demarage du timer qui appel la methode timerEvent() toute les 25 ms
    startTimer(25);
}


void MyCameraWindow::timerEvent(QTimerEvent*) {

    //----------------------------------------
    //  Version longue pour la compréhension
    //----------------------------------------
    //
    //  IplImage *tmp = cvQueryFrame(camera);
    //  cvwidget->putImage(tmp);
    //
    //----------------------------------------

    // On demande une image a l'objet camera pour l'afficher dans le label
    // de notre beau widget
    cvwidget->putImage(cvQueryFrame(camera));
}
