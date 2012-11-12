#include "MidiSignal.h"

#include <vector>

using std::vector;

MidiSignal::MidiSignal() : QObject()
{
	midiout = new RtMidiOut();
}

MidiSignal::~MidiSignal()
{
	delete midiout;
}

void MidiSignal::createPort()
{
	midiout->openVirtualPort("MDMA Midi Out Port");
}

void MidiSignal::changePort(int n)
{
	midiout->openPort(n);
}

void MidiSignal::sendMessage(const unsigned char* msg)
{
	vector<unsigned char> v(msg, msg+3);
	midiout->sendMessage(&v);
}


