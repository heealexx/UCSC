OBJS = ll.o gs.o hash.o newspeak.o speck.o bf.o bv.o parser.o
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -Wshadow -IprovidedCode
CC = clang $(CFLAGS) -ggdb

all:	newspeak
newspeak:	$(OBJS) newspeak.c
	$(CC) -o newspeak $(OBJS)
newspeak.o:	newspeak.c ll.o gs.o hash.o bf.o bv.o speck.o parser.o
	$(CC) -c newspeak.c
parser.o:	providedCode/parser.c
	$(CC) -c providedCode/parser.c
ll.o:   ll.c gs.o
	$(CC) -c ll.c
hash.o:	hash.c ll.o gs.o
	$(CC) -c hash.c
gs.o:	gs.c
	$(CC) -c gs.c
speck.o:	providedCode/speck.c
	$(CC) -c providedCode/speck.c
bf.o:	bf.c bv.o
	$(CC) -c bf.c
bv.o:	bv.c
	$(CC) -c bv.c
clean:
	rm -f newspeak $(OBJS)
infer:
	make clean; infer-capture -- make; infer-analyze -- make
valgrind:
	valgrind -v ./newspeak
