#include "midimanager.h"

#include <vector>
#include <iostream>

#ifdef __WINDOWS_MM__

#define MAX_SYSEX_BUFFER	65535

char *binToStr( const unsigned char *data, DWORD length ) {
    static char dumpBuffer[ MAX_SYSEX_BUFFER * 3 ];
    DWORD index = 0;

    while ( length-- ) {
        sprintf( dumpBuffer+index, "%02x", *data );
        if ( length ) {
            strcat( dumpBuffer, ":" );
        }
        index+=3;
        data++;
    }
    return dumpBuffer;
}

void CALLBACK teVMCallback( LPVM_MIDI_PORT midiPort, LPBYTE midiDataBytes, DWORD length, DWORD_PTR dwCallbackInstance ) {
    if ( ( NULL == midiDataBytes ) || ( 0 == length ) ) {
        std::cerr << "empty command - driver was probably shut down!" << std::endl;
        return;
    }
    if ( !virtualMIDISendData( midiPort, midiDataBytes, length ) ) {
        std::cerr << "error sending data: " << GetLastError() << std::endl;
        return;
    }
      qDebug() << "command: " << binToStr( midiDataBytes, length );
}

#endif

MidiManager::MidiManager()
{
#ifdef __WINDOWS_MM__
	port = NULL;
#endif //WIN32

	MIDIPortName = "";
	current_port = -1;

/*
	createPort(QString("MDMA"));
*/

#ifdef __WINDOWS_MM__
	changePort(0); // Using Windows, there normally always exists a MIDI port n.0
#elif //__WINDOWS_MM__
	createPort(QString("MDMA"));
#endif //NOT __WINDOWS_MM__
}

MidiManager::~MidiManager() throw()
{
#ifdef __WINDOWS_MM__
	if(port != NULL) virtualMIDIClosePort( port ); // This closes the port opened by virtualMIDISDK (if it exists)
#endif //__WINDOWS_MM__

	closePort(); // This closes an open MIDI connection initiated by RtMidiOut (if one exists)
}

void MidiManager::createPort(QString name)
{
	closePort();
	current_port = -1;

/*
#ifdef __WINDOWS_MM__
	// Go VirtuamMIDISDK
	// Pour ca il faut ajouter le teVirtualMIDI.h, ainsi que compiler avec teVirtualMIDI.lib

	if(port != NULL) {
		virtualMIDIClosePort(port);
		port = NULL;
	}

	// We need the name of the MIDI port in LPCWSTR, this this awfull part of code
	int len;
	int slength = name.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, name.toStdString().c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, name.toStdString().c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;

    port = virtualMIDICreatePortEx2(r.c_str(), teVMCallback, 0, MAX_SYSEX_BUFFER, TE_VM_FLAGS_PARSE_RX );
	if ( !port ) {
        std::cerr << "could not create port: " << GetLastError() << std::endl;
	}
#else
    openVirtualPort(name.toStdString());
#endif
*/
	openVirtualPort(name.toStdString());

	MIDIPortName = name.toStdString();
}

void MidiManager::changePort(int n)
{
	closePort();

/*
#ifdef __WINDOWS_MM__
	if(port != NULL) {
		virtualMIDIClosePort( port );
		port = NULL;
	}
#endif //__WINDOWS_MM__
*/

	current_port = n;
	openPort(current_port);

	MIDIPortName = "";
}

//void MidiManager::sendMessage(const unsigned char* msg)
void MidiManager::sendMessage(MDMA::signal msg)
{
#ifdef __WINDOWS_MM__
/*
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
*/
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
#else
	std::vector<unsigned char> v;

	if(((msg[0] & 0xf0) == 0xc0) || ((msg[0] & 0xf0) == 0xd0)) //program change or channel aftertouch
	{
		//qDebug() << "size 2: program change or channel aftertouch";
		v.assign(msg, msg+2);
	}
	else
	{
		//qDebug() << "size 3";
		v.assign(msg, msg+3);
	}
	//qDebug() << msg[0] << msg[1] << msg[2];

	RtMidiOut::sendMessage(&v);

	delete msg;
#endif // NOT __WINDOWS_MM__
}
