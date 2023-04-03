#include "utf8.h"

typedef struct MemBuf MemBuf;

static const rune utf8Range1byte = 0x0000007f;
static const rune utf8Range2byte = 0x000007ff;
static const rune utf8Range3byte = 0x0000ffff;
static const rune utf8Range4byte = 0x0010ffff;

uint utf8ResultLen(const UTF8Result r){
	byte b = r.data[0];
	if((b & 0x80) == 0x00) { return 1; }
	if((b & 0xe0) == 0xc0) { return 2; }
	if((b & 0xf0) == 0xe0) { return 3; }
	if((b & 0xf8) == 0xf0) { return 4; }
	return 0;
}

uint utf8RuneLen(const rune p){
	if(p <= utf8Range1byte){ return 1; }
	if(p <= utf8Range2byte){ return 2; }
	if(p <= utf8Range3byte){ return 3; }
	if(p <= utf8Range4byte){ return 4; }
	return 0;
}

// Encode Unicode point to UTF-8
UTF8Result utf8EncodePoint(rune p){
	UTF8Result r = {0};

	if(p <= utf8Range1byte){
		r.data[0] = p & 0x7f;
	}
	else if(p <= utf8Range2byte){
		r.data[1] = (p & 0x3f) | 0x80;
		p = p >> 6;
		r.data[0] = (p & 0x1f) | 0xc0;
	}
	else if(p <= utf8Range3byte){
		r.data[2] = (p & 0x3f) | 0x80;
		p = p >> 6;
		r.data[1] = (p & 0x3f) | 0x80;
		p = p >> 6;
		r.data[0] = (p & 0x0f) | 0xe0;
	}
	else if(p <= utf8Range4byte){
		r.data[3] = (p & 0x3f) | 0x80;
		p = p >> 6;
		r.data[2] = (p & 0x3f) | 0x80;
		p = p >> 6;
		r.data[1] = (p & 0x3f) | 0x80;
		p = p >> 6;
		r.data[0] = (p & 0x07) | 0xf0;
	}
	return r;
}

// Decode one unicode point from result, returns 0 on error.
rune utf8DecodePoint(UTF8Result b){
	rune p = 0;
	uint len = utf8ResultLen(b);

	if(len == 1) {
		p = b.data[0];
	}
	else if(len == 2) {
		p |= (b.data[1] & 0x3f);
		p |= (b.data[0] & 0x1f) << 6;
	}
	else if(len == 3) {
		p |= (b.data[2] & 0x3f);
		p |= (b.data[1] & 0x3f) << 6;
		p |= (b.data[0] & 0x0f) << 12;
	}
	else if(len == 4) {
		p |= (b.data[3] & 0x3f);
		p |= (b.data[2] & 0x3f) << 6;
		p |= (b.data[1] & 0x3f) << 12;
		p |= (b.data[0] & 0x07) << 18;
	}

	return p;
}
