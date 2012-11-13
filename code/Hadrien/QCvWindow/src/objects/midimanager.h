#ifndef MIDISIGNAL_H
#define MIDISIGNAL_H

#include <QObject>

#include "../classes/RtMidi.h"

class MidiSignal : public QObject, public RtMidiOut
{
	Q_OBJECT
	
	public:
		~MidiSignal() throw();
	
	public slots:
		void createPort();
		void changePort(int n);
		void sendMessage(const unsigned char* msg);
	
};

#endif //MIDISIGNAL_H

