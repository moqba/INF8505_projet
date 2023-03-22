/*
-- File : flx_div.p
--
-- Contents : Definition of multi cycle divide unit.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#define FLT_EXP 8
#define FLT_MANT 15
// Behavioural model for IA ISS
#ifdef __checkers__
void divide(w32 numerator, w32 denominator, w32& quotient, w32& remainder)
{
    quotient = (uint32_t)numerator / (uint32_t)denominator;
    remainder = (uint32_t)numerator % (uint32_t)denominator;
}
#endif

void div_step(w32 pi, w32 ai, w32& po, w32& ao, w32 b)
{
    uint64_t pa = pi::ai;
    uint64_t new_pa = pa << 1;
    //DEBUG_PRINT("new_pa=%x",new_pa);
    uint33_t diff = (uint33_t)(new_pa[63:32]) - (uint32_t)b;
    //DEBUG_PRINT("diff=%x",diff);
    if (diff[32] == 0) {
        new_pa[63:32] = diff;
        new_pa[0] = 1;
    }
    po =  new_pa[63:32];
    ao =  new_pa[31:0];
}

w32 div_clb(w32 a) // count number redundant leading bits
{
    uint5_t r = clb32_hier(a[30:0]::"1");
    if (a[31]) r=0;
    return r;
}

// flaot24_t format:
//     321098765432109876543210
//     SEEEEEEEEMMMMMMMMMMMMMMM

// Floating point division, based on open source VHDL code contributed by
// Jidan Al-eryani (with Technical University of Vienna when developing the VHDL code)
// with additional bug fixing

void fdiv_pre(w32 opa, w32 opb, w32& dvdnd, w32& dvsor, w32& other)
{
    FLT_DEBUG_PRINT("fdiv_pre: opa=0x%x {0x%x 0x%x 0x%x} opb=0x%x {0x%x 0x%x 0x%x}",
                opa, opa[23], opa[22:15], opa[14:0], opb, opb[23], opb[22:15], opb[14:0]);

    // Unpack, normalize denormals via left-shifting and increasing the exponent range

    // read from input
    uint1_t s_signa_i = opa[23];
    uint1_t s_signb_i = opb[23];
    uint8_t  s_expa   = opa[22:15];
    uint8_t  s_expb   = opb[22:15];
    uint15_t s_fracta = opa[14:0];
    uint15_t s_fractb = opb[14:0];

    // opa, opb is denormalized
    uint1_t s_opa_dn = (s_expa==0);
    uint1_t s_opb_dn = (s_expb==0);

    uint16_t s_fracta_16 = (~s_opa_dn)::s_fracta; // naming copied from VHDL; this really is a significand
    uint16_t s_fractb_16 = (~s_opb_dn)::s_fractb; // naming copied from VHDL; this really is a significand

    s_expa = s_expa + s_opa_dn;
    s_expb = s_expb + s_opb_dn;

    // count leading zeros
    uint5_t s_dvd_zeros = count_l_zeros_u16( s_fracta_16 );
    uint5_t s_div_zeros = count_l_zeros_u16( s_fractb_16 );

    // left-shift the dividend and divisor, to obtained normalized number with 1 extra exp bit
    // also zero-extend up to width of 19 bits; quotient needs extra precision bits because of
    // post-normalizing right shift
    uint19_t s_dvsor_19 = (s_fractb_16 << s_div_zeros)::"000";
    uint19_t s_dvdnd_19 = "0"::(s_fracta_16<< s_dvd_zeros)::"00"; // right shift by 1 here
                                                                   // left shift by 19 is app layer (dvdend in PH, instead of PL)
                                                                   // total left shift by 18, so binary point of quotient
                                                                   // is "left shifted" by 18 compared with integer number
    // Following line moved to post-processing
    // uint10_t s_exp_10 = (uint10_t)s_expa - (uint10_t)s_expb + 0x7f - s_dvd_zeros + s_div_zeros;

    dvdnd = s_dvdnd_19;
    dvsor = s_dvsor_19;

    // re-pack items which are needed in post-precessing after significand division, in a later cycle
    uint32_t tmp_other = 0;

    tmp_other[31] = s_signa_i;
    tmp_other[30:23] = s_expa;
    tmp_other[22] = (opa[22:0]==0);
    tmp_other[21] = (opa[14:0]!=0);
    tmp_other[20:16] = s_dvd_zeros;

    tmp_other[15] = s_signb_i;
    tmp_other[14:7] = s_expb;
    tmp_other[6] = (opb[22:0]==0);
    tmp_other[5] = (opb[14:0]!=0);
    tmp_other[4:0] = s_div_zeros;

    other = tmp_other;

    FLT_DEBUG_PRINT("fdiv_pre: s_dvdnd_19=0x%x s_dvsor_19=0x%x other=0x%x", s_dvdnd_19, s_dvsor_19, tmp_other);
}

w32 fdiv_post(w32 qutnt, w32 rmndr, w32 other)
{
    // First recover unpacked data, and compute tentative new exponent
    uint1_t s_signa_i = other[31];
    uint1_t s_signb_i = other[15];
    uint8_t  s_expa   = other[30:23];
    uint8_t  s_expb   = other[14:7];

    uint5_t s_dvd_zeros = other[20:16];
    uint5_t s_div_zeros = other[4:0];

    uint10_t s_exp_10 = (uint10_t)s_expa - (uint10_t)s_expb + 0x7f - s_dvd_zeros + s_div_zeros;

    uint1_t opa_zero = other[22];
    uint1_t opb_zero = other[6];

    uint1_t fraca_nz = other[21]; //(opa[14:0]!=0);
    uint1_t fracb_nz = other[5];  //(opb[14:0]!=0);

    uint1_t s_sign_i = s_signa_i ^ s_signb_i;

    FLT_DEBUG_PRINT("fdiv_post: qutnt=0x%x, rmndr=0x%x, s_exp_10=0x%x", qutnt, rmndr, s_exp_10);

    // qutnt
    // 26 25                    3
    // |  |                     |
    // h  fffffffffffffffffffffff grs

    // *** Stage 1 ****
    // figure out the exponent and how much the fraction has to be shifted right/left

    uint19_t s_qutnt_i = qutnt;
    uint19_t s_rmndr_i = rmndr;

    uint1_t s_qutdn = ~(s_qutnt_i[18]); // denormal quotient

    uint10_t s_exp_10_i = s_exp_10;
    uint10_t s_exp_10b = s_exp_10_i - s_qutdn;

    uint10_t v_shr, v_shl;
    uint9_t s_expo1;

    if (s_exp_10b[9] || (s_exp_10b == 0)) { // 0 or negative value
        FLT_DEBUG_PRINT("case1: if (s_exp_10b[9] || (s_exp_10b == 0))");
        v_shr = (1 - s_exp_10b) - s_qutdn;
        v_shl = 0;
        s_expo1 = 1;
    }
    else if (s_exp_10b[8]) { // large positive value (> 255)
        FLT_DEBUG_PRINT("case2: if (s_exp_10b[8])");
        v_shr = 0;
        v_shl = 0;
        s_expo1 = s_exp_10b[8:0];
    }
    else { // normal range
        FLT_DEBUG_PRINT("case3");
        v_shr = 0;
        v_shl = s_qutdn;
        s_expo1 = s_exp_10b[8:0];
    }

    uint6_t s_shr1;
    if (v_shr[9:6] != 0) { //(v_shr[6] | v_shr[7] | v_shr[8] | v_shr[9]) {
        s_shr1 = 0x3f; // 63
    }
    else  {
        s_shr1 = v_shr[5:0];
    }
    uint6_t s_shl1 = v_shl[5:0];

    FLT_DEBUG_PRINT("fdiv_post shift factor v_shr=%d v_shl=%d s_expo1=%d s_shr1=%d s_shl1=%d", v_shr, v_shl, s_expo1, s_shr1, s_shl1);

    // *** Stage 2 ***
    // Shifting the significand

    uint19_t s_fraco1;
    if (s_shr1 != 0) {
        s_fraco1 = s_qutnt_i >> s_shr1;
        // s_fraco1[0] is the sticky bit; it should be raised if non-zero bits are shifted out
        s_fraco1[0] = s_fraco1[0] | ((s_fraco1 << s_shr1) != s_qutnt_i);
    } else {
        s_fraco1 = s_qutnt_i << s_shl1;
    }

    // decrement exponent if subnormal (deferred till after rounding)
    //uint9_t s_expo2 = s_expo1 - (1-s_fraco1[18]); //s_fraco1[26] ? s_expo1 : s_expo1 - 1;

    FLT_DEBUG_PRINT("fdiv_post s_fraco1=0x%x expo1=0x%x", s_fraco1, s_expo1);

    uint5_t s_r_zeros = count_r_zeros_u19(s_qutnt_i);

    //trn s_shr2<uint1_t>;
    //uint1_t s_lost = ((s_shr1 + s_shr2) > s_r_zeros); // defer this

    // ***Stage 3***
    // Rounding (to nearest even)

    uint1_t s_guard = s_fraco1[2];
    uint1_t s_round = s_fraco1[1];
    uint1_t s_sticky = s_fraco1[0] | (s_rmndr_i != 0);

    uint1_t s_roundup = s_guard & ((s_round | s_sticky) | s_fraco1[3]);

    uint17_t s_frac_rnd =  s_fraco1[18:3] + s_roundup;

    // decrement exponent if subnormal (after rounding)
    uint9_t s_expo2 = s_expo1 - (1-s_frac_rnd[15]); //s_frac_rnd[15] ? s_expo1 : s_expo1 - 1;

    // post-normalize after rounding
    uint1_t s_shr2 = s_frac_rnd[16];

    uint9_t s_expo3   = s_shr2 ? s_expo2 + 1      : s_expo2;
    uint17_t s_fraco2 = s_shr2 ? s_frac_rnd[16:1] : s_frac_rnd;

    uint1_t s_lost = ((s_shr1 + s_shr2) > s_r_zeros); // moved from above

    FLT_DEBUG_PRINT("fdiv_post lost=%d sticky=%d roundup=%d shr2=%d frac_rnd=0x%x", s_lost, s_sticky, s_roundup, s_shr2, s_frac_rnd);

    // ***Stage 4****
    // Pack

    uint1_t s_op_0 = opa_zero & (~opb_zero); // <= not ( or_reduce(s_opa_i(30 downto 0)) and or_reduce(s_opb_i(30 downto 0)) );
    uint1_t s_opab_0 = opa_zero & opb_zero; // <= not ( or_reduce(s_opa_i(30 downto 0)) or or_reduce(s_opb_i(30 downto 0)) );
    uint1_t s_opb_0 = opb_zero;             // <= not or_reduce(s_opb_i(30 downto 0));

    uint1_t s_infa = (s_expa==0xff);
    uint1_t s_infb = (s_expb==0xff);

    uint1_t s_nan_a  = s_infa & fraca_nz;
    uint1_t s_nan_b  = s_infb & fracb_nz;
    uint1_t s_nan_in = s_nan_a | s_nan_b;
    uint1_t s_nan_op = (s_infa & s_infb) | s_opab_0; //  0 / 0, inf / inf

    uint1_t s_inf_result = ((s_expo3[7:0] == 0xff) | s_expo3[8]) | s_opb_0;

    //uint1_t s_overflow = s_inf_result & (~(s_infa | s_infb)) & (~s_opb_0);

    //uint1_t s_ine_o = (~s_op_0) & (s_lost | (s_fraco1[2:0] != 0) | s_overflow | (s_rmndr_i != 0));
                // <= '1' when s_op_0='0' and (s_lost or or_reduce(s_fraco1(2 downto 0)) or s_overflow or or_reduce(s_rmndr_i))='1' else '0';
                // extra output in the VHDL code, but not used here

    uint32_t s_output_o;
    if (s_nan_in | s_nan_op) {
        FLT_DEBUG_PRINT("fdiv_post QNAN");
        // modified the "1"::QNAN, to "0"::QNAN
        // The purpose is to make the PDG div has the same behavior with Native verilated C++ (from DesignWare)
        s_output_o = "00000000"::"0"::QNAN;
    }
    else if (s_infa /* | s_overflow */ | s_inf_result) {
        FLT_DEBUG_PRINT("fdiv_post INF");
        s_output_o = "00000000"::s_sign_i::INF;
    }
    else if (s_op_0 | s_infb /* | (s_fraco2 == 0) */ ) { // last term: no 1 left in significand
        FLT_DEBUG_PRINT("fdiv_post ZERO_VECTOR");
        //s_output_o = s_sign_i::ZERO_VECTOR;
        s_output_o = "00000000"::s_sign_i::ZERO_VECTOR; //"0"::ZERO_VECTOR;
    }
    else {
        s_output_o = "00000000"::s_sign_i::s_expo3[7:0]::s_fraco2[14:0];
    }

    return s_output_o;
}

