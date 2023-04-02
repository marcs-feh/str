#ifndef INCLUDE_TEST_NOW_H_
#define INCLUDE_TEST_NOW_H_

#include <stdio.h>
#include <stdbool.h>

#define uint unsigned int
#define Test_Proc static unsigned int

#ifndef TEST_NO_COLORS
#define TEST_COL_FAIL  "\e[0;31m"
#define TEST_COL_PASS  "\e[0;32m"
#define TEST_COL_TITLE "\e[1;37m"
#define TEST_COL_RESET "\e[0m"
#else
#define TEST_COL_FAIL  ""
#define TEST_COL_PASS  ""
#define TEST_COL_TITLE ""
#define TEST_COL_RESET ""
#endif

struct Test {
	const char* title;
	uint tests_count;
	uint error_count;
};

static
void test_display_header(struct Test* t) {
	printf("[" TEST_COL_TITLE "%s" TEST_COL_RESET "]\n", t->title);
}

static
void test_assert(struct Test* t, bool expr, const char* msg){
	t->tests_count += 1;
	if(!expr){
		t->error_count += 1;
		printf("\tFailed: %s\n", msg);
	}
}

static
void test_display_results(struct Test* t){
	if(t->error_count > 0){
		printf(TEST_COL_FAIL "FAIL" TEST_COL_RESET);
	} else {
		printf(TEST_COL_PASS "PASS" TEST_COL_RESET);
	}
	printf(" ok in %u/%u\n", t->tests_count - t->error_count, t->tests_count);
}

#define Test_Init(title_) struct Test _test_ = { .title = title_, .tests_count = 0, .error_count = 0}; \
	test_display_header(&_test_);
#define Test_End() test_display_results(&_test_); return _test_.error_count;
// Test predicate.
#define Tp(expr) { test_assert(&_test_, (expr), #expr); }

#undef uint
#undef TEST_COL_FAIL
#undef TEST_COL_PASS
#undef TEST_COL_TITLE
#undef TEST_COL_RESET

#endif /* include guard */
