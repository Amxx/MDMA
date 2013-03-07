#ifndef ZONE_H
#define ZONE_H

#include <QMap>
#include <QPainter>
#include <QPoint>
#include <QString>

#include "../Utils/define.h"
#include "pointer.h"

class Signal
{
	MDMA::signal type;
	unsigned char signal[3];
	unsigned char variable;
};


class Zone : QMap<MDMA::event, Signal>
{
	public:
		Zone();
		Zone(QRect r, int t);
		Zone(const Zone& cpy);
		~Zone();

		//void display(QPainter& painter);
		//MDMA::signal getMidi(MDMA::event ev);
		//QList<MDMA::event> update(QMap<int,Pointer>& pts);

	private:
		MDMA::type _type;
		QString _name;
		QRect _pos;
		int _tab;
		bool _active;
};

/*
 * Q_DECLARE_METATYPE(EventZone)
 * QDataStream & operator << (QDataStream & out, const EventZone& evz);
 * QDataStream & operator >> (QDataStream & in, EventZone& evz);
 */

#endif // ZONE_H
