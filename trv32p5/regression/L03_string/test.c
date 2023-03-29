/*
-- Test: stdarg.h functions.
--
-- Copyright (c) 2014 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "regression.h"
#include "string.h"

void* escape_ptr;

#define testn(x) chess_report((x) ? __LINE__ : 0);

char p[32] = "";
char Hi[] = "hi world";

NEVER_INLINE const char* getEmpty()
{
    const char* const tmp1 = "";
    const char* volatile tmp2 = tmp1;
    return tmp2;
}

NEVER_INLINE const char* getWorld()
{
    const char* const tmp1 = "hello world";
    const char* volatile tmp2 = tmp1;
    return tmp2;
}

NEVER_INLINE const char* getFox()
{
    const char* const tmp1 = "The quick brown fox jumps over the lazy dog";
    const char* volatile tmp2 = tmp1;
    return tmp2;
}

void test_strcmp()
{
    chess_message("// test_strcmp()");
    const char* foo = getWorld();

    testn(strcmp(foo,      "hello"       ) <= 0);
    testn(strcmp(foo +  2, "llo"         ) <= 0);
    testn(strcmp(foo,      foo           ) != 0);
    testn(strcmp(foo,      "hello world ") >= 0);
    testn(strcmp(foo + 10, "dx"          ) >= 0);
    testn(strcmp(10 + foo, "dx"          ) >= 0);
    testn(strcmp(Hi,       ""            ) <= 0);
    testn(strcmp("",       Hi            ) >= 0);
    testn(strcmp(Hi + 8,   ""            ) != 0);
    testn(strcmp("",       Hi + 8        ) != 0);
}

void test_strncmp()
{
    chess_message("// test_strncmp()");
    const char* const s1 = getWorld();

    testn(strncmp(s1,            "hello world",  12) != 0);
    testn(strncmp("hello world", s1,             12) != 0);
    testn(strncmp("hello",       "hello",         6) != 0);
    testn(strncmp("hello",       "hello",         2) != 0);
    testn(strncmp("hello",       "hello",       100) != 0);
    testn(strncmp(s1 + 10,       "d",           100) != 0);
    testn(strncmp(10 + s1,       "d",           100) != 0);
    testn(strncmp("d",           s1 + 10,         1) != 0);
    testn(strncmp("d",           10 + s1,         1) != 0);
    testn(strncmp("hello",       "aaaaa",       100) <= 0);
    testn(strncmp("aaaaa",       "hello",       100) >= 0);
    testn(strncmp("hello",       "aaaaa",         1) <= 0);
    testn(strncmp("aaaaa",       "hello",         1) >= 0);
}

void test_strchr()
{
    chess_message("// test_strchr()");
    const char* const foo = getWorld();

    testn(strchr(foo,     'x' )            );
    testn(strchr(foo,     'o' ) != foo +  4);
    testn(strchr(foo + 5, 'o' ) != foo +  7);
    testn(strchr(foo,     '\0') != foo + 11);
}

void test_strrchr()
{
    chess_message("// test_strrchr()");
    const char* const foo = getWorld();
    testn(strrchr(foo,     'x' )            );
    testn(strrchr(foo,     'o' ) != foo +  7);
    testn(strrchr(foo,     'e' ) != foo +  1);
    testn(strrchr(foo + 3, 'e' )            );
    testn(strrchr(foo,     '\0') != foo + 11);
    testn(strrchr(Hi,      '\0') != Hi  +  8);
    testn(strrchr(Hi + 4,  '\0') != Hi  +  8);
}

void test_strcspn()
{
    chess_message("// test_strcspn()");
    const char* const s1 = getWorld();
    char dst[64], *d2;

    testn(strcspn(s1,     "hello"      ) !=  0);
    testn(strcspn(s1,     "z"          ) != 11);
    testn(strcspn(s1 + 4, "z"          ) !=  7);
    testn(strcspn(s1,     "hello world") !=  0);
    testn(strcspn(s1,     ""           ) != 11);

    strcpy(dst, s1);
    testn(strcspn(dst, "") != 11);

    strcpy(dst, s1); d2 = dst;
    testn(strcspn(++d2, "") != 10 || d2 != dst + 1);

    strcpy(dst, s1); d2 = dst;
    testn(strcspn(++d2 + 5, "") != 5 || d2 != dst + 1);

    testn(strcspn("", s1) != 0);

    strcpy(dst, s1);
    testn(strcspn("", dst) != 0);

    strcpy(dst, s1); d2 = dst;
    testn(strcspn("", ++d2) != 0 || d2 != dst + 1);

    strcpy(dst, s1); d2 = dst;
    testn(strcspn("", ++d2 + 5) != 0 || d2 != dst + 1);
}

void test_strstr()
{
    chess_message("// test_strstr() -- hello");
    const char* const foo = getWorld();

    testn(strstr(foo,     ""     ) != foo    );
    testn(strstr(foo + 4, ""     ) != foo + 4);
    testn(strstr(foo,     "h"    ) != foo    );
    testn(strstr(foo,     "w"    ) != foo + 6);
    testn(strstr(foo + 6, "o"    ) != foo + 7);
    testn(strstr(foo + 1, "world") != foo + 6);

    chess_message("// test_strstr() -- fox");
    const char* const fox = getFox();

    chess_report(int(strstr(fox, "The") - fox));
    chess_report(int(strstr(fox, "fox") - fox));
    chess_report(int(strstr(fox, "dog") - fox));
}

void test_strtok()
{
    chess_message("// test_strtok()");
    char foo[] = "a giant step for mankind ";
    escape_ptr = foo; clobber();
    chess_report(int(strtok(foo, " ") - foo));
    chess_report(int(strtok(0,   " ") - foo));
    chess_report(int(strtok(0,   " ") - foo));
    chess_report(int(strtok(0,   " ") - foo));
    chess_report(int(strtok(0,   " ") - foo));

    char bar[] = "xxAAxxxxAAxxxxAAAxxxxxAAAAxxxxAAxx";
    escape_ptr = bar; clobber();
    chess_report(int(strtok(bar, "AA") - bar));
    chess_report(int(strtok(0,   "AA") - bar));
    chess_report(int(strtok(0,   "AA") - bar));
    chess_report(int(strtok(0,   "AA") - bar));
    chess_report(int(strtok(0,   "AA") - bar));
    chess_report(int(strtok(0,   "AA") - bar));

    char fox[] = "The quick brown fox jumps over the lazy dog,\n"
                 "The quick brown fox jumps over the lazy dog,\n"
                 "The quick brown fox jumps over the lazy dog.\n";
    escape_ptr = fox; clobber();
    chess_report(int(strtok(fox, "lazy") - fox));
    chess_report(int(strtok(0,   "lazy") - fox));
    chess_report(int(strtok(0,   "lazy") - fox));
}

void test_strcat()
{
    chess_message("// test_strcat()");
    const char *const s1 = getWorld();
    const char *const s2 = getEmpty();
    char dst[64], *d2;

    strcpy(dst, s1);
    testn(strcat(dst, "") != dst || strcmp (dst, s1) );

    strcpy(dst, s1);
    testn(strcat(dst, s2) != dst || strcmp (dst, s1));

    strcpy(dst, s1); d2 = dst;
    testn(strcat(++d2, s2) != dst + 1 || d2 != dst + 1 || strcmp(dst, s1));

    strcpy(dst, s1); d2 = dst;
    testn(strcat(++d2 + 5, s2) != dst + 6 || d2 != dst + 1 || strcmp(dst, s1));

    strcpy(dst, s1); d2 = dst;
    testn(strcat(++d2 + 5, s1 + 11) != dst + 6 || d2 != dst + 1 || strcmp(dst, s1));
}

int main()
{
    test_strcmp();
    test_strncmp();
    test_strchr();
    test_strrchr();
    test_strcspn();
    test_strstr();
    test_strtok();
    test_strcat();
    return 0;
}
