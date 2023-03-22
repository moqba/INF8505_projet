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

/*

  + The faddsub, fmul, fdiv, fsqrt are based on OpenCores fpu100
    http://opencores.org/project,fpu100
    contributed by Jidan Al-Eryani (with Technical University of Vienna when
    developing the VHDL code),  with additional bugs fixed by Synopsys.
    License: "You can use this code academically, commercially, etc. for free;
    just acknowledge the author."

  + The sfle, sfgt, sfle, i2f, f2i and frond  are transcribed to PDG from
    SoftFloat C code, contributed by John R. Hauser.
    License: see ./lib/softfloat/README.txt.

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

uint5_t count_l_zeros_u27(uint27_t a)
{
    uint5_t nz;
    if      (a[26]==1) nz =  0;
    else if (a[25]==1) nz =  1;
    else if (a[24]==1) nz =  2;
    else if (a[23]==1) nz =  3;
    else if (a[22]==1) nz =  4;
    else if (a[21]==1) nz =  5;
    else if (a[20]==1) nz =  6;
    else if (a[19]==1) nz =  7;
    else if (a[18]==1) nz =  8;
    else if (a[17]==1) nz =  9;
    else if (a[16]==1) nz =  10;
    else if (a[15]==1) nz =  11;
    else if (a[14]==1) nz =  12;
    else if (a[13]==1) nz =  13;
    else if (a[12]==1) nz =  14;
    else if (a[11]==1) nz =  15;
    else if (a[10]==1) nz =  16;
    else if (a[ 9]==1) nz =  17;
    else if (a[ 8]==1) nz =  18;
    else if (a[ 7]==1) nz =  19;
    else if (a[ 6]==1) nz =  20;
    else if (a[ 5]==1) nz =  21;
    else if (a[ 4]==1) nz =  22;
    else if (a[ 3]==1) nz =  23;
    else if (a[ 2]==1) nz =  24;
    else if (a[ 1]==1) nz =  25;
    else if (a[ 0]==1) nz =  26;
    else nz = 27;
    return nz;
}

uint5_t count_l_zeros_u31(uint31_t a)
{
    uint5_t nz;
    if      (a[30]==1) nz =  0;
    else if (a[29]==1) nz =  1;
    else if (a[28]==1) nz =  2;
    else if (a[27]==1) nz =  3;
    else if (a[26]==1) nz =  4;
    else if (a[25]==1) nz =  5;
    else if (a[24]==1) nz =  6;
    else if (a[23]==1) nz =  7;
    else if (a[22]==1) nz =  8;
    else if (a[21]==1) nz =  9;
    else if (a[20]==1) nz =  10;
    else if (a[19]==1) nz =  11;
    else if (a[18]==1) nz =  12;
    else if (a[17]==1) nz =  13;
    else if (a[16]==1) nz =  14;
    else if (a[15]==1) nz =  15;
    else if (a[14]==1) nz =  16;
    else if (a[13]==1) nz =  17;
    else if (a[12]==1) nz =  18;
    else if (a[11]==1) nz =  19;
    else if (a[10]==1) nz =  20;
    else if (a[ 9]==1) nz =  21;
    else if (a[ 8]==1) nz =  22;
    else if (a[ 7]==1) nz =  23;
    else if (a[ 6]==1) nz =  24;
    else if (a[ 5]==1) nz =  25;
    else if (a[ 4]==1) nz =  26;
    else if (a[ 3]==1) nz =  27;
    else if (a[ 2]==1) nz =  28;
    else if (a[ 1]==1) nz =  29;
    else if (a[ 0]==1) nz =  30;
    else nz = 31;
    return nz;
}

w32 faddsub(uint1 op/*0=add,1=sub*/, w32 opa, w32 opb)
{
    uint28_t fracta_28;
    uint28_t fractb_28;
    uint8_t  exp;

    FLT_DEBUG_PRINT("faddsub: op=%d opa=0x%x {0x%x 0x%x 0x%x} opb=0x%x {0x%x 0x%x 0x%x}",
                op, opa, opa[31], opa[30:23], opa[22:0], opb, opb[31], opb[30:23], opb[22:0]);


    // read from input
    uint8_t  s_expa   = opa[30:23];
    uint8_t  s_expb   = opb[30:23];
    uint23_t s_fracta = opa[22:0];
    uint23_t s_fractb = opb[22:0];

    uint1_t s_expa_lt_expb = (s_expa >  s_expb);

    FLT_DEBUG_PRINT("exp_eq=%d expa_lt_expb=%d", s_expa == s_expb, s_expa_lt_expb);

    // '1' if fraction is not zero
    uint1_t s_fracta_1 = (s_fracta != 0);
    uint1_t s_fractb_1 = (s_fractb != 0);

    // opa or opb is denormalized
    uint1_t s_opa_dn = (s_expa==0);
    uint1_t s_opb_dn = (s_expb==0);
    uint1_t s_op_dn = s_opa_dn | s_opb_dn;

    FLT_DEBUG_PRINT("dn=%d dna=%d dnb=%d", s_op_dn, s_opa_dn, s_opb_dn);

    // output the larger exponent
    uint8_t s_exp_o = s_expa_lt_expb?s_expa:s_expb;

    // convert to internal format: carry(1)::hidden(1):fraction(23)::guard(1)::round(1)::sticky(1)
    uint28_t s_fracta_28 = "0"::(~s_opa_dn)::s_fracta::"000";
    uint28_t s_fractb_28 = "0"::(~s_opb_dn)::s_fractb::"000";

    // calculate how many postions the fraction will be shifted
    uint8_t s_exp_diff = (s_expa_lt_expb ? (s_expa-s_expb) : (s_expb-s_expa)) - (uint8_t)(s_opa_dn ^ s_opb_dn);
    FLT_DEBUG_PRINT("s_fracta_28=0x%x s_fractb_28=0x%x exp_diff=%d", s_fracta_28, s_fractb_28, s_exp_diff);

    uint28_t s_fract_sm_28 = s_expa_lt_expb ? s_fractb_28 : s_fracta_28;

    // shift-right the fraction if necessary
    uint28_t s_fract_shr_28 = s_fract_sm_28 >> s_exp_diff;

    // count the zeros from right to check if result is inexact
    uint6_t s_rzeros = count_r_zeros_u28(s_fract_sm_28);
    uint1_t s_sticky = (s_exp_diff > s_rzeros) & (s_fract_sm_28!=0);

    FLT_DEBUG_PRINT("s_rzeros=%d s_sticky=%d", s_rzeros, s_sticky);

    uint28_t s_fracta_28_o = s_expa_lt_expb ? s_fracta_28 : (s_fract_shr_28[27:1]::(s_sticky|s_fract_shr_28[0]));
    uint28_t s_fractb_28_o = s_expa_lt_expb ? (s_fract_shr_28[27:1]::(s_sticky|s_fract_shr_28[0])) : s_fractb_28;

    // write to output
    fracta_28 = s_fracta_28_o;
    fractb_28 = s_fractb_28_o;
    exp = s_exp_o;

    FLT_DEBUG_PRINT("faddsub: fracta_28=0x%x fractb_28=0x%x exp=0x%x", fracta_28, fractb_28, exp);

    uint1_t fracta_lt_fractb = (fracta_28 > fractb_28);
    uint1_t s_signa_i =  opa[31];
    uint1_t s_signb_i =  opb[31];

    // check if its a subtraction or an addition operation
    uint1_t s_addop = ((s_signa_i ^ s_signb_i)& (~op)) | (~(s_signa_i ^ s_signb_i) & (op));

    FLT_DEBUG_PRINT("s_addop=%d fracta_lt_fractb=%d", s_addop, fracta_lt_fractb);

    // add/substract
    uint28_t s_fract;
    if (s_addop==0) {
        s_fract = fracta_28 + fractb_28;
    }
    else {
        if (fracta_lt_fractb) {
            s_fract = fracta_28 - fractb_28;
        }
        else {
            s_fract = fractb_28 - fracta_28;
        }
    }

    // sign of result
    uint1_t s_sign = ((s_fract==0) & (s_signa_i&s_signb_i==0))?0:(((~s_signa_i) & ((~fracta_lt_fractb) & (op ^ s_signb_i))) |
                     ((s_signa_i) & (fracta_lt_fractb | (op ^ s_signb_i))));

    FLT_DEBUG_PRINT("faddsub: after compute, sign=%d s_fract=0x%x addop=%d", s_sign, s_fract, s_addop);

    uint32_t output;
    uint1_t  ine;

    {
        uint1 s_op = op;
        uint28_t s_fract_28_i = s_fract;
        uint8_t s_exp_i  = exp;
        uint1_t s_sign_i = s_sign;
        uint32_t s_opa_i = opa;
        uint32_t s_opb_i = opb;
        // figure out the output exponent and howmuch the fraction has to be shiftd right/left

        uint1_t s_carry = s_fract_28_i[27];

        uint6_t s_zeros = s_fract_28_i[27]?0:count_l_zeros_u27(s_fract_28_i[26:0]);

        uint10_t s_exp10 = (uint10_t)s_exp_i + (uint10_t)s_carry - (uint10_t)s_zeros; // negative flag & large flag & exp

        FLT_DEBUG_PRINT("carry=%d l_zeros=%d exp10=0x%x", s_carry, s_zeros, s_exp10);

        uint6_t s_shr1,s_shl1;
        uint9_t s_expo9_1;
        if (s_exp10[9] | s_exp10==0) {
            s_shr1 = 0;
            if (s_exp_i!=0) {
                s_shl1 = s_exp_i[5:0] - 1;
            }
            else {
                s_shl1 = 0;
            }
            s_expo9_1 = 1;
        }
        else if (s_exp10[8]) {
            s_shr1 = 0;
            s_shl1 = 0;
            s_expo9_1 = 0xff;
        }
        else {
            s_shr1 = (uint6_t)s_carry;
            s_shl1 = s_zeros;
            s_expo9_1 = s_exp10[8:0];
        }

        FLT_DEBUG_PRINT("shr1=%d shl1=%d s_expo9_1=0x%x", s_shr1, s_shl1, s_expo9_1);

        // Shifting the fraction and rounding
        uint28_t s_fracto28_1;
        if (s_shr1 != 0) {
            s_fracto28_1 = s_fract_28_i>>s_shr1;
        }
        else {
            s_fracto28_1 = s_fract_28_i<<s_shl1;
        }

        uint9_t s_expo9_2 = (s_fracto28_1[27:26]==0)?s_expo9_1-1:s_expo9_1;

        FLT_DEBUG_PRINT("fracto28_1=0x%x expo9_2=0x%x", s_fracto28_1, s_expo9_2);

        // round
        uint1_t s_sticky = s_fracto28_1[0] | (s_fract_28_i[0] & s_fract_28_i[27]); // check last bit, before and after right-shift

        // EB: Only round to even is tested
        uint1_t s_roundup = (s_fracto28_1[2] & ((s_fracto28_1[1] | s_sticky) | s_fracto28_1[3]));

        uint28_t s_fracto28_rnd = s_fracto28_1 + (s_roundup::"000");

        FLT_DEBUG_PRINT("roundup=%d sticky=%d fracto28_rnd=0x%x", s_roundup, s_sticky, s_fracto28_rnd);

        // right-shift after rounding (if necessary)
        uint1_t s_shr2 = s_fracto28_rnd[27];

        uint9_t s_expo9_3 = s_expo9_2 + (s_shr2 & (s_expo9_2!=0xff));
        uint28_t s_fracto28_2 = s_shr2?("0"::s_fracto28_rnd[27:1]):s_fracto28_rnd;

        FLT_DEBUG_PRINT("2nd round? s_shr2=%d fracto28_2=0x%x s_expo9_3=0x%x", s_shr2, s_fracto28_2, s_expo9_3);

        uint1_t s_infa = (s_opa_i[30:23]==0xff);
        uint1_t s_infb = (s_opb_i[30:23]==0xff);

        uint1_t s_nan_a  = (s_infa & (s_opa_i[22:0]!=0));
        uint1_t s_nan_b  = (s_infb & (s_opb_i[22:0]!=0));
        uint1_t s_nan_in = s_nan_a | s_nan_b;
        uint1_t s_nan_op = (s_infa & s_infb) & (s_opa_i[31] ^ (s_op ^ s_opb_i[31]) ); // inf-inf=Nan

        uint1_t s_nan_sign =  (s_nan_a & s_nan_b)? s_sign_i : (s_nan_a?s_opa_i[31]:s_opb_i[31]);

        // check if result is inexact;
        uint1_t s_lost = (s_shr1[0] & s_fract_28_i[0]) | (s_shr2 & s_fracto28_rnd[0]) | (s_fracto28_2[2:0]!=0);
        uint1_t s_overflow = (s_expo9_3==0xff & ~(s_infa | s_infb));
        uint1_t s_ine_o = (s_lost | s_overflow) & ~(s_infa | s_infb);

        uint1_t s_zero_fract = (s_zeros==27) & ~s_fract_28_i[27]; // '1' if fraction result is zero

        FLT_DEBUG_PRINT("infa=%d infb=%d overflow=%d", s_infa, s_infb, s_overflow);

        uint32_t s_output_o;
        if (s_nan_in | s_nan_op) {
            FLT_DEBUG_PRINT("QNAN");
            s_output_o = /*s_nan_sign*/"1"::QNAN;
        }
        else if (s_infa | s_infb | s_overflow) {
            FLT_DEBUG_PRINT("INF");
            s_output_o = s_sign_i::INF;
        }
        else if (s_zero_fract) {
            FLT_DEBUG_PRINT("ZERO_VECTOR");
            // only -0.0 result in case of "-0.0 + -0.0" or "-0.0 - 0.0"
            uint1_t s_sign0 = s_opa_i[31] & (s_opb_i[31]^s_op) & s_opa_dn & s_opb_dn & ~s_fracta_1 & ~s_fractb_1;
            s_output_o = /*s_sign_i*//*"0"*/s_sign0::ZERO_VECTOR;
        }
        else {
            s_output_o = s_sign_i::s_expo9_3[7:0]::s_fracto28_2[25:3];
        }

        // write to output
        output = s_output_o;
        ine = s_ine_o;
    }
    return output;
}

