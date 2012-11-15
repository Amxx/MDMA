#ifndef EVENTZONE_H
#define EVENTZONE_H

#include <algorithm>

#include <QMap>
#include <QPainter>
#include <QPoint>
#include <QString>

#include "../config/constant.h"

#include "../classes/handdescriptor.h"

class EventZone
{
	public:
		EventZone();
		EventZone(QPoint _P1, QPoint _P2, int _tab);
		EventZone(const EventZone &cpy);
		~EventZone();

		// ----------------------------------------------------------

		void display(QPainter& painter);

		MDMA::signal getMidi(MDMA::event);
        QList<MDMA::event_signal> update(HandDescriptor& main);

		// ----------------------------------------------------------

		QString name;
		QPoint P1;
		QPoint P2;
		int tab;

		// ----------------------------------------------------------

		MDMA::type type;
		MDMA::active active[9];
		MDMA::signal signal[9];

		// ----------------------------------------------------------

		bool is_active;
		bool hand_in;
		bool hand_open;
};

#endif // EVENTZONE_H
