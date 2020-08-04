OBJS = sequence.o sieve.o bv.o
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
CC = clang $(CLFAGS)
LFLAGS = -lm

all:	sequence
sequence:	$(OBJS) sequence.c sieve.h bv.h
	$(CC) -o sequence $(OBJS) $(LFLAGS)
sequence.o:	sequence.c sieve.o bv.o
	$(CC) -c sequence.c
sieve.o:	sieve.c bv.o
	$(CC) -c sieve.c
bv.o:	bv.c
	$(CC) -c bv.c
clean:
	rm -f sequence sequence.o sieve.o bv.o
infer:
	make clean; infer-capture -- make; infer-analyze -- make
valgrind:
	valgrind ./sequence
