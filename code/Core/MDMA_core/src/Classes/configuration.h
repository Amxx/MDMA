#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QMap>

#include <QFileDialog>

#include "zone.h"

class Configuration : public QObject, public QList<Zone>//QMap<int,Zone>
{
		Q_OBJECT
	public:
		Configuration();
		Configuration(const Configuration& cpy);
		~Configuration();
		static void initZone();

		Zone& insertZone(Zone& z);
		void removeZone(Zone& z);

		bool reset();
		bool load();
		bool save();
		bool saveas();

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
