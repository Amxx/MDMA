#include "eventmanager.h"

eventManager::eventManager(configuration &_config) : config(_config)
{
}

void eventManager::detection(HandDescriptor& main)
{
    for(eventZone& zone : config.zones.values())
    {
        if(zone.tab == config.current_tab)
        {
            QList<unsigned char*> msg = zone.update(main);
            for(unsigned char* s : msg)
                emit sendMidi(s);
            //delete[] msg;
        }
    }
}
