#include "midimanager.h"

#include <vector>

MidiManager::~MidiManager() throw()
{
	
}

void MidiManager::createPort(QString name)
{
	openVirtualPort(name.toStdString());
}

void MidiManager::changePort(int n)
{
	openPort(n);
}

void MidiManager::sendMessage(const unsigned char* msg)
{
	std::vector <unsigned char> v;
	
	if(((msg[0] & 0xf0) == 0xc0) || ((msg[0] & 0xf0) == 0xd0))//program change or channel aftertouch
		v.assign(msg, msg+2);
	else
		v.assign(msg, msg+3);
	
	RtMidiOut::sendMessage(&v);
}


