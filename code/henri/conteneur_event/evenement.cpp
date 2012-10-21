#include "evenement.h"

Evenement::Evenement(QObject *parent) :
    QObject(parent), zones()
{
}

void Evenement::ajout_zone(Zone &_zone)
{
    zones.push_back(_zone);
}

void Evenement::detection(InfoMain &main)
{
    QList<Zone>::iterator it;
    for(it = zones.begin() ; it != zones.end() ; it++)
    {
        if(it->change(main))
            emit detect_machin(it->id, it->valeur_x);
    }
}
