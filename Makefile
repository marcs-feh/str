override CC      := clang -std=c11
override CFLAGS  := -O2 -pipe -Wall -Wextra -fPIC -I. $(CFLAGS)
override LDFLAGS := -L. -lstr $(LDFLAGS)
override AR      := ar

.PHONY: run release dev clean

run: main.bin
	@./main.bin

dev:
	@make run CFLAGS='-g -fsanitize=address,undefined' LDFLAGS='-lasan -lubsan'

main.bin: libstr.a main.o
	$(CC) main.o -o main.bin $(LDFLAGS)

libstr.a: str.h str.o utf8.h utf8.o
	$(AR) rcs libstr.a str.o utf8.o

str.o: str.c str.h utf8.o utf8.h
	$(CC) $(CFLAGS) -o str.o -c str.c

utf8.o: utf8.c utf8.h
	$(CC) $(CFLAGS) -o utf8.o -c utf8.c

main.o: main.c tests/utf8.c tests/str.c
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -f *.o *.bin *.a *.so
