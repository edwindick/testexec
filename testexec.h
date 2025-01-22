#ifndef __TESTEXEC_HEADER__
#define __TESTEXEC_HEADER__


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


#define test int main

#define TEST_RETURN_PASSED     0
#define TEST_RETURN_FAILED     1
#define TEST_RETURN_SKIPPED    77


#define TEST_MESSAGE(...) \
    _test_message(__FILE__, __LINE__, __VA_ARGS__);


#define TEST_FAILED(...) do { \
    TEST_MESSAGE("Test failed. " __VA_ARGS__); \
    exit(TEST_RETURN_FAILED); \
} while(0)

#define TEST_PASSED(...) do { \
    TEST_MESSAGE("Test passed. " __VA_ARGS__); \
    exit(TEST_RETURN_PASSED); \
} while(0)

#define TEST_SKIPPED(...) do {
    TEST_MESSAGE("Test skipped. " __VA_ARGS__);
    exit(TEST_RETURN_SKIPPED);
}


#define _TEST_ASSERT_IMPL(cond, func) do { \
    if (!(cond)) { \
        func("Assertion (" #cond ") failed."); \
    } \
} while(0)

#define TEST_ASSERT(cond) \
    _TEST_ASSERT_IMPL(cond, TEST_FAIL)
#define TEST_ASSERT_PASS(cond) \
    _TEST_ASSERT_IMPL(cond, TEST_MESSAGE)


// This may have to be changed for better readability on failures? In fact why
// do I even need this? It feels very out of place in a library like this...
#define _TEST_ASSERT_ARRAYS_IMPL(a, operator, b, elems, func) do { \
    for (int _test_itr = 0; _test_itr < elems; _test_itr++) { \
        func(a[_test_itr] operator b[_test_itr]); \
    } \
} while(0)

#define TEST_ASSERT_ARRAYS(a, operator, b, elems) \
    _TEST_ASSERT_ARRAYS_IMPL(a, operator, b, elems, TEST_ASSERT)
#define TEST_ASSERT_ARRAYS_PASS(a, operator, b, elems) \
    _TEST_ASSERT_ARRAYS_IMPL(a, operator, b, elems, TEST_ASSERT_PASS)


// Because having emptry variable arguments in a macro causes C to dislike you
// very much.
static inline void _test_message(const char *file, unsigned int line,
        const char *const str, ...) {
    va_list args;
    va_start(args, str);
    
    fprintf(stdout, "\n[%s:%u]:\n\t", file, line);
    vfprintf(stdout, str, args);
    fputs("\n", stdout);

    va_end(args);
}


#endif // __TESTEXEC_HEADER__