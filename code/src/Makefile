CC=g++
CFLAGS=-g -Wall -Wextra
LFLAGS=

BIN=../bin/MDMA

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)


.PHONY: all clean clear


all: $(OBJ)
	    $(CC) -o $(BIN) $^ $(LFLAGS)

%.o: %.c Makefile
	    $(CC) -o $@ -c $< $(CFLAGS)

clean:
	    rm *.o

clear: clean
		rm $(BIN)
