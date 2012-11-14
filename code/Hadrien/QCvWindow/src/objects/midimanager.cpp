#include "midimanager.h"

#include <vector>

using std::vector;

midiManager::~midiManager() throw()
{
	
}

void midiManager::createPort(QString name)
{
	openVirtualPort(name.toStdString());
}

void midiManager::changePort(int n)
{
	openPort(n);
}

void midiManager::sendMessage(const unsigned char* msg)
{
	vector<unsigned char> v;
	
	if(((msg[0] & 0xf0) == 0xc0) || ((msg[0] & 0xf0) == 0xd0))//program change or channel aftertouch
		v.assign(msg, msg+2);
	else
		v.assign(msg, msg+3);
	
	RtMidiOut::sendMessage(&v);
}


