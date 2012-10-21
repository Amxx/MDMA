#include "evenement.h"
#include "zone.h"

Zone::Zone(int _id, type_zone _type, int _csg_x, int _csg_y, int _cid_x, int _cid_y, fader_axe _axe) :
    id(_id), coin1(_csg_x, _csg_y), coin2(_cid_x, _cid_y), rect(coin1, coin2), type(_type)
{
    axe_x = _axe & AXE_X;
    axe_y = _axe & AXE_Y;
    valeur_x = valeur_y = 64;

    gauche_dedans = false;
    droite_dedans = false;
    actif = false;

    valide = true;
    if(type == zone_segment && (rect.width == 0 && rect.height == 0))
        valide = false;
    if(type == zone_pad && (rect.width == 0 || rect.height == 0))
        valide = false;
    if(type == zone_fader && (rect.width == 0 || rect.height == 0) && _axe == AXE_SANS)
        valide = false;
}

bool Zone::est_valide()
{
    /*
    valide = true;
    if(rect.w < 0 || rect.h < 0)
        valide = false;
    if(type == zone_segment && (rect.w == 0 && rect.h == 0))
        valide = false;
    if(type == zone_pad && (rect.w == 0 || rect.h == 0))
        valide = false;
    if(type == zone_fader && (rect.w == 0 || rect.h == 0) && _axe == SANS)
        valide = false;
    */
    return valide;
}

bool Zone::change(InfoMain &main)
{
    int d = 0, t;
    cv::Point vec1, vec2;
    cv::Point x;
    if(valide)
    {
        switch(type)
        {
        case zone_fader:
            if(main.ouvert < MAIN_OUVERTE && main.actuel.inside(rect))
            {
                valeur_x = (main.actuel.x - rect.x)*128/rect.width;
                valeur_y = (main.actuel.y - rect.y)*128/rect.height;
                return true;
            }
            break;
        case zone_pad:
            /*if(main.ouvert < MAIN_OUVERTE && main.actuel.inside(rect))
            {
                if(main.gauche && gauche_dedans)
                return true;
            }*/
            break;
        case zone_segment:
            //Intersection des deux segments, celui de la zone et celui de la main
            vec1 = main.actuel - main.precedent;
            vec2 = coin2 - coin1;
            //Calcul du dénominateur
            d = vec1.x * vec2.y - vec1.y * vec2.x;
            if(d == 0)
                return false;
            //Vérifie si l'intersection est dans le segment de la zone
            x = main.precedent - coin1;
            t = vec1.x * x.y - vec1.y * x.x;
            if(d*t < 0 || abs(t) > abs(d))
                return false;


            //Vérifie si l'intersection est dans le segment décrit par la main
            x = coin1 - main.precedent;
            t = vec2.x * x.y - vec2.y * x.x;
            if(d*t < 0 || abs(t) > abs(d))
                return false;
            actif = !actif;
            return true;
            break;
        }
    }
    return false;
}
