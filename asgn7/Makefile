OBJS = io.o trie.o word.o
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -Wshadow
CC = clang $(CFLAGS) -ggdb

all:	encode decode
encode:	$(OBJS) encode.c encode.o
	$(CC) -o encode $(OBJS) encode.o
encode.o:	encode.c io.c trie.c word.c
	$(CC) -c encode.c
decode:	$(OBJS) decode.c decode.o
	$(CC) -o decode $(OBJS) decode.o
decode.o:	decode.c io.c trie.c word.c
	$(CC) -c decode.c
io.o:	io.c
	$(CC) -c io.c
trie.o:	trie.c
	$(CC) -c trie.c
word.o:	word.c
	$(CC) -c word.c

clean:
	rm -f encode $(OBJS) decode
infer:
	make clean; infer-capture -- make; infer-analyze -- make
