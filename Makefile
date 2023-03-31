CC=clang -std=c11
CFLAGS=-O2 -pipe -Wall -Wextra -fPIC
LDFLAGS=
AR=ar

test: libstr.a test.o
	$(CC) -o test.bin libstr.a test.o $(LDFLAGS)
	@./test.bin

libstr.a: str.h str.o utf8.h utf8.o types.h
	$(AR) rcs libstr.a str.o utf8.o

str.o: str.c str.h utf8.o utf8.h
	$(CC) $(CFLAGS) -o str.o -c str.c

utf8.o: utf8.c utf8.h
	$(CC) $(CFLAGS) -o utf8.o -c utf8.c

test.o: test.c
	$(CC) $(CFLAGS) -o test.o -c test.c

clean:
	rm -f *.o *.bin *.a *.so
