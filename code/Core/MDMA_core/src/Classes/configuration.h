#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QSet>

#include "zone.h"

class Configuration : public QObject, public QSet<Zone*>
{
		Q_OBJECT
	public:
		Configuration();
		~Configuration();

		void Reset();
		void Load();
		void Save();
		void Saveas();

		void setTab(int t);
		int getTab();

	signals:
		void tabChanged(int);

	private:
		QString _file;
		int _tab;
};

#endif // CONFIGURATION_H
