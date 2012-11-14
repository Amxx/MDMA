#include "handdescriptor.h"

HandDescriptor::HandDescriptor() : actuel(),
    precedent(),
    gauche(false),
    seuil(0),
    ouverture(0)
{
    lastUpdate = time(NULL);
}

HandDescriptor::HandDescriptor(int x, int y) : actuel(x,y),
    precedent(x,y),
    gauche(false),
    seuil(0),
    ouverture(0)
{
    lastUpdate = time(NULL);
}

void HandDescriptor::newPosition(int x, int y)
{
    precedent = actuel;
    actuel = QPoint(x,y);
    duree = time(NULL)-lastUpdate;
    lastUpdate = time(NULL);
}
