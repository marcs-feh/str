#include <stdio.h>
#include "utf8.h"

static void printByte(byte b){
	for(int i = 7; i >= 0; i -= 1){
		printf("%d", (b >> i) & 1);
	}
}

static void printResult(UTF8Result r){
	byte buf[5] = {0};
	uint n = utf8ResultLen(r);
	for(uint i = 0; i < n; i += 1){
		buf[i] = r.data[i];
	}
	printf("%04x\t|%s\t|", utf8DecodePoint(r), buf);
	for(uint i = 0; i < n; i += 1){
		printByte(buf[i]);
		printf(" ");
	}
	printf("\n");
}

int main(){
	UTF8Result r = {0};

	printf("Point\t|Sym\t|Binary\n");
	r = utf8EncodePoint(0x24);
	printResult(r);
	r = utf8EncodePoint(0xa3);
	printResult(r);
	r = utf8EncodePoint(0x939);
	printResult(r);
	r = utf8EncodePoint(0xd55c);
	printResult(r);
	r = utf8EncodePoint(0x10348);
	printResult(r);

	// r = utf8EncodePoint(0x65e5);
	// printResult(r);
	// r = utf8EncodePoint(0x672c);
	// printResult(r);
	// r = utf8EncodePoint(0x8a9e);
	// printResult(r);

	return 0;
}
