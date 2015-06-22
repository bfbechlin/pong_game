CC=gcc
CFLAGS=-c

all: build

build: main.o ball.o paddle.o level.o graph.o config.o mode.o ranmar.o bot.o
	$(CC) main.o ball.o paddle.o level.o graph.o config.o mode.o ranmar.o bot.o -o pong -lncurses -lm

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

mode.o: mode.c
	$(CC) $(CFLAGS) mode.c

ranmar.o: ranmar.c
	$(CC) $(CFLAGS) ranmar.c

bot.o: bot.c
	$(CC) $(CFLAGS) bot.c

clean:
	rm *o pong
