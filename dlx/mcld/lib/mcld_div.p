/*
-- File : mcld_div.p
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



/* Integration
   One possibiliy is mapping the functions above to instructions, and integrating in the
   compiler header file (i.e. integrate in software)
   Another possiblity is integrating in a multicycle functional unit (in hardware). In
   this case, subsequent instructions can continue to the extent they don't depend on the
   div/sqrt result (and the compiler will take advantage of this)
*/

#define IDIV_MODE 0b01

multicycle_fu div
{
    reg cnt<uint6_t>;
    reg mode<uint2_t>;

    reg AH<w32>;     // dividend/remainder
    reg AL<w32>;     // quotient
    reg B<w32>;      // divisor

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

        cnt = new_cnt;

        div_busy      = vd_divide_divA_divB_wl_wh_div_EX_sig || cnt > 1;
        div_busy_raw  = vd_divide_divA_divB_wl_wh_div_EX_sig ||  cnt != 0;
        div_busy_wb  = (vd_divide_divA_divB_wl_wh_div_EX_sig && (new_cnt > 2)) || cnt > 3;

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


