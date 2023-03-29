/*
-- Test: ctype.h functions.
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
#include "ctype.h"

void test(char c)
{
    chess_message("// test: " << int(c));
    UNKNOWN(c);
    chess_report(isalnum(c)  ? 1 : 0);
    chess_report(isalpha(c)  ? 1 : 0);
    chess_report(isblank(c)  ? 1 : 0);
    chess_report(iscntrl(c)  ? 1 : 0);
    chess_report(isdigit(c)  ? 1 : 0);
    chess_report(isgraph(c)  ? 1 : 0);
    chess_report(islower(c)  ? 1 : 0);
    chess_report(isprint(c)  ? 1 : 0);
    chess_report(ispunct(c)  ? 1 : 0);
    chess_report(isspace(c)  ? 1 : 0);
    chess_report(isupper(c)  ? 1 : 0);
    chess_report(isxdigit(c) ? 1 : 0);
}

int main()
{
    chess_report(isalnum('a') ? 1 : 0);
    chess_report(isprint('~') ? 1 : 0);

    test('k');
    test('Z');
    test(' ');
    test('7');
    test('\t');
    test('\n');

    for (int c = 0; c < 128; c++) test(c);

    chess_report(tolower('P'));
    chess_report(tolower('p'));
    chess_report(tolower('.'));

    chess_report(toupper('a'));
    chess_report(toupper('A'));
    chess_report(toupper('.'));
    return 0;
}
