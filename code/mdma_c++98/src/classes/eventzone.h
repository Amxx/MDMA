#ifndef EVENTZONE_H
#define EVENTZONE_H

#include <cmath>
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

		static void initEventZone();

		// ----------------------------------------------------------
		// Methode
		// ----------------------------------------------------------

		void display(QPainter& painter);
		MDMA::signal getMidi(MDMA::event);
        QList<MDMA::event> update(HandDescriptor& main);

		// ----------------------------------------------------------
		// Variables
		// ----------------------------------------------------------

		QString name;
		QPoint P1;
		QPoint P2;
		int tab;

		// ----------------------------------------------------------

		MDMA::type type;
		MDMA::active active[9];
		MDMA::signal signal[9];
		bool variable[2];

		// ----------------------------------------------------------

		bool emph_display;
		bool is_active[3];
		bool hand_in[3];
		bool hand_open[3];
};


Q_DECLARE_METATYPE(EventZone)
QDataStream & operator << (QDataStream & out, const EventZone& evz);
QDataStream & operator >> (QDataStream & in, EventZone& evz);


#endif // EVENTZONE_H
