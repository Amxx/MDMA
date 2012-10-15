#include "mafenetre.h"

MaFenetre::MaFenetre(QWidget *parent) :
    QWidget(parent)
{
    even = new Evenement(this);
    log = new Log(this);

    QObject::connect(even, SIGNAL(detect_machin(int,int)), log, SLOT(receive_detection(int,int)));

    camera = cvCreateCameraCapture(0);
    assert(camera);
    IplImage * image=cvQueryFrame(camera);
    assert(image);


    // On passe l'objet camera à notre class MyCameraWindow
    mainWin = new MyCameraWindow(camera, this);


    mainWin->setWindowTitle("OpenCV with Qt");
}

MaFenetre::~MaFenetre()
{
    cvReleaseCapture(&camera);
}
