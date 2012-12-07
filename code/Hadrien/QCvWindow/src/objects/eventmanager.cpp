#include "eventmanager.h"

EventManager::EventManager(QObject* parent) :
	QObject(parent)
{
}

void EventManager::run_messages(EventZone& evz, QList<MDMA::event> msgs)
{
	for(MDMA::event msg: msgs)
	{
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
			{
				MDMA::signal midi = evz.getMidi(msg);
				if(midi) emit sendMidi(midi);
			}
		}
	}
}


void EventManager::detection()
{
	int current_tab = Configuration::config().data.current_tab;
	for(EventZone& evz : Configuration::config().data.zones)
	{
		if(evz.tab == current_tab)
        {
			if(Configuration::config().track_hand)
			{
				run_messages(evz, evz.update(Configuration::config().left_hand));
				run_messages(evz, evz.update(Configuration::config().right_hand));
			}
			if(Configuration::config().track_mouse)
			{
				run_messages(evz, evz.update(Configuration::config().mouse_hand));
			}
		}
    }
}
