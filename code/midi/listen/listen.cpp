#include <iostream>
#include <cstdlib>
#include <signal.h>
#include "RtMidi.h"
#include <time.h>
#include <cstdio>

#ifdef WIN32
  #include <conio.h>
  #include <windows.h>
#else
  #include <unistd.h>
  //Sleep t milliseconds
  void Sleep(int t)
  {
        usleep(t*1000);
  }
#endif

bool done;
static void finish(int ignore){ done = true; }

void displayInputPorts(RtMidiIn *midiin) {
	int nPorts = midiin->getPortCount();
	std::cout << "There are " << nPorts << " MIDI input ports available.\n";

	for(int i=0; i<nPorts; i++) {
	    std::string portName = midiin->getPortName(i);
	    std::cout << "    Input Port #" << i+1 << ": " << portName << std::endl;
	}
}

int askInputPorts(RtMidiIn *midiin) {
	int nPorts = midiin->getPortCount();
	std::cout << "There are " << nPorts << " MIDI input ports available.\n";

	for(int i=0; i<nPorts; i++) {
	    std::string portName = midiin->getPortName(i);
	    std::cout << "    Input Port #" << i+1 << ": " << portName << std::endl;
	}

	int portNumber = 0;

	while(portNumber == 0) {
		std::cout << "Choose a MIDI output port.\n";
		std::cin >> portNumber;

		if(portNumber < 1 || portNumber > nPorts) {
		    std::cout << "Invalid port number.\n\n";
		    portNumber = 0;
		}
	}

	portNumber--;

	return portNumber;
}

int main()
{
  RtMidiIn *midiin = new RtMidiIn();
  std::vector<unsigned char> message;
  int nBytes, i;
  double stamp;

  // Check available ports.
  unsigned int nPorts = midiin->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No ports available!\n";
    goto cleanup;
  }
  midiin->openPort(askInputPorts(midiin));

  // Don't ignore sysex, timing, or active sensing messages.
  midiin->ignoreTypes( false, false, false );

  // Install an interrupt handler function.
  done = false;
  (void) signal(SIGINT, finish);

  // Periodically check input queue.
  std::cout << "Reading MIDI from port ... quit with Ctrl-C.\n";
  while ( !done ) {
    stamp = midiin->getMessage( &message );
    nBytes = message.size();
    for ( i=0; i<nBytes; i++ )
      std::cout << "Byte " << i << " = " << (int)message[i] << ", ";
    if ( nBytes > 0 )
      std::cout << "stamp = " << stamp << std::endl;

    // Sleep for 10 milliseconds ... platform-dependent.
    Sleep( 10 );
  }

  // Clean up
 cleanup:
  delete midiin;

  return 0;
}
