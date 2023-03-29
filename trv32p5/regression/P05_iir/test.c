/*
-- Benchmark: Infinite Impulse Response filter
-- [based on real code]
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

#define N_DATA 256
#define MAX_SECTIONS 5
#define ACC_SCALE_FACTOR 10

void iir(short *InData,
         short *OutData,
         short DataSize,
         short (*NCoeff)[3],
         short (*DCoeff)[3],
         short *IData,
         short InputScaleFactor,
         short NumberSections)
{
    UNKNOWN(InData); UNKNOWN(OutData); UNKNOWN(DataSize);
    UNKNOWN(NCoeff); UNKNOWN(DCoeff); UNKNOWN(IData);
    UNKNOWN(InputScaleFactor); UNKNOWN(NumberSections);

    short SIndex, CIndex, DIndex;
    short StateVar[MAX_SECTIONS][3];
    long  Accumulator;

    for (SIndex = 0; SIndex < NumberSections; SIndex++) {
        for (CIndex = 0; CIndex <= 2; CIndex++) {
            StateVar[SIndex][CIndex] = 0;
        }
        IData[SIndex] = 0;
    }

    for (DIndex = 0; DIndex < DataSize; DIndex++) {

        IData[0] = InData[DIndex] >> InputScaleFactor;

        for (SIndex = 0; SIndex < NumberSections; SIndex++) {
            // uses cheap int * int = long
            Accumulator  = DCoeff[SIndex][0] * (long)(IData[SIndex]);
            Accumulator -= DCoeff[SIndex][1] * (long)(StateVar[SIndex][1]);
            Accumulator -= DCoeff[SIndex][2] * (long)(StateVar[SIndex][2]);
            StateVar[SIndex][0] = Accumulator >> ACC_SCALE_FACTOR;

            Accumulator  = NCoeff[SIndex][0] * (long)(StateVar[SIndex][0]);
            Accumulator += NCoeff[SIndex][1] * (long)(StateVar[SIndex][1]);
            Accumulator += NCoeff[SIndex][2] * (long)(StateVar[SIndex][2]);
            IData[SIndex + 1] = Accumulator >> ACC_SCALE_FACTOR;

            StateVar[SIndex][2] = StateVar[SIndex][1];
            StateVar[SIndex][1] = StateVar[SIndex][0];
        }
        OutData[DIndex] = IData[NumberSections] << InputScaleFactor;
    }
}

short g_ncoeff[MAX_SECTIONS][3] = {
    { 1830, 3659, 1830 },
    { 1830, 3659, 1830 },
    { 1830, 3659, 1830 },
    { 1830, 3659, 1830 },
    { 1830, 3659, 1830 }
};
short g_dcoeff[MAX_SECTIONS][3] = {
    { 16384, -19841, 12995 },
    { 16384, -16580,  8165 },
    { 16384, -14545,  5153 },
    { 16384, -13355,  3390 },
    { 16384, -12804,  2575 }
};

short g_idata[MAX_SECTIONS + 1];

short g_indata[N_DATA] = {
        0,  4081,  4203,  3596,  6407,  9738,  8929,  6193,  6425,  8041,  6018,  1437,  -375,   375, -1437, -6018,
    -8041, -6425, -6193, -8929, -9738, -6407, -3596, -4203, -4081,     0,  4081,  4203,  3596,  6407,  9738,  8929,
     6193,  6425,  8041,  6018,  1437,  -375,   375, -1437, -6018, -8041, -6425, -6193, -8929, -9738, -6407, -3596,
    -4203, -4081,     0,  4081,  4203,  3596,  6407,  9738,  8929,  6193,  6425,  8041,  6018,  1437,  -375,   375,
    -1437, -6018, -8041, -6425, -6193, -8929, -9738, -6407, -3596, -4203, -4081,     0,  4081,  4203,  3596,  6407,
     9738,  8929,  6193,  6425,  8041,  6018,  1437,  -375,   375, -1437, -6018, -8041, -6425, -6193, -8929, -9738,
    -6407, -3596, -4203, -4081,     0,  4081,  4203,  3596,  6407,  9738,  8929,  6193,  6425,  8041,  6018,  1437,
     -375,   375, -1437, -6018, -8041, -6425, -6193, -8929, -9738, -6407, -3596, -4203, -4081,     0,  4081,  4203,
     3596,  6407,  9738,  8929,  6193,  6425,  8041,  6018,  1437,  -375,   375, -1437, -6018, -8041, -6425, -6193,
    -8929, -9738, -6407, -3596, -4203, -4081,     0,  4081,  4203,  3596,  6407,  9738,  8929,  6193,  6425,  8041,
     6018,  1437, -375,    375, -1437, -6018, -8041, -6425, -6193, -8929, -9738, -6407, -3596, -4203, -4081,     0,
     4081,  4203,  3596,  6407,  9738,  8929,  6193,  6425,  8041,  6018,  1437,  -375,   375, -1437, -6018, -8041,
    -6425, -6193, -8929, -9738, -6407, -3596, -4203, -4081,     0,  4081,  4203,  3596,  6407,  9738,  8929,  6193,
     6425,  8041,  6018,  1437,  -375,   375, -1437, -6018, -8041, -6425, -6193, -8929, -9738, -6407, -3596, -4203,
    -4081,     0,  4081,  4203,  3596,  6407,  9738,  8929,  6193,  6425,  8041,  6018,  1437,  -375,   375, -1437,
    -6018, -8041, -6425, -6193, -8929, -9738, -6407, -3596, -4203, -4081,     0,  4081,  4203,  3596,  6407,  9738,
};

short g_outdata[N_DATA];

int main()
{
    iir(g_indata,      // InData
        g_outdata,     // OutData
        N_DATA,        // DataSize
        g_ncoeff,      // (*NCoeff)[3]
        g_dcoeff,      // (*DCoeff)[3]
        g_idata,       // IData
        1,             // InputScaleFactor
        MAX_SECTIONS); // NumberSections

    chess_message("// iir inputs:");
    for (int i = 0; i < MAX_SECTIONS + 1; ++i) {
        chess_report(g_idata[i]);
    }

    chess_message( "// iir outputs:" );
    for (int i = 0; i < N_DATA; ++i) {
        chess_report(g_outdata[i]);
    }
    return 0;
}
