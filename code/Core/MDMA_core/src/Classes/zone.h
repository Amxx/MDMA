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


class Zone : public QObject, public QMap<MDMA::event, Signal>
{
		Q_OBJECT
	public:
		Zone();
		Zone(QRect r, int t);
		Zone(const Zone& cpy);
		~Zone();

		//void display(QPainter& painter);
		//QList<MDMA::event> update(QMap<int,Pointer>& pts);

	signals:
		void updated();
		void deleted();

	//private:
	public:
		MDMA::type _type;
		QString _name;
		QRect _geo;
		int _tab;
		bool _active;
};

/*
 * Q_DECLARE_METATYPE(EventZone)
 * QDataStream & operator << (QDataStream & out, const EventZone& evz);
 * QDataStream & operator >> (QDataStream & in, EventZone& evz);
 */

#endif // ZONE_H
