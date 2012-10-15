#include "log.h"
#include <iostream>

Log::Log(QObject *parent) :
    QObject(parent)
{
}

void Log::receive_detection(int id, int valeur)
{
    std::cout << id << ' ' << valeur << std::endl;
}
