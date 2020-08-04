OBJS = bubble.o shell.o quick.o binary.o sorting.o
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -Wshadow
CC = clang $(CFLAGS)

all:	sorting
sorting:	$(OBJS) sorting.c bubble.h shell.h quick.h binary.h
	$(CC) -o sorting $(OBJS)
sorting.o:	sorting.c bubble.o shell.o quick.o binary.o
	$(CC) -c sorting.c
bubble.o:	bubble.c
	$(CC) -c bubble.c
shell.o:	shell.c
	$(CC) -c shell.c
quick.o:	quick.c
	$(CC) -c quick.c
binary.o:	binary.c
	$(CC) -c binary.c
clean:
	rm -f sorting $(OBJS)
infer:
	make clean; infer-capture -- make; infer-analyze -- make
valgrind:
	valgrind ./sorting
