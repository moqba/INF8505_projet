/*
-- Test conversion expressions.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#define C_CONVERSIONS {                         \
    signed char sc;                             \
    sc = a; chess_report(sc);                   \
                                                \
    unsigned char uc;                           \
    uc = a; chess_report(uc);                   \
    }


#define S_CONVERSIONS {                         \
    signed short ss;                            \
    ss = a; chess_report(ss);                   \
                                                \
    unsigned short us;                          \
    us = a; chess_report(us);                   \
    }

#define I_CONVERSIONS {                         \
    signed int si;                              \
    si = a; chess_report(si);                   \
                                                \
    unsigned int ui;                            \
    ui = a; chess_report(ui);                   \
    }


#define L_CONVERSIONS {                         \
    signed long long sl;                        \
    sl = a; chess_report(sl);                   \
                                                \
    unsigned long long ul;                      \
    ul = a; chess_report(ul);                   \
    }


void cast_from_signed_char(signed char a)
{
    chess_message( "// cast_from_signed_char(" << (int)a << ')' );
    if (a >= 0)
        C_CONVERSIONS
    S_CONVERSIONS
    I_CONVERSIONS
    L_CONVERSIONS
}

void cast_from_unsigned_char(unsigned char a)
{
    chess_message( "// cast_from_unsigned_char(" << (unsigned)a << ')' );
    if (a < 128)
        C_CONVERSIONS
    S_CONVERSIONS
    I_CONVERSIONS
    L_CONVERSIONS
}

void cast_from_signed_short(signed short a)
{
    chess_message( "// cast_from_signed_short(" << a << ')' );
    if (a >= 0 && a < 128)
        C_CONVERSIONS
    S_CONVERSIONS
    I_CONVERSIONS
    L_CONVERSIONS
}

void cast_from_unsigned_short(unsigned short a)
{
    chess_message( "// cast_from_unsigned_short(" << a << ')' );
    if (a < 128)
        C_CONVERSIONS
    S_CONVERSIONS
    I_CONVERSIONS
    L_CONVERSIONS
}

void cast_from_signed_int(signed int a)
{
    chess_message( "// cast_from_signed_int(" << a << ')' );
    if (a >= 0 && a < 128)
        C_CONVERSIONS
    S_CONVERSIONS
    I_CONVERSIONS
    L_CONVERSIONS
}


void cast_from_unsigned_int(unsigned int a)
{
    chess_message( "// cast_from_unsigned_int(" << a << ')' );
    if (a < 128)
        C_CONVERSIONS
    S_CONVERSIONS
    I_CONVERSIONS
    L_CONVERSIONS
}

void cast_from_signed_long_long(signed long long a)
{
    chess_message( "// cast_from_signed_long_long(" << a << ')' );
    if (a >= 0 && a < 128)
        C_CONVERSIONS
    S_CONVERSIONS
    I_CONVERSIONS
    L_CONVERSIONS
}

void cast_from_unsigned_long_long(unsigned long long a)
{
    chess_message( "// cast_from_unsigned_long_long(" << a << ')' );
    if (a < 128)
        C_CONVERSIONS
    S_CONVERSIONS
    I_CONVERSIONS
    L_CONVERSIONS
}


int main()
{
    {
        signed char aa;
        aa = 10;         cast_from_signed_char(aa);
        aa = -20;        cast_from_signed_char(aa);
        aa = 0x7f;       cast_from_signed_char(aa);
        aa = -1;         cast_from_signed_char(aa);
    }

    {
        unsigned char aa;
        aa = 10;         cast_from_unsigned_char(aa);
        aa = 20;         cast_from_unsigned_char(aa);
        aa = 0x7f;       cast_from_unsigned_char(aa);
        aa = 0xff;       cast_from_unsigned_char(aa);
    }

    {
        signed short aa;
        aa = 10;         cast_from_signed_short(aa);
        aa = -20;        cast_from_signed_short(aa);
        aa = 0x7fff;     cast_from_signed_short(aa);
        aa = -1;         cast_from_signed_short(aa);
    }

    {
        unsigned short aa;
        aa = 10;         cast_from_unsigned_short(aa);
        aa = 20;         cast_from_unsigned_short(aa);
        aa = 0x7fff;     cast_from_unsigned_short(aa);
        aa = 0xffff;     cast_from_unsigned_short(aa);
    }

    {
        signed int aa;
        aa = 10;         cast_from_signed_int(aa);
        aa = -20;        cast_from_signed_int(aa);
        aa = 0x7fffffff; cast_from_signed_int(aa);
        aa = -1;         cast_from_signed_int(aa);
    }

    {
        unsigned int aa;
        aa = 10;         cast_from_unsigned_int(aa);
        aa = 20;         cast_from_unsigned_int(aa);
        aa = 0x7fffffff; cast_from_unsigned_int(aa);
        aa = 0xffffffff; cast_from_unsigned_int(aa);
    }

    {
        signed long long aa;
        aa = 10;                     cast_from_signed_long_long(aa);
        aa = -20;                    cast_from_signed_long_long(aa);
        aa = 0x7fffffffffffffffULL;  cast_from_signed_long_long(aa);
        aa = -1;                     cast_from_signed_long_long(aa);
    }

    {
        unsigned long long aa;
        aa = 10;                     cast_from_unsigned_long_long(aa);
        aa = 20;                     cast_from_unsigned_long_long(aa);
        aa = 0x7fffffffffffffffULL;  cast_from_unsigned_long_long(aa);
        aa = 0xffffffffffffffffULL;  cast_from_unsigned_long_long(aa);
    }

    return 0;
}
