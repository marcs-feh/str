#include "str.h"
#include <stdlib.h>

String strNew(usize size_hint){
	String s = {0};
	if(size_hint > 0){
		s.buf = (MemBuf){
			.data = calloc(size_hint, 1),
			.len  = size_hint,
		};
	}
	return s;
}

void strDel(String* s){
	if(s == NULL){ return; }
	free(s->buf.data);
	s->size = 0;
	s->buf = (MemBuf){.data = NULL, .len = 0};
}
