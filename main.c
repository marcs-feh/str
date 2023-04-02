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

// Tests
#include "tests/utf8.c"
#include "tests/str.c"

int main(){
	uint test_res =
		+ utf8Test()
		+ strTest()
	;
	return test_res;
}
