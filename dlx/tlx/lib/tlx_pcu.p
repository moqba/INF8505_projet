/*
-- File : tlx_pcu.p
--
-- Contents : Definition of the TLX controller in PDG.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "tlx_define.h"
#include "isg/tlx_pdg_encoding.p"
#if defined(TLX_HAS_ADAPTERS)
wait_state_nop;
#endif

pcu_storages {
  reg reg_booting<bool>;

  reg reg_stall_trgt<addr>;   // record target address when stall occurs
  reg reg_stall_trgt_valid<bool>;

  trn debug_mode<bool>;       // set when debug request is accepted
  reg reg_debug_mode<bool>;   // delayed debug_mode signal

  // delay line for ocd_exe signal
  reg r1_ocd_exe<bool>;
  reg r2_ocd_exe<bool>;

  // interrupts
  reg reg_halted<bool>;      // is set when processor is in halted state
  trn trn_interrupted<bool>; // interrupt is accepted in current cycle
}

hw_init reg_booting = 1;
hw_init reg_debug_mode = 0;

hw_init reg_halted = 0;

#include "clb.p"

bool check_interrupts(uint16_t  i_req,     // interrupt requests
                      uint16_t  i_mask,    // interrupt mask
                      uint5s2&  i_vector,   // interrupt vector
                      uint16_t& i_ack)     // interrupt acknowledge
{
    uint16_t i    = i_req & (i_mask[7:1]::"0");  // never mask ireq 0 (reset)
    uint16_t mreq = i[0]::i[1]::i[2]::i[3]::i[4]::i[5]::i[6]::i[7]::i[8]::i[9]::i[10]::i[11]::i[12]::i[13]::i[14]::i[15]; // swap
    uint5_t  ivec = clb16_hier(mreq);            // determine highest IRQ

    //DEBUG_PRINT("IRQ i_req=%x i=%x mreq=%d -> ivec=%d", i_req, i, mreq,ivec);

    if (ivec[4]) {
      // no irq -> assign dummy output values
      i_vector = 0;
      i_ack    = 0;
      return 0;
    }
    else {
      i_vector = ivec[3:0]::"0";
      i_ack    = ((uint16_t)1)<<ivec[3:0];
      return 1;
    }
}
void tlx::user_issue()
{
    bool interruptible = !hw_stall_sig() && (!(ds1 || ds2) || reg_debug_mode);

    // ignore interruptible while we are in debug mode
    debug_mode = ocd_req && interruptible;

    bool stop_issue = reg_booting
                   || reg_halted
                   || debug_mode || reg_debug_mode;

    pcr = PC;

   // interrupts
    uint5s2 i_vector = 0;
    uint16_t i_ack = 0;
    trn_interrupted = 0;

    ier = IE;
    if (   interruptible && !ocd_dis_int && !debug_mode && ier) {
       trn_interrupted = check_interrupts(ireq_pcu_inp,imr=IM,i_vector,i_ack);
    }
    if (trn_interrupted) {
        iword instr = pdg_encoding_jti_instr(i_vector);
        issue_instr(0, 0, instr);
    }
    else  if (ocd_exe) {
        iword ii =  ocd_instr_r = ocd_instr;
        issue_instr(0, 0, ii);
    }
    else if (!hw_stall_sig() && !stop_issue && issue_sig() ) {
        iword ii =  pm_rd;
        issue_instr(pcr, 1, ii);
        DEBUG_PRINT("II :  %d  %x",pcr,ii);
    }


    halted_out = reg_halted;
    iack_pcu_out = i_ack;


    ocd_mod = reg_debug_mode;
    reg_debug_mode = debug_mode;
    r1_ocd_exe = ocd_exe; r2_ocd_exe = r1_ocd_exe;
}

void tlx::user_next_pc()
{
 // next PC computation


    lnk_if = pcr = PC;
    bool fetch = 1;

    bool abs_jump = vd_jr_trgt_EX_sig  | tex_lnk_jalr_trgt_EX_sig
                  | vd_rti_trgt_ID_sig | lnk_if_jti_trgt_ID_sig;
    bool r26_jump = vd_j_of26_ID_sig  | tid_lnk_jal_of26_ID_sig;
    bool r16_jump = vd_br_cnd_of16_EX_sig && cnd;

    bool del_jump = !hw_stall_sig() && reg_stall_trgt_valid;

    tid_lnk = pcr + 1;
    tex_lnk = pcr + 1;

    uint1_t lp_jump = 0;
    uint1_t lp_done = 0;
    uint1_t lp_update = 0;
    addr tlcr = 0;
    addr tlsr = 0;
    addr tler = 0;
    lfra = LF;
    if (lfra < 3) {
        tlcr = lcr = LC[lfra];
        tlsr = lsr = LS[lfra];
        tler = ler = LE[lfra];
        if (pcr == (w32)tler) {
            if (tlcr == 1)
                lp_done = 1;
            else
                lp_jump = 1;
        }
    }

    // end of loop test (zloop)
    uint1_t zlp_jump = 0;
    uint1_t zlp_done = 0;
    uint1_t zlp_update = 0;
    zcr = ZC;
    zsr = ZS;
    {
      zer = ZE;
      if (pcr == (w32)zer) {
        if (zcr == 1)
          zlp_done = 1;
        else
          zlp_jump = 1;
      }
    }

    addr default_pc = pcr;               // default: no increment
    if (r2_ocd_exe && vd_jr_trgt_EX_sig) // only in debug mode
      default_pc = trgt;

    addr next_pc = default_pc;
             //when there is an interrupt, It is only required that the PC is not modified. The jti and rti instructions affect
             //nextpc through the compact format of the jump signals
    fetch = !(trn_interrupted || reg_halted || debug_mode);
    if (debug_mode)          fetch = 0;
    else if (reg_debug_mode) /* default */;
    else if (reg_booting)    next_pc = 0;
    else if (abs_jump)       next_pc = trgt;
    else if (r26_jump)       next_pc = pcr + of26;
    else if (r16_jump)       next_pc = pcr + of16;
    else if (del_jump)       next_pc = reg_stall_trgt;
    else if (hw_stall_sig()) /* default */;
    else {

        if (fetch) {
        next_pc = pcr + 1;
            lp_update = 1;     // enable do loop update, for end of loop checking
            zlp_update = 1;
        }
    }
    if (lp_update) {
       if (lp_jump) {
           LC[lfra] = lcw = tlcr - 1;
           next_pc = tlsr;
        }
        if (lp_done) {
            LF = lfw = lfra - 1;
        }
    }

    if (zlp_update) {
        if (zlp_jump) {
            ZC = zcw = zcr - 1;
            next_pc = zsr;
        }
        if (zlp_done) { // zloop_count_invariant
            ZC = zcw = zdr = ZD;
        }
    }

    if (hw_stall_sig()) {
        PC = pcw = pcr;
        if (ds2 && (abs_jump || r16_jump))  {
            reg_stall_trgt = next_pc;
            reg_stall_trgt_valid = 1;
        }
    }

    else {
        PC = pcw = next_pc;
    }

    if (reg_booting) reg_booting = 0;
    if (del_jump) reg_stall_trgt_valid = 0;
// instruction pre fetch

    addr fetch_pc = hw_stall_sig() ? (addr)pcr : next_pc;

    if (fetch)
        pm_rd`1` = PM[pm_ad = fetch_pc]`1`;
    if (vd_halt_ID_sig) {
        reg_halted = 1;
    } else if (trn_interrupted) {
        reg_halted = 0;
    }
    DEBUG_PRINT("NPC : %d : %d,%d,%d,%d, %d : %d/%d",
                pcr,hw_stall_sig(),abs_jump,r26_jump,r16_jump,ds2,next_pc,fetch_pc);
    DEBUG_PRINT("STALL TRGT :  %d %d",reg_stall_trgt_valid, reg_stall_trgt);
}


