/*
-- Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_CHECKERS_DEBUGGER_LOGGER_H__
#define INCLUDED_CHECKERS_DEBUGGER_LOGGER_H__

#include <checkers_debugger.h>
#include <iostream>

#include <checkers_api_l_structs.h>

template <typename Base>
class Checkers_debugger_logger : public Base {
public:

  typedef Checkers_debugger::Core_status Core_status;
  typedef Checkers_debugger::Breakpoint_settings Breakpoint_settings;
  typedef Checkers_debugger::Watchpoint_settings Watchpoint_settings;
  typedef Checkers_debugger::Sync_start_status Sync_start_status;

  // constructor/destructor
  template <typename ...TArgs>
  Checkers_debugger_logger (TArgs ... args)
      : Base(args...) {
    log("Constructed Checkers_debugger", args...);
  }
  virtual ~Checkers_debugger_logger () = default;

  // access of PC
  AddressType get_program_counter () override {
    enter("get_program_counter");
    auto r = Base::get_program_counter();
    leave("get_program_counter", r);
    return r;
  }
  int put_program_counter (AddressType pc) override {
    enter("put_program_counter", pc);
    auto r = Base::put_program_counter(pc);
    leave("put_program_counter", pc, r);
    return r;
  }

  // software breakpoints (using sw-break instruction)
  int add_sw_break (AddressType pc, bool export_) override {
    enter("add_sw_break", pc, bool_cast(export_));
    auto r = Base::add_sw_break(pc, export_);
    leave("add_sw_break", pc, bool_cast(export_), r);
    return r;

  }
  int remove_sw_break (AddressType pc) override {
    enter("remove_sw_break", pc);
    auto r = Base::remove_sw_break(pc);
    leave("remove_sw_break", pc, r);
    return r;
  }

  // access of registers and memories
  int get_memory_at (std::string nm, AddressType a, DataType &v) override {
    enter("get_memory_at", nm, a);
    int r = Base::get_memory_at(nm, a, v);
    leave("get_memory_at", nm, a, "0x" + v.toHex(), r);
    return r;
  }
  int put_memory_at (std::string nm, AddressType a, const DataType &v)
      override {
    enter("put_memory_at", nm, a, "0x" + v.toHex());
    auto r = Base::put_memory_at(nm, a, v);
    leave("put_memory_at", nm, a, "0x" + v.toHex(), r);
    return r;
  }

  int get_register (std::string nm, DataType &v) override {
    enter("get_register", nm);
    int r = Base::get_register(nm, v);
    leave("get_register", nm, "0x" + v.toHex(), r);
    return r;
  }
  int put_register (std::string nm, const DataType &v) override {
    enter("put_register", nm, "0x" + v.toHex());
    auto r = Base::put_register(nm, v);
    leave("put_register", nm, "0x" + v.toHex(), r);
    return r;
  }

  // element access of vector registers and memories
  int get_memory_at (std::string nm, AddressType a, unsigned e, DataType &v)
      override {
    enter("get_memory_at", nm, a, e);
    int r = Base::get_memory_at(nm, a, e, v);
    leave("get_memory_at", nm, a, e, "0x" + v.toHex(), r);
    return r;
  }
  int put_memory_at (std::string nm, AddressType a, unsigned e,
                     const DataType &v) override {
    enter("put_memory_at", nm, a, e, "0x" + v.toHex());
    auto r = Base::put_memory_at(nm, a, e, v);
    leave("put_memory_at", nm, a, e, "0x" + v.toHex(), r);
    return r;
  }

  int get_register (std::string nm, unsigned e, DataType &v) override {
    enter("get_register", nm, e);
    int r = Base::get_register(nm, e, v);
    leave("get_register", nm, e, "0x" + v.toHex(), r);
    return r;
  }
  int put_register (std::string nm, unsigned e, const DataType &v) override {
    enter("get_register", nm, e, "0x" + v.toHex());
    auto r = Base::put_register(nm, e, v);
    leave("get_register", nm, e, "0x" + v.toHex(), r);
    return r;
  }

  // protect memory address range [a,b] from redundant load access
  // (avoid access to memory-mapped devices when doing block-based access)
  void protect_memory_at (std::string nm, AddressType a, AddressType b)
      override {
    log("protect_memory_at", nm, a, b);
    Base::protect_memory_at(nm, a, b);
  }
  void clear_memory_protections () override {
    log("clear_memory_protections");
    Base::clear_memory_protections();
  }

  // identification
  int check_device () const override {
    log("check_device");
    return Base::check_device();
  }

  // access of core status
  void get_status (Core_status *cs) override {
    enter("get_status");
    Base::get_status(cs);
    leave("get_status", "running: " + bool_cast(cs->running),
          "hwbrk: " + bool_cast(cs->hw_break),
          "swbrk: " + bool_cast(cs->sw_break),
          "extbrk: " + bool_cast(cs->external_break));
  }

  // reset
  void reset_pdc () override {
    enter("reset_pdc");
    Base::reset_pdc();
    leave("reset_pdc");
  }
  void reset_core (bool sync = false) override {
    enter("reset_core", "sync="+bool_cast(sync));
    Base::reset_core(sync);
    leave("reset_core", "sync="+bool_cast(sync));
  }

  // refresh (flush internal buffers and clear caches)
  void refresh () override {
    enter("refresh");
    Base::refresh();
    leave("refresh");
  }

  // stop and core-specific step/resume commands
  void request (bool sync = false) override {
    enter("request", "sync="+bool_cast(sync));
    Base::request(sync);
    leave("request", "sync="+bool_cast(sync));
  }
  void step () override {
    enter("step");
    Base::step();
    leave("step");
  }
  void step_dis_int () override {
    enter("step_dis_int");
    Base::step_dis_int();
    leave("step_dis_int");
  }
  void resume () override {
    enter("resume");
    Base::resume();
    leave("resume");
  }

  // synchronous step/resume commands in multicore context
  Sync_start_status prepare_sync_command () override {
    log("prepare_sync_command");
    return Base::prepare_sync_command();
  }
  void sync_step (bool sync = true) override {
    enter("sync_step", "sync="+bool_cast(sync));
    Base::sync_step(sync);
    leave("resume");
  }
  void sync_resume (bool sync = true) override {
    enter("sync_resume", "sync="+bool_cast(sync));
    Base::sync_resume(sync);
    leave("sync_resume", "sync="+bool_cast(sync));
  }

  // -1: no hw breakpoints supported
  int remaining_hw_breakpoints () const override {
    log("remaining_hw_breakpoints");
    return Base::remaining_hw_breakpoints();
  }
  int enable_hw_break (const Breakpoint_settings *x) override {
    log("enable_hw_break", "bkpt", x->address);
    return Base::enable_hw_break(x);
  }
  int enable_hw_break (const Watchpoint_settings *x) override {
    log("enable_hw_break", "wtpt", x->memory, x->address, x->block_size);
    return Base::enable_hw_break(x);
  }
  int disable_hw_break (int nr) override {
    log("disable_hw_break", nr);
    return Base::disable_hw_break(nr);
  }

  // storage access
  bool expand_into_root_locations (const Checkers_storinfo *st) override {
    enter("expand_into_root_locations", st->storage_name);
    bool r = Base::expand_into_root_locations(st);
    leave("expand_into_root_locations", st->storage_name, r);
    return r;
  }

  // multiple register contexts
  int get_context () override {
    log("get_context");
    return Base::get_context();
  }
  int put_context (int c) override {
    log("put_context");
    return Base::put_context(c);
  }
  Sync_start_status prepare_context_for_resume () override {
    log("prepare_context_for_resume");
    return Base::prepare_context_for_resume();
  }

  // verbosity
  void verbose (int lvl) override {
    log("verbose", lvl);
    Base::verbose(lvl);
  }

private:
  static inline std::string bool_cast(bool val) { return val ? "true" : "false"; }

  mutable int l = 0;

  // base case
  void doPrint(std::ostream& out) const {
    out << "\n";
  }

  template <typename T>
  void doPrint(std::ostream& out, T t) const {
    out << t << "\n";
  }

  template <typename T, typename... Args>
  void doPrint(std::ostream& out, T t, Args... args) const {
    out << t << ", ";
    doPrint(out, args...);
  }

  void log_ (std::string pfx, std::string fn) const {
    std::cerr << pfx << fn << "\n";
  }

  template <typename... Args>
  void log_ (std::string pfx, std::string fn, Args... args) const {
    std::cerr << pfx << fn << ": ";
    doPrint(std::cerr, args...);
  }

  template <typename... Args>
  void enter (std::string fn, Args... args) const {
    log_(">> DBG :: " + std::to_string(l) + " :: ", fn, args...);
    l++;
  }

  template <typename... Args>
  void leave (std::string fn, Args... args) const {
    l--;
    log_("<< DBG :: " + std::to_string(l) + " :: ", fn, args...);
  }

  template <typename... Args>
  void log (std::string fn, Args... args) const {
    log_("++ DBG :: " + std::to_string(l) + " :: ", fn, args...);
  }

};

#endif
