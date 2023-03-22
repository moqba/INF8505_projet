/*
-- Test expressions on long long.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/




void signed_binary(signed long long a, signed long long b)
{
    chess_message( "// signed_binary(" << a << ',' << b << ')' );

    signed long long c;
    chess_report( c = a + b );
    chess_report( c = a - b );
    chess_report( c = a * b );
    chess_report( c = a & b );
    chess_report( c = a | b );
    chess_report( c = a ^ b );

    chess_report( c = ~a );
    chess_report( c = ~b );
}

void signed_compare(signed long long a, signed long long b)
{
    chess_message( "// signed_compare(" << a << ',' << b << ')' );

    signed long long c;
    chess_report( a < b );
    chess_report( a <= b );
    chess_report( a > b );
    chess_report( a >= b );
    chess_report( a == b );
    chess_report( a != b );
}


void signed_shift(signed long long a, signed long long b)
{
    chess_message( "// signed_shift(" << a << ',' << b << ')' );

    signed long long c;
    chess_report( c = a << b );
    chess_report( c = a >> b );
}


void unsigned_binary(unsigned long long a, unsigned long long b)
{
    chess_message( "// unsigned_binary(" << a << ',' << b << ')' );

    unsigned long long c;
    chess_report( c = a + b );
    chess_report( c = a - b );
    chess_report( c = a * b );
    chess_report( c = a & b );
    chess_report( c = a | b );
    chess_report( c = a ^ b );

    chess_report( c = ~a );
    chess_report( c = ~b );
}

void unsigned_compare(unsigned long long a, unsigned long long b)
{
    chess_message( "// unsigned_compare(" << a << ',' << b << ')' );

    unsigned long long c;

    chess_report( a < b );
    chess_report( a <= b );
    chess_report( a > b );
    chess_report( a >= b );
    chess_report( a == b );
    chess_report( a != b );
}


void unsigned_shift(unsigned long long a, unsigned long long b)
{
    chess_message( "// unsigned_shift(" << a << ',' << b << ')' );

    unsigned long long c;
    chess_report( c = a << b );
    chess_report( c = a >> b );
}


void test(signed long long a, signed long long b)
{
    signed_binary(a,b);
    unsigned_binary(a,b);
}

void test_cmp(signed long long a, signed long long b)
{
    signed_compare(a,b);
    unsigned_compare(a,b);
}


void test_sh(signed long long a, signed long long b)
{
    signed_shift(a,b);
    unsigned_shift(a,b);
}


//-----------------------------------------------------------------------------

#define X0A 0x0aaaaaaaaaaaaaaaULL
#define X7F 0x7fffffffffffffffULL
#define X80 0x8000000000000000ULL
#define X08 0x0000000080000000ULL

int main()
{
    signed long long a, b;

    a = 0;      b = 0;          test(a,b); test_cmp(a,b); test_sh(a,b);
    a = 1;      b = 1;          test(a,b); test_cmp(a,b); test_sh(a,b);
    a = -25;    b = 4;          test(a,b); test_cmp(a,b); test_sh(a,b);
    a = 10;     b = 20;         test(a,b); test_cmp(a,b); test_sh(a,b);
    a = -122;   b = 53;         test(a,b); test_cmp(a,b);

    a = X0A;    b = 0;          test(a,b); test_cmp(a,b); test_sh(a,b);
    a = X0A;    b = 1;          test(a,b); test_cmp(a,b); test_sh(a,b);
    a = X0A;    b = 3;          test(a,b); test_cmp(a,b); test_sh(a,b);
    a = X0A;    b = 15;         test(a,b); test_cmp(a,b); test_sh(a,b);

    a = -X0A;   b = 0;          test(a,b); test_cmp(a,b);
    a = -X0A;   b = 1;          test(a,b); test_cmp(a,b);
    a = -X0A;   b = 3;          test(a,b); test_cmp(a,b);
    a = -X0A;   b = 15;         test(a,b); test_cmp(a,b);

    a = X7F;    b = 0;          test(a,b); test_cmp(a,b); test_sh(a,b);
    a = X7F;    b = 1;          test(a,b); test_cmp(a,b); test_sh(a,b);
    a = X7F;    b = 3;          test(a,b); test_cmp(a,b); test_sh(a,b);
    a = X7F;    b = 15;         test(a,b); test_cmp(a,b); test_sh(a,b);

    a = -X7F;   b = 0;          test(a,b); test_cmp(a,b);
    a = -X7F;   b = 1;          test(a,b); test_cmp(a,b);
    a = -X7F;   b = 3;          test(a,b); test_cmp(a,b);
    a = -X7F;   b = 15;         test(a,b); test_cmp(a,b);

    a = X80;    b = 0;          test(a,b);
    a = X80;    b = 1;          test(a,b);
    a = X80;    b = 3;          test(a,b);
    a = X80;    b = 15;         test(a,b);

    a = -15;    b = 16;         test(a,b); test_cmp(a,b); test_sh(a,b);
    a = X7F;    b = 16;         test(a,b); test_cmp(a,b); test_sh(a,b);
    a = -15;    b = 31;         test(a,b); test_cmp(a,b); test_sh(a,b);
    a = X7F;    b = 31;         test(a,b); test_cmp(a,b); test_sh(a,b);

    a = 0;      b = -1;         test(a,b); test_cmp(a,b);
    a = 1;      b = -1;         test(a,b); test_cmp(a,b);
    a = -1;     b = -1;         test(a,b); test_cmp(a,b);
    a = 15;     b = -1;         test(a,b); test_cmp(a,b);
    a = X0A;    b = -1;         test(a,b); test_cmp(a,b);
    a = -X0A;   b = -1;         test(a,b); test_cmp(a,b);
    a = X7F;    b = -1;         test(a,b); test_cmp(a,b);
    a = -X7F;   b = -1;         test(a,b); test_cmp(a,b);
    a = X80;    b = -1;         test(a,b);

    a = 0;      b = X7F;        test(a,b); test_cmp(a,b);
    a = 1;      b = X7F;        test(a,b); test_cmp(a,b);
    a = -1;     b = X7F;        test(a,b); test_cmp(a,b);
    a = 15;     b = X7F;        test(a,b); test_cmp(a,b);
    a = X0A;    b = X7F;        test(a,b); test_cmp(a,b);
    a = -X0A;   b = X7F;        test(a,b); test_cmp(a,b);
    a = X7F;    b = X7F;        test(a,b); test_cmp(a,b);
    a = -X7F;   b = X7F;        test(a,b); test_cmp(a,b);
    a = X80;    b = X7F;        test(a,b);

    a = 0;      b = -X7F;       test(a,b); test_cmp(a,b);
    a = 1;      b = -X7F;       test(a,b); test_cmp(a,b);
    a = -1;     b = -X7F;       test(a,b); test_cmp(a,b);
    a = 15;     b = -X7F;       test(a,b); test_cmp(a,b);
    a = X0A;    b = -X7F;       test(a,b); test_cmp(a,b);
    a = -X0A;   b = -X7F;       test(a,b); test_cmp(a,b);
    a = X7F;    b = -X7F;       test(a,b); test_cmp(a,b);
    a = -X7F;   b = -X7F;       test(a,b); test_cmp(a,b);
    a = X80;    b = -X7F;       test(a,b);

    a = 0;      b = X80;        test(a,b);
    a = 1;      b = X80;        test(a,b);
    a = -1;     b = X80;        test(a,b);
    a = 15;     b = X80;        test(a,b);
    a = X0A;    b = X80;        test(a,b);
    a = -X0A;   b = X80;        test(a,b);
    a = X7F;    b = X80;        test(a,b);
    a = -X7F;   b = X80;        test(a,b);
    a = X80;    b = X80;        test(a,b);

    return 0;
}
