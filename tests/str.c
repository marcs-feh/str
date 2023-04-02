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
	Test_End();
}


#endif /* include guard */
