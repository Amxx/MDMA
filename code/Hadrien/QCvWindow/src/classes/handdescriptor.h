#ifndef HANDDESCRIPTOR_H
#define HANDDESCRIPTOR_H

#include <QPoint>
#include <ctime>

class HandDescriptor {
public:
    HandDescriptor();
    HandDescriptor(int x, int y);

    void newPosition(int x, int y);

    QPoint actuel;
    QPoint precedent;

    bool gauche;
    int ouverture;
    int seuil;

    time_t lastUpdate;
    int duree;
};

#endif // HANDDESCRIPTOR_H
