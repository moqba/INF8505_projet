/*
-- Copyright (c) 2019-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

#include "trv32p5_define.h"

#ifdef NOGUI
#include "Mdl_trv32p5_uicore.h"
#include "trv32p5_sc_no_gui_systemc.h"
#else
#include "trv32p5_sc_systemc.h"
#endif

template <int w>
SC_MODULE(Memory)
{
public:
  tlm::tlm_target_socket<w> socket;

public:
  SC_HAS_PROCESS(Memory);

  Memory(sc_core::sc_module_name name, unsigned long long sz) :
    sc_core::sc_module(name),
    socket("socket"),
    mAdapter("mAdapter", socket),
    mMemory("mMemory", sz * ((w + 1) / 8)) {

    mAdapter(mMemory);
  }

private:
  scml2::tlm2_gp_target_adapter<w> mAdapter;
  scml2::memory<unsigned char>     mMemory;
};

int sc_main(int argc, char** argv) {

  sc_clock clock;

#ifdef NOGUI
  if (argc < 2 || argc > 3) {
    std::cerr << "Usage: " << argv[0] << " <program> [<chess_report_filename>]" << std::endl;
    return 1;
  }

  trv32p5_load_program_args_sc pl_args(argv[1]);
  pl_args.cycle_count_breakpoints = 1;

  trv32p5_sc iss("iss", pl_args);

  if (argc == 3) {
    std::string fnm(argv[2]);
    chkapi_l_chess_report_set_file_name(iss.uicore, fnm);
  }

#else
  trv32p5_sc iss("iss");
#endif

  Memory<32> eDM("eDM", (1<<(MEM_eDM_SZ_NBIT)));

  sc_signal<bool> reset;

  iss.p_eDM.bind(eDM.socket);

  iss.clock(clock);
  iss.reset(reset);

#ifndef NOGUI
  // wait for the debugger to join before the actual run
  ChkrsOSCIDebugControl::instance()->startAfterDebuggerJoins();
#endif

  reset = 0;
  sc_start(sc_time(100, SC_NS));
  reset = 1;
  sc_start();

  return 0;
}
