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
#include "stdlib.h"
#include "stddef.h"
#include "errno.h"

void tst_strtol(const char* str, char** endptr, int base)
{
    UNKNOWN(str); UNKNOWN(endptr); UNKNOWN(base);
    long l = strtol(str, endptr, base);
    chess_report(l);
    chess_report(errno); errno = 0;
    if (endptr) {
        chess_report(**endptr);
    }
}
void test_strtol()
{
    chess_message("// test_strtol()");
    char* ep;

    tst_strtol("0765",                NULL,  8);
    tst_strtol("123",                 NULL, 10);
    tst_strtol(" 2147483647 ",        NULL, 10);
    tst_strtol(" -2147483648 ",       NULL, 10);
    tst_strtol("0xBabe",              NULL, 16);
    tst_strtol("  7fffFFFFffff ",     NULL, 16);
    tst_strtol(" -800000000000 ",     NULL, 16);
    tst_strtol(" FFFFFFFFFFFFFFFFF ", NULL, 16); // out of range
    tst_strtol("   -987iabc",         &ep,  10);
    tst_strtol("12356789123456789",   NULL, 10); // out of range
}

void tst_strtoul(const char* str, char** endptr, int base)
{
    UNKNOWN(str); UNKNOWN(endptr); UNKNOWN(base);
    unsigned long l = strtoul(str, endptr, base);
    chess_report(l);
    chess_report(errno); errno = 0;
    if (endptr) {
        chess_report(**endptr);
    }
}
void test_strtoul()
{
    chess_message("// test_strtoul()");
    char* ep;

    tst_strtoul("0765",             NULL,  8);
    tst_strtoul("123",              NULL, 10);
    tst_strtoul(" 2147483647 ",     NULL, 10);
    tst_strtoul(" -2147483648 ",    NULL, 10); // convert, but errror because signed
    tst_strtoul(" 4294967295 ",     NULL, 10);
    tst_strtoul("0xBabe",           NULL, 16);
    tst_strtoul(" FFFFFFFFFFFF ",   NULL, 16); // in range for 48 bit
    tst_strtoul(" 1000000000000 ",  NULL, 16); // out of range
    tst_strtoul("   987iabc",       &ep,  10);
    tst_strtoul(" -66",             NULL, 10);
    tst_strtoul("1235678912356789", NULL, 10); // out of range
}

int wrap_atoi(const char* str)
{
    UNKNOWN(str);
    return atoi(str);
}

void test_atoi() // base is always 10
{
    chess_message("// test_atoi()");
    int i;
    i = wrap_atoi("123");      chess_report(i);
    i = wrap_atoi("   -765");  chess_report(i);
    i = wrap_atoi(" 32767 ");  chess_report(i);
    i = wrap_atoi(" -32768 "); chess_report(i);
}

long wrap_atol(const char* str)
{
    UNKNOWN(str);
    return atol(str);
}

void test_atol() // base is always 10
{
    chess_message("// test_atol()");
    long l;
    l = wrap_atol(" 123456789 "); chess_report(l);
    l = wrap_atol("-987654321");  chess_report(l);
}

int main()
{
    test_strtol();
    test_strtoul();
    test_atoi();
    test_atol();
    return 0;
}
