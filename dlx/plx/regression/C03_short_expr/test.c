/*
-- Test expressions on int.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



void signed_binary(signed int a, signed int b)
{
    chess_message( "// signed_binary(" << a << ',' << b << ')' );

    signed int c;
    chess_report( c = a + b );
    chess_report( c = a - b );
    chess_report( c = a * b );
    chess_report( c = a & b );
    chess_report( c = a | b );
    chess_report( c = a ^ b );

    chess_report( c = ~a );
    chess_report( c = ~b );

    chess_report( a < b );
    chess_report( a <= b );
    chess_report( a > b );
    chess_report( a >= b );
    chess_report( a == b );
    chess_report( a != b );
}


void signed_shift(signed int a, signed int b)
{
    chess_message( "// signed_shift(" << a << ',' << b << ')' );

    signed int c;
    chess_report( c = a << b );
    chess_report( c = a >> b );
}


void unsigned_binary(unsigned int a, unsigned int b)
{
    chess_message( "// unsigned_binary(" << a << ',' << b << ')' );

    unsigned int c;
    chess_report( c = a + b );
    chess_report( c = a - b );
    chess_report( c = a * b );
    chess_report( c = a & b );
    chess_report( c = a | b );
    chess_report( c = a ^ b );

    chess_report( c = ~a );
    chess_report( c = ~b );

    chess_report( a < b );
    chess_report( a <= b );
    chess_report( a > b );
    chess_report( a >= b );
    chess_report( a == b );
    chess_report( a != b );
}


void unsigned_shift(unsigned int a, unsigned int b)
{
    chess_message( "// unsigned_shift(" << a << ',' << b << ')' );

    unsigned int c;
    chess_report( c = a << b );
    chess_report( c = a >> b );
}


void test(signed int a, signed int b)
{
    signed_binary(a,b);
    unsigned_binary(a,b);
    signed_shift(a,b);
    unsigned_shift(a,b);
}


// Beware of negative shift factors
void test_no_shift(signed int a, signed int b)
{
    signed_binary(a,b);
    unsigned_binary(a,b);
}


//-----------------------------------------------------------------------------

#define X0A 0x0aaa
#define X7F 0x7fff
#define X80 0x8000


int main()
{
    signed int a, b;

    a = 0;      b = 0;          test(a,b);
    a = 1;      b = 1;          test(a,b);
    a = 10;     b = 20;         test_no_shift(a,b);
    a = -25;    b = 4;          test(a,b);
    a = -122;   b = 53;         test_no_shift(a,b);

    a = X0A;    b = 0;          test(a,b);
    a = X0A;    b = 1;          test(a,b);
    a = X0A;    b = 3;          test(a,b);
    a = X0A;    b = 15;         test(a,b);

    a = -X0A;   b = 0;          test(a,b);
    a = -X0A;   b = 1;          test(a,b);
    a = -X0A;   b = 3;          test(a,b);
    a = -X0A;   b = 15;         test(a,b);

    a = X7F;    b = 0;          test(a,b);
    a = X7F;    b = 1;          test(a,b);
    a = X7F;    b = 3;          test(a,b);
    a = X7F;    b = 15;         test(a,b);

    a = -X7F;   b = 0;          test(a,b);
    a = -X7F;   b = 1;          test(a,b);
    a = -X7F;   b = 3;          test(a,b);
    a = -X7F;   b = 15;         test(a,b);

    a = X80;    b = 0;          test(a,b);
    a = X80;    b = 1;          test(a,b);
    a = X80;    b = 3;          test(a,b);
    a = X80;    b = 15;         test(a,b);

    a = 0;      b = -1;         test_no_shift(a,b);
    a = 1;      b = -1;         test_no_shift(a,b);
    a = -1;     b = -1;         test_no_shift(a,b);
    a = 15;     b = -1;         test_no_shift(a,b);
    a = X0A;    b = -1;         test_no_shift(a,b);
    a = -X0A;   b = -1;         test_no_shift(a,b);
    a = X7F;    b = -1;         test_no_shift(a,b);
    a = -X7F;   b = -1;         test_no_shift(a,b);
    a = X80;    b = -1;         test_no_shift(a,b);

    a = 0;      b = X7F;        test_no_shift(a,b);
    a = 1;      b = X7F;        test_no_shift(a,b);
    a = -1;     b = X7F;        test_no_shift(a,b);
    a = 15;     b = X7F;        test_no_shift(a,b);
    a = X0A;    b = X7F;        test_no_shift(a,b);
    a = -X0A;   b = X7F;        test_no_shift(a,b);
    a = X7F;    b = X7F;        test_no_shift(a,b);
    a = -X7F;   b = X7F;        test_no_shift(a,b);
    a = X80;    b = X7F;        test_no_shift(a,b);

    a = 0;      b = -X7F;       test_no_shift(a,b);
    a = 1;      b = -X7F;       test_no_shift(a,b);
    a = -1;     b = -X7F;       test_no_shift(a,b);
    a = 15;     b = -X7F;       test_no_shift(a,b);
    a = X0A;    b = -X7F;       test_no_shift(a,b);
    a = -X0A;   b = -X7F;       test_no_shift(a,b);
    a = X7F;    b = -X7F;       test_no_shift(a,b);
    a = -X7F;   b = -X7F;       test_no_shift(a,b);
    a = X80;    b = -X7F;       test_no_shift(a,b);

    a = 0;      b = X80;        test_no_shift(a,b);
    a = 1;      b = X80;        test_no_shift(a,b);
    a = -1;     b = X80;        test_no_shift(a,b);
    a = 15;     b = X80;        test_no_shift(a,b);
    a = X0A;    b = X80;        test_no_shift(a,b);
    a = -X0A;   b = X80;        test_no_shift(a,b);
    a = X7F;    b = X80;        test_no_shift(a,b);
    a = -X7F;   b = X80;        test_no_shift(a,b);
    a = X80;    b = X80;        test_no_shift(a,b);
    return 0;
}
