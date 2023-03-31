CC=clang -std=c11
CFLAGS=-O2 -pipe -Wall -Wextra -fPIC
LDFLAGS= -L. -lstr
AR=ar

.PHONY: test clean

test: libstr.a test.o
	$(CC) test.o -o test.bin $(LDFLAGS)
	@./test.bin

libstr.a: str.h str.o utf8.h utf8.o
	$(AR) rcs libstr.a str.o utf8.o

str.o: str.c str.h utf8.o utf8.h
	$(CC) $(CFLAGS) -o str.o -c str.c

utf8.o: utf8.c utf8.h
	$(CC) $(CFLAGS) -o utf8.o -c utf8.c

test.o: test.c
	$(CC) $(CFLAGS) -o test.o -c test.c

clean:
	rm -f *.o *.bin *.a *.so
