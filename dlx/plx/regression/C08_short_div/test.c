/*
-- Test division on ints.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



void signed_div(signed int a, signed int b)
{
    chess_message( "// signed_div(" << a << ',' << b << ')' );

    signed int c;
    chess_report( c = a / b );
    chess_report( c = a % b );
}


void unsigned_div(unsigned int a, unsigned int b)
{
    chess_message( "// unsigned_div(" << a << ',' << b << ')' );

    unsigned int c;
    chess_report( c = a / b );
    //chess_report( c = a % b );
}


void test(signed int a, signed int b) // b != 0
{
    signed_div(a,b);
    unsigned_div(a,b);
}


int main()
{
    signed int a, b;

    a = 1;              b = 1;                  test(a,b);
    a = 10;             b = 20;                 test(a,b);
    a = -25;            b = 4;                  test(a,b);
    a = -122;           b = 53;                 test(a,b);

    a = 0x7f;           b = 1;                  test(a,b);
    a = 0x7f;           b = 0x7f;               test(a,b);

    a = 0;              b = 0x7f;               test(a,b);
    a = 1;              b = 0x7f;               test(a,b);
    a = -1;             b = 0x7f;               test(a,b);

    a = 1;              b = 0x7fff;             test(a,b);
    a = 0x7fff;         b = 1;                  test(a,b);
    a = -3;             b = 0x7fff;             test(a,b);
    a = 0x7fff;         b = -3;                 test(a,b);

    a = -0x7f;          b = 1;                  test(a,b);

    a = 0;              b = -0x7f;              test(a,b);
    a = 1;              b = -0x7f;              test(a,b);
    a = -1;             b = -0x7f;              test(a,b);
    a = -0x7f;          b = -0x7f;              test(a,b);

    a = -0x80;          b = 1;                  test(a,b);

    a = -0x80;          b = -0x80;              test(a,b);
    a = 0;              b = -0x80;              test(a,b);
    a = 1;              b = -0x80;              test(a,b);
    a = -1;             b = -0x80;              test(a,b);

    return 0;
}
