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

// Creates a string with a size hint as underlying storage, use `size_hint = 0`
// to only alloc when needed.
String strNew(usize size_hint);
// Destroy string.
void strDel(String* s);
// Create string from a c-string.
String strFrom(const char* cs);
// Create copy of string.
String strClone(const String* s);
// Encode and append codepoint to string.
void strAppendRune(String* s, rune r);
// Append contents of one string to another.
void strAppendStr(String* s, const String* src);
// Append c-string to string.
void strAppendCstr(String* s, const char* cs);
// Get position of the first byte of N-th rune, if it is out of bounds, a
// position bigger than the string's size is returned.
usize strRuneBytePos(const String* s, usize n);
// Get codepoint at a position, returns 0 if out of bounds.
rune strAt(const String* s, usize idx);
// Get length (in runes) from string.
usize strLen(const String* s);
// Get raw data of string
const byte* strData(const String* s);

// UTF-32 encoded string.
typedef struct {
	MemBuf buf;  // Data buffer
	usize  size; // Length in bytes
} String32;

// Creates a string32 with a size hint as underlying storage, use `size_hint = 0`
// to only alloc when needed.
String32 str32New(usize size_hint);
// Destroy string32.
void str32Del(String32* s);
// Create string from a c-string.
String str32From(const char* cs);
// Create copy of string.
String str32Clone(const String32* s);
// Encode and append codepoint to string.
void str32AppendRune(String32* s, rune r);

#endif /* include guard */
