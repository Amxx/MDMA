#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QList>
#include <QFileDialog>
#include <QMessageBox>

#include "zone.h"

class Configuration : public QObject, public QList<Zone>
{
		Q_OBJECT
	public:
		Configuration();
		Configuration(const Configuration& cpy);
		~Configuration();

		Zone& insertZone(Zone& z);
		void removeZone(Zone& z);

		bool isEdited();

		void setTab(int t);
		int getTab();

		bool reset();
		bool load();
		bool save();
		bool saveas();

	public slots:
		void edited(bool e = true);

	signals:
		void reconstruct();
		void tabChanged(int);

	private:
		QString _file;
		int _tab;
		bool _edit;
};

//Q_DECLARE_METATYPE(Configuration)
QDataStream & operator << (QDataStream & out, const Configuration& c);
QDataStream & operator >> (QDataStream & in, Configuration& c);

#endif // CONFIGURATION_H
