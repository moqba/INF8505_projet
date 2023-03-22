/*
-- File : blx_pcu.p
--
-- Contents : Definition of the BLX controller in PDG.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#include "blx_define.h"

/***************************************************************/
// Branch predictor (BPD) types

#define BTB_ENTRIES 64
typedef uint6_t     btb_idx_t;
typedef uint64_t    btb_idx_oh_t;   // one hot
typedef uint32_t    pc_t;

// Control flow instruction types
/* enum cfi_t {
    BRANCH, JUMP
}; */
typedef uint1_t     cfi_t;
#define JUMP    0
#define BRANCH  1

// Branch target buffer line type
struct btb_line_t {
    uint1_t     vld;        // valid
    addr        epc_tag;    // Entry PC Tag
    addr        tgt;        // Target PC
    cfi_t       cfi;        // CFI type
};

// BTB memory type
class btb_t property (vector btb_line_t [64]);

// BTB hit info type
struct btb_hit_info_t {
    uint1_t     vld;        // Valid
    btb_idx_t   idx;        // Index of table hit
    pc_t        tgt;        // Predicted PC
    uint1_t     tak;        // Predicted outcome (taken?)
};

/***************************************************************/


pcu_storages {
  reg reg_booting<bool>;

  reg PC_ID<w32>;
  reg PC_EX<w32>;

  trn killed_stalled<bool>;         // killed instr@ID that caused hw_stall -> ignore hw_stall

  // Branch target buffer
  reg btb<btb_t>;

  // Pipeline BTB hit info
  reg btb_hit_ID<btb_hit_info_t>;
  reg btb_hit_EX<btb_hit_info_t>;

  reg btb_idx_next  <btb_idx_t>;

  trn t_issue_ins   <bool>;           // move instr. from IF to ID

  // BTB Update handling
  trn update_btb    <uint1_t>;
  trn btb_upd_idx   <btb_idx_t>;

  //
  trn prv_hit       <uint1_t>;
  trn prv_idx       <btb_idx_t>;

  trn prd_vld       <uint1_t>;        // prediction valid
  trn prd_tgt       <pc_t>;           // predicted target
  trn prd_tak       <uint1_t>;        // predicted taken
  trn prd_cfi       <cfi_t>;          // predicted CFI type


  trn cfi_rpl       <uint1_t>;        // Replay CFI
  trn cfi_tgt       <addr>;           // Target address of CFI

  trn bpd_kill_IF   <uint1_t>;
  trn bpd_kill_ID   <uint1_t>;
//
  reg reg_debug_mode<bool>;   // delayed debug_mode signal
  trn debug_mode<bool>;       // set when debug request is accepted
  reg r1_ocd_exe<bool>;
  reg r2_ocd_exe<bool>;
}

hw_init reg_booting = 1;

// BTB
hw_init btb = 0;

hw_init btb_idx_next = 0;
/// --------------------
hw_init reg_debug_mode = 0;

