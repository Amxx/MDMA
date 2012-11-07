#include "eventzone.h"

eventZone::eventZone()
{
}

eventZone::eventZone(QPoint _P1, QPoint _P2, int _tab) : P1(_P1), P2(_P2), tab(_tab)
{
	name = "New Zone";
	type = MDMA::FADER;
	axes = MDMA::AXE_X;
}

eventZone::~eventZone()
{
}



QString MDMA::type_to_string(type t)
{
	switch(t)
	{
		case FADER : return "Fader";
		case PAD : return "Pad";
		case SEGMENT : return "Segment";
	}
	return "";
}
