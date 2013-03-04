#ifndef ZONE_H
#define ZONE_H

#include <QMap>
#include <QPainter>
#include <QPoint>
#include <QString>

#include "../Utils/define.h"
#include "pointer.h"

class Zone
{
	public:
		Zone();
		Zone(QPoint _p1, QPoint _p2, int _t);
		Zone(const Zone& cpy);
		~Zone();

		void display(QPainter& painter);
		MDMA::signal getMidi(MDMA::event ev);
		QList<MDMA::event> update(QMap<int,Pointer>& pts);

//	private:
		QString name;
		QPoint pos[2];
		int tab;

		MDMA::type type;
		MDMA::active active[9];
		MDMA::signal signal[9];

		bool variable[2];
		bool emph_display;
		// bool is_active[3];
		// bool hand_in[3];
		// bool hand_open[3];

};

/*
 * Q_DECLARE_METATYPE(EventZone)
 * QDataStream & operator << (QDataStream & out, const EventZone& evz);
 * QDataStream & operator >> (QDataStream & in, EventZone& evz);
 */

#endif // ZONE_H