void fsqrt_pre(w32 opa, w32& remainder, w32& other)
{
    FLT_DEBUG_PRINT("fsqrt_pre: opa=0x%x {0x%x 0x%x 0x%x}",
                opa, opa[23], opa[22:15], opa[14:0]);

    // Unpack, normalize denormals via left-shifting and increasing the exponent range

    // read from input
    uint1_t s_signa_i = opa[23];
    uint8_t  s_expa   = opa[22:15];
    uint15_t s_fracta = opa[14:0];

    // opa, opb is denormalized
    uint1_t s_opa_dn = (s_expa==0);

    uint16_t s_fracta_16 = (~s_opa_dn)::s_fracta; // naming copied from VHDL; this really is a significand

    s_expa = s_expa + s_opa_dn;

    // count leading zeros
    uint5_t s_rdcnd_zeros = count_l_zeros_u16( s_fracta_16 );

    // left-shift the radicand, to obtain normalized number with 1 extra exp bit
    //// also zero-extend up to width of 27 bits; root needs extra precision bits because of
    //// post-normalizing right shift
    uint16_t s_rdcnd_16 = (s_fracta_16 << s_rdcnd_zeros);
    //uint27_t s_dvsor_27 = (s_fractb_16 << s_div_zeros)::"000";
    //uint27_t s_dvdnd_27 = "0"::(s_fracta_16 << s_dvd_zeros)::"00"; // right shift by 1 here
                                                                   // left shift by 27 is app layer (dvdend in PH, instead of PL)
                                                                   // total left shift by 26, so binary point of quotient
                                                                   // is "left shifted" by 26 compared with integer number
    // Following line moved to post-processing
    // uint10_t s_exp_10 = (uint10_t)s_expa - (uint10_t)s_expb + 0x7f - s_dvd_zeros + s_div_zeros;

    uint9_t s_exp_tem = (uint9_t)s_expa + 0x7f - (uint9_t)s_rdcnd_zeros; // bias added twice now

    uint8_t s_exp_o = (opa[22:0] == 0) ? 0 : (uint8_t) s_exp_tem[8:1]; // s_exp_tem / 2 - bias present once
    uint17_t s_rdcnd_17 = s_exp_tem[0] ? (s_rdcnd_16::"0") : ("0"::s_rdcnd_16); // significand eats up s_exp_tem[0]
                                                                       // so in range [1,4)

    FLT_DEBUG_PRINT("fsqrt_pre: s_fracta_16=0x%x, s_rdcnd_zeros=0x%x,s_expa=0x%xs, exp_tem=0x%x ",s_fracta_16,s_rdcnd_zeros, s_expa, s_exp_tem);


    int17_t s_remainder = (int17_t) s_rdcnd_17 - (int17_t) 0x8000;
    remainder = (uint17_t) s_remainder;

    // re-pack items which are needed in post-precessing after significand division, in a later cycle
    uint32_t tmp_other = 0;

    tmp_other[31] = s_signa_i;
    tmp_other[7:0] = s_exp_o;
    tmp_other[30] = (opa[14:0]!=0);
    tmp_other[29] = (opa[22:0]!=0);
    tmp_other[28] = (s_expa==0xff);

    other = tmp_other;

    FLT_DEBUG_PRINT("fsqrt_pre: s_rdcnd_17=0x%x s_remainder=0x%x, other=0x%x",
                                    s_rdcnd_17::"0", s_remainder::"0", tmp_other);
                                    // all printed values have 24 fractional bits
}

