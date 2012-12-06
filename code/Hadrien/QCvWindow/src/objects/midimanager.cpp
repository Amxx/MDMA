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
	if(port != NULL) virtualMIDIClosePort( port ); // This closes the port opened by virtualMIDISDK (if it exists)
#endif //WIN32

	closePort(); // This closes an open MIDI connection initiated by RtMidiOut (if one exists)
}

void MidiManager::createPort(QString name)
{
	closePort();

#ifndef WIN32
	openVirtualPort(name.toStdString());
#endif

#ifdef WIN32
	// Go VirtuamMIDISDK
	// Pour ca il faut ajouter le teVirtualMIDI.h, ainsi que compiler avec teVirtualMIDI32.lib

	if(port != NULL) {
		virtualMIDIClosePort(port);
		port = NULL;
	}

	// We need the name of the MIDI port in LPCWSTR, this this awfull part of code
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
#endif
}

void MidiManager::changePort(int n)
{
	closePort();

#ifdef WIN32
	if(port != NULL) {
		virtualMIDIClosePort( port );
		port = NULL;
	}
#endif //WIN32

	openPort(n);
}

//void MidiManager::sendMessage(const unsigned char* msg)
void MidiManager::sendMessage(MDMA::signal msg)
{
#ifdef WIN32
    if(port) { // Utilisation d'un port cree par VirtualMIDISDK
        if(((msg[0] & 0xf0) == 0xc0) || ((msg[0] & 0xf0) == 0xd0)) // program change or channel aftertouch
        {
            qDebug() << "size 2: program change or channel aftertouch";
            char midiDataBytes[2] = {msg[0], msg[1]};
            virtualMIDISendData(port, (LPBYTE)midiDataBytes, (DWORD)16);
        }
        else {
            qDebug() << "size 3";
            char midiDataBytes[3] = {msg[0], msg[1], msg[2]};
            virtualMIDISendData(port, (LPBYTE)midiDataBytes, (DWORD)24);
        }
    }
    else { // Utilisation d'un port déjà existant
        std::vector <unsigned char> v;

        if(((msg[0] & 0xf0) == 0xc0) || ((msg[0] & 0xf0) == 0xd0)) // program change or channel aftertouch
        {
            qDebug() << "size 2: program change or channel aftertouch";
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
#endif //WIN32

#ifndef WIN32
	std::vector <unsigned char> v;

	if(((msg[0] & 0xf0) == 0xc0) || ((msg[0] & 0xf0) == 0xd0))//program change or channel aftertouch
	{
		qDebug() << "size 2: program change or channel aftertouch";
		v.assign(msg, msg+2);
	}
	else
	{
		qDebug() << "size 3";
		v.assign(msg, msg+3);
	}

	RtMidiOut::sendMessage(&v);

	delete msg;
#endif //NOT WIN32
}
