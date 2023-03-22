/*
-- Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include <tlm.h>
#include <scml2.h>
#include <systemc>

#include "Mdl_trv32p3_systemc.h"
#include "checkers_sc_time_gater.h"

#include "trv32p3_define.h"

SC_MODULE(Tlm2Memory)
{
public:
  tlm::tlm_target_socket<8> socket;

public:
  SC_HAS_PROCESS(Tlm2Memory);

  Tlm2Memory(sc_core::sc_module_name name, unsigned long long mem_size)
    : sc_core::sc_module(name)
    , socket    ("socket")
    , mAdapter  ("mAdapter", socket)
    , mMemory   ("mMemory", mem_size)
  {
    mAdapter(mMemory);
  }

private:
  scml2::tlm2_gp_target_adapter<8>      mAdapter;
  scml2::memory<unsigned char>          mMemory;
};


#define PM_SIZE (1ULL<<(PM_SIZE_NBIT)) /* in byte  */
#define DM_SIZE (1ULL<<(DM_SIZE_NBIT)) /* in byte */



SC_MODULE(trv32p3_top_sc)
{
public:
  sc_in_clk                             clock;
  sc_in<bool>                           reset;

  // ------------------------------------------
  // Internal connections
  // ------------------------------------------

  // PM
  Tlm2Memory                            pm;

  // DM
  Tlm2Memory                            dm;

  // time gater (connection to GUI)
  checkers_time_gater                   gclock;
  sc_signal<bool>                       scbreak_req;

  // TRV32P3 core
  trv32p3_sc                            trv32p3;

  // ------------------------------------------
  // Constructor
  // ------------------------------------------
public:
  SC_CTOR(trv32p3_top_sc)
    : clock             ("clock"        )
    , reset             ("reset"        )
    , pm                ("pm", PM_SIZE  )
    , dm                ("dm", DM_SIZE  )
    , trv32p3           ("TRV32P3")             // Core
    , gclock            ("gclock")              // time gater (connection to GUI)
  {
    // TRV32P3 connections
    trv32p3.clock               (clock          );
    trv32p3.reset               (reset          );

    trv32p3.scbreak_req         (scbreak_req    );

    // TRV32P3 - PM
    trv32p3.p_PMb               (pm.socket      );

    // TRV32P3 - DM
    trv32p3.p_DMb               (dm.socket      );

    // time gater (connection to GUI)
    gclock.clock                (clock          );
    gclock.break_req            (scbreak_req    );

  } // c'tor

}; // trv32p3_top_sc



Tcl_Interp* sc_interp = 0;

int sc_main(int, char*[])
{
  // Top module
  trv32p3_top_sc trv32p3_top("trv32p3_top");

  // signals
  sc_clock                       clock;
  sc_signal<bool>                reset;

  // Connections
  trv32p3_top.clock                 (clock          );
  trv32p3_top.reset                 (reset          );

  // Run
  reset = true;
  sc_start(sc_time(100, SC_NS));
  reset = false;
  sc_start();

  return 0;
}

