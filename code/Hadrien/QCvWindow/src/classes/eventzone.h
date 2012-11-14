#ifndef EVENTZONE_H
#define EVENTZONE_H

#include <algorithm>

#include <QMap>
#include <QPainter>
#include <QPoint>
#include <QString>

#include "../config/constant.h"

class HandDescriptor;

class EventZone
{
	public:
		EventZone();
		EventZone(const EventZone &cpy);
		EventZone(QPoint _P1, QPoint _P2, int _tab);
		~EventZone();

		void display(QPainter& painter);

		MDMA::signal getMidi(MDMA::event);
		QList<MDMA::signal> update(HandDescriptor& main);

		QString name;
		QPoint P1;
		QPoint P2;
		int tab;

	bool state;
	bool hand_in;

		MDMA::type type;

		MDMA::active active[9];
		MDMA::signal signal[9];

};

#endif // EVENTZONE_H
