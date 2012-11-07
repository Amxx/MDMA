#ifndef EVENTZONE_H
#define EVENTZONE_H

#include <QMap>
#include <QPoint>
#include <QString>

#include "midisignal.h"

namespace MDMA
{
	enum type
	{
		FADER,
		PAD,
		SEGMENT
	};
	enum axes
	{
		AXE_X,
		AXE_Y,
		AXE_XY
	};
	enum event
	{
		EVENT_X,
		EVENT_Y,
		ENTER,
		EXIT,
		OPEN,
		CLOSE,
		SHOCK
	};
	QString type_to_string(type t);
}

class eventZone
{
	public:
		explicit eventZone();
		explicit eventZone(QPoint _P1, QPoint _P2, int _tab);
		~eventZone();

		QString name;
		QPoint P1;
		QPoint P2;
		int tab;

		MDMA::type type;
		MDMA::axes axes;

		char events[7][3];

};

#endif // EVENTZONE_H
