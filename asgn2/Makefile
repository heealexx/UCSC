CFLAGS=-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)
LFLAGS = -lm

all	:	math
math	:	math.o
	$(CC) -o math math.o $(LFLAGS)
math.o	:	math.c
	$(CC) -c math.c
clean   :
	rm -f math math.o
infer   :
	make clean; infer-capture -- make; infer-analyze -- make
