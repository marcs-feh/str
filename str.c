#include "str.h"
#include <stdlib.h>

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

static usize cstrLen(const char* cs){
	if(cs == NULL){ return 0; }
	usize n = 0;
	while(cs[n] != '\0'){ n += 1; }
	return n;
}

String strFrom(const char* cs){
	usize n = cstrLen(cs);
	String s = strNew(n + 2);

	for(usize i = 0; i < n; i += 1){
		s.buf.data[i] = cs[i];
	}

	s.size = n;
	return s;
}

static void strResize(String* s, usize n){
	byte* new_data = calloc(n, 1);
	for(usize i = 0; i < s->size; i += 1){
		new_data[i] = s->buf.data[i];
	}
	free(s->buf.data);
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
		strResize(s, (s->buf.len * 1.5) + 5);
	}

	for(usize i = 0; i < len; i += 1){
		s->buf.data[s->size + i] = res.data[i];
	}

	s->size += len;
}

usize strLen(const String* s){
	usize p = 0;
	usize len = 0;
	usize byteLen;
	while(p < s->size){
		byteLen = utf8FirstByteLen(s->buf.data[p]);
		p += byteLen;
		len += 1;
	}
	return len;
}

void strAppendCstr(String* s, const char* cs){
	usize len = cstrLen(cs);

	if((s->size + len + 1) >= s->buf.len){
		strResize(s, s->size + len + 2);
	}

	for(usize i = 0; i < len; i += 1){
		s->buf.data[s->size + i] = cs[i];
	}

	s->size += len;
}

void strAppendStr(String* s, const String* src){
	usize len = src->size;
	const byte* buf = src->buf.data;

	if((s->size + len + 1) >= s->buf.len){
		strResize(s, s->size + len + 2);
	}

	for(usize i = 0; i < len; i += 1){
		s->buf.data[s->size + i] = buf[i];
	}

	s->size += len;
}

// #include <stdio.h>
String strClone(const String* s){
	String sc = strNew(s->size + 1);
	for(usize i = 0; i < s->size; i += 1){
		sc.buf.data[i] = s->buf.data[i];
	}
	sc.size = s->size;
	return sc;
}


