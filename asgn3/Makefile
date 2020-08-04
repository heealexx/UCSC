OBJS = pathfinder.o stack.o
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99
CC=clang $(CFLAGS)

all:		pathfinder
pathfinder:	$(OBJS) pathfinder.c stack.h
	$(CC) -o pathfinder $(OBJS)
pathfinder.o:	pathfinder.c stack.o
	$(CC) -c pathfinder.c
stack.o:	stack.c
	$(CC) -c stack.c
clean:
	rm -f pathfinder pathfinder.o stack.o
infer:
	make clean; infer-capture -- make; infer-analyze -- make
