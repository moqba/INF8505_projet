/*
-- File : pdc_commands.h
--
-- Contents : Declaration of PDC command class,
--            interfacing with the physical OCD link (jtag_socket library).
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef _pdc_commands_h
#define _pdc_commands_h

#include "checkers_errors.h"
#include "pdc_opcodes.h"  // opcodes header, generated by the Go tool
#include "jts_ocd_cable.h"
#include "checkers_debugger.h"
#include "pdc_caches.h"
#include "trv32p5_define.h"

#include <map>
#include <iostream>

// #define TRACE_OCD_CABLE_API
#ifdef TRACE_OCD_CABLE_API
#include "ocd_cable_logger.h"
#endif

struct pdc_mem_instr {
    int ld_instr = 0;
    int st_instr = 0;
    bool via_inst_reg = false;  // default is via data_reg
    int addr_incr = 1;

    pdc_mem_instr() = default;

    pdc_mem_instr(int ld, int st, bool inst = false)
        : ld_instr(ld), st_instr(st), via_inst_reg(inst)
        {
            addr_incr = via_inst_reg ? 4 : 1;
        }
    bool empty() const { return (ld_instr | st_instr) == 0; }
};

class pdc_commands {
public:
  typedef Checkers_debugger::Core_status Core_status;
  typedef Checkers_debugger::Breakpoint_settings Breakpoint_settings;
  typedef Checkers_debugger::Watchpoint_settings Watchpoint_settings;

  enum {
    max_core_id = 30,
    nr_breakpoints = DBG_BP_HIT_INDX -1 - DBG_MODE_INDX
  };

  pdc_commands(int coreid, std::string server, int port=41001);
  ~pdc_commands();

  // access of special registers :
  void get_status(Core_status*);
  AddressType get_program_counter();
  int put_program_counter(AddressType);
  static std::string pc_name;

  // refresh :
  void refresh();

  // start/stop/reset :
  void step(bool);
  void step_dis_int(bool);
  void resume(bool);
  void request(bool);
  void reset_core(bool);

  // hardware breakpoints/watchpoints :
  int watch_supported(const Watchpoint_settings*, bool&);
  void enable_hw_break(int, const Breakpoint_settings*);
  void enable_hw_break(const std::vector<int>&, const Watchpoint_settings*);
  void disable_hw_break(const std::vector<int>&);

  // software breakpoint info :
  enum {
    sw_break_enabled = 1,
    sw_break_decrements_pc = 0
  };
  typedef DataType instr_type;
  static std::string pmem_name;
  instr_type sw_break_instr(bool, instr_type);

  // buffered write access to storages (flush happpens on step/resume) :
  int put_register(std::string, const DataType&);
  int put_memory_at(std::string, AddressType, const DataType&);
  void check_buffer_overflow();
  void flush_buffer();

  // blocked based read access of storages :
  int get_register(std::string);
  int get_memory_at(std::string, AddressType);
  void send_and_receive();
  DataType received_next_mem(std::string);
  DataType received_next_reg(std::string);
  unsigned address_step(std::string);

  // common registers loaded in single send-receive call :
  std::vector<std::string> common_regs();
  std::vector<std::string> common_vec_regs(unsigned);

  // direct read access of storages :
  int get_register(std::string, DataType&);
  int get_memory_at(std::string, AddressType, DataType&);

  // vectorised access to registers and memories :
  unsigned vector_size(std::string);
  int get_register(std::string, pdc_caches::range elems);
  int get_memory_at(std::string, AddressType, pdc_caches::range);
  void received_next(std::string, pdc_caches::range, std::vector<DataType>&);
  int put_register(std::string, pdc_caches::range,
                   const std::vector<DataType>&);
  int put_memory_at(std::string, AddressType, pdc_caches::range,
                    const std::vector<DataType>&);

  // verbosity :
  void verbose(int);

private:

  // ---------------------------------------------------------------------------

  // breakpoint instruction codes: 001bbbii
  int bp_enable_instr[nr_breakpoints];
  int bp_export_instr[nr_breakpoints];
  int bp_disable_instr[nr_breakpoints];
  std::map<std::string,std::string> bp_root_mem;
  std::map<std::string,std::array<int,nr_breakpoints>> bp_watch_load_instr;
  std::map<std::string,std::array<int,nr_breakpoints>> bp_watch_store_instr;

  // watch range configuration
  int bpu_config_instr[nr_breakpoints];
  int bpu_enable_instr[nr_breakpoints];
  std::map<std::string,int> bp_mem_nr;

  void init_bpwp_codes(int);

  // ---------------------------------------------------------------------------


  void init_pdc_codes(int);

  // instruction codes: 0001iiii
  int request_instr;
  int resume_instr;
  int reset_instr;
  int step_instr;
  int stepdi_instr;
  int execute_instr;

  // load/store instruction codes: 010mmmmi
  std::map<std::string,pdc_mem_instr> mem_instr;

  std::string mem_name(const pdc_mem_instr&) const;

  // processor move instructions to access registers
  std::map<std::string,instr_type> reg_get_code;
  std::map<std::string,instr_type> reg_put_code;

  // software break instructions (key: instruction length)
  std::map<unsigned,instr_type> swbrk_code;

  instr_type jalr_x3_instr;

  void init_instr_codes();

  struct {
    std::string name;
    AddressType addr;
  } reg_access_via_mem;

  // physical link
#ifdef TRACE_OCD_CABLE_API
  ocd_cable_logger<jts_ocd_cable> cbl;
#else
  jts_ocd_cable cbl;
#endif

  DataType received_next();

  // current value of ocd_address_register, incremented on each st/ld :
  AddressType current_address = 0;
  bool ocd_address_set = false;

  void put_address_register(AddressType);

  void put_data_register(const DataType&);

  void execute_ldst_instr(int, int);

  bool verb = false;
};

#endif