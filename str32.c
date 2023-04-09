#include "str.h"
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

String32 str32New(usize size_hint){
	String32 s = {0};
	usize size = size_hint * sizeof(rune);
	if(size > 0){
		s.buf = (MemBuf){
			.data = calloc(size, 1),
			.len  = size,
		};
		s.size = 0;
	}
	return s;
}

// Resize string to be n runes long.
static void str32BufResize(String32* s, usize n){
	n = n * sizeof(rune);
	byte* new_data = calloc(n, 1);
	usize new_size = MIN(n, s->size);

	if(s->buf.data != NULL){
		memcpy(new_data, s->buf.data, new_size);
	}

	free(s->buf.data);
	s->size = new_size;
	s->buf = (MemBuf){
		.data = new_data,
		.len = n,
	};
}

void str32Del(String32* s){
	if(s == NULL){ return; }
	free(s->buf.data);
	s->size = 0;
	s->buf = (MemBuf){.data = NULL, .len = 0};
}

String32 str32Clone(const String32* s){
	String32 sc = str32New(s->size + 1);
	memcpy(sc.buf.data, s->buf.data, s->size);
	sc.size = s->size;
	return sc;
}

void str32AppendRune(String32* s, rune r){
	if((s->buf.len + sizeof(rune)) >= s->buf.len){
		str32BufResize(s, (s->buf.len * 1.5) + 1);
	}
	s->buf.data[s->size] = r;
	s->size += 1;
}