// binary restoring sqrt step
// Behrooz Parhami, "Computer Arithmetic, Second Edition", Section 21.2
// Adapted to use a minimal number of general purpose registers to hold intermediate results
void sqrt_step(w32 s_in,w32 q_in,w32& s_out,w32& q_out)
{
    uint18_t s = s_in; // three whole bits, 15 fraction bits
    uint4_t index = q_in[23:20]; //???
    uint17_t q = q_in[16:0]; // one whole bit, 16 fraction bits (extra fraction bit for rounding)

    uint4_t index_min_1 = index - (uint4_t)1;
    uint18_t shifted_01 = (uint17_t)"01" << index; // first index should be 15
    uint18_t subtrahend = (q::"0") | shifted_01;
    uint19_t trial_subtraction = (uint19_t) (s::"00") - (uint19_t) subtrahend;
                                // 3 whole bits (including sign), 16 fraction bits
                                // s is left-shifted by one, and receives an extra fraction bit
    uint1_t sign = trial_subtraction[18];
    FLT_DEBUG_PRINT("sqrt_step two_s=0x%x, shifted_01=0x%x, subtrahend=0x%x, trial_subtraction=0x%x",
                        s::"00", shifted_01, subtrahend, trial_subtraction);

    uint18_t new_s = sign ? s[16:0]::"0" : (uint18_t) trial_subtraction[18:1];
    uint1_t new_q_bit = !sign;
    uint17_t q_bit_shifted = (uint17_t)new_q_bit << index;
    uint17_t new_q = q | q_bit_shifted;

    s_out = new_s;
    q_out = "00000000"::index_min_1::"000"::new_q; //???
    FLT_DEBUG_PRINT("sqrt_step s=0x%x, q=0x%x, idx=%d, new_s=0x%x, new_q=0x%x",
                        s::"0", q, index, new_s::"0", new_q);
                        // 24 fraction bits for all printed values
}

