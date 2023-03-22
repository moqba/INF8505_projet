/*
-- File : ilx_pcu.p
--
-- Contents : Definition of the ILX controller in PDG.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#include "ilx_define.h"

#include "ilx_threaded.h"

#define next_decl(stage)                                                    \
                                                                            \
addr ilx::next(addr pc) {                                                   \
    bool abs_jump = tex_lnk_jalr_trgt_##stage##_sig || vd_jr_trgt_##stage##_sig || vd_jti_trgt_##stage##_sig;  \
    bool r26_jump = tex_lnk_jal_of26_##stage##_sig  || vd_j_of26_##stage##_sig;   \
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

#include "isg/ilx_pdg_encoding.p"

pcu_storages {
    reg reg_valid_IF<bool>;
    reg reg_valid_ID<bool>;
    reg reg_valid_EX<bool>;
    reg reg_ctxt_IF<ctxt>;
    //reg reg_ocd_req<bool>;   // delayed ocd_req signal
    trn debug_mode<bool>;       // set when debug request is accepted
    reg reg_debug_mode<bool>;   // delayed debug_mode signal
}

hw_init reg_ctxt_IF = 3;

void ilx::user_issue()
{
    //DEBUG_PRINT("user_issue");


    bool interruptible = !(cmd_r = host_CMD);// || reg_debug_mode;
    // ignore interruptible while we are in debug mode

    debug_mode = ocd_req && interruptible ;

    // IF: issue

    pcr_IF = PC.context(reg_ctxt_IF);

    bool issue_ins = 0;
    ctxt issue_ctx = 0;

    ocd_pc_valid   = reg_valid_IF;
    ocd_pc_context = reg_ctxt_IF;
    ocd_pc_value   = pcr_IF;

    //reg_ocd_req = ocd_req;
    reg_debug_mode = debug_mode;
    if (debug_mode || reg_debug_mode) {
        if (ocd_exe) {
            iword fi = ocd_instr_r = ocd_instr;
            issue_instr(0,0,fi[31:24],fi[23:16],fi[15:8],fi[7:0]);
            issue_ctx = ocd_ctxt_r = ocd_ctxt;
        }
    } else

    if ((cmd_r = host_CMD) && ((ctx_r = host_CTX) == reg_ctxt_IF)) {
        iword fi = pdg_encoding_jti_instr();
        issue_instr(0,0,fi[31:24],fi[23:16],fi[15:8],fi[7:0]);
        //DEBUG_PRINT("  spawn - thread: %d, instr: %x", reg_ctxt_IF,fi);
        issue_ins = 1;
        issue_ctx = reg_ctxt_IF;
    } else

    if (reg_valid_IF) {
        iword fi = pm_rd;
        issue_instr(pcr_IF,1,fi[31:24],fi[23:16],fi[15:8],fi[7:0]);
        //DEBUG_PRINT("  issue - thread: %d, instr: %x", reg_ctxt_IF,fi);
        issue_ins = 1;
        issue_ctx = reg_ctxt_IF;
    }

    reg_valid_ID = issue_ins;
    context_IF   = issue_ctx;
}

next_decl(EX)

void ilx::user_next_pc()
{
    //DEBUG_PRINT("user_next_pc");

    // ID: delay

    reg_valid_EX = reg_valid_ID;

    if (reg_valid_ID) {

        bool kill_next_instr = (div_busy_0 && pl_ph_read)
                            || (div_busy_3 && pl_ph_write);
        bool kill_other_div  = (div_busy_2 && divide_id);

        //if (kill_next_instr) DEBUG_PRINT("too early for reading result");
        //if (kill_other_div ) DEBUG_PRINT("too early for other division");

        if (kill_next_instr || kill_other_div) {
            kill_instr();
            reg_valid_EX = false;
        }

    }

    // EX: update PC

    if (reg_valid_EX || vd_jr_trgt_EX_sig) {
        addr next_pc = pcr_EX = PC.context(context_id_EX);
        tex_lnk = pcr_EX + 4;
        next_pc = next(next_pc);
        PC.context(context_id_EX) = pcw = next_pc;
    }

    ctx_id = context_id_EX;

    // PF: next fetch

    ctxt next_ctxt = (reg_ctxt_IF == 3) ? 0 : (reg_ctxt_IF+1);
    bool dbg = (debug_mode || reg_debug_mode);
    if (dbg) next_ctxt = ocd_ctxt_r = ocd_ctxt;
    addr next_pc = pcr_PF = PC.context(next_ctxt);
    pm_ad = next_pc;
    en_r = EN;
    bool fetch = !debug_mode && en_r[next_ctxt];
    if (fetch) {
        pm_rd`1` = PM[pm_ad]`1`;
        //DEBUG_PRINT("  fetch - thread: %d, addr: %d ",next_ctxt, next_pc);
    }
    reg_ctxt_IF = next_ctxt;
    reg_valid_IF = fetch;
}

#else

pcu_storages {
    trn trn_next_pc<addr>;
    reg reg_booting<bool>;
}

hw_init reg_booting = 1;

next_decl(ID)

void ilx::user_next_pc()
{
    addr next_pc = pcr_IF = PC;
    tex_lnk = pcr_IF + 4;
    if (reg_booting) reg_booting = 0;
    else next_pc = next(next_pc);
    PC = pcw = next_pc;
    pm_rd = PM[pm_ad = next_pc];
    trn_next_pc = next_pc;
}

void ilx::user_issue()
{
    issue_instr(trn_next_pc,1,pm_rd[31:24],pm_rd[23:16],pm_rd[15:8],pm_rd[7:0]);
}

#endif