uint6_t count_l_zeros_u46(uint46_t a)
{
    uint6_t nz;
    if      (a[45]==1) nz =  0;
    else if (a[44]==1) nz =  1;
    else if (a[43]==1) nz =  2;
    else if (a[42]==1) nz =  3;
    else if (a[41]==1) nz =  4;
    else if (a[40]==1) nz =  5;
    else if (a[39]==1) nz =  6;
    else if (a[38]==1) nz =  7;
    else if (a[37]==1) nz =  8;
    else if (a[36]==1) nz =  9;
    else if (a[35]==1) nz =  10;
    else if (a[34]==1) nz =  11;
    else if (a[33]==1) nz =  12;
    else if (a[32]==1) nz =  13;
    else if (a[31]==1) nz =  14;
    else if (a[30]==1) nz =  15;
    else if (a[29]==1) nz =  16;
    else if (a[28]==1) nz =  17;
    else if (a[27]==1) nz =  18;
    else if (a[26]==1) nz =  19;
    else if (a[25]==1) nz =  20;
    else if (a[24]==1) nz =  21;
    else if (a[23]==1) nz =  22;
    else if (a[22]==1) nz =  23;
    else if (a[21]==1) nz =  24;
    else if (a[20]==1) nz =  25;
    else if (a[19]==1) nz =  26;
    else if (a[18]==1) nz =  27;
    else if (a[17]==1) nz =  28;
    else if (a[16]==1) nz =  29;
    else if (a[15]==1) nz =  30;
    else if (a[14]==1) nz =  31;
    else if (a[13]==1) nz =  32;
    else if (a[12]==1) nz =  33;
    else if (a[11]==1) nz =  34;
    else if (a[10]==1) nz =  35;
    else if (a[ 9]==1) nz =  36;
    else if (a[ 8]==1) nz =  37;
    else if (a[ 7]==1) nz =  38;
    else if (a[ 6]==1) nz =  39;
    else if (a[ 5]==1) nz =  40;
    else if (a[ 4]==1) nz =  41;
    else if (a[ 3]==1) nz =  42;
    else if (a[ 2]==1) nz =  43;
    else if (a[ 1]==1) nz =  44;
    else if (a[ 0]==1) nz =  45;
    else nz = 46;
    return nz;
}

