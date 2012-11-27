#include <iostream>
#include <cstdlib>
#include <map>
#include "RtMidi.h"
#include <time.h>
#include <cstdio>

#include <conio.h>
#include <windows.h>

#include "teVirtualMIDI.h"

#define MAX_SYSEX_BUFFER	65535

using namespace std;

RtMidiOut *midiout = 0;
LPVM_MIDI_PORT port = NULL;

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
		printf( "empty command - driver was probably shut down!\n" );
		return;
	}
	if ( !virtualMIDISendData( midiPort, midiDataBytes, length ) ) {
		printf( "error sending data: %d\n" + GetLastError() );
		return;
	}
      printf( "command: %s\n", binToStr( midiDataBytes, length ) );
}

void send2(unsigned char a, unsigned char b)
{
    if(port) {
        char midiDataBytes[2] = {a, b};
        virtualMIDISendData(port, (LPBYTE)midiDataBytes, (DWORD)16);
    }
    else {
        static vector<unsigned char> msg(2);
        msg[0] = a;
        msg[1] = b;
        midiout->sendMessage(&msg);
    }
}

void send3(unsigned char a, unsigned char b, unsigned char c)
{
    if(port) {
        char midiDataBytes[3] = {a, b ,c};
        virtualMIDISendData(port, (LPBYTE)midiDataBytes, (DWORD)24);
    }
    else {
        static vector<unsigned char> msg(3);
        msg[0] = a;
        msg[1] = b;
        msg[2] = c;
        midiout->sendMessage(&msg);
    }
}

void displayOutputPorts(RtMidiOut *midiout) {
	int nPorts = midiout->getPortCount();
	std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";

	for(int i=0; i<nPorts; i++) {
	    std::string portName = midiout->getPortName(i);
	    std::cout << "    Output Port #" << i+1 << ": " << portName << std::endl;
	}
}

int askOutputPorts(RtMidiOut *midiout) {
	int nPorts = midiout->getPortCount();
	std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";

	for(int i = 0; i < nPorts; i++) {
	    std::string portName = midiout->getPortName(i);
	    std::cout << "    Output Port #" << i+1 << ": " << portName << std::endl;
	}

	std::cout << "    Output Port #" << nPorts+1 << ": Create virtual port" << std::endl;

	int portNumber = 0;

	while(portNumber == 0) {
		cout << "Choose a MIDI output port.\n";
		cin >> portNumber;
		if(portNumber == nPorts+1) {
			return -1;
		}

		if(portNumber < 1 || portNumber > nPorts) {
		    cout << "Invalid port number.\n\n";
		    portNumber = 0;
		}
	}

	portNumber--;

	return portNumber;
}

int main()
{
	// Create an api map. (to print api names more easily)
	std::map<int, std::string> apiMap;
	apiMap[RtMidi::MACOSX_CORE] = "OS-X CoreMidi";
	apiMap[RtMidi::WINDOWS_MM] = "Windows MultiMedia";
	apiMap[RtMidi::WINDOWS_KS] = "Windows Kernel Straming";
	apiMap[RtMidi::UNIX_JACK] = "Jack Client";
	apiMap[RtMidi::LINUX_ALSA] = "Linux ALSA";
	apiMap[RtMidi::RTMIDI_DUMMY] = "RtMidi Dummy";

	std::vector< RtMidi::Api > apis;
	RtMidi :: getCompiledApi( apis );

	std::cout << "\nCompiled APIs:\n";
	for(unsigned int i=0; i < apis.size(); i++) {
		std::cout << "    " << apiMap[ apis[i] ] << std::endl;
	}

	try {
		// RtMidiOut constructor ... exception possible
		midiout = new RtMidiOut();

		std::cout << "\nCurrent output API: " << apiMap[ midiout->getCurrentApi() ] << std::endl;
	} catch (RtError &error) {
		error.printMessage();
		return 1;
	}

	std::vector<unsigned char> message;

	int portNumber = askOutputPorts(midiout);
	std::string portName = "MDMA";

	if(portNumber == -1) {
        port = virtualMIDICreatePortEx2( L"MDMA", teVMCallback, 0, MAX_SYSEX_BUFFER, TE_VM_FLAGS_PARSE_RX );
        if ( !port ) {
            printf( "could not create port: %d\n", GetLastError() );
            return 0;
        }
	}
	else {
		midiout->openPort(portNumber);
	}

	int extraNotes = 0;
	cout << "Extra notes to send: ";
	cin >> extraNotes;
	cout << endl;

	// Send out a series of MIDI messages.
	std::vector<unsigned int> gamme;
	gamme.push_back(0);
	gamme.push_back(3);
	gamme.push_back(5);
	gamme.push_back(7);
	gamme.push_back(9);

	srand(time(NULL));

	int note;
	int duree;

	int position = rand() % 7;
	int a, b, c;
	a = 50*(rand() % 6 + 1);
	b = (rand() % 4 + 4);
	c = rand() % 128;
	std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;

	// Program change: 192, 5
//	message.resize(2);
//	message[0] = 192;
//	message[1] = c;
//	midiout->sendMessage( &message );
//	message.resize(3);
    send2(192, c);

	for(int i = 0; i < extraNotes; i++) {
        note = 12 * (2 + position) + ((rand() % 2) * 12 + gamme[rand() % 4]);
        duree = a*(rand() % b);

        // Note On: 144, 64, 90
    //	message[0] = 144;
    //	message[1] = note;
    //	message[2] = 90;
        send3(144, note, 90);

        Sleep(duree);

        // Note Off: 128, 64, 40
    //	message[0] = 128;
    //	message[1] = note;
    //	message[2] = 40;
        send3(128, note, 40);
	}

	cout << "End of music." << endl;

    if(port) {
        virtualMIDIClosePort( port );
    }
    else {
        delete midiout;
    }

	return 0;
}
