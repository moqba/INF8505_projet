/*
-- File : dlx_pcu.p
--
-- Contents : Definition of the DLX controller in PDG.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "dlx_define.h"

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


 trn in_stall<uint1_t>;
}

hw_init reg_booting = 1;


hw_init reg_debug_mode = 0;


void dlx::user_issue()
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
    in_stall = hw_stall_sig() || in_stall_cycle(ID);
    if (ocd_exe) {
        iword instr =  ocd_instr_r = ocd_instr;
        fi0 = instr[31:24];
        fi1 = instr[23:16];
        fi2 = instr[15:8];
        fi3 = instr[7:0];
        issue_instr(0, 0, fi0, fi1, fi2, fi3);
    }
    else if (!in_stall  && !stop_issue /* && issue_sig() */) {
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

void dlx::user_next_pc()
{
 // next PC computation
    lnk_if = pcr = PC;
    bool fetch = 1;

    bool abs_jump = vd_jr_trgt_EX_sig | tex_lnk_jalr_trgt_EX_sig;
    bool r26_jump = vd_j_of26_ID_sig  | tid_lnk_jal_of26_ID_sig;
    bool r16_jump = vd_br_cnd_of16_EX_sig && cnd;
    bool del_jump = !in_stall && reg_stall_trgt_valid;

    tid_lnk = pcr + 4;
    tex_lnk = pcr + 4;



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
    else if (in_stall)       next_pc = pcr;
    else {

        if (fetch) {
        next_pc = pcr + 4;
        }
    }


    if (in_stall) {
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
    addr fetch_pc = in_stall? (addr)pcr : next_pc;
    if (fetch)
        pm_rd`1` = PM[pm_ad = fetch_pc]`1`;
    DEBUG_PRINT("NPC : %d : %d,%d,%d,%d, %d : %d/%d",
                pcr,hw_stall_sig(),abs_jump,r26_jump,r16_jump,ds2,next_pc,fetch_pc);
    DEBUG_PRINT("STALL TRGT :  %d %d",reg_stall_trgt_valid, reg_stall_trgt);
}

//#define ENABLE_HAZARD_COVERAGE
