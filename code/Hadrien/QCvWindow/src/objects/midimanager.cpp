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
	// Pour ça il faut ajouter le teVirtualMIDI.h, ainsi que compiler avec teVirtualMIDI32.lib

	// On a besoin du nom de port en LPCWSTR, d'où le code un peu dégueu qui va suivre
    int len;
    int slength = (int)name.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, name.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, name.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;

    port = virtualMIDICreatePortEx2(r.c_str, teVMCallback, 0, MAX_SYSEX_BUFFER, TE_VM_FLAGS_PARSE_RX );
	if ( !port ) {
		printf( "could not create port: %d\n", GetLastError() );
	}
    // A ce moment là, le port est créé et il est possible de s'y connecter

	// Il faut ajouter "if(port != NULL) virtualMIDIClosePort( port );" dans le destructeur
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


