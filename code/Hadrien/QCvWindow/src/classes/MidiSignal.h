#ifndef MIDISIGNAL_H
#define MIDISIGNAL_H

#include <QObject>

#include "RtMidi.h"

class MidiSignal : public QObject
{
	Q_OBJECT
	
	public:
		MidiSignal();
		~MidiSignal();
	
	public slots:
		void createPort();
		void changePort(int n);
		void sendMessage(const unsigned char* msg);
	
	private:
		RtMidiOut *midiout;
};

#endif //MIDISIGNAL_H

