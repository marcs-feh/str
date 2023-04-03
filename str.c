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

#include <stdio.h>
static usize cstrLen(const char* cs){
	usize n = 0;
	while(cs[n] != '\0'){ n += 1; }
	return n;
}

String strFrom(const char* cs){
	usize n = cstrLen(cs);
	String s = strNew(n + 2);

	printf("n:%zu\n", n);
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

// overflow, but why?
void strAppendRune(String* s, rune p){
	UTF8Result res = utf8EncodePoint(p);
	usize len = utf8ResultLen(res);
	if((len == 0) || (p == 0)){ return; }

	if((s->size + len + 1) >= s->buf.len){
		strResize(s, (s->buf.len * 1.5) + 5); // 5 because of a 4byte utf-8 char + NUL term
	}

	for(usize i = 0; i < len; i += 1){
		s->buf.data[s->size + i] = res.data[i];
	}

	s->size += len;
}

