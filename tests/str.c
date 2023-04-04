#ifndef INCLUDE_STR_C_
#define INCLUDE_STR_C_

#include <string.h>
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
		Tp(s.size == 5);
		strAppendRune(&s, ' ');
		Tp(s.size == 6);
		strAppendRune(&s, 0x4e16);
		strAppendRune(&s, 0x754c);
		Test_Log("%s", s.buf.data);
		Tp(strLen(&s) == 8);
		strDel(&s);
	}
	{
		String s = strNew(1);
		strAppendCstr(&s, "Hello ");
		strAppendCstr(&s, "again ");
		Tp(s.size == 12);
		strAppendRune(&s, 0x4e16);
		strAppendRune(&s, 0x754c);
		usize n = (12 + utf8RuneLen(0x4e16) + utf8RuneLen(0x754c));
		Tp(s.size == n);
		Test_Log("%s", s.buf.data);
		String s2 = strClone(&s);
		Tp(s2.size == s.size);
		Tp(strcmp((const char*)s2.buf.data, (const char*)s.buf.data) == 0);
		strAppendStr(&s, &s2);
		Tp(s.size == (n*2));

		Tp(strAt(&s2, 0) == 'H');
		Tp(strAt(&s2, 12) == 0x4e16);
		Tp(strAt(&s2, 13) == 0x754c);
		Tp(strAt(&s2, 15) == 0);

		strDel(&s);
		strDel(&s2);
	}

	{
		String s = strFrom("");
		Tp(strLen(&s) == 0);
		Tp(s.size == 0);
		strDel(&s);
	}
	Test_End();
}

#endif /* include guard */
