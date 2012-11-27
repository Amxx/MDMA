// midiprobe.cpp
//
// Simple program to check MIDI inputs and outputs.
//
// by Gary Scavone, 2003-2012.

#include <iostream>
#include <cstdlib>
#include <map>
#include "RtMidi.h"

#ifdef WIN32
  #include <conio.h>
  #include <windows.h>
#else
  #include <unistd.h>
  //sleep t milliseconds
  void Sleep(int t)
  {
        usleep(t*1000);
  }
#endif

#include <time.h>
#include <cstdio>

using namespace std;

void send2(RtMidiOut *out, unsigned char a, unsigned char b)
{
	static vector<unsigned char> msg(2);
	msg[0] = a;
	msg[1] = b;
	out->sendMessage(&msg);
}

void send3(RtMidiOut *out, unsigned char a, unsigned char b, unsigned char c)
{
	static vector<unsigned char> msg(3);
	msg[0] = a;
	msg[1] = b;
	msg[2] = c;
	out->sendMessage(&msg);
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

#ifndef WIN32
	std::cout << "    Output Port #" << nPorts+1 << ": Create virtual port" << std::endl;
#endif

	int portNumber = 0;

	while(portNumber == 0) {
		cout << "Choose a MIDI output port.\n";
		cin >> portNumber;

#ifndef WIN32
		if(portNumber == nPorts+1) {
			return -1;
		}
#endif

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

	RtMidiOut *midiout = 0;

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
		midiout->openVirtualPort(portName);
//		std::cout << "Création d'un port virtuel" << std::endl;
	}
	else {
		// Open first available port.
		midiout->openPort(portNumber);
	}

	// Check available ports.
	displayOutputPorts(midiout);

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
	message.resize(2);
	message[0] = 192;
	message[1] = c;
	midiout->sendMessage( &message );
	message.resize(3);

	for(int i=0; i<extraNotes; i++) {
	note = 12 * (2 + position) + ((rand() % 2) * 12 + gamme[rand() % 4]);
	duree = a*(rand() % b);

	// Note On
	send3(midiout, 144, note, 90);

	Sleep(duree);

	// Note Off
	send3(midiout, 128, note, 40);
	}
	cout << "End of music." << endl;

	delete midiout;


	return 0;
}
