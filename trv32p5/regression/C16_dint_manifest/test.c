/*
-- Test chess_manifest checks in l_mul routine.
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


// These must be set externally:
// #define DINT_        long long
// #define DINT_USUFFIX ULL

// derived types
#define STYPE   signed DINT_
#define UTYPE unsigned DINT_
#define VAL(A)         DINT_##A

/* (only) apply mask to native code if asip and native type are not exactly matching (eg. 24bit) */
#define SE(A)        DINT_##SE(A)
#define ZE(A)        DINT_##ZE(A)

#define SVAL(A)      (STYPE)SE(DINT_##A)
#define UVAL(A)      (UTYPE)ZE(DINT_##A)


#define  C1 DINT_CONCAT_INT_4DIG(0000,0000) /* 0x0000000000000000 */
#define  C2 DINT_CONCAT_INT_4DIG(0000,0001) /* 0x0000000000000001 */
#define  C3 DINT_CONCAT_INT_4DIG(0000,0011) /* 0x0000000000000011 */
#define  C4 DINT_CONCAT_INT_4DIG(0001,0100) /* 0x0000000100000100 */
#define  C5 DINT_CONCAT_INT_4DIG(0010,0101) /* 0x0000001000000101 */
#define  C6 DINT_CONCAT_INT_4DIG(0011,0010) /* 0x0000001100000110 */
#define  C7 DINT_CONCAT_INT_4DIG(0001,0111) /* 0x0000000100000111 */
#define  C8 DINT_CONCAT_INT_4DIG(0011,1001) /* 0x0000001100001001 */
#define  C9 DINT_CONCAT_INT_4DIG(0001,1011) /* 0x0000000100001011 */

#define SL_ADD(X) \
UTYPE CONCAT(sl_addl_,X)(UTYPE a) \
{ \
    chess_message("// sl_addl(" << a << ", " << CONCAT(X,DINT_USUFFIX) << ')'); \
    UTYPE c; \
    chess_report(c = a + (UTYPE)(CONCAT(X,DINT_USUFFIX))); \
    return c; \
} \
UTYPE CONCAT(sl_addr_,X)(UTYPE a) \
{ \
    chess_message("// sl_addr(" << CONCAT(X,DINT_USUFFIX) << ", " << a << ')'); \
    UTYPE c; \
    chess_report(c = (UTYPE)(CONCAT(X,DINT_USUFFIX)) + a); \
    return c; \
}\
UTYPE CONCAT(sl_add_,X)(UTYPE a) \
{ \
    UTYPE x = CONCAT(sl_addl_,X)(a); \
    UTYPE y = CONCAT(sl_addr_,X)(a); \
    chess_report(x == y); \
    return x; \
}

#define SL_SUB(X) \
UTYPE CONCAT(sl_subl_,X)(UTYPE a) \
{ \
    chess_message("// sl_subl(" << a << ", " << CONCAT(X,DINT_USUFFIX) << ')'); \
    UTYPE c; \
    chess_report(c = a - (UTYPE)(CONCAT(X,DINT_USUFFIX))); \
    return c; \
} \
UTYPE CONCAT(sl_subr_,X)(UTYPE a) \
{ \
    chess_message("// sl_subr(" << CONCAT(X,DINT_USUFFIX) << ", " << a << ')'); \
    UTYPE c; \
    chess_report(c = (UTYPE)(CONCAT(X,DINT_USUFFIX)) - a); \
    return c; \
}\
UTYPE CONCAT(sl_sub_,X)(UTYPE a) \
{ \
    UTYPE x = CONCAT(sl_subl_,X)(a); \
    UTYPE y = CONCAT(sl_subr_,X)(a); \
    chess_report(x == -y); \
    return x; \
}

#define SL_MUL(X) \
STYPE CONCAT(sl_mull_,X)(STYPE a) \
{ \
    chess_message("// sl_mull(" << a << ", " << CONCAT(X,DINT_USUFFIX) << ')'); \
    STYPE c; \
    chess_report(c = a * (STYPE)(CONCAT(X,DINT_USUFFIX))); \
    return c; \
} \
STYPE CONCAT(sl_mulr_,X)(STYPE a) \
{ \
    chess_message("// sl_mulr(" << CONCAT(X,DINT_USUFFIX) << ", " << a << ')'); \
    STYPE c; \
    chess_report(c = (STYPE)(CONCAT(X,DINT_USUFFIX)) * a); \
    return c; \
} \
STYPE CONCAT(sl_mul_,X)(STYPE a) \
{ \
    STYPE x = CONCAT(sl_mull_,X)(a); \
    STYPE y = CONCAT(sl_mulr_,X)(a); \
    chess_report(x == y); \
    return x; \
}

