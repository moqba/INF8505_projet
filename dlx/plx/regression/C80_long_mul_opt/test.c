/*
-- Test chess_manigest checks in l_mul routine.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



typedef  long long slong_t;
typedef  unsigned long long ulong_t;

#define SL_ADD(X) \
void sl_addl_##X(slong_t a) \
{ \
    chess_message( "// sl_addl(" << a << ',' << X##ULL << ')' ); \
    slong_t c; \
    chess_report( c = a + (slong_t)(X##ULL)); \
} \
void sl_addr_##X(slong_t a) \
{ \
    chess_message( "// sl_addr(" << X##ULL << ',' << a << ')' ); \
    slong_t c; \
    chess_report( c = (slong_t)(X##ULL) + a); \
}\
void sl_add_##X(slong_t a) \
{ \
    sl_addl_##X(a); \
    sl_addr_##X(a); \
}

#define SL_SUB(X) \
void sl_subl_##X(slong_t a) \
{ \
    chess_message( "// sl_subl(" << a << ',' << X##ULL << ')' ); \
    slong_t c; \
    chess_report( c = a - (slong_t)(X##ULL)); \
} \
void sl_subr_##X(slong_t a) \
{ \
    chess_message( "// sl_subr(" << X##ULL << ',' << a << ')' ); \
    slong_t c; \
    chess_report( c = (slong_t)(X##ULL) - a); \
}\
void sl_sub_##X(slong_t a) \
{ \
    sl_subl_##X(a); \
    sl_subr_##X(a); \
}

SL_ADD(0x0000000000000000)
SL_ADD(0x0000000000000001)
SL_ADD(0x0000000000000011)
SL_ADD(0x0000000100000000)
SL_ADD(0x0000001000000000)
SL_ADD(0x0000001100000000)
SL_ADD(0x0000000100000001)
SL_ADD(0x0000001100000001)
SL_ADD(0x0000000100000011)

SL_SUB(0x0000000000000000)
SL_SUB(0x0000000000000001)
SL_SUB(0x0000000000000011)
SL_SUB(0x0000000100000000)
SL_SUB(0x0000001000000000)
SL_SUB(0x0000001100000000)
SL_SUB(0x0000000100000001)
SL_SUB(0x0000001100000001)
SL_SUB(0x0000000100000011)

void sl_add(slong_t a)
{
    sl_add_0x0000000000000000(a);
    sl_add_0x0000000000000001(a);
    sl_add_0x0000000000000011(a);
    sl_add_0x0000000100000000(a);
    sl_add_0x0000001000000000(a);
    sl_add_0x0000001100000000(a);
    sl_add_0x0000000100000001(a);
    sl_add_0x0000001100000001(a);
    sl_add_0x0000000100000011(a);
}

void sl_sub(ulong_t a)
{
    sl_sub_0x0000000000000000(a);
    sl_sub_0x0000000000000001(a);
    sl_sub_0x0000000000000011(a);
    sl_sub_0x0000000100000000(a);
    sl_sub_0x0000001000000000(a);
    sl_sub_0x0000001100000000(a);
    sl_sub_0x0000000100000001(a);
    sl_sub_0x0000001100000001(a);
    sl_sub_0x0000000100000011(a);
}

#define SL_MUL(X) \
void sl_mull_##X(slong_t a) \
{ \
    chess_message( "// sl_mull(" << a << ',' << X##ULL << ')' ); \
    slong_t c; \
    chess_report( c = a * (slong_t)(X##ULL)); \
} \
void sl_mulr_##X(slong_t a) \
{ \
    chess_message( "// sl_mulr(" << X##ULL << ',' << a << ')' ); \
    slong_t c; \
    chess_report( c = (slong_t)(X##ULL) * a); \
} \
void sl_mul_##X(slong_t a) \
{ \
    sl_mull_##X(a); \
    sl_mulr_##X(a); \
}

#define UL_MUL(X) \
void ul_mul_##X(ulong_t a) \
{ \
    chess_message( "// ul_mul(" << a << ',' << X##ULL << ')' ); \
    ulong_t c; \
    chess_report( c = a * (ulong_t)(X##ULL)); \
}

SL_MUL(0x0000000000000000)
SL_MUL(0x0000000000000001)
SL_MUL(0x0000000000000011)
SL_MUL(0x0000000100000000)
SL_MUL(0x0000001000000000)
SL_MUL(0x0000001100000000)
SL_MUL(0x0000000100000001)
SL_MUL(0x0000001100000001)
SL_MUL(0x0000000100000011)

UL_MUL(0x0000000000000000)
UL_MUL(0x0000000000000001)
UL_MUL(0x0000000000000011)
UL_MUL(0x0000000100000000)
UL_MUL(0x0000001000000000)
UL_MUL(0x0000001100000000)
UL_MUL(0x0000000100000001)
UL_MUL(0x0000001100000001)
UL_MUL(0x0000000100000011)

void sl_mul(slong_t a)
{
    sl_mul_0x0000000000000000(a);
    sl_mul_0x0000000000000001(a);
    sl_mul_0x0000000000000011(a);
    sl_mul_0x0000000100000000(a);
    sl_mul_0x0000001000000000(a);
    sl_mul_0x0000001100000000(a);
    sl_mul_0x0000000100000001(a);
    sl_mul_0x0000001100000001(a);
    sl_mul_0x0000000100000011(a);
}

void ul_mul(ulong_t a)
{
    ul_mul_0x0000000000000000(a);
    ul_mul_0x0000000000000001(a);
    ul_mul_0x0000000000000011(a);
    ul_mul_0x0000000100000000(a);
    ul_mul_0x0000001000000000(a);
    ul_mul_0x0000001100000000(a);
    ul_mul_0x0000000100000001(a);
    ul_mul_0x0000001100000001(a);
    ul_mul_0x0000000100000011(a);
}

#define X0A 0x0aaaaaaaaaaaaaaaULL
#define X7F 0x7fffffffffffffffULL
#define X80 0x8000000000000000ULL
#define X08 0x0000000080000000ULL

void test(long long a)
{
     sl_add(a);
     sl_sub(a);
     sl_mul(a);
     ul_mul(a);
}

int main()
{
    slong_t a;

    a =  1;                        test(a);
    a = -1;                        test(a);
    a = 10;                        test(a);
    a = 0x0000002200000011ULL;     test(a);
    a = 0x8000000200000011ULL;     test(a);
    a = 0x8000000280000003ULL;     test(a);
    a = 0x0000003280000004ULL;     test(a);

    return 0;
}
