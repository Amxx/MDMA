#ifndef ZONEMANAGER_H
#define ZONEMANAGER_H

#include <algorithm>

#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QObject>
#include <QVector>

#include "configuration.h"
#include "../config/constant.h"
#include "../UI/zoneeditor.h"

class zoneManager : public QObject, public QPainter
{
		Q_OBJECT
	public:
		explicit zoneManager(configuration& _config, QObject *parent = 0);
		~zoneManager();

		void clic(QPoint pointer);
		void reset_clic();

	protected:
		void timerEvent(QTimerEvent*);

	private:
		void display();
		configuration& config;
		QPixmap pixmax;
		QPoint P1;
		QPoint P2;
};

#endif // ZONEMANAGER_H
