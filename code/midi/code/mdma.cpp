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

int main()
{
    // Create an api map.
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
    for ( unsigned int i=0; i<apis.size(); i++ )
        std::cout << "    " << apiMap[ apis[i] ] << std::endl;

    RtMidiOut *midiout = 0;

    try {
        // RtMidiOut constructor ... exception possible
        midiout = new RtMidiOut();

        std::cout << "\nCurrent output API: " << apiMap[ midiout->getCurrentApi() ] << std::endl;

        // Check outputs.
        int nPorts = midiout->getPortCount();
        std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";

        for ( int i=0; i<nPorts; i++ ) {
            std::string portName = midiout->getPortName(i);
            std::cout << "    Output Port #" << i+1 << ": " << portName << std::endl;
        }
        std::cout << std::endl;

    } catch ( RtError &error ) {
        error.printMessage();
        return 1;
    }


    std::vector<unsigned char> message;

    // Check available ports.
    int nPorts = midiout->getPortCount();
    if ( nPorts == 0 ) {
        std::cout << "No ports available!\n";
    }
    else {
        int portNumber = -1;

        while(portNumber == -1) {
            cout << "Choose a MIDI output ports.\n";
            char tmpStr[4];
            cin.getline(tmpStr, 4, '\n');

            portNumber = atoi(tmpStr);

            if(portNumber < 1 || portNumber > nPorts) {
                cout << "Invalid port number.\n\n";
                portNumber = -1;
            }
        }

        portNumber--;

        // Open first available port.
        midiout->openPort(portNumber);

        // Send out a series of MIDI messages.

        // Program change: 192, 5
        message.push_back( 192 );
        message.push_back( 5 );
        midiout->sendMessage( &message );

        // Control Change: 176, 7, 100 (volume)
        message[0] = 176;
        message[1] = 7;
        message.push_back( 100 );
        midiout->sendMessage( &message );

        // Note On: 144, 64, 90
        message[0] = 144;
        message[1] = 64;
        message[2] = 90;
        midiout->sendMessage( &message );

        Sleep(500); // Platform-dependent ... see example in tests directory.

        // Note Off: 128, 64, 40
        message[0] = 128;
        message[1] = 64;
        message[2] = 40;
        midiout->sendMessage( &message );

        // Note On: 144, 64, 90
        message[0] = 144;
        message[1] = 64;
        message[2] = 90;
        midiout->sendMessage( &message );

        Sleep(500); // Platform-dependent ... see example in tests directory.

        // Note Off: 128, 64, 40
        message[0] = 128;
        message[1] = 64;
        message[2] = 40;
        midiout->sendMessage( &message );

        // Note On: 144, 64, 90
        message[0] = 144;
        message[1] = 64;
        message[2] = 90;
        midiout->sendMessage( &message );

        Sleep(500); // Platform-dependent ... see example in tests directory.

        // Note Off: 128, 64, 40
        message[0] = 128;
        message[1] = 64;
        message[2] = 40;
        midiout->sendMessage( &message );

        // Note On: 144, 64, 90
        message[0] = 144;
        message[1] = 64;
        message[2] = 90;
        midiout->sendMessage( &message );

        Sleep(500); // Platform-dependent ... see example in tests directory.

        // Note Off: 128, 64, 40
        message[0] = 128;
        message[1] = 64;
        message[2] = 40;
        midiout->sendMessage( &message );

        // Note On: 144, 64, 90
        message[0] = 144;
        message[1] = 64;
        message[2] = 90;
        midiout->sendMessage( &message );

        Sleep(250); // Platform-dependent ... see example in tests directory.

        // Note Off: 128, 64, 40
        message[0] = 128;
        message[1] = 64;
        message[2] = 40;
        midiout->sendMessage( &message );

        // Note On: 144, 64, 90
        message[0] = 144;
        message[1] = 64;
        message[2] = 90;
        midiout->sendMessage( &message );

        Sleep(250); // Platform-dependent ... see example in tests directory.

        // Note Off: 128, 64, 40
        message[0] = 128;
        message[1] = 64;
        message[2] = 40;
        midiout->sendMessage( &message );

        // Note On: 144, 64, 90
        message[0] = 144;
        message[1] = 64;
        message[2] = 90;
        midiout->sendMessage( &message );

        Sleep(500); // Platform-dependent ... see example in tests directory.

        // Note Off: 128, 64, 40
        message[0] = 128;
        message[1] = 64;
        message[2] = 40;
        midiout->sendMessage( &message );

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

        while(true) {
            note = 12 * (2 + position) + ((rand() % 2) * 12 + gamme[rand() % 5]);
            duree = a*(rand() % b);

            // Program change: 192, 5
            message.resize(2);
            message[0] = 192;
            message[1] = c;
            midiout->sendMessage( &message );

            // Note On: 144, 64, 90
            message[0] = 144;
            message[1] = note;
            message.push_back(90);
            midiout->sendMessage( &message );

            Sleep(duree); // Platform-dependent ... see example in tests directory.

            // Note Off: 128, 64, 40
            message[0] = 128;
            message[1] = note;
            message[2] = 40;
            midiout->sendMessage( &message );
        }
        
    }//nPorts != 0

    delete midiout;

    getchar();

    return 0;
}
