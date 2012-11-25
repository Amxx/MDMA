#ifndef MIDIMANAGER_H
#define MIDIMANAGER_H

#include <QObject>
#include <QDebug>

#include "../classes/RtMidi.h"

class MidiManager : public QObject, public RtMidiOut
{
	Q_OBJECT

	private LPVM_MIDI_PORT port; // L'initialiser à NULL dans le constructeur

	public:
		~MidiManager() throw();

	public slots:
		void createPort(QString name);
		void changePort(int n);
		void sendMessage(const unsigned char* msg);

};

#endif //MIDIMANAGER_H