#define UL_MUL(X) \
UTYPE CONCAT(ul_mull_,X)(UTYPE a) \
{ \
    chess_message("// ul_mull(" << a << ", " << CONCAT(X,DINT_USUFFIX) << ')'); \
    UTYPE c; \
    chess_report(c = a * (UTYPE)(CONCAT(X,DINT_USUFFIX))); \
    return c; \
} \
UTYPE CONCAT(ul_mulr_,X)(UTYPE a) \
{ \
    chess_message("// ul_mulr(" << CONCAT(X,DINT_USUFFIX) << ", " << a << ')'); \
    UTYPE c; \
    chess_report(c = (UTYPE)(CONCAT(X,DINT_USUFFIX)) * a); \
    return c; \
} \
UTYPE CONCAT(ul_mul_,X)(UTYPE a) \
{ \
    UTYPE x = CONCAT(ul_mull_,X)(a); \
    UTYPE y = CONCAT(ul_mulr_,X)(a); \
    chess_report(x == y); \
    return x; \
}

SL_ADD(C1)
SL_ADD(C2)
SL_ADD(C3)
SL_ADD(C4)
SL_ADD(C5)
SL_ADD(C6)
SL_ADD(C7)
SL_ADD(C8)
SL_ADD(C9)

SL_SUB(C1)
SL_SUB(C2)
SL_SUB(C3)
SL_SUB(C4)
SL_SUB(C5)
SL_SUB(C6)
SL_SUB(C7)
SL_SUB(C8)
SL_SUB(C9)

SL_MUL(C1)
SL_MUL(C2)
SL_MUL(C3)
SL_MUL(C4)
SL_MUL(C5)
SL_MUL(C6)
SL_MUL(C7)
SL_MUL(C8)
SL_MUL(C9)

UL_MUL(C1)
UL_MUL(C2)
UL_MUL(C3)
UL_MUL(C4)
UL_MUL(C5)
UL_MUL(C6)
UL_MUL(C7)
UL_MUL(C8)
UL_MUL(C9)

UTYPE sl_add(UTYPE a)
{
    UTYPE x = 0;
    x += CONCAT(sl_add_,C1)(a);
    x += CONCAT(sl_add_,C2)(a);
    x += CONCAT(sl_add_,C3)(a);
    x += CONCAT(sl_add_,C4)(a);
    x += CONCAT(sl_add_,C5)(a);
    x += CONCAT(sl_add_,C6)(a);
    x += CONCAT(sl_add_,C7)(a);
    x += CONCAT(sl_add_,C8)(a);
    x += CONCAT(sl_add_,C9)(a);
    return x;
}

UTYPE sl_sub(UTYPE a)
{
    UTYPE x = 0;
    x += CONCAT(sl_sub_,C1)(a);
    x += CONCAT(sl_sub_,C2)(a);
    x += CONCAT(sl_sub_,C3)(a);
    x += CONCAT(sl_sub_,C4)(a);
    x += CONCAT(sl_sub_,C5)(a);
    x += CONCAT(sl_sub_,C6)(a);
    x += CONCAT(sl_sub_,C7)(a);
    x += CONCAT(sl_sub_,C8)(a);
    x += CONCAT(sl_sub_,C9)(a);
    return x;
}

UTYPE sl_mul(UTYPE a)
{
    UTYPE x = 0;
    x += CONCAT(sl_mul_,C1)(a);
    x += CONCAT(sl_mul_,C2)(a);
    x += CONCAT(sl_mul_,C3)(a);
    x += CONCAT(sl_mul_,C4)(a);
    x += CONCAT(sl_mul_,C5)(a);
    x += CONCAT(sl_mul_,C6)(a);
    x += CONCAT(sl_mul_,C7)(a);
    x += CONCAT(sl_mul_,C8)(a);
    x += CONCAT(sl_mul_,C9)(a);
    return x;
}

UTYPE ul_mul(UTYPE a)
{
    UTYPE x = 0;
    x += CONCAT(ul_mul_,C1)(a);
    x += CONCAT(ul_mul_,C2)(a);
    x += CONCAT(ul_mul_,C3)(a);
    x += CONCAT(ul_mul_,C4)(a);
    x += CONCAT(ul_mul_,C5)(a);
    x += CONCAT(ul_mul_,C6)(a);
    x += CONCAT(ul_mul_,C7)(a);
    x += CONCAT(ul_mul_,C8)(a);
    x += CONCAT(ul_mul_,C9)(a);
    return x;
}

void test(STYPE a)
{
    chess_report(sl_add(a));
    chess_report(sl_sub(a));
    chess_report(sl_mul(a));
    chess_report(ul_mul(a));
}

STYPE A[] = { 0,1,-1,4,10,-25,-122,53, SVAL(MAXSH),
              SVAL(X0AAA), -SVAL(X0AAA),
              SVAL(X7FFF), -SVAL(X7FFF),
              SVAL(X8000),  SVAL(X7FFF)-1,
              SVAL(XFFFF),  SVAL(XFFFF-1) };

int main()
{
    // more exhaustive data
    int N=sizeof(A)/sizeof(STYPE);
    for (int i=0; i<N; i++) {
       STYPE a =  A[i];  test(a);
    }

    return 0;
}