uint6_t count_r_zeros_u48(uint48_t a)
{
    uint6_t nz;
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
    else if (a[27]==1) nz =  27;
    else if (a[28]==1) nz =  28;
    else if (a[29]==1) nz =  29;
    else if (a[30]==1) nz =  30;
    else if (a[31]==1) nz =  31;
    else if (a[32]==1) nz =  32;
    else if (a[33]==1) nz =  33;
    else if (a[34]==1) nz =  34;
    else if (a[35]==1) nz =  35;
    else if (a[36]==1) nz =  36;
    else if (a[37]==1) nz =  37;
    else if (a[38]==1) nz =  38;
    else if (a[39]==1) nz =  39;
    else if (a[40]==1) nz =  40;
    else if (a[41]==1) nz =  41;
    else if (a[42]==1) nz =  42;
    else if (a[43]==1) nz =  43;
    else if (a[44]==1) nz =  44;
    else if (a[45]==1) nz =  45;
    else if (a[46]==1) nz =  46;
    else if (a[47]==1) nz =  47;
    else nz = 48;
    return nz;
}

w32 fmul   (w32 opa, w32 opb)
{
    FLT_DEBUG_PRINT("fmul: opa=0x%x {0x%x 0x%x 0x%x} opb=0x%x {0x%x 0x%x 0x%x}",
                opa, opa[31], opa[30:23], opa[22:0], opb, opb[31], opb[30:23], opb[22:0]);

    // pre normalization

    // read from input
    uint1_t s_signa_i = opa[31];
    uint1_t s_signb_i = opb[31];
    uint8_t  s_expa   = opa[30:23];
    uint8_t  s_expb   = opb[30:23];
    uint23_t s_fracta = opa[22:0];
    uint23_t s_fractb = opb[22:0];

    // opa, opb is denormalized
    uint1_t s_opa_dn = (s_expa==0);
    uint1_t s_opb_dn = (s_expb==0);

    uint24_t fracta_24 = (~s_opa_dn)::s_fracta;
    uint24_t fractb_24 = (~s_opb_dn)::s_fractb;

    uint10_t s_expa10 = (uint10_t)s_expa + s_opa_dn;
    uint10_t s_expb10 = (uint10_t)s_expb + s_opb_dn;

    uint10_t s_exp_10 = s_expa10 + s_expb10 - 0x7f;

    FLT_DEBUG_PRINT("fmul: fracta_24=%x fractb_24=0x%x s_exp_10=%x", fracta_24, fractb_24, s_exp_10);

    // do the actual mult
    uint1_t s_mul_sign = s_signa_i^s_signb_i;
    uint48_t s_mul_fract_48 = fracta_24*fractb_24;

    FLT_DEBUG_PRINT("s_mul_sign=%d s_mul_fract_48=0x%x", s_mul_sign, s_mul_fract_48);

    // post normalization
    uint1_t s_carry = s_mul_fract_48[47];

    uint6_t s_zeros          = (s_mul_fract_48[47])?0:count_l_zeros_u46(s_mul_fract_48[46:1]);
    uint6_t s_r_zeros = count_r_zeros_u48(s_mul_fract_48);


    uint10_t s_exp_10a = s_exp_10  + s_carry;
    uint10_t s_exp_10b = s_exp_10a - s_zeros;

    FLT_DEBUG_PRINT("carry=%d zeros=%d r_zeros=%d exp_10=0x%x exp_10a=0x%x exp_10b=0x%x", s_carry, s_zeros, s_r_zeros, s_exp_10, s_exp_10a, s_exp_10b);

    uint10_t v_shr1, v_shl1;
    uint9_t  s_expo1;
    if (s_exp_10a[9] | (s_exp_10a[9:1]/*EB-FIX*/==0)) {
        // EB: the new exponent is 1,0 or negative -> result is denormalized -> rightshift
        FLT_DEBUG_PRINT("case1: if (s_exp_10a[9] | (s_exp_10a==0))");
        v_shr1  = (uint10_t)1 - s_exp_10a + s_carry;
        v_shl1  = 0;
        s_expo1 = 1;
    }
//    else if (s_exp_10a==1) {
//    }
    else if (s_exp_10b[9] | (s_exp_10b==0)) {
        // EB: the new exponent will be 0 or negative because at least on fraction was also denormalized
        FLT_DEBUG_PRINT("case2: if (s_exp_10b[9] | (s_exp_10b=0))");
        v_shr1  = 0;
        v_shl1  = s_exp_10a-1;// EB-FIX: this was originally: (uint10_t)s_zeros - s_exp_10a;
        s_expo1 = 1;
    }
    else if (s_exp_10b[8]) {
        // EB: the new exponent is larger than 255 -> infinity
        FLT_DEBUG_PRINT("case3: if (s_exp_10b[8])");
        v_shr1 = 0;
        v_shl1 = 0;
        s_expo1 = 0xff;
    }
    else {
        // EB: normal case; shift one to the right if carry, otherwise normalize by shifting to the left
        v_shr1  = s_carry;
        v_shl1  = s_zeros;
        s_expo1 = s_exp_10b[8:0];
        FLT_DEBUG_PRINT("case4: else ; s_expo1=0x%x s_exp_10b=0x%x", s_expo1, s_exp_10b);
    }

    uint6_t s_shr2;
    if (v_shr1[6]) { // "110000" = 48; maximal shift-right postions
        s_shr2 = 0x3f;
    }
    else  {
        s_shr2 = v_shr1[5:0];
    }
    uint6_t s_shl2 = v_shl1[5:0];

    FLT_DEBUG_PRINT("fmul shift factor v_shr1=%d v_shl1=%d s_expo1=%d s_shr2=%d s_shl2=%d", v_shr1, v_shl1, s_expo1, s_shr2, s_shl2);

    // Shifting the fraction and rounding


    // shift the fraction
    uint48_t s_frac2a;
    if (s_shr2 != 0) {
        s_frac2a = s_mul_fract_48>>s_shr2;
    }
    else {
        s_frac2a = s_mul_fract_48<<s_shl2;
    }

    uint9_t s_expo2b = s_expo1 - (1-s_frac2a[46]);

    FLT_DEBUG_PRINT("fmul frac2a=0x%x expo2b=0x%x", s_frac2a, s_expo2b);

    // signals if precision was last during the right-shift above
    uint1_t s_lostA = (s_shr2 > s_r_zeros);


    // Rounding

    //                                                                   23
    //                                                                        |
    //                         xx00000000000000000000000grsxxxxxxxxxxxxxxxxxxxx
    // guard bit: s_frac2a(23) (LSB of output)
    //  round bit: s_frac2a(22)
    uint1_t s_guard = s_frac2a[22];
    uint1_t s_round = s_frac2a[21];
    uint1_t s_stickyA = (s_frac2a[20:0]!=0) | s_lostA;

    // EB: Only round to even is tested
    uint1_t s_roundupA;
    s_roundupA = s_guard & ((s_round | s_stickyA) | s_frac2a[23]);  /* round to nearset even */

    uint25_t s_frac_rndA = (uint25_t)(s_frac2a[47:23]) + s_roundupA;

    uint1_t s_shr3A = s_frac_rndA[24];

    FLT_DEBUG_PRINT("fmul lostA=%d guard=%d round=%d stickyA=%d roundupA=%d shr3A=%d", s_lostA, s_guard, s_round, s_stickyA, s_roundupA, s_shr3A);

    // second rounding (rare case)
    uint1_t s_lost = ((s_shr2+s_shr3A) > s_r_zeros);
    uint1_t s_sticky = (s_frac2a[20:0]!=0) | s_lost;
    uint1_t s_roundup;
    s_roundup = s_guard & ((s_round | s_sticky) | s_frac2a[23]);  /* round to nearset even */

    uint25_t s_frac_rnd = (uint25_t)(s_frac2a[47:23]) + s_roundup;
    uint1_t s_shr3 = s_frac_rnd[24];

    FLT_DEBUG_PRINT("fmul lost=%d sticky=%d roundup=%d shr3=%d frac_rnd=0x%x", s_lost, s_sticky, s_roundup, s_shr3, s_frac_rnd);

    // EB: the number could get normalized because of the s_roundup. The exponent should be made 1 in this case
    uint1_t just_normalized = (~s_frac2a[46] & s_frac_rnd[23]) & (s_expo2b==0);

    uint1_t s_shift1 = s_shr3 & (s_expo2b!=0xff);
    uint9_t s_expo3 = s_expo2b + (s_shift1|just_normalized);// EB: ??  (s_shift1|just_normalized)
    uint25_t s_frac3 = s_shift1?("0"::s_frac_rnd[24:1]):s_frac_rnd;

    FLT_DEBUG_PRINT("fmul shift1=%d expo3=0x%x frac3=0x%x", s_shift1, s_expo3, s_frac3);

    // Output

    uint1_t s_op_0 = (opa[30:0]==0) | (opb[30:0]==0);

    uint1_t s_infa = (s_expa==0xff);
    uint1_t s_infb = (s_expb==0xff);

    uint1_t s_nan_a  = (s_infa & (opa[22:0]!=0));
    uint1_t s_nan_b  = (s_infb & (opb[22:0]!=0));
    uint1_t s_nan_in = s_nan_a | s_nan_b;
    uint1_t s_nan_op = (s_infa | s_infb) & s_op_0; // 0 * inf = nan

    uint1_t s_overflow = (s_expo3==0xff) & ((s_infa | s_infb)==0);

    uint1_t s_ine_o = (~s_op_0) & (s_lost | (s_frac2a[22:0]!=0) | s_overflow);

    uint32_t s_output_o;
    if (s_nan_in | s_nan_op) {
        FLT_DEBUG_PRINT("fmul QNAN");
        s_output_o = /*s_mul_sign*/"1"::QNAN;
    }
    else if (s_infa | s_infb | s_overflow) {
        FLT_DEBUG_PRINT("fmul INF");
        s_output_o = s_mul_sign::INF;
    }
    else if (s_r_zeros==48) {
        FLT_DEBUG_PRINT("fmul ZERO_VECTOR s_r_zeros=%d", s_r_zeros);
        s_output_o = s_mul_sign/*"0"*/::ZERO_VECTOR;
    }
    else {
        s_output_o = s_mul_sign::s_expo3[7:0]::s_frac3[22:0];
    }

    return s_output_o;
}


