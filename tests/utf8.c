#include "tests_now.h"
#include "utf8.h"

Test_Proc utf8_test(){
	Test_Init("UTF-8");
	UTF8Result r = {0};
	r = utf8EncodePoint(0x24);    // $
	Test(utf8DecodePoint(r) == 0x24);
	r = utf8EncodePoint(0xa3);    // £
	Test(utf8DecodePoint(r) == 0xa3);
	r = utf8EncodePoint(0x939);   // ह
	Test(utf8DecodePoint(r) == 0x939);
	r = utf8EncodePoint(0xd55c);  // 한
	Test(utf8DecodePoint(r) == 0xd55c);
	r = utf8EncodePoint(0x10348); // 𐍈
	Test(utf8DecodePoint(r) == 0x10348);
	r = utf8EncodePoint(0xfffd);  // �
	Test(utf8DecodePoint(r) == 0xfffd);
	Test_End();
}

