#ifndef MIDIMANAGER_H
#define MIDIMANAGER_H

#include <QObject>
#include <QDebug>

#include "../classes/RtMidi.h"

#ifdef WIN32
#include "../include/teVirtualMIDI.h"
#endif //WIN32

class MidiManager : public QObject, public RtMidiOut
{
	Q_OBJECT

#ifdef WIN32
	private:
		LPVM_MIDI_PORT port; // L'initialiser  NULL dans le constructeur
#endif //WIN32

	public:
		MidiManager();
		~MidiManager() throw();

	public slots:
		void createPort(QString name);
		void changePort(int n);
		void sendMessage(const unsigned char* msg);

};

#endif //MIDIMANAGER_H
