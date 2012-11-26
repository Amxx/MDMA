#include "eventmanager.h"

EventManager::EventManager(Configuration &_config, QObject* parent) :
	QObject(parent),
	config(_config)
{
}


void EventManager::detection()
{
	for(EventZone& evz : config.data.zones.values())
    {
		if(evz.tab == config.data.current_tab)
        {
            QList<MDMA::event> msgs = evz.update(config.left_hand);
            for(MDMA::event msg: msgs)
            {
                MDMA::signal midi;
                switch(evz.active[msg])
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
                    midi = evz.getMidi(msg);
                    if(midi)
                        emit sendMidi(midi);
                }
            }
            msgs = evz.update(config.right_hand);
            for(MDMA::event msg: msgs)
            {
                MDMA::signal midi;
                switch(evz.active[msg])
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
                    midi = evz.getMidi(msg);
                    if(midi)
                        emit sendMidi(midi);
                }
            }
		}
    }
}
