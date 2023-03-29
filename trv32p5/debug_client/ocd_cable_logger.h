/*
-- Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_OCD_CABLE_LOGGER_H__
#define INCLUDED_OCD_CABLE_LOGGER_H__

#include "ocd_cable.h"

static std::map<long long, std::string> pdc_opcode_map = {
#include "pdc_opcodes_dbg.h"
};

template <typename Base>
class ocd_cable_logger : public Base {
public:

  template <typename...TArgs>
  ocd_cable_logger(TArgs ... args) : Base(args...) {
   log("Constructed cable", args...);
  }

  virtual ~ocd_cable_logger() = default;

    int open () override {
      enter ("open");
      auto r = Base::open ();
      leave ("open", r);
      return r;
    }

    int close () override {
      enter ("close");
      auto r = Base::close ();
      leave ("close", r);
      return r;
    }

    int add_iwrite (long long v) override {
      enter ("add_iwrite",
             pdc_opcode (v) + " (0x" + VBit<16, false> (v).toHex () + ")");
      auto r = Base::add_iwrite (v);
      leave ("add_iwrite",
             pdc_opcode (v) + " (0x" + VBit<16, false> (v).toHex () + ")", r);
      return r;
    }

    int add_dwrite (ocd_cable::reg_type r, const DataType &v) override {
      enter ("add_dwrite", to_string (r), "0x" + v.toHex ());
      auto rc = Base::add_dwrite (r, v);
      leave ("add_dwrite", to_string (r), "0x" + v.toHex (), rc);
      return rc;
    }

    int add_dread (ocd_cable::reg_type r) override {
      enter ("add_dread", to_string (r));
      auto rc = Base::add_dread (r);
      leave ("add_dread", to_string (r), rc);
      return rc;
    }

    int add_dwrite_dread (ocd_cable::reg_type r, const DataType &v) override {
      enter ("add_dwrite_dread", to_string (r), "0x" + v.toHex ());
      auto rc = Base::add_dwrite_dread (r, v);
      leave ("add_dwrite_dread", to_string (r), "0x" + v.toHex (), rc);
      return rc;
    }

    int send_and_receive () override {
      enter ("send_and_receive");
      auto r = Base::send_and_receive ();
      leave ("send_and_receive", r);
      return r;
    }

    int get_next_data (DataType &v) override {
      enter ("get_next_data");
      auto r = Base::get_next_data (v);
      leave ("get_next_data", r, "0x" + v.toHex ());
      return r;
    }

    bool buffer_overflow_imminent () {
      enter ("buffer_overflow_imminent");
      auto r = Base::buffer_overflow_imminent ();
      leave ("buffer_overflow_imminent", bool_cast (r));
      return r;
    }

    bool buffer_is_empty () {
      enter ("buffer_is_empty");
      auto r = Base::buffer_is_empty ();
      leave ("buffer_is_empty", bool_cast (r));
      return r;
    }

    void set_verbose (int l) override {
      log ("set_verbose", l);
      Base::set_verbose (l);
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
    log_(">> CBL :: " + std::to_string(l) + " :: ", fn, args...);
    l++;
  }

  template <typename... Args>
  void leave (std::string fn, Args... args) const {
    l--;
    log_("<< CBL :: " + std::to_string(l) + " :: ", fn, args...);
  }

  template <typename... Args>
  void log (std::string fn, Args... args) const {
    log_("++ CBL :: " + std::to_string(l) + " :: ", fn, args...);
  }

  static std::string pdc_opcode (long long instr) {
    int cid = (instr >> 11) & 0x1f;
    long long base = instr & 0x7ff;
    if (cid == 31) base = instr; // sync
    if (pdc_opcode_map.count(base) == 0) {
      return "??";
    } else {
      return pdc_opcode_map[base];
    }
  }

  static std::string to_string(ocd_cable::reg_type r) {
    switch (r) {
      case ocd_cable::reg_type::data: return "ocd_data";
      case ocd_cable::reg_type::addr: return "ocd_addr";
      case ocd_cable::reg_type::inst: return "ocd_inst";
      case ocd_cable::reg_type::stat: return "ocd_stat";
      case ocd_cable::reg_type::ctxt: return "ocd_ctxt";
      default:                        return "invalid";
    }
  }

};

#endif // def INCLUDED_OCD_CABLE_LOGGER_H__
