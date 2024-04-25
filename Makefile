CC = gcc
CFLAGS = -Wall -Wextra -Werror -ansi -pedantic

all: fw

valgrind: fw
	valgrind ./fw

fw: clean main.o readlongwords.o dict.o
	${CC} main.o readlongwords.o dict.o -o fw

main.o: readlongwords.h dict.h
	${CC} -c -g ${CFLAGS} main.c	

readlongwords.o: readlongwords.c readlongwords.h
	${CC} -c -g ${CFLAGS} readlongwords.c

dict.o: dict.o dict.h
	${CC} -c -g ${CFLAGS} dict.c

clean:
	rm -f fw main.o readlongwords.o dict.o


