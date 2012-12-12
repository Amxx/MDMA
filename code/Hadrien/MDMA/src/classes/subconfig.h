#ifndef SUBCONFIG_H
#define SUBCONFIG_H

#include <QMap>
#include <QString>

#include "eventzone.h"

class SubConfig
{
	public:
		SubConfig();
		SubConfig(const SubConfig& sub_config);
		~SubConfig();

		static void initSubConfig();

		QString version;
		QString name;
		QString path;
		int current_tab;
		QMap<QString, EventZone> zones;
};

Q_DECLARE_METATYPE(SubConfig)
QDataStream & operator << (QDataStream & out, const SubConfig& evz);
QDataStream & operator >> (QDataStream & in, SubConfig& evz);

#endif // SUBCONFIG_H
