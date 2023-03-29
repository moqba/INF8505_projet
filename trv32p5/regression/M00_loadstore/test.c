/*
-- Test load/stores of byte/short/int/long/longlong
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

void* escape_ptr;

#define INT_SVAL(A) INT_SE(INT_##A)

int A[] = {
    0, 1, -1, 4, 10, -25, -122, 53,
    INT_SVAL(XCDEF), -INT_SVAL(XCDEF),
    INT_SVAL(X3210), -INT_SVAL(X3210),
    INT_SVAL(X0AAA), -INT_SVAL(X0AAA),
    INT_SVAL(X7FFF), -INT_SVAL(X7FFF),
    INT_SVAL(X8000),  INT_SVAL(X7FFF) - 1,
    INT_SVAL(XFFFF),  INT_SVAL(XFFFF - 1)
};

int      T_int [32];
unsigned T_uint[32];

#ifdef HAS_CHAR
char          T_char [32];
unsigned char T_uchar[32];
#endif

#ifdef HAS_SHORT
short          T_shrt [32];
unsigned short T_ushrt[32];
#endif

#ifdef HAS_LONG
long          T_long [32];
unsigned long T_ulong[32];
#endif

#ifdef HAS_LONG_LONG
long long          T_llong [32];
unsigned long long T_ullong[32];
#endif


int main()
{
    int N = sizeof(A) / sizeof(int);

    chess_message("// load int");
    escape_ptr = A; clobber();
    for (int i = 0; i < N; ++i) {
        chess_report(A[i]);
    }

    chess_message("// store int (and load back)");
    clobber();
    for (int i = 0; i < N; ++i) {
        T_int[i] = A[i];
    }
    escape_ptr = T_int; clobber();
    for (int i = 0; i < N; ++i) {
        chess_report(T_int[i]);
    }

    chess_message("// store unsigned (and load back)");
    clobber();
    for (int i = 0; i < N; ++i) {
        T_uint[i] = A[i];
    }
    escape_ptr = T_uint; clobber();
    for (int i = 0; i < N; ++i) {
        chess_report(T_uint[i]);
    }

#ifdef HAS_CHAR
    chess_message("// store char (and load back)");
    clobber();
    for (int i = 0; i < N; ++i) {
        T_char[i] = A[i];
    }
    escape_ptr = T_char; clobber();
    for (int i = 0; i < N; ++i) {
        chess_report(T_char[i]);
    }

    chess_message("// store uchar (and load back)");
    clobber();
    for (int i = 0; i < N; ++i) {
        T_uchar[i] = A[i];
    }
    escape_ptr = T_uchar; clobber();
    for (int i = 0; i < N; ++i) {
        chess_report(T_uchar[i]);
    }
#endif

#ifdef HAS_SHORT
    chess_message("// store short (and load back)");
    clobber();
    for (int i = 0; i < N; ++i) {
        T_shrt[i] = A[i];
    }
    escape_ptr = T_shrt; clobber();
    for (int i = 0; i < N; ++i) {
        chess_report(T_shrt[i]);
    }

    chess_message("// store ushort (and load back)");
    clobber();
    for (int i = 0; i < N; ++i) {
        T_ushrt[i] = A[i];
    }
    escape_ptr = T_ushrt; clobber();
    for (int i = 0; i < N; ++i) {
        chess_report(T_ushrt[i]);
    }
#endif

#ifdef HAS_LONG
    chess_message("// store long (and load back)");
    clobber();
    for (int i = 0; i < N; ++i) {
        T_long[i] = A[i];
    }
    escape_ptr = T_long; clobber();
    for (int i = 0; i < N; ++i) {
        chess_report(T_long[i]);
    }

    chess_message("// store ulong (and load back)");
    clobber();
    for (int i = 0; i < N; ++i) {
        T_ulong[i] = A[i];
    }
    escape_ptr = T_ulong; clobber();
    for (int i = 0; i < N; ++i) {
        chess_report(T_ulong[i]);
    }
#endif

#ifdef HAS_LONG_LONG
    chess_message("// store llong (and load back)");
    clobber();
    for (int i = 0; i < N; ++i) {
        T_llong[i] = A[i];
    }
    escape_ptr = T_llong; clobber();
    for (int i = 0; i < N; ++i) {
        chess_report(T_llong[i]);
    }

    chess_message("// store ullong (and load back)");
    clobber();
    for (int i = 0; i < N; ++i) {
        T_ullong[i] = A[i];
    }
    escape_ptr = T_ullong; clobber();
    for (int i = 0; i < N; ++i) {
        chess_report(T_ullong[i]);
    }
#endif
    return 0;
}

