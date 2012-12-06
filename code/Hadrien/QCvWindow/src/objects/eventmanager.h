#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <QDebug>

#include "configuration.h"

class HandDescriptor;

class EventManager : public QObject
{
		Q_OBJECT

	public:
		EventManager(QObject* parent = 0);

	public slots:
        void detection();

	signals:
		void sendMidi(MDMA::signal);
};

#endif // EVENTMANAGER_H
