/*
 -- File : checkers_pdc_interface.h
 --
 -- Contents : Implementation of Checkers_debugger interface,
 --            in terms of the PDC commands class: pdc_commands.
 --
 -- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
 */

#ifndef INCLUDED_CHECKERS_PDC_INTERFACE_H__
#define INCLUDED_CHECKERS_PDC_INTERFACE_H__

#include <map>
#include <set>
#include <checkers_debugger.h>
#include "pdc_commands.h"

class Checkers_pdc_interface : public Checkers_debugger64 {
public:

  Checkers_pdc_interface(int coreid, std::string server, int port=41001);
  virtual ~Checkers_pdc_interface();

  // access of special registers :
  void get_status(Core_status*) override;
  AddressType get_program_counter() override;
  int put_program_counter(AddressType) override;

  // reset :
  void reset_pdc() override;
  void reset_core(bool sync = false) override;

  // refresh (flush internal buffers and clear caches) :
  void refresh() override;

  // stop and core-specific step/resume commands :
  void request(bool sync = false) override;
  void step() override;
  void step_dis_int() override;
  void resume() override;

  // synchronous step/resume commands in multicore context :
  Sync_start_status prepare_sync_command() override;
  void sync_step(bool sync = true) override;
  void sync_resume(bool sync = true) override;

  // hardware breakpoints/watchpoints :
  int remaining_hw_breakpoints() const override;
  int enable_hw_break(const Breakpoint_settings*) override;
  int enable_hw_break(const Watchpoint_settings*) override;
  int disable_hw_break(int) override;

  // software breakpoints (using sw-break instruction) :
  int add_sw_break(AddressType, bool) override;
  int remove_sw_break(AddressType) override;

  // access of registers and memories :
  int get_memory_at(std::string, AddressType, DataType&) override;
  int put_memory_at(std::string, AddressType, const DataType&) override;
  int get_register(std::string, DataType&) override;
  int put_register(std::string, const DataType&) override;

  // element access of vector registers and memories:
  int get_memory_at(std::string, AddressType, unsigned, DataType&) override;
  int put_memory_at(std::string, AddressType, unsigned, const DataType&) override;
  int get_register(std::string, unsigned, DataType&) override;
  int put_register(std::string, unsigned, const DataType&) override;

  // verbosity :
  void verbose(int) override;

  Sync_start_status prepare_context_for_resume() override;

  // NOTE check tmicro db client for protected memory address ranges support

  // NOTE check tmicro db client for multiple (interleaved) register contexts support

protected:
  pdc_commands cmd;

  // breakpoints:
  struct pmem_instr_pair {
    VBitWrapper orig_instr;
    VBitWrapper sw_break;
  };
  int hw_break_in_use[pdc_commands::nr_breakpoints];
  std::map<AddressType,pmem_instr_pair> sw_break_instrs;
  std::map<AddressType,int> hw_break_instrs;
  enum Processor_status {unknown, progress, stopped} status = unknown;
  virtual int special_step();
  virtual VBitWrapper get_instruction_at(AddressType);
  virtual void put_instruction_at(AddressType, VBitWrapper);
  virtual AddressType next_instruction(AddressType pc) {return pc+1;}
  virtual AddressType prev_instruction(AddressType pc) {return pc-1;}

  // caching of memory/register get results:
  std::map<std::string, std::map<AddressType,pdc_caches::cache_line> > mem_caches;
  std::map<std::string, std::map<AddressType,pdc_caches::vcache_line> > mem_vcaches;
  std::map<std::string, std::map<unsigned,pdc_caches::sa_vcache_line> > reg_vcaches;
  std::map<std::string,DataType> reg_cache;
  bool reg_cache_loaded = false;
  virtual void load_reg_cache();
  virtual int load_reg_vcache(const std::vector<std::string>&, pdc_caches::range);

  // write-merge-buffers for vector/record storages:
  std::map<std::string,pdc_caches::write_merge_vline> write_merge_buffers;
  void flush_write_merge_buffers();

  // when stepping or resuming:
  void flush_invalidate();

  std::vector<std::string> common_scl_regs;
  std::map<unsigned,std::vector<std::string>> common_vec_regs;

  // Common scalar registers - loaded (if not cached) when any scalar register is accessed
  virtual void populate_common_scl_regs() { }

  // Common vector registers - loaded (if not cached) when any vector register of the same length is accessed
  virtual void populate_common_vec_regs() { }

  bool verb = false;
};

#endif // def INCLUDED_CHECKERS_PDC_INTERFACE_H__
