#include "str.h"
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

static usize cstrLen(const char* cs){
	if(cs == NULL){ return 0; }
	usize n = 0;
	while(cs[n] != '\0'){ n += 1; }
	return n;
}

String strNew(usize size_hint){
	String s = {0};
	if(size_hint > 0){
		s.buf = (MemBuf){
			.data = calloc(size_hint, 1),
			.len  = size_hint,
		};
		s.size = 0;
	}
	return s;
}

void strDel(String* s){
	if(s == NULL){ return; }
	free(s->buf.data);
	s->size = 0;
	s->buf = (MemBuf){.data = NULL, .len = 0};
}

String strFrom(const char* cs){
	usize n = cstrLen(cs);
	String s = strNew(n + 2);

	memcpy(s.buf.data, cs, n);

	s.size = n;
	return s;
}

usize strLen(const String* s){
	usize i = 0;
	usize len = 0;
	usize byteLen;
	while(i < s->size){
		byteLen = utf8FirstByteLen(s->buf.data[i]);
		i += byteLen;
		len += 1;
	}
	return len;
}

// Get position of the first byte of N-th rune
static usize strRuneBytePos(const String* s, usize n){
	// if((n == 0) || (s->size > 0)){ return 0; }
	usize byteLen;
	usize bp = 0;
	usize rp = 0;
	while(bp < s->size){
		if(rp == n){ break; }
		byteLen = utf8FirstByteLen(s->buf.data[bp]);
		bp += byteLen;
		rp += 1;
	}

	if((bp + byteLen) > s->size){ return s->size + 1; }

	return bp;
}

rune strAt(const String* s, usize idx){
	if(idx >= s->size){ return 0; }
	usize pos = strRuneBytePos(s, idx);
	if(pos >= s->size){
		return 0;
	}

	usize len = utf8FirstByteLen(s->buf.data[pos]);
	UTF8Result buf = {0};
	for(usize i = 0; i < len; i += 1){
		buf.data[i] = s->buf.data[pos + i];
	}

	return utf8DecodePoint(buf);
}

// Resize string to be n bytes long. This may result in invalid byte sequences, be warned!
static void strBufResize(String* s, usize n){
	byte* new_data = calloc(n, 1);
	usize new_size = MIN(n, s->size);

	memcpy(new_data, s->buf.data, new_size);

	free(s->buf.data);
	s->size = new_size;
	s->buf = (MemBuf){
		.data = new_data,
		.len = n,
		};
}

void strAppendRune(String* s, rune p){
	UTF8Result res = utf8EncodePoint(p);
	usize len = utf8ResultLen(res);
	if((len == 0) || (p == 0)){ return; }

	if((s->size + len + 1) >= s->buf.len){
		// increase by at least 5 because of a 4byte utf-8 char + NUL term
		strBufResize(s, (s->buf.len * 1.5) + 5);
	}

	for(usize i = 0; i < len; i += 1){
		s->buf.data[s->size + i] = res.data[i];
	}

	s->size += len;
}

void strAppendCstr(String* s, const char* cs){
	usize len = cstrLen(cs);

	if((s->size + len + 1) >= s->buf.len){
		strBufResize(s, s->size + len + 2);
	}

	memcpy(s->buf.data + s->size, cs, len);

	s->size += len;
}

void strAppendStr(String* s, const String* src){
	usize len = src->size;
	const byte* buf = src->buf.data;

	if((s->size + len + 1) >= s->buf.len){
		strBufResize(s, s->size + len + 2);
	}

	memcpy(s->buf.data + s->size, buf, len);

	s->size += len;
}

String strClone(const String* s){
	String sc = strNew(s->size + 1);
	for(usize i = 0; i < s->size; i += 1){
		sc.buf.data[i] = s->buf.data[i];
	}
	sc.size = s->size;
	return sc;
}

