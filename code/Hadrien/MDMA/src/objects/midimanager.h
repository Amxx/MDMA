#ifndef MIDIMANAGER_H
#define MIDIMANAGER_H

#include <QObject>
#include <QDebug>

#include "../config/constant.h"
#include "../classes/RtMidi.h"

#ifdef WIN32
#include "../include/teVirtualMIDI.h"
#endif //WIN32

class MidiManager : public QObject, public RtMidiOut
{
	Q_OBJECT

#ifdef WIN32
	private:
		LPVM_MIDI_PORT port;
#endif //WIN32

	public:
		MidiManager();
		~MidiManager() throw();

		int current_port;

	public slots:
		void createPort(QString name);
		void changePort(int n);
		//void sendMessage(const unsigned char* msg);
		void sendMessage(MDMA::signal msg);

};

#endif //MIDIMANAGER_H
