#ifndef _utf8_h_include_
#define _utf8_h_include_

#include "types.h"

// UTF-8 encoded codepoint, as a sequence of bytes, mostly for internal usage
typedef struct{
	byte data[4];
} UTF8Result;

// Get length of UTF-8 result from its first byte. Returns 0 if invalid
uint utf8ResultLen(const UTF8Result r);
// Get length required to encode rune as UTF-8. Returns 0 if rune is invalid.
uint utf8RuneLen(const rune p);
// Get length based on first byte of UTF-8 sequence.
uint utf8FirstByteLen(const byte b);
// Encode Unicode point to UTF-8
UTF8Result utf8EncodePoint(rune r);
// Decode one unicode point
rune utf8DecodePoint(UTF8Result b);

#endif /* Include guard */
