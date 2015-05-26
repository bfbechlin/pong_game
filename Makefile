CC=gcc
CFLAGS=-c -Wall

all: build

build: main.o ball.o
	$(CC) main.o ball.o -o pong -lncurses

main.o: main.c
	$(CC) $(CFLAGS) main.c

ball.o: ball.c
	$(CC) $(CFLAGS) ball.c

clean:
	rm *o pong

