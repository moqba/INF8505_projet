/*
-- File : dm.p
--
-- Contents : Definition of the trv32p5 DM IO interface.
-- This IO interfaces merges the aligned access from DMb DMh DMw
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

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ DM IO Interface
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// One io_interface unit
//  1) merge byte/half/word accesses


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Merge byte/half/word accesses
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// This IO Interface
// * merges the memory record aliases
// * interfaces to a single-cycle 32b wide memory with byte enables
// * supports only aligned addresses
// * has an external interface with word addresses

io_interface dm_merge (DMb) {

  // Assumption:
  // nml_side {
  //   mem DMb [SIZE,1]<w08,addr> access {
  //     ld_dmb`0`: dmb_rd`1` = DMb[dm_addr`0`]`1`;
  //     st_dmb`0`: DMb[dm_addr`0`]`0` = dmb_wr`0`;
  //   };
  //   mem DMh [SIZE,2]<w16,addr> alias DMb access {
  //     ld_dmh`0`: dmh_rd`1` = DMh[dm_addr`0`]`1`;
  //     st_dmh`0`: DMh[dm_addr`0`]`0` = dmh_wr`0`;
  //   };
  //   mem DMw [SIZE,4]<w32,addr> alias DMb access {
  //     ld_dmw`0`: dmw_rd`1` = DMw[dm_addr`0`]`1`;
  //     st_dmw`0`: DMw[dm_addr`0`]`0` = dmw_wr`0`;
  //   };
  // }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ External Interface
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  trn st_edm <uint4_t>; // byte write mask

  mem eDM [2**(MEM_eDM_SZ_NBIT)] <v4u8,addr> access {
    ld_edm`0`: edm_rd`1`           = eDM[edm_addr`0`]`1`;
    st_edm`0`: eDM[edm_addr`0`]`0` = edm_wr`0`;
  };


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Local Storage
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  reg col_ff <uint2_t>; hw_init col_ff = 0;


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Process response from memory
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  process process_result() {

    // dmb_rd, dmh_rd, dmw_rd
    u08 b0 = edm_rd[col_ff];                    // 0, 1, 2, 3
    // dmh_rd, dmw_rd
    u08 b1 = edm_rd[col_ff[1]::"1"];            // 1, 3

    dmw_rd = edm_rd[3]::edm_rd[2]::b1::b0;
    dmh_rd = b1::b0;
    dmb_rd = b0;

  }


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Process request from core
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  process process_request() {

    // split address
    addr    row = dm_addr[31:2];
    uint2_t col = dm_addr[1:0];

    // addr (read or write)
    edm_addr = row;

    // read enable
    ld_edm = ld_dmw | ld_dmh | ld_dmb;

    // register read info
    col_ff = col;

    // write enable
    uint4_t          t1 = "0000";
    if      (st_dmw) t1 = "1111";
    else if (st_dmh) t1 = "0011" << (col[1]::"0");
    else if (st_dmb) t1 = "0001" << (col);
    st_edm = t1;

    // write data
    if (st_dmw) {
      edm_wr = dmw_wr;
    } else if (st_dmh) {
      edm_wr = dmh_wr::dmh_wr;
    } else if (st_dmb) {
      edm_wr = dmb_wr::dmb_wr::dmb_wr::dmb_wr;
    }

  }


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ DC Synthesis embedded options
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef SYNTHESIS_NO_UNGROUP
  vlog synthesis_options() {%

    // Ungroup this design. It is in the critical path.
    %% synopsys dc_tcl_script_begin
    %% set_ungroup [current_design]
    %% synopsys dc_tcl_script_end

  %}
#endif


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Debug Access
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  void dbg_access_DMb(AddressType a, w08& val, bool read) {
    addr    row = a[31:2];
    uint2_t col = a[1:0];

    u08 v = val;
    dbg_access_eDM(row,col,v,read);
    val = v;
  }
}
