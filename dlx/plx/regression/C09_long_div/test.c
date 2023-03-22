/*
-- Test division on longs.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


void signed_div(signed long long a, signed long long b)
{
    chess_message( "// signed_div(" << a << ',' << b << ')' );

    signed long long c;
    chess_report( c = a / b );
    chess_report( c = a % b );
}


void unsigned_div(unsigned long long a, unsigned long long b)
{
    chess_message( "// unsigned_div(" << a << ',' << b << ')' );

    unsigned long long c;
    chess_report( c = a / b );
    chess_report( c = a % b );
}


void test(signed long long a, signed long long b) // b != 0
{
    signed_div(a,b);
    unsigned_div(a,b);
}

void stest(signed long long a, signed long long b) // b != 0
{
    signed_div(a,b);
}


int main()
{
    signed long long  a, b;

    a = 1;              b = 1;                  test(a,b);
    a = 10;             b = 20;                 test(a,b);

    a = 0x7f;           b = 1;                  test(a,b);
    a = 0x7f;           b = 0x7f;               test(a,b);

    a = 0x7fffffffffffffffULL;     b = 0x7f;            test(a,b);
    a = 0x7f;           b = 0x7fffffffffffffffULL;              test(a,b);

    a = 0;              b = 0x7f;               test(a,b);
    a = 1;              b = 0x7f;               test(a,b);


    a = 0;              b = -0x7f;              test(a,b);
    a = 1;              b = -0x7f;              test(a,b);


    a = 0;              b = -0x80;              test(a,b);
    a = 1;              b = -0x80;              test(a,b);

    a = -25;            b = 4;                  stest(a,b);
    a = -122;           b = 53;                 stest(a,b);
    a = -1;             b = 0x7f;               stest(a,b);
    a = -0x7f;          b = 1;                  stest(a,b);
    a = -1;             b = -0x7f;              stest(a,b);
    a = -0x7f;          b = -0x7f;              stest(a,b);
    a = -0x80;          b = 1;                  stest(a,b);
    a = -0x80;          b = -0x80;              stest(a,b);
    a = -1;             b = -0x80;              stest(a,b);
    return 0;
}
