CC = gcc
CFLAGS = -Wall -Wextra -Werror -ansi -pedantic

all: fw

valgrind: fw
	valgrind fw

fw: clean main.o readlongwords.o
	${CC} main.o readlongwords.o -o fw

main.o:
	${CC} -c -g main.c	

readlongwords.o: readlongwords.c
	${CC} -c -g readlongwords.c
clean:
	rm -f main.o readlongwords.o fw


