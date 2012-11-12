#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "../objects/configuration.h"

class eventManager
{
public:
    eventManager(configuration& _config);

private:
    configuration& config;


public slots:
    //void detection(Info& main);

signals:
    void sendMidi();
};

#endif // EVENTMANAGER_H
