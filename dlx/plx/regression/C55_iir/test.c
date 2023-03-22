/*
-- Test: infinite impulse response filter.
-- [based on real code]
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#define N_DATA 256
#define MAX_SECTIONS 5
#define ACC_SCALE_FACTOR 14

typedef short Short;
typedef long Long;


void
iir (
    Short *InData,
    Short *OutData,
    Short DataSize,
    Short (*NCoeff)[3],
    Short (*DCoeff)[3],
    Short *IData,
    Short InputScaleFactor,
    Short NumberSections)
{
    Short SIndex,CIndex,DIndex;
    Short StateVar[MAX_SECTIONS][3];
    Long  Accumulator;

    for (SIndex = 0; SIndex < NumberSections; SIndex++) {
        for (CIndex = 0; CIndex <=2; CIndex++) {
            StateVar[SIndex][CIndex] = 0;
        }
        IData[SIndex] = 0;
    }

    for (DIndex = 0; DIndex < DataSize; DIndex++) {

        IData[0] = InData[DIndex]>>InputScaleFactor;

        for (SIndex = 0; SIndex < NumberSections; SIndex++) {

#define L(X) ((long)X)

            Accumulator = L(DCoeff[SIndex][0])*IData[SIndex];
            Accumulator -= L(DCoeff[SIndex][1])*StateVar[SIndex][1];
            Accumulator -= L(DCoeff[SIndex][2])*StateVar[SIndex][2];

            StateVar[SIndex][0] = Accumulator>>ACC_SCALE_FACTOR;

            Accumulator = L(NCoeff[SIndex][0])*StateVar[SIndex][0];
            Accumulator += L(NCoeff[SIndex][1])*StateVar[SIndex][1];
            Accumulator += L(NCoeff[SIndex][2])*StateVar[SIndex][2];

            IData[SIndex+1] = Accumulator>>ACC_SCALE_FACTOR;

            StateVar[SIndex][2] = StateVar[SIndex][1];
            StateVar[SIndex][1] = StateVar[SIndex][0];
        }
        OutData[DIndex] = IData[NumberSections]<<InputScaleFactor;
    }
}

Short g_ncoeff[MAX_SECTIONS][3] = {{1830,3659,1830},
                     {1830,3659,1830},
                     {1830,3659,1830},
                     {1830,3659,1830},
                     {1830,3659,1830}};


Short g_dcoeff[MAX_SECTIONS][3] = {{16384,-19841,12995},
                     {16384,-16580,8165},
                     {16384,-14545,5153},
                     {16384,-13355,3390},
                     {16384,-12804,2575}};

Short g_idata[MAX_SECTIONS+1];

Short g_indata[N_DATA] = {
    0,4081,4203,3596,6407,9738,8929,6193,6425,8041,6018,1437,-375,375,-1437,-6018,
    -8041,-6425,-6193,-8929,-9738,-6407,-3596,-4203,-4081,0,4081,4203,3596,6407,9738,8929,
    6193,6425,8041,6018,1437,-375,375,-1437,-6018,-8041,-6425,-6193,-8929,-9738,-6407,-3596,
    -4203,-4081,0,4081,4203,3596,6407,9738,8929,6193,6425,8041,6018,1437,-375,375,
    -1437,-6018,-8041,-6425,-6193,-8929,-9738,-6407,-3596,-4203,-4081,0,4081,4203,3596,6407,
    9738,8929,6193,6425,8041,6018,1437,-375,375,-1437,-6018,-8041,-6425,-6193,-8929,-9738,
    -6407,-3596,-4203,-4081,0,4081,4203,3596,6407,9738,8929,6193,6425,8041,6018,1437,
    -375,375,-1437,-6018,-8041,-6425,-6193,-8929,-9738,-6407,-3596,-4203,-4081,0,4081,4203,
    3596,6407,9738,8929,6193,6425,8041,6018,1437,-375,375,-1437,-6018,-8041,-6425,-6193,
    -8929,-9738,-6407,-3596,-4203,-4081,0,4081,4203,3596,6407,9738,8929,6193,6425,8041,
    6018,1437,-375,375,-1437,-6018,-8041,-6425,-6193,-8929,-9738,-6407,-3596,-4203,-4081,0,
    4081,4203,3596,6407,9738,8929,6193,6425,8041,6018,1437,-375,375,-1437,-6018,-8041,
    -6425,-6193,-8929,-9738,-6407,-3596,-4203,-4081,0,4081,4203,3596,6407,9738,8929,6193,
    6425,8041,6018,1437,-375,375,-1437,-6018,-8041,-6425,-6193,-8929,-9738,-6407,-3596,-4203,
    -4081,0,4081,4203,3596,6407,9738,8929,6193,6425,8041,6018,1437,-375,375,-1437,
    -6018,-8041,-6425,-6193,-8929,-9738,-6407,-3596,-4203,-4081,0,4081,4203,3596,6407,9738,
};

Short g_outdata[N_DATA];

int main(void)
{
    iir(
        g_indata,       /* InData */
        g_outdata,      /* OutData */
        32, // N_DATA,  /* DataSize */
        g_ncoeff,       /* (*NCoeff)[3] */
        g_dcoeff,       /* (*DCoeff)[3] */
        g_idata,        /* IData */
        1,              /* InputScaleFactor */
        3 // MAX_SECTIONS       /* NumberSections */
        );

    chess_message( "// iir inputs:" );
    for (int i = 0; i < MAX_SECTIONS+1; i++)
        chess_report( g_idata[i] );
    chess_message( "// iir chess_messages:" );
    for (int i = 0; i < N_DATA; i++)
        chess_report( g_outdata[i] );

    return 0;
}
