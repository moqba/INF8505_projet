/*
-- File : trv32p5_pcu.p
--
-- Contents : Definition of the trv32p5 controller in PDG.
--
-- Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "trv32p5_define.h"

// #define PRINT_PCU
#ifdef        PRINT_PCU
#define DEBUG_PRINT_PCU(FMT,ARGS...)  DEBUG_PRINT_NAME(); DEBUG_PRINTF(".PCU cyc="); DEBUG_PRINT_CYCLES(); DEBUG_PRINT(" : "FMT, ##ARGS)
#else
#define DEBUG_PRINT_PCU(FMT,ARGS...)
#endif


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Local Types
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class v4uint8_t property(vector uint8_t[4]);

#define PCU_NORMAL  0b0000
#define PCU_DEBUG   0b1111
#define PCU_LEAVE0  0b1110
#define PCU_LEAVE1  0b1100
#define PCU_LEAVE2  0b1000

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Storages
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

pcu_storages {
  reg r_booting         <uint1_t>;      // first cycle e.g. after reset
  reg r_fetched         <uint1_t>;

  // user_issue() to user_next_pc()
  trn t_stop_issue      <uint1_t>;

  reg r_state           <uint4_t>;
}

hw_init r_booting = 1;
hw_init r_fetched = 0;
hw_init r_state = PCU_NORMAL;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Issue Logic
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void trv32p5::user_issue() {
  DEBUG_PRINT_PCU("--------------------------------------------------------");

  addr PC_IF_l = pcr = PC;

  // Set link address - address of next instruction after jump-and-link
  // NOTE: jal/jalr stall the issue stage, hence the next instruction is
  // stalled in the fetch stage - its address is in the PC register.
  lnk_id = PC_IF_l;
  lnk_ex = PC_IF_l;

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Remove speculatively issued & fetched instructions (@ID @IF)

  bool br_EX = jump_of13_cd_sig; // only set if branch is taken
  bool flush_IF = br_EX;
  bool flush_ID = br_EX;

  if (flush_ID)
    kill_instr();

  // NOTE: Signals like hw_stall_sig() originating from a removed instruction
  // are not removed, they must be ignored.

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Determine Issue mode

  bool could_issue = issue_sig() && !(hw_stall_sig() && !flush_ID);
  // issue_sig(): cycles(N) -> false for N-1 cycles
  // hw_stall_sig(): false if valid instr@ID stalled due to hw_stall rule
  //   -> here: instr@ID is not advancing, hence don't issue
  // flush_ID: ignore stall if it comes from an instr. removed by a taken branch
  v4uint8_t ii = pm_rd;

  bool instr_avail = r_fetched;

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Handle debug mode

  // mode change opportunity if interruptible, when we could issue
  bool interruptible = could_issue;

  bool ocd_req_int = ocd_req && interruptible;

  if (r_state == PCU_NORMAL) {
    if (ocd_req_int)
      r_state = PCU_DEBUG;
  } else if (r_state == PCU_DEBUG) {
    if (!ocd_req)
      r_state = PCU_LEAVE0;
  } else if (r_state == PCU_LEAVE0) {
    r_state = PCU_LEAVE1;
  } else if (r_state == PCU_LEAVE1) {
    if (instr_avail)
      r_state = PCU_LEAVE2;
  } else if (r_state == PCU_LEAVE2) {
    r_state = PCU_NORMAL;
  }

  bool stop_issue =
      (r_state == PCU_NORMAL && ocd_req_int) ||
      (r_state == PCU_DEBUG) || (r_state == PCU_LEAVE0) ||
      (r_state == PCU_LEAVE1);

  ocd_mode =
      (r_state == PCU_DEBUG) || (r_state == PCU_LEAVE0) ||
      (r_state == PCU_LEAVE1 );

  if (ocd_exe) {
    v4uint8_t ii = ocd_instr_r = ocd_instr;
    issue_instr(0,0,ii[0],ii[1],ii[2],ii[3]);
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Issue instruction

  bool issue_ins = instr_avail && !flush_IF && could_issue && !stop_issue;

  if (issue_ins) {
    issue_instr(PC_IF_l,1,ii[0],ii[1],ii[2],ii[3]);

    // save addr of instr that we just issued
    PC_ID = PC_ID_w = PC_IF_l;

    DEBUG_PRINT_PCU("II: pm=%x ii=%x pcr=%d len=%d ",
                    pm_rd,ii,PC_IF_l,4);
  } else {
    DEBUG_PRINT_PCU("II stall: ii %d bf %d hw %d br %d",
                    !issue_sig(),!instr_avail,
                    hw_stall_sig() && !flush_ID,br_EX);
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // first fetch cycle after boot

  if (r_booting)
    r_booting = 0;

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // to user_next_pc()
  t_stop_issue = stop_issue;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Next PC Logic
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void trv32p5::user_next_pc() {
  addr PC_IF_l = pcr = PC;

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Handle non-linear control flow changes

  // control flow instructions
  bool br_EX   = jump_of13_cd_sig; // only set if branch is taken
  bool jalr_EX = jump_trgt_sig;
  bool jal_ID  = jump_of21_sig;

  // at most one source of change:
  PDG_ASSERT( ((uint8_t)br_EX + (jal_ID && !br_EX) + jalr_EX) <= 1 );

  DEBUG_PRINT_PCU("jump %d%d%d",br_EX,jalr_EX,jal_ID);

  // NOTE (jump) control signals originating from operations in the decode stage
  // are NOT removed when we use kill_instr() or when the decode stage is stalled.
  // These must be ignored. Here: if a branch is taken, we flush IF & ID, i.e.,
  // need to ignore signals from jumps in the decode stage.
  // Either disable (<sig> && !br_EX) or ignore (priority mux: if(..) else ...)

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Determine next PC value

  // next instr on incremental, i.e., linear path
  addr incr_pc = PC_IF_l + 4;

  bool leave_dbg = (r_state == PCU_LEAVE0);

  // Ordered by priority
  addr jump_pc = PC_IF_l; // booting (pipe empty)
  if (leave_dbg)    jump_pc = PC_IF_l;
  else if (br_EX)   jump_pc = jmp_tgt_EX;
  else if (jalr_EX) jump_pc = jmp_tgt_EX;
  else if (jal_ID)  jump_pc = jmp_tgt_ID;

  bool jump = br_EX || jal_ID || jalr_EX;

  addr next_pc = jump ? jump_pc : incr_pc;

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Are we advancing?

  // could advance on linear path in normal mode?
  bool could_issue = issue_sig() && !hw_stall_sig();

  // could advance on non-linear path in normal mode?
  // Ignore stalled jumps at decode stage
  bool could_jump = br_EX || jalr_EX || (jal_ID && !hw_stall_sig());

  // instruction available - ignore flush_IF (would imply could_jump)
  bool instr_avail = r_fetched;
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Update PC

  // stop linear path in debug mode, but allow regular jumps to change PC
  bool update_pc = (could_issue && instr_avail && !t_stop_issue) || could_jump;

  // Only update if we advance
  if (update_pc)
    PC = pcw = next_pc;

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Fetch

  bool ocd_issue_stall = (r_state == PCU_LEAVE1);

  // Use next_pc if we could issue or jump
  bool fetch_next = (could_issue && instr_avail && !ocd_issue_stall) || could_jump;

  // Otherwise, if stalled, fetch again at current address
  addr fetch_pc = (fetch_next) ? next_pc : PC_IF_l;

  // Do not fetch in debug mode (delayed by 1 cycle)
  bool fetch = (r_state != PCU_DEBUG);
  r_fetched = fetch;

  pm_addr = fetch_pc;
  if (fetch) {
    DEBUG_PRINT_PCU("fetch @ %d",fetch_pc);
    pm_rd`1` = PM[pm_addr]`1`;
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  DEBUG_PRINT_PCU("NPC: sigs=%d%d%d%d, pcr=%d, next_pc=%d",
                  hw_stall_sig(),jump_of13_cd_sig,jump_of21_sig,jump_trgt_sig,
                  PC_IF_l,next_pc);
}
