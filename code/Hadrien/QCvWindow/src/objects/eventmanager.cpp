#include "eventmanager.h"

EventManager::EventManager(QObject* parent) :
	QObject(parent)
{
}


void EventManager::detection()
{
	for(EventZone& evz : Configuration::config().data.zones.values())
    {
		if(evz.tab == Configuration::config().data.current_tab)
        {
			QList<MDMA::event> msgs = evz.update(Configuration::config().left_hand);
            for(MDMA::event msg: msgs)
            {
                MDMA::signal midi;
                switch(evz.active[msg])
                {
                case MDMA::GOTO_TAB1:
					Configuration::config().setCurrentTab(0);
                    break;
                case MDMA::GOTO_TAB2:
					Configuration::config().setCurrentTab(1);
                    break;
                case MDMA::GOTO_TAB3:
					Configuration::config().setCurrentTab(2);
                    break;
                default:
                    midi = evz.getMidi(msg);
                    if(midi)
                        emit sendMidi(midi);
                }
            }
			msgs = evz.update(Configuration::config().right_hand);
            for(MDMA::event msg: msgs)
            {
                MDMA::signal midi;
                switch(evz.active[msg])
                {
                case MDMA::GOTO_TAB1:
					Configuration::config().setCurrentTab(0);
                    break;
                case MDMA::GOTO_TAB2:
					Configuration::config().setCurrentTab(1);
					break;
                case MDMA::GOTO_TAB3:
					Configuration::config().setCurrentTab(2);
                    break;
                default:
                    midi = evz.getMidi(msg);
                    if(midi)
                        emit sendMidi(midi);
                }
            }
			if(Configuration::config().track_mouse)
			{
				msgs = evz.update(Configuration::config().mouse_hand);
				for(MDMA::event msg: msgs)
				{
					MDMA::signal midi;
					switch(evz.active[msg])
					{
					case MDMA::GOTO_TAB1:
						Configuration::config().setCurrentTab(0);
						break;
					case MDMA::GOTO_TAB2:
						Configuration::config().setCurrentTab(1);
						break;
					case MDMA::GOTO_TAB3:
						Configuration::config().setCurrentTab(2);
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
}
