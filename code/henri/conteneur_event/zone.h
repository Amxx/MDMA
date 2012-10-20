#ifndef ZONE_H
#define ZONE_H

#include <opencv2/opencv.hpp>

enum type_zone { zone_fader, zone_pad, zone_segment };
enum fader_axe { AXE_SANS = 0, AXE_X, AXE_Y, AXES_XY };

class InfoMain;

class Zone
{
public:
    //Constructeur
    Zone(int _id, type_zone _type, int _csg_x, int _csg_y, int _cid_x, int _cid_y, fader_axe _axe = AXE_SANS);

    //Donne la validité de la zone
    bool est_valide();
    //Indique si la zone à changer de status
    bool change(InfoMain &main);

    //Type de zone : Fader, Pad ou Segment
    type_zone type;
    //Position
    cv::Rect rect;
    cv::Point coin1;
    cv::Point coin2;

    //Si Fader, axes utilisés et la valeurs sur ces axes
    bool axe_x, axe_y;
    int valeur_x, valeur_y;

    //Si la main est à l'intérieur
    bool gauche_dedans;
    bool droite_dedans;

    int id;

protected:
    //Validité de la zone (si elle est bien initialisé)
    bool valide;

    //Etat de la zone, utile pour le segment et le pad
    bool actif;
};

#endif // ZONE_H
