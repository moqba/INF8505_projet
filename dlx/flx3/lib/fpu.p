/*
-- File : fpu.p
--
-- Contents : Definition of the floating point primitives.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#define FLT_DEBUG_PRINT(FMT,ARGS...) DEBUG_PRINT(FMT, ##ARGS)
#define CMPLXIO_DEBUG_PRINT(FMT,ARGS...) //DEBUG_PRINT(FMT, ##ARGS)
#define NEW_FLT_DEBUG_PRINT(FMT,ARGS...) //DEBUG_PRINT(FMT, ##ARGS)
#define COARSE_FLT_DEBUG_PRINT(FMT,ARGS...) //DEBUG_PRINT(FMT, ##ARGS)

uint5_t count_r_zeros_u19(uint19_t a)
{
    uint5_t nz;
    if      (a[0]==1) nz =  0;
    else if (a[1]==1) nz =  1;
    else if (a[2]==1) nz =  2;
    else if (a[3]==1) nz =  3;
    else if (a[4]==1) nz =  4;
    else if (a[5]==1) nz =  5;
    else if (a[6]==1) nz =  6;
    else if (a[7]==1) nz =  7;
    else if (a[8]==1) nz =  8;
    else if (a[9]==1) nz =  9;
    else if (a[10]==1) nz =  10;
    else if (a[11]==1) nz =  11;
    else if (a[12]==1) nz =  12;
    else if (a[13]==1) nz =  13;
    else if (a[14]==1) nz =  14;
    else if (a[15]==1) nz =  15;
    else if (a[16]==1) nz =  16;
    else if (a[17]==1) nz =  17;
    else nz = 18;
    return nz;
}

uint5_t count_l_zeros_u16(uint16_t a)
{
    uint5_t nz;
    if      (a[15]==1) nz =  0;
    else if (a[14]==1) nz =  1;
    else if (a[13]==1) nz =  2;
    else if (a[12]==1) nz =  3;
    else if (a[11]==1) nz =  4;
    else if (a[10]==1) nz =  5;
    else if (a[ 9]==1) nz =  6;
    else if (a[ 8]==1) nz =  7;
    else if (a[ 7]==1) nz =  8;
    else if (a[ 6]==1) nz =  9;
    else if (a[ 5]==1) nz =  10;
    else if (a[ 4]==1) nz =  11;
    else if (a[ 3]==1) nz =  12;
    else if (a[ 2]==1) nz =  13;
    else if (a[ 1]==1) nz =  14;
    else if (a[ 0]==1) nz =  15;
    else nz = 15;
    return nz;
}

// The purpose is to make the PDG div/sqrt has the same behavior with Native verilated C++ (from DesignWare)
// old: #define QNAN        ((uint23_t)"11111111100000000000000")

#define QNAN        ((uint23_t)"11111111000000000000001")
#define ZERO_VECTOR ((uint23_t)0)
#define INF         ((uint23_t)"11111111000000000000000")

// roundf, based on softfloat "float32_round_to_int"
// Adapt it from float to float24_t
w32 frnd(w32 a)
{
    //NEW_FLT_DEBUG_PRINT("frnd: opa=0x%x {0x%x 0x%x 0x%x}",
    //            a, a[31], a[30:23], a[22:0]);

    // unpack
    uint15_t aFrac = a[14:0];
    uint8_t aExp = a[22:15];
    uint1_t aSign = a[23];

    uint32_t z = 0;

    if ( 0x8E <= aExp ) { // 0x8E = 127+15
        if ( ( aExp == 0xFF ) && (aFrac != 0) ) {
            return a   |   0x4000;
        }
        return a;
    }
    if ( aExp <= 0x7E ) {
        if ( a[22:0] == 0 ) return a; // +/- 00:
        if ( ( aExp == 0x7E ) && (aFrac != 0) ) {
            return "0000_0000"::aSign :: "0111_1111" :: (uint15_t) 0;
        }
        else {
            return "0000_0000"::aSign :: (uint8_t) 0 :: (uint15_t) 0;
        }
    }
    uint32_t lastBitMask = 1;
    lastBitMask <<= 0x8E - aExp;
    uint32_t roundBitsMask = lastBitMask - 1;
    z = a;
    z += lastBitMask[31:1]; //lastBitMask>>1;
    if ( ( z & roundBitsMask ) == 0 ) z &= ~ lastBitMask;
    z &= ~ roundBitsMask;
    return z;
}

// roundf, based on softfloat "float32_round_to_int"
// Rounding mode:
// mode = 0 : round, nearest away from 0
// mode = 1 : floor, left
// mode = 2 : ceil , right
// mode = 3 : trunc

w32 fround(w32 a,w32 imode)
{
    uint2_t mode = imode;
    //NEW_FLT_DEBUG_PRINT("frnd: opa=0x%x {0x%x 0x%x 0x%x}",
    //            a, a[23], a[22:15], a[14:0]);

    // unpack
    uint15_t aFrac = a[14:0];
    uint8_t aExp = a[22:15];
    uint1_t aSign = a[23];

    if ( 0x8E <= aExp ) { // 0x8E = 127+15
        if ( ( aExp == 0xFF ) && (aFrac != 0) ) {
            return a   |   0x4000;
        }
        return a;
    }

    if ( aExp <= 0x7E ) {
        if ( a[22:0] == 0 ) return a; // +/- 0
        if ( ((aExp==0x7E) && (mode==0)) || (aSign&&(mode==1)) || ((~aSign)&&(mode==2)) ) {
            return "0000_0000"::aSign :: "0111_1111" :: (uint15_t) 0;
        }
        else {
            return "0000_0000"::aSign :: (uint8_t) 0 :: (uint15_t) 0;
        }
    }

    uint32_t lastBitMask2 = 0x00ffffff;
    int9_t shf = aExp-119;                // shf must be positive
    if (shf>24) shf=0;
    lastBitMask2 >>= shf;
    uint32_t lastBitMask3 = lastBitMask2 ^ ("0"::lastBitMask2[31:1]);
    uint32_t roundBitsMask = "0"::lastBitMask2[31:1];
    uint32_t z = a;
    uint32_t rnd_add=0;
    if (((lastBitMask2[15:1]&aFrac)==0) || (((lastBitMask2[16:2]&aFrac)!=0) && mode==0)){
      rnd_add = lastBitMask3[31:1];
    }
    else if ((mode==0) || ((mode==1) && aSign) || ((mode==2) && ~aSign)) {
      rnd_add = lastBitMask3;
    }

    z+=rnd_add;
    if ( ( z & roundBitsMask ) == 0 ) z &= ~ lastBitMask3;
    z &= ~ roundBitsMask;
    return z;
}





