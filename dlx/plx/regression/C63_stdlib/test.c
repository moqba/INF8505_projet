/*
-- Test: stdarg.h functions.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#include "stdlib.h"
#include "stddef.h"
#include "errno.h"

void test_strtol()
{
    chess_message( "// test_strtol()" );
    long sl;
    char* ep;
    sl = strtol("0765", (char **)NULL, 8);            chess_report(sl); chess_report(errno);
    sl = strtol("123", (char **)NULL, 10);            chess_report(sl); chess_report(errno);
    sl = strtol("0xBabe", (char **)NULL, 16);         chess_report(sl); chess_report(errno);
    sl = strtol(" 2147483647 ", (char **)NULL, 10);   chess_report(sl); chess_report(errno);
    sl = strtol(" -2147483648 ", (char **)NULL, 10);  chess_report(sl); chess_report(errno);
    sl = strtol(" -1 ", (char **)NULL, 10);           chess_report(sl); chess_report(errno);
    sl = strtol("   -987iabc", &ep, 10);              chess_report(sl); chess_report(*ep);
    sl = strtol("123567891234567892356789123456789", (char **)NULL, 10); chess_report(errno);
}

void test_strtoul()
{
    chess_message( "// test_strtoul()" );
    unsigned long ul;
    char* ep;
    ul = strtoul("0765", (char **)NULL, 8);            chess_report(ul); chess_report(errno);
    ul = strtoul("123", (char **)NULL, 10);            chess_report(ul); chess_report(errno);
    ul = strtoul("0xBabe", (char **)NULL, 16);         chess_report(ul); chess_report(errno);
    ul = strtoul(" 2147483647 ", (char **)NULL, 10);   chess_report(ul); chess_report(errno);
    ul = strtoul(" -2147483648 ", (char **)NULL, 10);  chess_report(ul); chess_report(errno);
    ul = strtoul(" 4294967295 ", (char **)NULL, 10);   chess_report(ul); chess_report(errno);
    ul = strtoul("   987iabc", &ep, 10);               chess_report(ul); chess_report(*ep);
    ul = strtoul(" -66", (char **)NULL, 10);                          chess_report(errno);
    ul = strtoul("123567891234567892356789123456789", (char **)NULL, 10);                chess_report(errno);
}

void test_atoi()
{
    chess_message( "// test_atoi()" );
    int i;
    i = atoi("123");         chess_report(i);
    i = atoi("   -765");     chess_report(i);
    i = atoi(" 32767 ");     chess_report(i);
    i = atoi(" -32768 ");    chess_report(i);
}

void test_atol()
{
    chess_message( "// test_atol()" );
    long l;
    l = atol("123");         chess_report(l);
    l = atol("   -765");     chess_report(l);
}

int main()
{
    test_strtol();
    test_strtoul();
    test_atoi();
    test_atol();
    return 0;
}

