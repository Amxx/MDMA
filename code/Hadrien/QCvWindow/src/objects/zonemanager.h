#ifndef ZONEDISPLAY_H
#define ZONEDISPLAY_H

#include <algorithm>

#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QObject>
#include <QVector>

#include "../classes/configuration.h"
#include "../UI/zoneeditor.h"

class zoneDisplay : public QObject, public QPainter
{
		Q_OBJECT
	public:
		explicit zoneDisplay(configuration* _config, QObject *parent = 0);
		~zoneDisplay();

		void clic(QPoint pointer);
		void clear();

	protected:
		void timerEvent(QTimerEvent*);

	private:
		configuration* config;
		QPixmap* pixmax;

		QPoint cursor;

		//QVector<QRect> zones;
};

#endif // ZONEDISPLAY_H
