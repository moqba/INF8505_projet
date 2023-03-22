/*
-- File : trv32p3_pcu.p
--
-- Contents : Definition of the trv32p3 controller in PDG.
--
-- Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "trv32p3_define.h"

//#define PRINT_PCU
#ifdef        PRINT_PCU
#define DEBUG_PRINT_PCU(FMT,ARGS...)  DEBUG_PRINT_NAME(); DEBUG_PRINTF(".PCU cyc="); DEBUG_PRINT_CYCLES(); DEBUG_PRINT(" : "FMT, ##ARGS)
#else
#define DEBUG_PRINT_PCU(FMT,ARGS...)
#endif


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Local Types
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class ibuf_t property(vector uint8_t[8]);
class irow_t property(vector uint8_t[12]);


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Storages
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

pcu_storages {
  reg reg_booting       <uint1_t>;      // first cycle after reset
  reg reg_fetch         <uint1_t>;      // fetch in previous cycle
  reg FPC               <addr>;         // Fetch PC

  // instruction fetch buffer
  reg reg_ibuf          <ibuf_t>;
  reg reg_ibuf_cnt      <int5_t>;       // 0..8

  // user_issue() to user_next_pc()
  trn jump              <uint1_t>;
  trn jump_pc           <addr>;
}

hw_init reg_booting     = 1;
hw_init reg_fetch       = 0;
hw_init FPC             = 0;
hw_init reg_ibuf        = 0;
hw_init reg_ibuf_cnt    = 0;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Helper Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

uint32_t chop_lsb_side(uint64_t a) { return a[63:32]; }

// select 4 bytes from instr row
v4u8 select(irow_t row, uint5_t p)
{
  v4u8 x;
  PDG_ASSERT( p[1:0] == 0 && p <= 8 );
  x[0] = row[p[3:2]::"00"];
  x[1] = row[p[3:2]::"01"];
  x[2] = row[p[3:2]::"10"];
  x[3] = row[p[3:2]::"11"];
  return x;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Issue logic
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void trv32p3::user_issue()
{
  DEBUG_PRINT_PCU(" --------------------------------------------------------");

  pcr = PC;
  lnk_id = pcr;
  lnk_ex = pcr;

  addr PC_ID = trPC_ID = pif_PC;
  addr PC_EX = trPC_EX = pid_PC;

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // process control signals from pipeline

  bool br_EX   = jump_of13_cd_sig;
  bool jalr_EX = jump_trgt_sig;
  bool jal_ID  = jump_of21_sig     && !hw_stall_sig() && !br_EX;
  // hw_stall_sig(): ignore ctrl instr @ ID if stage ID is stalled
  // br_EX: ignore jal @ ID if killed by cjump @ EX

  // kill speculatively issued & fetched instructions (@ID @IF)
  bool flush_IF = br_EX;
  bool flush_ID = br_EX;
  if (flush_ID) kill_instr();

  // Could we issue?
  bool could_issue = issue_sig() && !(hw_stall_sig() && !flush_ID);
  // issue_sig(): cycles(N) -> false for N-1 cycles
  // hw_stall_sig(): false if valid instr@ID stalled due to hw_stall rule
  //   -> here: instr@ID is not advancing, hence don't issue
  // flush_ID: ignore stall if it comes from an instr. killed by a taken branch

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Instruction alignment

  DEBUG_PRINT_PCU("buf_cnt: %d, ibuf: %x",reg_ibuf_cnt,reg_ibuf);
  DEBUG_PRINT_PCU("IF: pm: (%d) %x",reg_fetch,pm_rd);

  //  ---------------------------------------------------------------------------
  //  | pm[3] | pm[2] | pm[1] | pm[0] | ibuf[IB-1] | ibuf[IB-2] | ... | ibuf[0] |
  //  ---------------------------------------------------------------------------
  //  | IB+3  | IB+2  | IB+1  | IB+0  | IB-1       | IB-2       |     | 0       |
  //  ---------------------------------------------------------------------------
  //                                  |-> cnt (0..8)
  //
  //  e.g. cnt=2         ^^      ^^      ^^           ^^ selected

  // select 4 bytes
  irow_t  row = pm_rd :: reg_ibuf;
  uint5_t idx = 8 - reg_ibuf_cnt;
  v4u8    ii  = select(row, idx); // ibuf[idx+3:idx]

  // if we didn't fetch, then ibuf should be sufficient (unless booting)
  PDG_ASSERT( reg_booting || reg_fetch || (reg_ibuf_cnt >= 4) );


  // Sufficient data available?
  int5_t avail   = reg_ibuf_cnt + (reg_fetch ? 4 : 0);
  bool buf_avail = reg_fetch || (reg_ibuf_cnt > 0);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Issue instruction

  // Should we issue?
  bool issue_ins = buf_avail && !flush_IF && could_issue;
  // buf_avail: fetched instr is available
  // flush_IF: discard speculatively fetched instr, if any

  // Issue selected instruction
  if (issue_ins) {
    issue_instr(pcr,1,ii[0],ii[1],ii[2],ii[3]);

    // save addr of instr that we just issued
    pif_PC = tif_PC = pcr;

    DEBUG_PRINT_PCU("II: ii=%x pcr=%d nw=%d ",ii,pcr,4);
  } else {
    DEBUG_PRINT_PCU("II stall: ii %d bf %d hw %d br %d",!issue_sig(),!buf_avail,(hw_stall_sig() && !flush_ID),br_EX);
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // process jumps

  jump = br_EX || jal_ID || jalr_EX || reg_booting;
  PDG_ASSERT( ((uint8_t)br_EX + jal_ID + jalr_EX) <= 1 );

  // determine jump target
  if      (br_EX)   jump_pc = PC_EX + of13_cd; // relative to instr
  else if (jal_ID)  jump_pc = PC_ID + of21;    // relative to instr
  else if (jalr_EX) jump_pc = trgt[31:1]::"0"; // force LSB to zero, accord. to RISC-V spec.
  else              jump_pc = pcr;             // reg_booting
  // jump & jump_pc -> user_next_pc() process

  DEBUG_PRINT_PCU("jump %d%d%d%d",br_EX,jal_ID,jalr_EX,reg_booting);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Update state

  // advance PC
  uint3_t pc_step = (issue_ins) ? 4 : 0;

  // update instruction buffer pointer
  int5_t new_ibuf_cnt = avail - pc_step;
  if (jump) // flush buffer
    new_ibuf_cnt = 0;
  reg_ibuf_cnt = new_ibuf_cnt;

  // update instruction buffer
  if (reg_fetch && (new_ibuf_cnt > 0))
    reg_ibuf = pm_rd :: chop_lsb_side(reg_ibuf);

  // assume no buffer overflow possible, fetched data can be stored
  PDG_ASSERT(new_ibuf_cnt <= 8);

  // update PC
  PC = pcw = (jump) ? jump_pc : (addr)(pcr + pc_step);
  // NOTE pc_step=0 possible while not issuing
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Next PC logic
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void trv32p3::user_next_pc()
{
  // elements in buffer + what was fetched in prev cycle
  uint5_t lead = reg_ibuf_cnt + (reg_fetch ? 4 : 0);

  // Determine next FPC and if we should fetch
  addr next_fpc = 0;
  bool fetch = 0;
  if (jump) {
    next_fpc = jump_pc[31:2]::"00";

    // buffer flushed; always fetch
    fetch = 1;
  }
  else { // linear
    next_fpc = (FPC[31:2]::"00") + 4;

    // fetch only if sufficient space available
    fetch = (lead < 8);
  }

  // update state
  if (fetch)
    FPC = next_fpc;
  reg_fetch = fetch;

  // send request to PM
  pm_addr = next_fpc;
  if (fetch) {
    DEBUG_PRINT_PCU("fetch @ %d",next_fpc);
    pm_rd`1` = PM[pm_addr]`1`;
  }

  // leave boot cycle after first fetch
  if (fetch)
    reg_booting = 0;

  DEBUG_PRINT_PCU("NPC: sigs=%d%d%d%d, pcr=%d, next_fpc=%d",
                  hw_stall_sig(),jump_of13_cd_sig,jump_of21_sig,jump_trgt_sig,
                  pcr,next_fpc);
}