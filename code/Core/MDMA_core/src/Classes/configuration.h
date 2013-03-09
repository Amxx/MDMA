#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QList>

#include "zone.h"

class Configuration : public QObject, public QList<Zone>
{
		Q_OBJECT
	public:
		Configuration();
		Configuration(const Configuration& cpy);
		~Configuration();
		static void initConfiguration();

		Zone& insertZone(Zone& z);
		void removeZone(Zone& z);

	public slots:
		void edited();

	public:
		QString _file;
		int _tab;
		bool _edit;
};

Q_DECLARE_METATYPE(Configuration)
QDataStream & operator << (QDataStream & out, const Configuration& c);
QDataStream & operator >> (QDataStream & in, Configuration& c);

#endif // CONFIGURATION_H
