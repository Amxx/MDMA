
OBJS = build/mdma.o build/RtMidi.o

BIN = mdma

#comment out to not compile ALSA
ALSAFL = -D__LINUX_ALSA__
LALSAFL = -lasound

#comment out to not compile JACK
JACKFL = -D__UNIX_JACK__
LJACKFL = -ljack

FLAGS = -g -Wall -Wextra -fexceptions -D_DEBUG -D_CONSOLE $(ALSAFL) $(JACKFL)

LFLAGS = $(LALSAFL) $(LJACKFL)
#-lfl -lm

all: mdma

mdma: $(OBJS)
	g++ $(FLAGS) $(OBJS) $(LFLAGS) -o $(BIN)


build/%.o: %.cpp
	g++ $(FLAGS) -o $@ -c $<

clean:
	rm -f build/*.*
