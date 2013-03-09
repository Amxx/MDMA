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
	public:
		Signal();
		static void initSignal();

		MDMA::signal type;
		unsigned char signal[3];
		unsigned char variable;
};

Q_DECLARE_METATYPE(Signal)
QDataStream & operator << (QDataStream & out, const Signal& s);
QDataStream & operator >> (QDataStream & in, Signal& s);

class Zone : public QObject, public QMap<MDMA::event, Signal>
{
		Q_OBJECT
	public:
		Zone();
		Zone(QRect r, int t);
		Zone(const Zone& cpy);
		~Zone();

		static void initZone();
		QList<Signal> update(QMap<int,Pointer>& pts);
		bool operator==( const Zone& z ) const { return this == &z; }
	signals:
		void updated();
		void deleted();
	public:
		//int _id;
		MDMA::type _type;
		QString _name;
		QRect _geo;
		int _tab;
		bool _active;
};

Q_DECLARE_METATYPE(Zone)
QDataStream & operator << (QDataStream & out, const Zone& evz);
QDataStream & operator >> (QDataStream & in, Zone& evz);


#endif // ZONE_H
