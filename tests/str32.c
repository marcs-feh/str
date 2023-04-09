#include "tests_now.h"
#include "str.h"

Test_Proc str32Test(){
	Test_Init("String32");
	{
		String32 s = str32New(0);
		Tp(s.size == 0);
		Tp(s.buf.len == 0);
		Tp(s.buf.data == NULL);
	}
	Test_End();
}
