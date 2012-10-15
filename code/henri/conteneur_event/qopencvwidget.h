#ifndef QOPENCVWIDGET_H

#define QOPENCVWIDGET_H

// Penser à inclure les headers d'openCV

#include <opencv2/opencv.hpp>

#include <QPixmap>

#include <QLabel>

#include <QWidget>

#include <QVBoxLayout>

#include <QImage>

#include <cstdio>

class QOpenCVWidget : public QWidget {

    private:

        // Le label permet l'affichage d'image le plus rapide dans Qt

         // c'est dans ce label que vont apparaitre les images de la camera

        QLabel *imagelabel;

        // De objets pour la mise en page

        QVBoxLayout *layout;

        QHBoxLayout *hLayout;
        // Image reçue de la camera
        QImage image;



    public:

        QOpenCVWidget(QWidget *parent = 0);

        ~QOpenCVWidget(void);


        // Convertir IplImage en QImage

        QImage IplImage2QImage(const IplImage *iplImage);


         // Convertir QImage en IplImage

        IplImage* qImage2IplImage(const QImage& qImage);

         // Cette fonction permettra de donner l'image à afficher par le label

         void putImage(IplImage *);

};

#endif
