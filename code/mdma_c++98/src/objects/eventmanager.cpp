#include "eventmanager.h"

EventManager::EventManager(QObject* parent) :
	QObject(parent)
{
}

void EventManager::run_messages(EventZone& evz, QList<MDMA::event> msgs)
{
    //for(MDMA::event msg: msgs)
    for(QList<MDMA::event>::Iterator it = msgs.begin() ; it != msgs.end() ; ++it)
    {
        switch(evz.active[*it])
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
                MDMA::signal midi = evz.getMidi(*it);
				if(midi) emit sendMidi(midi);

			}
		}
	}
}


void EventManager::detection()
{
	int current_tab = Configuration::config().data.current_tab;
    //for(EventZone& evz : Configuration::config().data.zones)
    for(QMap<QString, EventZone>::Iterator it = Configuration::config().data.zones.begin() ; it != Configuration::config().data.zones.end() ; ++it)
    {
        if(it->tab == current_tab)
        {
			if(Configuration::config().track_hand)
			{
                run_messages(*it, it->update(Configuration::config().left_hand));
                run_messages(*it, it->update(Configuration::config().right_hand));
			}
			if(Configuration::config().track_mouse)
			{
                run_messages(*it, it->update(Configuration::config().mouse_hand));
			}
		}
    }
}
