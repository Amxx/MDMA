CC=g++
CFLAGS=
LDFLAGS=-lopencv_video -lopencv_core -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect -lopencv_gpu
DEBUG=-g -Wall -DDEBUG

SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
EXE=$(SRC:.cpp=.exe)

.PHONY: all clear clean

all: $(EXE)

%.exe: %.o
	$(CC) -o $@ $< $(LDFLAGS) $(DEBUG)

%.o: %.cpp Makefile
	$(CC) -c $< $(CFLAGS) $(DEBUG)

clean:
	-rm -f $(OBJ) *~ \#*

clear:
	$(MAKE) clean
	-rm -f $(EXE)
