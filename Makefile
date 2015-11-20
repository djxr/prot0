CC=cc
CFLAGS=-std=c99 -Wall -W -g -pedantic-errors
LDFLAGS=-lSDL2 -lm

all: main

run:
	./main

clean:
	rm -f main
