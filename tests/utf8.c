#include "tests_now.h"
#include "utf8.h"

Test_Proc utf8Test(){
	Test_Init("UTF-8");
	UTF8Result r = {0};
	r = utf8EncodePoint(0x24);    // $
	Tp(utf8DecodePoint(r) == 0x24);
	r = utf8EncodePoint(0xa3);    // £
	Tp(utf8DecodePoint(r) == 0xa3);
	r = utf8EncodePoint(0x939);   // ह
	Tp(utf8DecodePoint(r) == 0x939);
	r = utf8EncodePoint(0xd55c);  // 한
	Tp(utf8DecodePoint(r) == 0xd55c);
	r = utf8EncodePoint(0x10348); // 𐍈
	Tp(utf8DecodePoint(r) == 0x10348);
	r = utf8EncodePoint(0xfffd);  // �
	Tp(utf8DecodePoint(r) == 0xfffd);
	Test_End();
}

