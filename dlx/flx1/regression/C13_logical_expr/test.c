/*
-- Test logical expressions (jumps and side-effects).
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



int AND_3(int a, int b, int c)
{
    if (a && b && c)
        return 1;
    else
        return 0;
}
void test_AND_3()
{
    chess_message("// test_AND_3");
    chess_report(AND_3(0, 0, 0));
    chess_report(AND_3(0, 0, 4));
    chess_report(AND_3(0, 2, 0));
    chess_report(AND_3(0, 2, 4));
    chess_report(AND_3(1, 0, 0));
    chess_report(AND_3(1, 0, 4));
    chess_report(AND_3(1, 2, 0));
    chess_report(AND_3(1, 2, 4));
}


int OR_3(int a, int b, int c)
{
    if (a || b || c)
        return 1;
    else
        return 0;
}
void test_OR_3()
{
    chess_message("// test_OR_3");
    chess_report(OR_3(0, 0, 0));
    chess_report(OR_3(0, 0, 4));
    chess_report(OR_3(0, 2, 0));
    chess_report(OR_3(0, 2, 4));
    chess_report(OR_3(1, 0, 0));
    chess_report(OR_3(1, 0, 4));
    chess_report(OR_3(1, 2, 0));
    chess_report(OR_3(1, 2, 4));
}


int AND_OR_3(int a, int b, int c)
{
    int res = 0;

    if (a && b || c)
        res |= 0x1;
    else
        res |= 0x2;

    if (a || b && c)
        res |= 0x4;
    else
        res |= 0x8;

    if ((a || b) && c)
        res |= 0x10;
    else
        res |= 0x20;

    if (a && (b || c))
        res |= 0x40;
    else
        res |= 0x80;

    return res;
}
void test_AND_OR_3()
{
    chess_message("// test_AND_OR_3");
    chess_report(AND_OR_3(0, 0, 0));
    chess_report(AND_OR_3(0, 0, 4));
    chess_report(AND_OR_3(0, 2, 0));
    chess_report(AND_OR_3(0, 2, 4));
    chess_report(AND_OR_3(1, 0, 0));
    chess_report(AND_OR_3(1, 0, 4));
    chess_report(AND_OR_3(1, 2, 0));
    chess_report(AND_OR_3(1, 2, 4));
}


int nested(int a, int b, int c)
{
    int res = 0;

    if (a && b && c)
        res |= 0x1;
    else if (a || b || c) {
        res |= a ? 0x10 : 0;
        res |= b ? 0x20 : 0;
        res |= c ? 0x40 : 0;
    }

    return res;
}
void test_nested()
{
    chess_message("// test_nested");
    chess_report(nested(0, 0, 0));
    chess_report(nested(0, 0, 4));
    chess_report(nested(0, 2, 0));
    chess_report(nested(0, 2, 4));
    chess_report(nested(1, 0, 0));
    chess_report(nested(1, 0, 4));
    chess_report(nested(1, 2, 0));
    chess_report(nested(1, 2, 4));
}


int side_effect_1(int a, int b, int c)
{
    int res = 0;

    if (a++ || ++b && (c = c + 2))
        res = 1000;
    else
        res = 2000;

    return res + a + b + c;
}
void test_side_effect_1()
{
    chess_message("// test_side_effect_1");
    chess_report(side_effect_1(0, 0, 0));
    chess_report(side_effect_1(1, 0, 0));
    chess_report(side_effect_1(0, 1, 0));
    chess_report(side_effect_1(0,-1,-2));
    chess_report(side_effect_1(0,-1, 0));
    chess_report(side_effect_1(0, 0,-2));
    chess_report(side_effect_1(1, 2, 3));
}


inline int foo(int& a)
{
        int tmp = a; a = a + 11; return tmp;
}
int bar(int& a)
{
        int tmp = a; a = a + 222; return tmp;
}
int side_effect_2(int a, int b, int c)
{
    int res = 0;

    if (a || foo(b) && bar(c))
        res = 1000;
    else
        res = 2000;

    return res + a + b + c;
}
void test_side_effect_2()
{
    chess_message("// test_side_effect_2");
    chess_report(side_effect_2(1, 0, 0));
    chess_report(side_effect_2(1,10,20));
    chess_report(side_effect_2(0, 0, 0));
    chess_report(side_effect_2(0, 1, 0));
    chess_report(side_effect_2(0, 0, 1));
    chess_report(side_effect_2(0, 1, 1));
}


int main()
{
    test_AND_3();
    test_OR_3();
    test_AND_OR_3();
    test_nested();
    test_side_effect_1();
    test_side_effect_2();
    return 0;
}
