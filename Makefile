CC=gcc
CFLAGS=-c

all: build

build: main.o ball.o paddle.o level.o graph.o
	$(CC) main.o ball.o paddle.o level.o graph.o -o pong -lncurses

main.o: main.c
	$(CC) $(CFLAGS) main.c

ball.o: ball.c
	$(CC) $(CFLAGS) ball.c

paddle.o: paddle.c
	$(CC) $(CFLAGS) paddle.c

level.o:
	$(CC) $(CFLAGS) level.c
	
graph.o:
	$(CC) $(CFLAGS) graph.c

clean:
	rm *o pong

