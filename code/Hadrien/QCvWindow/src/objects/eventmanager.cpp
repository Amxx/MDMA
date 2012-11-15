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
            QList<MDMA::event_signal> msgs = evz.update(main);
            for(MDMA::event_signal msg: msgs)
			{
                switch(msg.first)
                {
                case MDMA::GOTO_TAB1:
                    config.setCurrentTab(0);
                    break;
                case MDMA::GOTO_TAB2:
                    config.setCurrentTab(1);
                    break;
                case MDMA::GOTO_TAB3:
                    config.setCurrentTab(2);
                    break;
                default:
                    if(msg.second)
                        emit sendMidi(msg.second);
                }
			}
		}
    }
}
