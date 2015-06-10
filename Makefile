CC=gcc
CFLAGS=-c

all: build

build: main.o ball.o paddle.o level.o graph.o config.o cpumode.o ranmar.o
	$(CC) main.o ball.o paddle.o level.o graph.o config.o CPUmode.o ranmar.o -o pong -lncurses

main.o: main.c
	$(CC) $(CFLAGS) main.c

ball.o: ball.c
	$(CC) $(CFLAGS) ball.c

paddle.o: paddle.c
	$(CC) $(CFLAGS) paddle.c

level.o: level.c
	$(CC) $(CFLAGS) level.c
	
graph.o: graph.c
	$(CC) $(CFLAGS) graph.c

config.o: config.c
	$(CC) $(CFLAGS) config.c

cpumode.o: CPUmode.c
	$(CC) $(CFLAGS) CPUmode.c

ranmar.o: ranmar.c
	$(CC) $(CFLAGS) ranmar.c

clean:
	rm *o pong

