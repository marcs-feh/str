#ifndef INCLUDE_STR_H_
#define INCLUDE_STR_H_

#include "types.h"
#include "utf8.h"

// Generic memory buffer with length
typedef struct {
	byte* data; // Pointer to data
	usize len;  // Length in bytes
} MemBuf;

// UTF-8 encoded string.
typedef struct {
	MemBuf buf;  // Data buffer
	usize  size; // Length in bytes
} String;

// // UTF-32 encoded string.
// typedef struct {
// 	MemBuf buf;  // Data buffer
// 	usize  size; // Length in bytes
// } String32;

// Creates a string with a size hint as underlying storage, use `size_hint = 0`
// to only alloc when needed.
String strNew(usize size_hint);
void   strDel(String* s);
String strFrom(const char* cs);
void   strAppendRune(String* s, rune r);
void   strAppendStr(String* s, const String* src);
void   strAppendCstr(String* s, const char* cs);

#endif /* include guard */
