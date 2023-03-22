/*
-- File : dm.p
--
-- Contents : Definition of the trv32p3 DM IO interface.
-- This IO interfaces merges the aligned access from DMb DMh DMw
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

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ DM IO Interface
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Two chained io_interface modules
//  1) merge byte/half/word/double accesses
//  2) write back buffer


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Merge byte/half/word/double accesses
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// this IO Interface
// * merges the memory record aliases
// * interfaces to a single-cycle 32b wide memory with byte enables
// * supports only aligned addresses
// * has an external interface with word addresses

// NOTE
// * RTL model uses only dm_addr[DM_SIZE_NBITS-1:0] (see trv32p3_define.h)
//   MSBs are ignored.

io_interface dm_merge (DMb) {

  // Assumption:
  // nml_side {
  //    mem DMb [SIZE,1]<w08,addr> access {
  //      ld_dmb`0`: dmb_rd `1` = DMb[dm_addr `0`] `1`;
  //      st_dmb`0`: DMb[dm_addr`0`]`1` = dmb_wr`1`;
  //    };
  //    mem DMh [SIZE,2]<w16,addr> alias DMb access {
  //      ld_dmh`0`: dmh_rd `1` = DMh[dm_addr `0`] `1`;
  //      st_dmh`0`: DMh[dm_addr`0`]`1` = dmh_wr`1`;
  //    };
  //    mem DMw [SIZE,4]<w32,addr> alias DMb access {
  //      ld_dmw`0`: dmw_rd `1` = DMw[dm_addr `0`] `1`;
  //      st_dm`0`w: DMw[dm_addr`0`]`1` = dmw_wr`1`;
  //    };
  //  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ External interface
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  trn st_wdm<v4u1>; // byte write mask

  mem wDM [2**(DM_SIZE_NBIT-2)] <v4u8,addr> access {
    ld_wdm`0`: wdm_rd`1`           = wDM[wdm_addr`0`]`1`;
    st_wdm`0`: wDM[wdm_addr`0`]`1` = wdm_wr`1`;
  };


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Local storage
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  reg col_ff<uint2_t>; hw_init col_ff = 0;
  reg st_ff<uint3_t>;  hw_init st_ff = 0;


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Process response from memory
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  process process_result() {

    // dmb_rd, dmh_rd, dmw_rd
    t8u b0 = wdm_rd[col_ff];                    // 0, 1, 2, 3
    // dmh_rd, dmw_rd
    t8u b1 = wdm_rd[col_ff[1]::"1"];            // 1, 3

    dmw_rd = wdm_rd[3]::wdm_rd[2]::b1::b0;
    dmh_rd = b1::b0;
    dmb_rd = b0;

  }


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Process request from core
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  process process_request() {

    // split address
#ifdef __go__ // For RTL only
    addr    row = dm_addr[DM_SIZE_NBIT-1:2];
#else // ISS
    addr    row = dm_addr[31:2];
#endif
    uint2_t col = dm_addr[1:0];

    // addr (read or write)
    wdm_addr = row;

    // read enable
    ld_wdm = ld_dmw | ld_dmh | ld_dmb;

    // register read info
    col_ff = col;

    // write enable
    uint4_t          t1= "0000";
    if      (st_dmw) t1= "1111";
    else if (st_dmh) t1= "0011" << (col[1]::"0");
    else if (st_dmb) t1= "0001" << (col);
    st_wdm = t1;

    // write data
    if (st_ff[2]) {
      wdm_wr = dmw_wr;
    } else if (st_ff[1]) {
      wdm_wr = dmh_wr::dmh_wr;
    } else if (st_ff[0]) {
      wdm_wr = dmb_wr::dmb_wr::dmb_wr::dmb_wr;
    }

    // delay store control
    st_ff = st_dmw :: st_dmh :: st_dmb;

  }


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ DC Synthesis embedded options
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  vlog synthesis_options() {%

    // Ungroup this design. It is in the critical path.
    %% synopsys dc_tcl_script_begin
    %% set_ungroup [current_design]
    %% synopsys dc_tcl_script_end

  %}


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Debug access
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  void dbg_access_DMb(AddressType a, w08& val, bool read) {
    addr    row = a[31:2];
    uint2_t col = a[1:0];

    t8u v = val;
    dbg_access_wDM(row,col,v,read);
    val = v;
  }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Writeback buffer
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

io_interface dm_wbb (wDM) {

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ External interface
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  trn st_edm<v4u1>; // byte write mask

  mem eDM [2**(DM_SIZE_NBIT-2)] <v4u8,addr> access {
    ld_edm`0`: edm_rd`1`           = eDM[edm_addr`0`]`1`;
    st_edm`0`: eDM[edm_addr`0`]`0` = edm_wr`0`;
  };


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Local storage
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  reg edm_addr_ff<addr>;          hw_init edm_addr_ff = 0;       //delay store address
  reg edm_strb_ff<v4u1>;          hw_init edm_strb_ff = 0;       //delay store strobe
  reg st_edm_ff<uint1_t>;         hw_init st_edm_ff = 0;         //delay store control
  reg edm_data_ff<v4u8>;          hw_init edm_data_ff = 0;       //write-back buffer
  reg edm_wbb_ff<uint1_t>;        hw_init edm_wbb_ff = 0;        //buffer contains data
  reg edm_addr_match_ff<uint1_t>; hw_init edm_addr_match_ff = 0; //load addr matches wbb


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Process response from memory
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  process process_result() {
    bool byp = (edm_wbb_ff && edm_addr_match_ff);
    uint4_t sel = edm_strb_ff & (byp::byp::byp::byp);
    wdm_rd =
        (sel[3] == 0 ? edm_rd[3] : edm_data_ff[3]) ::
        (sel[2] == 0 ? edm_rd[2] : edm_data_ff[2]) ::
        (sel[1] == 0 ? edm_rd[1] : edm_data_ff[1]) ::
        (sel[0] == 0 ? edm_rd[0] : edm_data_ff[0]);
  }


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Process request from core
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  process process_request() {
    // issue load request
    ld_edm = ld_wdm;
    if (ld_wdm) {
      edm_addr = wdm_addr;
      edm_addr_match_ff = (wdm_addr == edm_addr_ff);
    }

    // process new and pending store requests
    st_edm = (t1u)0;
    if (ld_wdm) {
      if (st_edm_ff) {
        // cannot issue store request now; buffer data instead
        edm_data_ff = wdm_wr;
        edm_wbb_ff = 1;
      }
    }
    else {
      if (edm_wbb_ff) {
        // issue pending store request
        st_edm   = edm_strb_ff;
        edm_addr = edm_addr_ff;
        edm_wr   = edm_data_ff;
        edm_wbb_ff = 0;
      }
      else if (st_edm_ff) {
        // issue store request from previous cycle
        st_edm   = edm_strb_ff;
        edm_addr = edm_addr_ff;
        edm_wr   = wdm_wr;
      }

      if (st_wdm != 0) {
        // delay new store request
        edm_addr_ff = wdm_addr;
        edm_strb_ff = st_wdm;
      }
    }
    // delay store control
    st_edm_ff = (st_wdm != 0);
  }


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ DC Synthesis embedded options
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  vlog synthesis_options() {%

    // Ungroup this design. It is in the critical path.
    %% synopsys dc_tcl_script_begin
    %% set_ungroup [current_design]
    %% synopsys dc_tcl_script_end

  %}


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Debug access
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  void dbg_access_wDM(AddressType a, VectorIndexType elem, t8u& val, bool read) {
    if (edm_wbb_ff && edm_addr_ff == a) {
      // read wbb
      v4u8 tmp_wbb;
      dbg_access_edm_data_ff(tmp_wbb,/*read*/true);
      if (!read && edm_strb_ff[elem]) {
        // update wbb
        tmp_wbb[elem] = val;
        dbg_access_edm_data_ff(tmp_wbb,/*read*/false);
      }
      // access eDM
      dbg_access_eDM(a,elem,val,read);
      // select eDM or wbb
      val = edm_strb_ff[elem] ? tmp_wbb[elem] : val;
    } else {
      // access eDM
      dbg_access_eDM(a,elem,val,read);
    }
  }
}