void blx::user_issue()
{
    w08  fi0,  fi1,  fi2,  fi3; // fetched instruction bytes
//
    bool interruptible = !hw_stall_sig() && (!(ds1 || ds2) || reg_debug_mode);

    // ignore interruptible while we are in debug mode
    debug_mode = ocd_req && interruptible;
//
    killed_stalled = false;

    pcr = PC;
    tid_lnk = PC_ID+4;
    tex_lnk = PC_EX+4;

    // hw_stall_sig(): low if instr@ID stalled due to hw_stall rule
    // in_stall_cycle(): low if instr@ID stalled due to stall_instr()
    bool ID_stalled = hw_stall_sig();

    // issue_sig(): cycles(N) -> low for N-1 cycles
    // hw_stall_sig(): low if instr@ID stalled due to hw_stall rule
    bool IF_stalled = !issue_sig() || ID_stalled;

    bool stop_issue = reg_booting || debug_mode || reg_debug_mode;

    // ----------------------------------------
    // BPD
    // disable BPD while booting (and in debug mode)
    bool disable_bpd = stop_issue;

    // If we pass the fetched instruction to the decode stage, then run branch prediction for its PC value
    bool run_bpd = !IF_stalled && !disable_bpd;

    // ----------------------------------------
    // BTB @ IF stage
    // ++ Detect BTB Hit
    uint1_t     btb_hit = 0;    // BTB hit
    btb_idx_t   btb_idx = 0;    // BTB hit index
    // trn shadows, to read/write those variables
    pc_t        _prd_tgt = 0;   // Predicted target
    cfi_t       _prd_cfi = 0;   // Predicted CFI type
    //
    prd_vld = false;
    prd_tak = true;             // default: Predicted taken

    //
    if (run_bpd) {  // only when instr@IF might advance to ID
        // EPC tag match
        pc_t            pc_tag = pcr;
        btb_idx_oh_t    cnt = 0;        // DEBUG
        //
        for (btb_idx_t i = BTB_ENTRIES-1; i >= 0; i--) {
            btb_line_t  line = btb[i];
            uint1_t     tag_hit = line.vld & (line.epc_tag == pc_tag);
            // Use the fact that there is at most one hit
            btb_hit  |= tag_hit;
            btb_idx  |= i           & (tag_hit ? ~(btb_idx_t)0  : 0);
            _prd_tgt |= line.tgt    & (tag_hit ? ~(pc_t)0       : 0);
            _prd_cfi |= line.cfi    & (tag_hit ? ~(cfi_t)0      : 0);
            //
            cnt += tag_hit; // DEBUG
        }
        PDG_ASSERT(cnt <= 1);   // DEBUG

        if (btb_hit) { // BTB hit, make a prediction
            // TODO depending on hit type, change prd_tak (e.g. for conditional branches)
            // and/or invalidate prediction if needed
            prd_vld = true;
            DEBUG_PRINT("BTB: Hit @ PC %d Idx %d CFI %d Tgt %d",pcr,btb_idx,_prd_cfi,_prd_tgt);
        }

    }

    // assign shadows to trn's
    prd_tgt = _prd_tgt;
    prd_cfi = _prd_cfi;


    // ++ Process CFIs in ID or EX stage
    // detect type
    uint1_t is_jmp_at_ID  = (vd_j_of26_ID_sig || tid_lnk_jal_of26_ID_sig);
    uint1_t is_jmp_at_EX  = (vd_jr_trgt_EX_sig || tex_lnk_jalr_trgt_EX_sig);
    uint1_t is_branch     = vd_br_cnd_of16_EX_sig;
    uint1_t br_taken      = vd_br_cnd_of16_EX_sig && cnd;   // read cnd only if vd_br_cnd_of16_EX_sig set
    // per-stage CFI detect
    uint1_t is_cfi_at_ID  = is_jmp_at_ID;
    uint1_t is_cfi_at_EX  = is_jmp_at_EX | is_branch;

    // Request BTB update
    uint1_t upd_req_ID = false;
    uint1_t upd_req_EX = false;
    // Request replay
    uint1_t replay_ID = false;
    uint1_t replay_EX = false;

    // NOTE avoid reading data transitories (of21,...) from a killed JAL @ ID
    // When we kill a JAL @ ID, jump_of21_sig remains set, but of21 are uninitialized

    // ++ process CFI @ ID
    if (is_cfi_at_ID && ! ID_stalled) { // CFI @ ID = unconditional jump
        upd_req_ID = ! btb_hit_ID.vld;
        replay_ID  = ! btb_hit_ID.vld;
    }

    // ++ process CFI @ EX
    if (is_cfi_at_EX) { // && ! in_stall_cycle(EX)
        if (is_jmp_at_EX) {
            upd_req_EX = ! btb_hit_EX.vld || (btb_hit_EX.tgt != (pc_t)trgt);
            replay_EX  = upd_req_EX;
        } else if (is_branch) {                                             // conditional jump (=branch)
            upd_req_EX = ! btb_hit_EX.vld && br_taken;                      // no hit and not taken = no update
            replay_EX  = upd_req_EX || (btb_hit_EX.vld && (btb_hit_EX.tak != br_taken));
        } else PDG_ASSERT(false);
    }

    // Kill IF (=no instr issue) on replay
    // Kill ID on replay

    bpd_kill_IF = replay_ID || replay_EX;
    bpd_kill_ID = replay_EX;


    if (bpd_kill_IF) {
        prd_vld = false;    // suppress any prediction originating from the instr @ IF
        if (replay_EX) DEBUG_PRINT("** BPD kill IF due to CFI @ %d in EX", PC_EX);
        else           DEBUG_PRINT("** BPD kill IF due to CFI @ %d in ID", PC_ID);
    }

    // kill instr@ID if speculated && ( jmp@EX || taken branch @ EX )
    if (bpd_kill_ID) {
        kill_instr();                       // instr @ ID
        killed_stalled = hw_stall_sig();    // ignore stall if it comes from instr @ ID that we just killed
        upd_req_ID = false;                 // suppress upd.req. coming from killed instr @ ID
        DEBUG_PRINT("** BPD kill ID due to CFI @ %d in EX", PC_EX);
    }

    // Replay after incorrect execution of control flow instruction
    cfi_rpl = replay_ID || replay_EX;   // to user_next_pc()


    // compute target addr, forwarded to user_next_pc
    cfi_tgt = 0; // avoid latch
    if (replay_EX) { // EX has higher priority
        if (is_jmp_at_EX) cfi_tgt = trgt;
        else if(br_taken) cfi_tgt = PC_EX + of16;
        else              cfi_tgt = PC_EX + 4;
    } else if (replay_ID) cfi_tgt = PC_ID + of26;

    if (is_cfi_at_ID && !replay_ID) DEBUG_PRINT("## Pred. OK CFI @ %d in ID", PC_ID);
    if (is_cfi_at_EX && !replay_EX) DEBUG_PRINT("## Pred. OK CFI @ %d in EX", PC_EX);

    if (!disable_bpd && (upd_req_ID || upd_req_EX)) {
        update_btb = true; // DEBUG

        pc_t  entry_pc;
        cfi_t cfi_type;
        if (upd_req_EX) {               // JALR, BR @ EX
            entry_pc  = PC_EX;
            prv_hit   = btb_hit_EX.vld;
            prv_idx   = btb_hit_EX.idx;
            if (is_jmp_at_EX) cfi_type = JUMP;
            else              cfi_type = BRANCH;
        } else {                        // JAL @ ID
            entry_pc  = PC_ID;
            prv_hit   = btb_hit_ID.vld;
            prv_idx   = btb_hit_ID.idx;
            cfi_type  = JUMP;
        }

        btb_idx_t _upd_idx;
        // determine update index
        if (prv_hit) {                  // update prev. hit
            _upd_idx = prv_idx;
        } else {
            _upd_idx = btb_idx_next;    // TODO Pseudo-LRU
            btb_idx_next += 1;          // w/ overflow
        }
        btb_upd_idx = _upd_idx;         // DEBUG

        // Table Update
        btb_t       _btb = btb;               // read-modify-write vector type
        btb_line_t  _line = _btb[_upd_idx];   // read-modify-write struct type
        //
        _line.vld       = 1;
        _line.cfi       = cfi_type;
        _line.epc_tag   = entry_pc;  // CFI entry address
        _line.tgt       = cfi_tgt;   // CFI target address
        //
        _btb[_upd_idx] = _line;
        btb = _btb;

        DEBUG_PRINT("++ BTB Upd: %d EPC %d CFI %d Tgt %d  ID %d EX %d",_upd_idx,entry_pc,cfi_type,cfi_tgt,upd_req_ID,upd_req_EX);
    }

    // BTB end ------------------------

    t_issue_ins = 0;    // track if we shift IF to ID

    if (ocd_exe) {
        iword instr =  ocd_instr_r = ocd_instr;
        fi0 = instr[31:24];
        fi1 = instr[23:16];
        fi2 = instr[15:8];
        fi3 = instr[7:0];
        issue_instr(0, 0, fi0, fi1, fi2, fi3);
    }
    if (!IF_stalled && !stop_issue && !bpd_kill_IF) {
        iword instr =  pm_rd;
        fi0 = instr[31:24];
        fi1 = instr[23:16];
        fi2 = instr[15:8];
        fi3 = instr[7:0];
        issue_instr(pcr, 1, fi0, fi1, fi2, fi3);
        DEBUG_PRINT("II :  %d  %x",pcr,instr);
        t_issue_ins = 1;    // pass instr from IF to ID
    }

    // pipeline BTB info
    if (t_issue_ins) {      // IF not stalled
       PC_ID     = pcr = PC;
       //
       btb_hit_info_t _hit = (btb_hit_info_t)0;
       _hit.vld = btb_hit;
       _hit.idx = btb_idx;
       if (prd_vld) {
           _hit.tgt = prd_tgt;
           _hit.tak = prd_tak;
       }
       btb_hit_ID = _hit;
    }
    if (!ID_stalled) { // ID not stalled, TODO CHECK
       PC_EX      = PC_ID;
       btb_hit_EX = btb_hit_ID;
    }
    ocd_mod = reg_debug_mode;
    reg_debug_mode = debug_mode;
    r1_ocd_exe = ocd_exe; r2_ocd_exe = r1_ocd_exe;
}

