#ifndef EVENTZONE_H
#define EVENTZONE_H

#include <QMap>
#include <QPainter>
#include <QPoint>
#include <QString>

#include "../config/constant.h"

class HandDescriptor;

class eventZone
{
	public:
		eventZone();
		eventZone(const eventZone &cpy);
		eventZone(QPoint _P1, QPoint _P2, int _tab);
		~eventZone();

		void display(QPainter& painter);

		unsigned char* getMidi(MDMA::event);

        unsigned char* update(HandDescriptor& main);

		QString name;
		QPoint P1;
		QPoint P2;
		int tab;

        bool state;
        bool hand_in;

		MDMA::type type;

		MDMA::active active[7];
		MDMA::signal signal[7];

};

#endif // EVENTZONE_H
