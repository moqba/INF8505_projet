/*
-- File : vlx_pcu.p
--
-- Contents : Definition of the VLX controller in PDG.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "vlx_define.h"

/* In case, a systemc adapter triggers a wait state */
#ifdef SYSTEMC_FLOW
wait_state_repeat;
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


}

hw_init reg_booting = 1;


hw_init reg_debug_mode = 0;


void vlx::user_issue()
{
    w08  fi0,  fi1,  fi2,  fi3; // fetched instruction bytes

    bool interruptible = !hw_stall_sig() && (!(ds1 || ds2) || reg_debug_mode);

    // ignore interruptible while we are in debug mode
    debug_mode = ocd_req && interruptible;

    // decoder > ocd_swbreak > ocd_req > debug_mode
    // decoder > ds1/ds2 > interruptible > debug_mode

    bool stop_issue = reg_booting
                   || debug_mode || reg_debug_mode;

    pcr = PC;
    if (ocd_exe) {
        iword instr =  ocd_instr_r = ocd_instr;
        fi0 = instr[31:24];
        fi1 = instr[23:16];
        fi2 = instr[15:8];
        fi3 = instr[7:0];
        issue_instr(0, 0, fi0, fi1, fi2, fi3);
    }
    else if (!hw_stall_sig() && !stop_issue /*&& issue_sig() */) {
        // NOTE add issue_sig() to cond. if cycles(N) instructions are used
        iword instr =  pm_rd;
        fi0 = instr[31:24];
        fi1 = instr[23:16];
        fi2 = instr[15:8];
        fi3 = instr[7:0];
        issue_instr(pcr, 1, fi0, fi1, fi2, fi3);

        DEBUG_PRINT("II :  %d  %x",pcr,instr);
    }

    ocd_mod = reg_debug_mode;
    reg_debug_mode = debug_mode;
    r1_ocd_exe = ocd_exe; r2_ocd_exe = r1_ocd_exe;
}

void vlx::user_next_pc()
{
 // next PC computation
    lnk_if = pcr = PC;
    bool fetch = 1;

    bool abs_jump = vd_jr_trgt_EX_sig | tex_lnk_jalr_trgt_EX_sig;
    bool r26_jump = vd_j_of26_ID_sig  | tid_lnk_jal_of26_ID_sig;
    bool r16_jump = vd_br_cnd_of16_EX_sig && cnd;
    bool del_jump = !hw_stall_sig() && reg_stall_trgt_valid;

    tid_lnk = pcr + 4;
    tex_lnk = pcr + 4;

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
        next_pc = pcr + 4;
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
    DEBUG_PRINT("NPC : %d : %d,%d,%d,%d, %d : %d/%d",
                pcr,hw_stall_sig(),abs_jump,r26_jump,r16_jump,ds2,next_pc,fetch_pc);
    DEBUG_PRINT("STALL TRGT :  %d %d",reg_stall_trgt_valid, reg_stall_trgt);
}

//#define ENABLE_HAZARD_COVERAGE
