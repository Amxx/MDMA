#ifndef MIDIMANAGER_H
#define MIDIMANAGER_H

#include <QObject>
#include <QDebug>

#include "../config/constant.h"
#include "../classes/RtMidi.h"

#ifdef __WINDOWS_MM__
#include "../include/teVirtualMIDI.h"
#endif //WIN32

class MidiManager : public QObject, public RtMidiOut
{
	Q_OBJECT

#ifdef __WINDOWS_MM__
	private:
		LPVM_MIDI_PORT port;
#endif //WIN32

	public:
		std::string MIDIPortName;

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