w32 sfle(w32 a, w32 b)
{
    uint1_t  a_sign  = a[31];
    uint1_t  b_sign  = b[31];
    uint8_t  a_exp   = a[30:23];
    uint8_t  b_exp   = b[30:23];
    uint23_t a_fract = a[22:0];
    uint23_t b_fract = b[22:0];

    if (a_exp == 0xFF && a_fract != 0 || b_exp == 0xFF && b_fract != 0)
        return 0;
    if (a_sign != b_sign)
        return a_sign || ( ( a | b )<<1  == 0 );
    return ( a == b ) || ( a_sign ^ ( a < b ) );
}

w32 sflt(w32 a, w32 b)
{
    uint1_t  a_sign  = a[31];
    uint1_t  b_sign  = b[31];
    uint8_t  a_exp   = a[30:23];
    uint8_t  b_exp   = b[30:23];
    uint23_t a_fract = a[22:0];
    uint23_t b_fract = b[22:0];

    if (a_exp == 0xFF && a_fract != 0 || b_exp == 0xFF && b_fract != 0)
        return 0;
    if (a_sign != b_sign)
        return a_sign && ( ( a | b )<<1  != 0 );
    return ( a != b ) && ( a_sign ^ ( a < b ) );
}

w32 sfeq(w32 a, w32 b)
{
    uint1_t  a_sign  = a[31];
    uint1_t  b_sign  = b[31];
    uint8_t  a_exp   = a[30:23];
    uint8_t  b_exp   = b[30:23];
    uint23_t a_fract = a[22:0];
    uint23_t b_fract = b[22:0];

    if (a_exp == 0xFF && a_fract != 0 || b_exp == 0xFF && b_fract != 0)
        return 0;
    return (a == b)  || ( ( a | b )<<1 == 0 );
}


