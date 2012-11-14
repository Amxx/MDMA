#ifndef MIDIMANAGER_H
#define MIDIMANAGER_H

#include <QObject>

#include "../classes/RtMidi.h"

class midiManager : public QObject, public RtMidiOut
{
	Q_OBJECT
	
	public:
		~midiManager() throw();
	
	public slots:
		void createPort(QString name);
		void changePort(int n);
		void sendMessage(const unsigned char* msg);
	
};

#endif //MIDIMANAGER_H

