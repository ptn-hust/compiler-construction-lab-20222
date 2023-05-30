CC = gcc
#CFLAGS = -Wall -Werror

all: scanner.c token.o charcode.o error.o reader.o
	$(CC) $(CFLAGS) scanner.c token.o charcode.o error.o reader.o -o scanner

token.o: token.c token.h
	$(CC) $(CFLAGS) token.c -o token.o -c

error.o: error.c error.h
	$(CC) $(CFLAGS) error.c -o error.o -c

reader.o: reader.c reader.h
	$(CC) $(CFLAGS) reader.c -o reader.o -c

charcode.o: charcode.c charcode.h
	$(CC) $(CFLAGS) charcode.c -o charcode.o -c

clean:
	rm -f *.o scanner