// int to float
w32 i2f(w32 a)
{
    FLT_DEBUG_PRINT("i2f: a=0x%x {0x%x 0x%x 0x%x}", a, a[31], a[30:23], a[22:0]);

    uint32_t s_output_o;

    if (a == 0) {
        s_output_o = "0"::ZERO_VECTOR;
    }
    else if (a == (w32)0x80000000) {
        s_output_o = 1::(uint8_t)0x9e::(uint23_t)0x0;
    }
    else {
        uint1_t sign = a[31];
        int32_t pos_a = sign ? -a : a;
        uint31_t sig = (uint31_t) pos_a[30:0]; // re-interpret, with binary
                                               // point between bits 30 and 29
        uint8_t exp = 157; // 127 + 30, since binary point is shifted by
                           // 30 positions

        uint5_t leading_zeros = count_l_zeros_u31( sig[30:0] );

        uint8_t new_exp = exp - leading_zeros;
        uint31_t new_sig = sig << leading_zeros;

        uint1_t ulp = new_sig[7]; // lowest precision bit
        uint1_t guard = new_sig[6];
        uint1_t sticky = (new_sig[5:0] != 0);

        uint1_t roundup = (guard & ulp) | (guard & sticky);

        // round
        uint25_t sig25 = (uint25_t) new_sig[30:7] + roundup;

        // post-normalize
        uint23_t frac     = sig25[24] ? sig25[23:1]   : sig25[22:0];
        uint8_t final_exp = sig25[24] ? (new_exp + 1) : new_exp;

        // pack
        s_output_o = sign::final_exp::frac;
    }

    return s_output_o;
};