w32 fsqrt_post(w32 q_in, w32 other)
{
    uint16_t q = q_in[16:1];
    uint1_t s_roundup = q_in[0];

    uint1_t s_sign = other[31];
    uint8_t s_expo = other[7:0];
    uint1_t fraca_nz = other[30]; //(opa[22:0]!=0);
    uint1_t a_nz = other[29]; //(opa[30:0]!=0);

    uint16_t s_frac_rnd = s_roundup ? (q + 1) : q;

    uint1_t s_infa = other[28]; //(s_expa==0xff);

    uint1_t s_nan_a  = s_infa & fraca_nz;
    uint1_t s_nan_op = s_sign & a_nz; // sqrt(-x) = NaN

    uint32_t s_output_o;
    if (s_nan_a | s_nan_op) {
        FLT_DEBUG_PRINT("fsqrt_post QNAN");
        // modified the "1"::QNAN, to "0"::QNAN
        // The purpose is to make the PDG sqrt has the same behavior with Native verilated C++ (from DesignWare)
        s_output_o = "00000000"::"0"::QNAN;
    }
    else if (s_infa) {
        FLT_DEBUG_PRINT("fsqrt_post INF");
        s_output_o = "00000000"::s_sign::INF;
    }
    else {
        s_output_o = "00000000"::s_sign::s_expo::s_frac_rnd[14:0];
    }

    return s_output_o;
}

