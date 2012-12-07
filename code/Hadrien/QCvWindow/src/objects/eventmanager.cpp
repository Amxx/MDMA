#include "eventmanager.h"

EventManager::EventManager(QObject* parent) :
	QObject(parent)
{
}


void EventManager::detection()
{
	QMap<QString, EventZone>::Iterator evz;
	for(evz = Configuration::config().data.zones.begin(); evz != Configuration::config().data.zones.end(); ++evz)
	{
		if(evz.value().tab == Configuration::config().data.current_tab)
        {
			QList<MDMA::event> msgs;
			if(Configuration::config().track_image)
			{
				msgs = evz.value().update(Configuration::config().left_hand);
				for(MDMA::event msg: msgs)
				{
					MDMA::signal midi;
					switch(evz.value().active[msg])
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
						midi = evz.value().getMidi(msg);
						if(midi)
							emit sendMidi(midi);
					}
				}
				msgs = evz.value().update(Configuration::config().right_hand);
				for(MDMA::event msg: msgs)
				{
					MDMA::signal midi;
					switch(evz.value().active[msg])
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
						midi = evz.value().getMidi(msg);
						if(midi)
							emit sendMidi(midi);
					}
				}
			}
			if(Configuration::config().track_mouse)
			{
				msgs = evz.value().update(Configuration::config().mouse_hand);
				for(MDMA::event msg: msgs)
				{
					MDMA::signal midi;
					switch(evz.value().active[msg])
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
						midi = evz.value().getMidi(msg);
						if(midi)
							emit sendMidi(midi);
					}
				}
			}
		}
    }
}
