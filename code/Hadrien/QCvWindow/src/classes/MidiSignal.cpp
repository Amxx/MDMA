#include "MidiSignal.h"

#include <vector>

using std::vector;

void MidiSignal::createPort()
{
	openVirtualPort("MDMA Midi Out Port");
}

void MidiSignal::changePort(int n)
{
	openPort(n);
}

void MidiSignal::sendMessage(const unsigned char* msg)
{
	vector<unsigned char> v;
	
	if(((msg[0] & 0xf0) == 0xc0) || ((msg[0] & 0xf0) == 0xd0))//program change or channel aftertouch
		v.assign(msg, msg+2);
	else
		v.assign(msg, msg+3);
	
	sendMessage(&v);
}


