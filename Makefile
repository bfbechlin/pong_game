CC=gcc
CFLAGS=-c

all: build

build: main.o ball.o level.o graph.o
	$(CC) main.o ball.o level.o graph.o -o pong -lncurses

main.o: main.c
	$(CC) $(CFLAGS) main.c

ball.o: ball.c
	$(CC) $(CFLAGS) ball.c

level.o:
	$(CC) $(CFLAGS) level.c
	
graph.o:
	$(CC) $(CFLAGS) graph.c

clean:
	rm *o pong

