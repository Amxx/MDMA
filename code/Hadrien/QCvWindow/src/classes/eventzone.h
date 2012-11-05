#ifndef EVENTZONE_H
#define EVENTZONE_H

#include <QString>
#include <QMap>

#include "midisignal.h"

namespace zone
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
		ENTER,
		EXIT,
		OPEN,
		CLOSE,
		SHOCK
	};
}

class EventZone
{
	public:
		EventZone();

		QString Name;
		int tab;

		zone::type type;
		zone::axes axes;
		QMap<zone::event, MidiSignal*> event_lists;

};

#endif // EVENTZONE_H
