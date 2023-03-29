/*
-- Test: memcpy() function.
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
#include "string.h"

#if defined(HAS_LONG_LONG)
typedef long long MAX_T;
#elif defined(HAS_LONG)
typedef long MAX_T;
#else
typedef int MAX_T;
#endif


#ifndef MAX_OFFSET
#define MAX_OFFSET (sizeof(MAX_T))
#endif

#ifndef MAX_COPY
#define MAX_COPY (8 * sizeof(MAX_T))
#endif

#ifndef MAX_EXTRA
#define MAX_EXTRA (sizeof(MAX_T))
#endif

#define MAX_LENGTH (MAX_OFFSET + MAX_COPY + MAX_EXTRA)

static union {
    char buf[MAX_LENGTH];
    MAX_T align_int;
} u1, u2;

void inner_loop(int off1, int off2, int len)
{
    chess_message("// gcc_torture_memcpy_2(" << off1 << ", " << off2 << ", " << len << ')');
    UNKNOWN(off1); UNKNOWN(off2); UNKNOWN(len);

    for (size_t i = 0; i < MAX_LENGTH; ++i) {
        u1.buf[i] = 'a';
        u2.buf[i] = 'A';
    }

    char* p = (char*)memcpy(u1.buf + off1, u2.buf + off2, len);
    chess_report(p != u1.buf + off1);

    char* q = u1.buf;
    unsigned sum = 0;
    for (int i = 0; i < off1; i++, q++) {
        sum += (unsigned char)*q;
    }
    chess_report(sum);

    for (int i = 0; i < len; i++, q++) {
        sum += (unsigned char)*q;
    }
    chess_report(sum);

    for (size_t i = 0; i < MAX_EXTRA; i++, q++) {
        sum += (unsigned char)*q;
    }
    chess_report(sum);
}

void gcc_torture_memcpy_2()
{
    chess_message("// gcc_torture_memcpy_2" << MAX_OFFSET << ", " << MAX_COPY);
    for (size_t off1 = 0; off1 < MAX_OFFSET; ++off1) {
        for (size_t off2 = 0; off2 < MAX_OFFSET; ++off2) {
            for (size_t len = 1; len < 2 * MAX_OFFSET; ++len) {
                inner_loop(off1, off2, len);
            }
        }
    }

    int step = MAX_OFFSET / 4;
    if (step < 1) step = 1;
    for (size_t off1 = 0; off1 < MAX_OFFSET; off1 += step) {
        for (size_t off2 = 0; off2 < MAX_OFFSET; off2 += step) {
            for (size_t len = 6 * MAX_OFFSET; len < 8 * MAX_OFFSET; ++len) {
                inner_loop(off1, off2, len);
            }
        }
    }
}

int main()
{
    gcc_torture_memcpy_2();
    return 0;
}
