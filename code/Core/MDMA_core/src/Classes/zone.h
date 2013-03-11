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

		MDMA::signal type;
		unsigned char signal[3];
		unsigned char variable;
};

QDataStream & operator << (QDataStream & out, const Signal& s);
QDataStream & operator >> (QDataStream & in, Signal& s);

class Zone : public QObject, public QMap<int, Signal>
{
		Q_OBJECT
	public:
		Zone();
		Zone(QRect r, int t);
		Zone(const Zone& cpy);
		~Zone();

		QList<Signal> getSignals(QMap<int,Pointer>& pts);
		bool operator==( const Zone& z ) const { return this == &z; }

	public slots:
		void update();
	signals:
		void updated();
		void deleted();
	public:
		MDMA::type _type;
		QString _name;
		QRect _geo;
		int _tab;
		int _var;
		bool _active;
};

QDataStream & operator << (QDataStream & out, const Zone& evz);
QDataStream & operator >> (QDataStream & in, Zone& evz);


#endif // ZONE_H