//#define Q_INIT ((1 << 16) | (15 << 19))
#define Q_INIT 0b1111::0b0001_0000_0000_0000_0000
// initial q = 1.0 with 16 fractional bits + index 15 in bits [31:27]



/* Integration
   One possibiliy is mapping the functions above to instructions, and integrating in the
   compiler header file (i.e. integrate in software)
   Another possiblity is integrating in a multicycle functional unit (in hardware). In
   this case, subsequent instructions can continue to the extent they don't depend on the
   div/sqrt result (and the compiler will take advantage of this)
*/

#define IDIV_MODE 0b01
#define FDIV_MODE 0b10
#define FSQRT_MODE 0b11

multicycle_fu div
{
    reg cnt<uint6_t>;
    reg mode<uint2_t>;

    reg AH<w32>;     // dividend/remainder
    reg AL<w32>;     // quotient
    reg B<w32>;      // divisor
    reg OTHER<w32>;  // extra floating point fields

    process main () {
        uint6_t new_cnt = 0;

        // integer division
        if (vd_divide_divA_divB_wl_wh_div_EX_sig) {
            uint5_t n = div_clb((uint32_t)divA);
            uint64_t pa = (uint32_t)divA << n;
            B = divB;
            new_cnt = 33 - n;
            AH = pa[63:32];
            AL = pa[31:0];
            mode = IDIV_MODE;
        } else if (mode == IDIV_MODE && cnt > 1) {
            div_step(AH, AL, AH, AL, B);
            new_cnt = cnt - 1;
        } else if (mode == IDIV_MODE && cnt == 1) {
            PL = wl = AL; //pa[31:0];
            PH = wh = AH; //pa[63:32];
            new_cnt = cnt - 1;
        }

        // Floating point division
        else if (vd_fdivide_divA_divB_wl_div_EX_sig) {
            w32 dvdnd, dvsor, other;
            // unpacking, extracting 27-bit significands to be divided, repacking in "other"
            fdiv_pre(divA, divB, dvdnd, dvsor, other);
            OTHER = other;
            B = dvsor;
            mode = FDIV_MODE;
            w32 ah = dvdnd;
            w32 al = 0;
            AH = ah;
            AL = al;
            new_cnt = FLT_MANT+5; // steps to go
        } else if (mode == FDIV_MODE && cnt > 1) {
            div_step(AH, AL, AH, AL, B);
            new_cnt = cnt - 1;
        } else if (mode == FDIV_MODE && cnt == 1) {
            w32 remainder, quotient;
            remainder = AH;
            quotient = AL;
            // post-normalize, round, post-normalize again, pack
            PL = wl = fdiv_post(quotient, remainder, OTHER);
            new_cnt = cnt - 1;
        }

        // Floating point square root
        else if (vd_fsqrt_divA_wl_div_EX_sig) {
            w32 remainder, other, q;
            // unpack, normalize, extrace integer radicand in range [1,4), re-pack other stuff in "other"
            fsqrt_pre(divA, remainder, other);
            OTHER = other;
            q = Q_INIT;
            mode = FSQRT_MODE;
            w32 ah = remainder;
            w32 al = q;
            AH = ah;
            AL = al;
            new_cnt = FLT_MANT+2; // steps to go
        } else if (mode == FSQRT_MODE && cnt > 1) {
            sqrt_step(AH, AL, AH, AL);
            new_cnt = cnt - 1;
        } else if (mode == FSQRT_MODE && cnt == 1) {
            //w32 remainder, quotient;
            w32 quotient = AL;
            // rounding and packing
            PL = wl = fsqrt_post(quotient, OTHER);
            new_cnt = cnt - 1;
        }
        cnt = new_cnt;

        div_busy      = vd_divide_divA_divB_wl_wh_div_EX_sig || cnt > 1;
        div_busy_raw  = vd_divide_divA_divB_wl_wh_div_EX_sig ||  cnt != 0;
        div_busy_wb  = (vd_divide_divA_divB_wl_wh_div_EX_sig && (new_cnt > 2)) || cnt > 3;

        fdiv_busy     = vd_fdivide_divA_divB_wl_div_EX_sig || vd_fsqrt_divA_wl_div_EX_sig || cnt > 1;
        fdiv_busy_raw = vd_fdivide_divA_divB_wl_div_EX_sig || vd_fsqrt_divA_wl_div_EX_sig || cnt != 0;
    }
}

