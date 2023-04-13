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
	{
		String32 s = str32New(8);
		Tp(s.size == 0);
		Tp(s.buf.len == (8 * sizeof(rune)));
		Tp(s.buf.data != NULL);
		str32AppendRune(&s, 0x4e16);
		Tp(str32At(&s, 0) == 0x4e16);
		Tp(str32Len(&s) == 1);
		Tp(s.size == 4);
		Tp(str32At(&s, 1) == 0);

		str32AppendRune(&s, '!');
		Tp(str32Len(&s) == 2);
		Tp(s.size == 8);
		Tp(str32At(&s, 1) == '!');

		str32Del(&s);
	}
	Test_End();
}
