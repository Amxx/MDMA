#ifndef ZONEMANAGER_H
#define ZONEMANAGER_H

#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QObject>
#include <QVector>

#include "configuration.h"
#include "../config/constant.h"
#include "../UI/zoneeditor.h"

class ZoneManager : public QObject, public QPainter
{
		Q_OBJECT
	public:
		explicit ZoneManager(Configuration& _config, QObject *parent = 0);
		~ZoneManager();

		void set_zone(QPoint pointer);
		void reset_clic();

	protected:
		void timerEvent(QTimerEvent*);

	private:
		void display();
		Configuration& config;
		QPixmap pixmax;
		QPoint P1;
		QPoint P2;
};

#endif // ZONEMANAGER_H
