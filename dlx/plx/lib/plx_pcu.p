/*
-- File : plx_pcu.p
--
-- Contents : Definition of the PLX controller in PDG.
--
-- Copyright (c) 2014-2017 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

//#define     PRINT_PCU
#ifdef        PRINT_PCU
#define DEBUG_PRINT_PCU(FMT,ARGS...) DEBUG_PRINT("pcu: "FMT, ##ARGS)
#else
#define DEBUG_PRINT_PCU(FMT,ARGS...)
#endif



#include "common.h"

#define next_decl(stage)                                                    \
                                                                            \
addr plx::next(addr pc) {                                                   \
    bool abs_jump = vd_jr_trgt_##stage##_sig || vd_jalr_trgt_##stage##_sig  \
                                             || vd_jti_trgt_##stage##_sig;  \
    bool r26_jump = vd_jal_of26_##stage##_sig || vd_j_of26_##stage##_sig;   \
    bool r16_jump = vd_br_cnd_of16_##stage##_sig && cnd;                    \
                                                                            \
    addr next_pc = pc;                                                      \
         if (abs_jump) next_pc = trgt;                                      \
    else if (r26_jump) next_pc = next_pc + of26;                            \
    else if (r16_jump) next_pc = next_pc + of16;                            \
    else               next_pc = next_pc + 4;                               \
    return next_pc;                                                         \
}                                                                           \

#ifdef _THREADED

#include "isg/plx_pdg_encoding.p"

// This function was named 'set_bit', but this name clashed with the same function name in 'pcu.p'.
state set_bit1(state s, ctxt c, uint1 v) {
    state s1 = s;
    ctxt c1 = c;
    s1[c1] = v;
    return s1;
}

ctxt count_leading_zeros(state a, ctxt offset) {
    ctxt n = offset-1;
    uint1 seek = 1;
    for (uint16 i=0; i<(CSIZE-1); i++) {
        ctxt idx = offset+i; // wraps
        if (seek & a[idx]) {
            seek = 0;
            n = idx;
        }
    }
    return n;
}

pcu_storages {
    reg reg_booting<bool>;
    reg reg_valid_IF<bool>;
    reg reg_valid_ID<bool>;
    reg reg_valid_EX<bool>;
    reg reg_valid_ME<bool>;
    reg reg_cntxt_IF<ctxt>;
    reg reg_ocd_req<bool>;
    reg reg_spawn<uint2_t>;
    trn trn_step<addr>;
    trn trn_taken_ME<bool>;
    reg reg_j_ME1<bool>;
    reg reg_j_ME2<bool>;
    reg reg_debug_rdy<uint1>;
    reg reg_ocd_req_pending<uint1>;
    reg reg_debug_rdy_count<uint3_t>;
    reg reg_exception0<bool>;
    reg reg_exception1<bool>;
}

hw_init reg_debug_rdy = 1;
hw_init reg_booting = 1;

#define PROTECT_4_CYCLES
#define PROTECT_3_CYCLES
#define PROTECT_2_CYCLES
#define PROTECT_1_CYCLES

void plx::user_issue()
{
    DEBUG_PRINT_PCU("user_issue");

    trn_step = 4;
    trn_taken_ME = reg_j_ME2 && !dm_ack;
    reg_j_ME2 = reg_j_ME1;
    reg_j_ME1 = j_ME;
    ocd_exe_DM = reg_j_ME2 & !reg_valid_ME;

    // IF: issue

    bool issue_ins = 0;

    if (reg_spawn==3) {
        iword fi = pdg_encoding_jti_instr();
        issue_instr(0,0,fi[31:24],fi[23:16],fi[15:8],fi[7:0]);
        DEBUG_PRINT_PCU("  spawn - thread: %d, instr: %x", reg_cntxt_IF,fi);
        issue_ins = 1;
    } else
    if (reg_ocd_req) {
        if (ocd_exe) {
            iword fi = ocd_inst_r = ocd_instr;
            issue_instr(0,0,fi[31:24],fi[23:16],fi[15:8],fi[7:0]);
            /*
            Instruction travels through pipeline with false reg_valid_*
            Distinction is used to:
              1. avoid updating PC (except vd_jr_trgt_EX_sig to set PC)
              2. avoid updating ACK
              3. avoid non-blocking DM access (so blocking)
            */
        }
    } else
    if (reg_valid_IF && !ocd_req) {
        issue_ins = 1;
#ifdef PROTECT_3_CYCLES
        if (reg_valid_ME && (reg_cntxt_IF==context_id_ME) && trn_taken_ME) {
            issue_ins = 0;
            DEBUG_PRINT_PCU("  insert wait ME2");
            trn_step = 0; // retry same address
        }
#endif
#ifdef PROTECT_1_CYCLES
        if (reg_valid_ID && (reg_cntxt_IF==context_id_ID) && (j_ME|j_EX|j_ID|!issue_sig()|hw_stall_sig())) {
            issue_ins = 0;
            DEBUG_PRINT_PCU("  insert wait ME|EX|ID|MPY|DIV");
            trn_step = 0; // retry same address
        }
#endif
        if (issue_ins) {
            iword fi = pm_rd;
            pcr_IF = PC.context(reg_cntxt_IF);
            issue_instr(pcr_IF,1,fi[31:24],fi[23:16],fi[15:8],fi[7:0]);
            DEBUG_PRINT_PCU("  issue - thread: %d, instr: %x", reg_cntxt_IF,fi);
        }
    }

    bool l_stall_ID = reg_valid_ID && hw_stall_sig() && (!reg_valid_IF || (reg_cntxt_IF==context_id_ID));
    reg_valid_ID = issue_ins || l_stall_ID;
    context_IF   = reg_cntxt_IF;

    //----------- ocd_rdy logic ---------------------------
    bool debug_mode = ocd_req /* && interruptible*/;
    // lower ocd_rdy on ocd_exe or ocd mem accesses:
    if (debug_mode && ( ocd_exe || ocd_ld_PMb || ocd_st_PMb || ocd_ld_DMb || ocd_st_DMb )) {
        reg_debug_rdy = false;
        reg_debug_rdy_count = 0x7; // value 7 is upper bound + margin
    }
    // decrement rdy counter if not in wait_cycle
    if (reg_debug_rdy_count > 1) {
        reg_debug_rdy_count = reg_debug_rdy_count - 1;
    }
    if ((reg_debug_rdy_count==1) && !dm_wait) {
        // raise ocd_rdy when finished:
        reg_debug_rdy_count = 0;
        reg_debug_rdy = true;
    }
    // Handle ocd_req:
    // lower ocd_rdy on posedge ocd_req:
    if (ocd_req && !reg_ocd_req) {
        reg_ocd_req_pending = true;
        reg_debug_rdy = false;
    }
    // raise again when entered debug mode:
    if (reg_ocd_req_pending && debug_mode) {
        reg_ocd_req_pending = false;
        reg_debug_rdy = true;
    }
    reg_ocd_req = ocd_req;
    // output to debug_controller:
    ocd_rdy = reg_debug_rdy;
}

