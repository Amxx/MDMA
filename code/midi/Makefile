
OBJS = build/mdma.o build/RtMidi.o

BIN = mdma

FLAGS = -g -Wall -Wextra -fexceptions -D_DEBUG -D_CONSOLE -D__LINUX_ALSA__

LFLAGS = -lasound -lfl -lm

all: $(OBJS)
	g++ $(FLAGS) $(OBJS) $(LFLAGS) -o $(BIN)


build/%.o: %.cpp
	g++ $(FLAGS) -o $@ -c $<

clean:
	rm -f build/*.*
