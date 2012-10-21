#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QObject>
#include <QList>

#include <opencv2/opencv.hpp>
#include "zone.h"

#define MAIN_OUVERTE 1

class InfoMain
{
public:
    InfoMain() : precedent(), actuel(), vitesse(), ouvert(0), gauche(true) {}

    cv::Point precedent;
    cv::Point actuel;
    cv::Point vitesse;
    bool gauche;
    int ouvert;
};

class Evenement : public QObject
{
    Q_OBJECT
public:
    explicit Evenement(QObject *parent = 0);

    void detection(InfoMain &main);

protected:
    QList<Zone> zones;

signals:
    void detect_machin(int id, int valeur);

public slots:
    void ajout_zone(Zone &_zone);


};

#endif // EVENEMENT_H
