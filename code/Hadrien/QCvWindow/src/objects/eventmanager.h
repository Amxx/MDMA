#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "configuration.h"

class HandDescriptor;

class EventManager : public QObject
{
		Q_OBJECT

	public:
		EventManager(Configuration& _config, QObject* parent = 0);

	public slots:
		void detection(HandDescriptor& main);

	signals:
		void sendMidi(MDMA::signal);

	private:
		Configuration& config;

};

#endif // EVENTMANAGER_H
