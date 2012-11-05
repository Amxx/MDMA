#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QVector>
#include "eventzone.h"

class configuration
{
	public:
		configuration();

		QString name;
		QString file;

		bool changed;
		int current_tab;
		QVector<EventZone> Zones;

};

#endif // CONFIGURATION_H
