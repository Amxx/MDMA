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
	vector<unsigned char> v(msg, msg+3);
	sendMessage(&v);
}


