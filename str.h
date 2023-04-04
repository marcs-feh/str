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
// Destroy string.
void   strDel(String* s);
// Create string from a c-string.
String strFrom(const char* cs);
// Encode and append codepoint to string.
void   strAppendRune(String* s, rune r);
// Append contents of one string to another.
void   strAppendStr(String* s, const String* src);
// Append c-string to string.
void   strAppendCstr(String* s, const char* cs);
// Get length (in runes) from string.
usize  strLen(String* s);

#endif /* include guard */
