/*
-- File : pm.p
--
-- Contents : Definition of the trv32p3 PM IO interface.
-- This IO interfaces translates byte to word addresses for PM
--
-- Copyright (c) 2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "trv32p3_define.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ PM IO Interface
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Functionality
// * Byte to word addresses
// * Limit address range to 0..2**PM_SIZE_NBIT-1

io_interface pm (PMb) {

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ External interface
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  mem ePM [2**(PM_SIZE_NBIT-2)] <v4u8,addr> access {
    ld_epm`0` : epm_rd`1` = ePM[epm_addr`0`]`1`;
  };


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Process response from memory
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  process process_result() {
    pm_rd = epm_rd;
  }


  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Process request from core
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  process process_request() {
    ld_epm = ld_pm;
#ifdef __go__ // For RTL only
    epm_addr = pm_addr[PM_SIZE_NBIT-1:2];
#else // ISS
    epm_addr = pm_addr[31:2];
#endif
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

  void dbg_access_PMb(AddressType a, t8u& val, bool read) {
    addr    row = a[31:2];
    uint2_t col = a[1:0];

    t8u v = val;
    dbg_access_ePM(row,col,v,read);
    val = v;
  }

}
