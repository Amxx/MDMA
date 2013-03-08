#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QMap>

#include "zone.h"

class Configuration : public QMap<QString, Zone*>
{
	public:
		Configuration();
		~Configuration();

		void Reset();
		void Load();
		void Save();
		void Saveas();

		void setTab(int tb);
		int getTab();

		/*
		void addZone(Zone zn);
		Zone& getZone(QString zn_id);
		*/

	private:
		QString file;

		int tab;
//		QMap<QString,Zone> zns;
};

#endif // CONFIGURATION_H
