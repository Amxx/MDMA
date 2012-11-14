#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "../objects/configuration.h"

class HandDescriptor;

class eventManager
{
public:
    eventManager(configuration& _config);

private:
    configuration& config;


public slots:
    void detection(HandDescriptor& main);

signals:
    void sendMidi(MDMA::signal);
};

#endif // EVENTMANAGER_H