/*

  cnt = 33 - clb(A), with clb(A) in [0,31]
  -> cnt in [2,33]

  cnt == 2 -> clb(A) = 31 -> A[31:0] == 0


  Cycle    :   0     1     2     3     4     5     6     7     8     9
  ---------:----------------------------------------------------------
  div      :   IF    ID    EX
                           ^^ div start
  +1       :         IF    ID    ...
  +2       :               IF    ID    ...
  ---------:----------------------------------------------------------
  div_sig  :               1
  cnt      :   *     *     0     33    ...   4     3     2     1     0
  ---------:----------------------------------------------------------
  div_busy :         0     1     1     ...   1     1     1     0     0
  div_raw  :               1     1     ...   1     1     1     1     0
  div_waw  :               1     1     ...   1     0     0     0     0
  ---------:----------------------------------------------------------
  wr PL PH :                                                   1



  Cycle    :   0     1     2     3     4     5     6     7     8     9
  ---------:----------------------------------------------------------
  div      :   IF    ID    EX
                           ^^ div start
  +1       :         IF    ID    ...
  +2       :               IF    ID    ...
  ---------:----------------------------------------------------------
  div_sig  :               1
  cnt      :   *     *     0     4     3     2     1     0
  ---------:----------------------------------------------------------
  div_busy :         0     1     1     1     1     0     0
  div_raw  :               1     1     1     1     1     0
  div_waw  :               1     1     0     0     0     0
  ---------:----------------------------------------------------------
  wr PL PH :                                       1



  Cycle    :   0     1     2     3     4     5     6     7     8     9
  ---------:----------------------------------------------------------
  div      :   IF    ID    EX
                           ^^ div start
  +1       :         IF    ID    ...
  +2       :               IF    ID    ...
  ---------:----------------------------------------------------------
  div_sig  :               1
  cnt      :   *     *     0     3     2     1     0
  ---------:----------------------------------------------------------
  div_busy :         0     1     1     1     0     0
  div_raw  :               1     1     1     1     0
  div_waw  :               1     0     0     0     0
  ---------:----------------------------------------------------------
  wr PL PH :                                 1



  Cycle    :   0     1     2     3     4     5     6     7     8     9
  ---------:----------------------------------------------------------
  div      :   IF    ID    EX
                           ^^ div start
  +1       :         IF    ID    ...
  +2       :               IF    ID    ...
  ---------:----------------------------------------------------------
  div_sig  :               1
  cnt      :   *     *     0     2     1     0
  ---------:----------------------------------------------------------
  div_busy :         0     1     1     0     0
  div_raw  :               1     1     1     0
  div_waw  :               0     0     0     0
  ---------:----------------------------------------------------------
  wr PL PH :                           1



  Cycle    :   0     1     2     3     4     5     6     7     8     9
  ---------:----------------------------------------------------------
  div      :   IF    ID    EX
                           ^^ div start
  div      :         IF    ID*   ID*   ID    EX    ...
                                             ^^ div start
  ---------:----------------------------------------------------------
  div_sig  :               1                 1
  cnt      :   *     *     0     2     1     0     ...
  ---------:----------------------------------------------------------
  div_busy :         0     1     1     0     1
  div_raw  :               1     1     1     1
  div_waw  :               0     0     0     0/1
  ---------:----------------------------------------------------------
  wr PL PH :                           1



  Cycle    :   0     1     2     3     4     5     6     7     8     9
  ---------:----------------------------------------------------------
  div      :   IF    ID    EX
                           ^^ div start
  +1       :         IF    ID    EX    ME    WB
                                             ^^ could write to PL/PH
  +2       :               IF    ID    ...
  div      :                     IF    ID    EX    ...
                                             ^^ div start
  ---------:----------------------------------------------------------
  div_sig  :               1                 1
  cnt      :   *     *     0     2     1     0     ...
  ---------:----------------------------------------------------------
  div_busy :         0     1     1     0     1
  div_raw  :               1     1     1     1
  div_waw  :               0     0     0     0/1
  ---------:----------------------------------------------------------
  wr PL PH :                           1



  Cycle    :   0     1     2     3     4     5     6     7     8     9
  ---------:----------------------------------------------------------
  div      :   IF    ID    EX
                           ^^ div start
  +1       :         IF    ID    EX    ME    WB
                                             ^^ could write to PL/PH
  div      :               IF    ID*   ID    EX    ...
                                             ^^ div start
  ---------:----------------------------------------------------------
  div_sig  :               1                 1
  cnt      :   *     *     0     2     1     0     ...
  ---------:----------------------------------------------------------
  div_busy :         0     1     1     0     1
  div_raw  :               1     1     1     1
  div_waw  :               0     0     0     0/1
  ---------:----------------------------------------------------------
  wr PL PH :                           1


  Cycle    :   0     1     2     3     4     5     6     7     8     9
  ---------:----------------------------------------------------------
  wr PL    :   IF    ID    EX    ME    WB
                                       ^^ writes to PL
  div      :         IF    ID    EX
                                 ^^ div start
                                             ^^ div writes to PL,PH
  ---------:----------------------------------------------------------
  div_sig  :                     1
  cnt      :         *     *     0     2     1     0
  ---------:----------------------------------------------------------
  div_busy :               0     1     1     0     0
  div_raw  :                     1     1     1     0
  div_waw  :                     0     0     0     0
  ---------:----------------------------------------------------------
  wr PL PH :                                 1



  Cycle    :   0     1     2     3     4     5     6     7     8     9
  ---------:----------------------------------------------------------
  wr PL    :   IF    ID    EX    ME    WB
                                       ^^ writes to PL
  +1       :         IF    ID    ...
  div      :               IF    ID    EX
                                       ^^ div start
                                                   ^^ div writes to PL,PH
  ---------:----------------------------------------------------------
  div_sig  :                           1
  cnt      :               *     *     0     2     1     0
  ---------:----------------------------------------------------------
  div_busy :                     0     1     1     0     0
  div_raw  :                           1     1     1     0
  div_waw  :                           0     0     0     0
  ---------:----------------------------------------------------------
  wr PL PH :                                       1



  Cycle    :   0     1     2     3     4     5     6     7     8     9
  ---------:----------------------------------------------------------
  wr PL    :   IF    ID    EX    ME    WB
                                       ^^ writes to PL
  +1       :         IF    ID    ...
  +2       :               IF    ID    ...
  div      :                     IF    ID    EX
                                             ^^ div start
                                                         ^^ div writes to PL,PH
  ---------:----------------------------------------------------------
  div_sig  :                                 1
  cnt      :                     *     *     0     2     1     0
  ---------:----------------------------------------------------------
  div_busy :                           0     1     1     0     0
  div_raw  :                                 1     1     1     0
  div_waw  :                                 0     0     0     0
  ---------:----------------------------------------------------------
  wr PL PH :                                             1




  Cycle    :   0     1     2     3     4     5     6     7     8     9
  ---------:----------------------------------------------------------
  wr rX    :   IF    ID    EX    ME    WB
  div      :         IF    ID    EX
                                 ^^ div start
  +1       :               IF    ID    ...
  +2       :                     IF    ID    ...
  ---------:----------------------------------------------------------
  div_sig  :                     1
  cnt      :         *     *     0     3     2     1     0
  ---------:----------------------------------------------------------
  div_busy :               0     1     1     1     0     0
  div_raw  :                     1     1     1     1     0
  div_waw  :                     1     0     0     0     0
  ---------:----------------------------------------------------------
  wr PL PH :                                       1





  Cycle    :   0     1     2     3     4     5     6     7     8     9
  ---------:----------------------------------------------------------
  wr rX    :   IF    ID    EX    ME    WB
  wr rY    :         IF    ID    EX    ME    WB
  div      :               IF    ID    EX
                                       ^^ div start
  +1       :                     IF    ID    ...
  +2       :                           IF    ID    ...
  ---------:----------------------------------------------------------
  div_sig  :                           1
  cnt      :               *     *     0     3     2     1     0
  ---------:----------------------------------------------------------
  div_busy :                     0     1     1     1     0     0
  div_raw  :                           1     1     1     1     0
  div_waw  :                           1     0     0     0     0
  ---------:----------------------------------------------------------
  wr PL PH :                                             1

 */