void plx::user_next_pc()
{
    if (reg_exception0) {
        DEBUG_PRINT("exception: ap_r>=3 && trn_step!=4");
        PDG_ERROR("Exception thrown.");
    }
    if (reg_exception1) {
        DEBUG_PRINT("exception: count>1");
        PDG_ERROR("Exception thrown.");
    }

    DEBUG_PRINT_PCU("user_next_pc");

    ctx_id = context_id_EX;

    reg_valid_EX = reg_valid_ID;
    reg_valid_ME = reg_valid_EX;

    bool r26_jump = vd_jal_of26_ID_sig || vd_j_of26_ID_sig;
    bool r16_jump = vd_br_cnd_of16_EX_sig;
    bool abs_jump = vd_jr_trgt_EX_sig || vd_jalr_trgt_EX_sig || vd_jti_trgt_EX_sig;

    // IF: update PC

    addr next_pc_IF = 0;
    bool jump_IF = (trn_step!=0);
    if (reg_valid_IF) {
        addr next_pc = pcr_IF = PC.context(reg_cntxt_IF);
        next_pc = next_pc + trn_step;
        next_pc_IF = next_pc;
        if (jump_IF && !ocd_req) {
          PC.context(reg_cntxt_IF) = pcw_IF = next_pc;
          DEBUG_PRINT_PCU("  PC[%d]=%d (IF)",reg_cntxt_IF,next_pc);
        }
    }

    // ID: update PC

    addr next_pc_ID = 0;
    bool jump_ID = 0;
    if (reg_valid_ID) {
        addr next_pc = pcr_ID = PC.context(context_id_ID);
        if (hw_stall_sig()) {
            reg_valid_EX = false;
            if (reg_valid_IF && (reg_cntxt_IF!=context_id_ID)) {
                DEBUG_PRINT_PCU("  kill_instr(ID)");
                kill_instr(ID);
                jump_ID = 1;
                next_pc = next_pc - 4; // reverse +4 of previous cycle
                PC.context(context_id_ID) = pcw_ID = next_pc;
                DEBUG_PRINT_PCU("  PC[%d]=%d (ID)",context_id_ID,next_pc);
            } else {
                // slot IF not taken by other thread
                DEBUG_PRINT_PCU("  stall_instr(ID)");
                //stall_instr(ID); cf. PDG manual, default action already on hw_stall_sig()
            }
        } else {
            if (vd_jal_of26_ID_sig) {
                DEBUG_PRINT_PCU("  pc_incremented=%d",next_pc);
                pc_incremented = next_pc;
            }
            if (r26_jump) {
                jump_ID = 1;
                next_pc = next_pc + of26 - 4;
                PC.context(context_id_ID) = pcw_ID = next_pc;
                DEBUG_PRINT_PCU("  PC[%d]=%d (ID)",context_id_ID,next_pc);
            }
        }
        next_pc_ID = next_pc;
    }

    // EX: update PC

    addr next_pc_EX = 0;
    bool jump_EX = r16_jump || abs_jump;
    if (reg_valid_EX || vd_jr_trgt_EX_sig /* set PC over OCD*/) {
        addr next_pc = pcr_EX = PC.context(context_id_EX);
        if (vd_jalr_trgt_EX_sig) {
            DEBUG_PRINT_PCU("  pc_incremented=%d",next_pc);
            pc_incremented = next_pc;
        }
        if (jump_EX) {
            if (abs_jump)                          next_pc = trgt;
            else if (vd_br_cnd_of16_EX_sig && cnd) next_pc = next_pc + of16 - 4;
            else /*false cnd*/                     jump_EX = 0;
            PC.context(context_id_EX) = pcw_EX = next_pc;
            DEBUG_PRINT_PCU("  PC[%d]=%d (EX)",context_id_EX,next_pc);
        }
        next_pc_EX = next_pc;
    }

    // ME: update PC

    addr next_pc_ME = 0;
    if (reg_valid_ME && reg_j_ME2) {
        ACK = ack_w = dm_ack; // not overwrite by load/store instruction via ocd_exe
        addr next_pc = pcr_ME = PC.context(context_id_ME);
        if (trn_taken_ME) {
            kill_instr(ME);
            next_pc -= 4; // retry
            PC.context(context_id_ME) = pcw_ME = next_pc;
            DEBUG_PRINT_PCU("  PC[%d]=%d (ME)",context_id_ME,next_pc);
        }
        next_pc_ME = next_pc;
    }

    // PF: next fetch

    bool fetch = 0;
    ctxt cntxt = reg_cntxt_IF;
    if (reg_spawn != 0) reg_spawn -= 1;
    if (reg_booting) {
        // no fetch
        reg_booting = 0;
    }
    else if ((cmd_r = host_CMD) && (reg_spawn == 0)) {
        reg_spawn = 3; // issue without fetch
        cntxt = ctx_r = host_CTX;
    }
    else if (ocd_req) {
        // no fetch
        cntxt = ocd_ctxt_r = ocd_ctxt; // drive ocd_pc_value with PC of active context (used at DBG_ADDR_REG read)
    }
    else if (reg_ocd_req) { // first cycle after ocd_req release
        cntxt = ocd_ctxt_r = ocd_ctxt;
        en_r = EN;
        fetch = en_r[cntxt] && !suspend[cntxt];
    }
    else {
        state cands = (en_r = EN) & ~suspend;
        if (true) {
            if (reg_spawn==2) cands = set_bit1(cands, reg_cntxt_IF , 0);
            if (reg_valid_ID && (j_EX|j_ME))
                              cands = set_bit1(cands, context_id_ID, 0);
        }
        ap_r=AP;
        if (ap_r>=1) {
            if (reg_valid_IF) cands = set_bit1(cands, reg_cntxt_IF , 0);
        }
        if (ap_r>=2) {
            if (reg_valid_ID) cands = set_bit1(cands, context_id_ID, 0);
        }
        if (ap_r>=3) {
            if (reg_valid_EX) cands = set_bit1(cands, context_id_EX, 0);
            if (trn_step != 4) { reg_exception0 = 1; }
        }
        if (ap_r>=4) {
            if (reg_valid_ME) cands = set_bit1(cands, context_id_ME, 0);
        }
        fetch = (cands != 0);
        cntxt = count_leading_zeros(cands,cntxt+1);
    }

    addr next_pc = pcr_PF = PC.context(cntxt);
    if (fetch) {
        uint32_t count=0;
#ifdef PROTECT_4_CYCLES
        if (reg_valid_ME && (cntxt==context_id_ME) && trn_taken_ME) {
            DEBUG_PRINT_PCU("  comb. upd. PC (ME)");
            next_pc = next_pc_ME;
            count += 1;
        }
#endif
#ifdef PROTECT_3_CYCLES
        if (reg_valid_EX && (cntxt==context_id_EX) && jump_EX) {
            DEBUG_PRINT_PCU("  comb. upd. PC (EX)");
            next_pc = next_pc_EX;
            count += 1;
        }
#endif
#ifdef PROTECT_2_CYCLES
        if (reg_valid_ID && (cntxt==context_id_ID) && jump_ID ) {
            DEBUG_PRINT_PCU("  comb. upd. PC (ID)");
            next_pc = next_pc_ID;
            count += 1;
        }
#endif
#ifdef PROTECT_1_CYCLES
        if (reg_valid_IF && (cntxt==reg_cntxt_IF) && jump_IF ) {
            DEBUG_PRINT_PCU("  comb. upd. PC (IF)");
            next_pc = next_pc_IF;
            count += 1;
        }
#endif
        if (count>1) { reg_exception1 = 1; }

        pm_rd`1` = PM[pm_addr = next_pc]`1`;
        DEBUG_PRINT_PCU("  fetch - thread: %d, addr: %d ",cntxt, next_pc);
    }
    reg_cntxt_IF = cntxt;
    reg_valid_IF = fetch;

    ocd_pc_value   = next_pc;
    ocd_pc_valid   = fetch;
    ocd_pc_context = cntxt;
}

#else // not _THREADED

pcu_storages {
    trn trn_next_pc<addr>;
    reg reg_booting<bool>;
}

hw_init reg_booting = 1;

next_decl(ID)

void plx::user_next_pc()
{
    addr next_pc = pcr_IF = PC;
    pc_incremented = pcr_IF + 4;
    if (reg_booting) reg_booting = 0;
    else next_pc = next(next_pc);
    PC = pcw_EX = next_pc;
    pm_rd = PM[pm_addr = next_pc];
    trn_next_pc = next_pc;
}

void plx::user_issue()
{
    issue_instr(trn_next_pc,1,pm_rd[31:24],pm_rd[23:16],pm_rd[15:8],pm_rd[7:0]);
}

#endif
