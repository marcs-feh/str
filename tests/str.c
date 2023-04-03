#ifndef INCLUDE_STR_C_
#define INCLUDE_STR_C_

#include "str.h"
#include "tests_now.h"

Test_Proc strTest(){
	Test_Init("String");
	{
		String s = strNew(0);
		Tp(s.buf.data == NULL);
		Tp(s.buf.len == 0);
		Tp(s.size == 0);
	}
	{
		String s = strNew(64);
		Tp(s.size == 0);
		Tp(s.buf.len == 64);
		Tp(s.buf.data != NULL);
		strDel(&s);
	}
	{
		String s = strFrom("Hello");
		// String s = strNew(5);
		Tp(s.size == 5);
		strAppendRune(&s, ' ');
		Tp(s.size == 6);
		strAppendRune(&s, 0x4e16);
		strAppendRune(&s, 0x754c);
		Test_Log("%s", s.buf.data);
		strDel(&s);
	}
	{
		String s = strNew(1);
		strAppendCstr(&s, "Hello ");
		strAppendCstr(&s, "again ");
		Tp(s.size == 12);
		strAppendRune(&s, 0x4e16);
		strAppendRune(&s, 0x754c);
		Tp(s.size == (12 + utf8RuneLen(0x4e16) + utf8RuneLen(0x754c)));
		Test_Log("%s", s.buf.data);
		strDel(&s);
	}
	Test_End();
}


#endif /* include guard */
