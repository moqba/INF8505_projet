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


#define FLT_DEBUG_PRINT(FMT,ARGS...) //DEBUG_PRINT(FMT, ##ARGS)

uint5_t count_r_zeros_u28(uint28_t a)
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
    else if (a[18]==1) nz =  18;
    else if (a[19]==1) nz =  19;
    else if (a[20]==1) nz =  20;
    else if (a[21]==1) nz =  21;
    else if (a[22]==1) nz =  22;
    else if (a[23]==1) nz =  23;
    else if (a[24]==1) nz =  24;
    else if (a[25]==1) nz =  25;
    else if (a[26]==1) nz =  26;
    else nz = 27;
    return nz;
}

uint5_t count_l_zeros_u24(uint24_t a)
{
    uint5_t nz;
    if      (a[23]==1) nz =  0;
    else if (a[22]==1) nz =  1;
    else if (a[21]==1) nz =  2;
    else if (a[20]==1) nz =  3;
    else if (a[19]==1) nz =  4;
    else if (a[18]==1) nz =  5;
    else if (a[17]==1) nz =  6;
    else if (a[16]==1) nz =  7;
    else if (a[15]==1) nz =  8;
    else if (a[14]==1) nz =  9;
    else if (a[13]==1) nz =  10;
    else if (a[12]==1) nz =  11;
    else if (a[11]==1) nz =  12;
    else if (a[10]==1) nz =  13;
    else if (a[ 9]==1) nz =  14;
    else if (a[ 8]==1) nz =  15;
    else if (a[ 7]==1) nz =  16;
    else if (a[ 6]==1) nz =  17;
    else if (a[ 5]==1) nz =  18;
    else if (a[ 4]==1) nz =  19;
    else if (a[ 3]==1) nz =  20;
    else if (a[ 2]==1) nz =  21;
    else if (a[ 1]==1) nz =  22;
    else if (a[ 0]==1) nz =  23;
    else nz = 24;
    return nz;
}

#define QNAN        ((uint31_t)"1111111110000000000000000000000")
#define ZERO_VECTOR ((uint31_t)0)
#define INF         ((uint31_t)"1111111100000000000000000000000")

// roundf, based on softfloat "float32_round_to_int"
w32 fround(w32 a,w32 imode)
{
    uint2_t mode = imode;
    //FLT_DEBUG_PRINT("frnd: opa=0x%x {0x%x 0x%x 0x%x}", a, a[31], a[30:23], a[22:0]);

    // unpack
    uint23_t aFrac = a[22:0];
    uint8_t aExp = a[30:23];
    uint1_t aSign = a[31];

    if ( 0x96 <= aExp ) {
        if ( ( aExp == 0xFF ) && (aFrac != 0) ) {
            return a   |   0x400000;
        }
        return a;
    }

    if ( aExp <= 0x7E ) {
        if ( a[30:0] == 0 ) return a; // +/- 0
        if ( ((aExp==0x7E) && (mode==0)) || (aSign&&(mode==1)) || ((~aSign)&&(mode==2)) ) {
            return aSign :: "0111_1111" :: (uint23_t) 0;
        }
        else {
            return aSign :: (uint8_t) 0 :: (uint23_t) 0;
        }
    }

    uint32_t lastBitMask2 = 0xffffffff;
    int9_t shf = aExp-119;
    if (shf>32) shf=0;
    lastBitMask2 >>= shf;
    uint32_t lastBitMask3 = lastBitMask2 ^ ("0"::lastBitMask2[31:1]);
    uint32_t roundBitsMask = "0"::lastBitMask2[31:1];
    uint32_t z = a;
    uint32_t rnd_add=0;
     if (((lastBitMask2[23:1]&aFrac)==0) || (((lastBitMask2[24:2]&aFrac)!=0) && mode==0)){
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





