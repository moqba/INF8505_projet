/*
-- File : div.p
--
-- Contents : Definition of multi cycle divide unit.
--
-- Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Behavioural models for IA ISS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifdef __checkers__
w32 divs(w32 a, w32 b) { if(b==0) return -1; else return a / b; }
w32 rems(w32 a, w32 b) { if(b==0) return  a; else return a % b; }
w32 divu(w32 a, w32 b) { if(b==0) return -1; else return (uint32_t)a / (uint32_t)b; }
w32 remu(w32 a, w32 b) { if(b==0) return  a; else return (uint32_t)a % (uint32_t)b; }
#endif


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Implementation model
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ One division step

uint64_t div_step(uint64_t pa, uint32_t b)
{
  uint64_t new_pa = pa << 1;
  uint33_t diff = (uint33_t)(new_pa[63:32]) - b;
  if (diff[32] == 0) {
    new_pa[63:32] = diff;
    new_pa[0] = 1;
  }
  return new_pa;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Multi-Cycle Functional Unit

multicycle_fu div
{
  reg cnt             <uint6_t>;
  reg PA              <uint64_t>;
  reg B               <uint32_t>;
  reg Q_addr_reg      <uint5_t>;
  reg is_div          <uint1_t>;
  reg is_neg          <uint1_t>;

  hw_init cnt = 0;

  process main () {
    uint1_t is_divs = divR_divs_divA_divB_div_EX_sig;
    uint1_t is_divu = divR_divu_divA_divB_div_EX_sig;
    uint1_t is_rems = divR_rems_divA_divB_div_EX_sig;
    uint1_t is_remu = divR_remu_divA_divB_div_EX_sig;

    uint1_t div_start =
        (cnt == 0) &&
        (is_divs || is_divu || is_rems || is_remu) &&
        (div_wad != 0);

    if (div_start) {
      int32_t divA_loc;
      int32_t divB_loc;

      if( is_divs || is_rems) {
        if(divA[31]) { divA_loc = -divA; }
        else         { divA_loc =  divA; }

        if(divB[31]) { divB_loc = -divB; }
        else         { divB_loc =  divB; }

        is_neg = divA[31] ^ (divB[31] & is_divs);
      }
      else {
        divA_loc = divA;
        divB_loc = divB;
        is_neg   = 0;
      }

      PA = (uint32_t)divA_loc; // set 32 msbs to 0
      B  = divB_loc;

      Q_addr_reg = div_wad;
      is_div = (is_divs || is_divu);

      cnt = 33;

    } else if (cnt > 1) {

      PA = div_step(PA,B);
      cnt = cnt - 1;

    } else if (cnt == 1) {

      uint64_t pa = PA;
      int32_t res = is_div ? pa[31:0] : pa[63:32];
      if( is_neg ) { res = -res; }
      if( B == 0 && is_div ) res = -1; // RISC-V divByZero
      X[Q_addr_reg] = w1 = res;
      cnt = cnt - 1;
    }
  }

  process state_to_core() {
    div_bsy = cnt != 0;
    div_adr = Q_addr_reg;
    div_wnc = (cnt == 2);
  }
}