/*
   float to int, similar to float32_to_int32_round_to_zero in softfloat
   This is consistent with the C99 standard, which specifies rounding to zero
   For NaN, return largest positive int
   For overflow, return correct sign and largest magnitude
   C99 actually leaves the result of overflow undefined. On Pentium host,
   result is mostly "0x80000000".
*/

w32 f2i(w32 opa)
{
    FLT_DEBUG_PRINT("f2i: opa=0x%x {0x%x 0x%x 0x%x}", opa, opa[31], opa[30:23], opa[22:0]);

    // unpack
    uint23_t aSig = opa[22:0]; // name copied from softfloat;
                               // is really a fraction
    uint8_t aExp = opa[30:23];
    uint1_t aSign = opa[31];

    int32_t z;
    uint32_t aSigExtra;

    int9_t shiftCount = (int9_t) aExp - (int9_t) 0x96;
       // to move binary point 23 positions to the right,
       // the significand should be left-shifted by this amount

    if ( 0 <= shiftCount ) {
        if ( 0x9E <= aExp ) { // left-shift by 8 or more: overflow
            if ((uint32_t)opa != 0xcf000000) { // not (negative, exp 0x9E, frac 0)
                if ( ! aSign || ( ( aExp == 0xFF ) && ( aSig != 0 ) ) ) { // positive nbr, or NaN
                    return 0x7FFFFFFF;
                }
            }
            return 0x80000000;
        }
        z = (uint32_t) ("1"::aSig) << shiftCount; //( aSig | 0x00800000 )<<shiftCount;
        if ( aSign ) z = - z;
    }
    else if ( aExp < 0x7E ) { // result < 1, but perhaps to be rounded up
        return 0;
    }
    else {
        z = (uint32_t) ("1"::aSig) >> ( - shiftCount );
        if ( aSign ) z = - z;
    }

    return z;
}




