#include "midimanager.h"

#include <vector>

MidiManager::MidiManager()
{
#ifdef WIN32
	port = NULL;
#endif //WIN32
}

MidiManager::~MidiManager() throw()
{
#ifdef WIN32
	if(port != NULL) virtualMIDIClosePort( port );
#endif //WIN32
}

void MidiManager::createPort(QString name)
{
#ifndef WIN32
	openVirtualPort(name.toStdString());
#endif

#ifdef WIN32
	// Go VirtuamMIDISDK
	// Pour a il faut ajouter le teVirtualMIDI.h, ainsi que compiler avec teVirtualMIDI32.lib

	// On a besoin du nom de port en LPCWSTR, d'o le code un peu dgueu qui va suivre
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
	// A ce moment l, le port est cr et il est possible de s'y connecter
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


