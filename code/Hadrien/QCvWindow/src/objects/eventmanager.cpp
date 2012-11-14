#include "eventmanager.h"

EventManager::EventManager(Configuration &_config, QObject* parent) :
	QObject(parent),
	config(_config)
{
}


void EventManager::detection(HandDescriptor& main)
{
	for(EventZone& evz : config.zones.values())
    {
		if(evz.tab == config.current_tab)
        {
			QList<MDMA::signal> msgs = evz.update(main);
			for(MDMA::signal msg: msgs)
			{
				emit sendMidi(msg);
			}
		}
    }
}
