CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: tinyparser

tinyparser: main.o lexer.o parser.o
	$(CC) $(CFLAGS) -o tinyparser main.o lexer.o parser.o

main.o: main.c lexer.h parser.h token.h
	$(CC) $(CFLAGS) -c main.c

lexer.o: lexer.c lexer.h token.h
	$(CC) $(CFLAGS) -c lexer.c

parser.o: parser.c parser.h lexer.h token.h
	$(CC) $(CFLAGS) -c parser.c

run: tinyparser
	./tinyparser input.tiny

clean:
	rm -f *.o tinyparser tinyparser.exe