void blx::user_next_pc()
{
 // next PC computation
    bool fetch = !debug_mode;

    addr default_pc = pcr; // default: no increment
    if (r2_ocd_exe && vd_jr_trgt_EX_sig) // only in debug mode
      default_pc = trgt;
    addr next_pc = default_pc;
    bool ID_stalled = hw_stall_sig();

    bool update_pc = !ID_stalled || killed_stalled;
    if (debug_mode || reg_debug_mode) {
      update_pc=0;
    }

    if (update_pc) {                    // prefetch not stalled
        if (prd_vld && prd_tak) {       // Prediction valid, and predicted taken
            next_pc = prd_tgt;
            DEBUG_PRINT("BTB: Start speculation, NPC %d",next_pc);
        } else if (cfi_rpl) {  // Replay
            next_pc = cfi_tgt;
            DEBUG_PRINT("BTB: Replay, NPC %d",next_pc);
        } else if (!reg_booting) {
            // PC increment disabled while booting
            next_pc = pcr + 4;
        }
    }

    PC = pcw = next_pc;

    if (reg_booting) reg_booting = 0;

 // instruction pre fetch

    if (fetch) {
      pm_rd`1` = PM[pm_ad = next_pc]`1`;
    }

    bool abs_jump = (vd_jr_trgt_EX_sig || tex_lnk_jalr_trgt_EX_sig);
    bool r26_jump = (vd_j_of26_ID_sig || tid_lnk_jal_of26_ID_sig);
    bool r16_jump = vd_br_cnd_of16_EX_sig && cnd;

    DEBUG_PRINT("NPC : pcr=%d : sigs=%d%d%d%d : npc=%d",
           pcr,hw_stall_sig(),abs_jump,r26_jump,r16_jump,next_pc);
}





