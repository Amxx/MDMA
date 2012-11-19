#include "midimanager.h"

#include <vector>

MidiManager::~MidiManager() throw()
{
	
}

void MidiManager::createPort(QString name)
{
#ifndef WIN32
	openVirtualPort(name.toStdString());
#endif

#ifdef WIN32
	// Go VirtuamMIDISDK
#endif
}

void MidiManager::changePort(int n)
{
	openPort(n);
}

void MidiManager::sendMessage(const unsigned char* msg)
{
	std::vector <unsigned char> v;
	
	if(((msg[0] & 0xf0) == 0xc0) || ((msg[0] & 0xf0) == 0xd0))//program change or channel aftertouch
	{
		qDebug() << "size 2 : program change or channel aftertouch";
		v.assign(msg, msg+2);
	}
	else
	{
		qDebug() << "size 3";
		v.assign(msg, msg+3);
	}

	RtMidiOut::sendMessage(&v);

	delete msg;
}


