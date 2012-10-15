CC = g++
CFLAGS = -lopencv_video -lopencv_core -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect -lopencv_gpu

SRC=$(wildcard *.cpp)
EXE=$(SRC:.cpp=)

.PHONY: all clean

all: $(EXE)

%: %.cpp Makefile
	$(CC) $< $(CFLAGS) -o $@

clean:
	-rm -f $(OBJ) *~ \#*

clear:
	$(MAKE) clean
	-rm -f $(EXE)

