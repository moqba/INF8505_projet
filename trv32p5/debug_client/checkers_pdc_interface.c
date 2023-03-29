/*
-- File : checkers_pdc_interface.c
--
-- Contents : Implementation of Checkers_pdc_interface class
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include <algorithm>
#include <sstream>
#include "checkers_pdc_interface.h"
#include "checkers_errors.h"
#include "checkers_uicore.h"

using std::vector;
using std::string;
using std::map;
using std::cerr;

using pdc_caches::range;
using pdc_caches::arange;
using pdc_caches::cache_line;
using pdc_caches::vcache_line;
using pdc_caches::sa_vcache_line;
using pdc_caches::write_merge_vline;


#define vrb() if (unlikely(verb)) std::cerr

// use lower case for register names in cache:
static void to_lower(string& a)
{
  for (unsigned i = 0; i < a.length(); i++)
    a[i] = tolower(a[i]);
}

Checkers_pdc_interface::Checkers_pdc_interface(int coreid, string server, int port)
    : Checkers_debugger64(coreid), cmd(coreid,server,port)
{
}

Checkers_pdc_interface::~Checkers_pdc_interface()
{
    flush_write_merge_buffers();
}

//  reset functions

void Checkers_pdc_interface::reset_pdc()
{
 // disable hardware breakpoints/watchpoints
    std::vector<int> nrs(pdc_commands::nr_breakpoints);
    for (int i = 0; i < pdc_commands::nr_breakpoints; i++) {
        hw_break_in_use[i] = -1;
        nrs[i] = i;
    }
    cmd.disable_hw_break(nrs);
    hw_break_instrs.clear();

 // remove software breakpoints
    for (auto p = sw_break_instrs.cbegin(); p != sw_break_instrs.cend(); ++p)
        put_instruction_at(p->first,p->second.orig_instr);
    sw_break_instrs.clear();
}

void Checkers_pdc_interface::reset_core(bool sync)
{
    flush_invalidate();
    try {
      cmd.reset_core(sync);
    } catch (std::runtime_error const& e) {
      uicore()->errors.put(chkapi_ERR, e.what(), "reset_core");
    }
    status = unknown;
}

void Checkers_pdc_interface::refresh()
{
    flush_invalidate();
    try {
      cmd.refresh();
    } catch (std::runtime_error const& e) {
      uicore()->errors.put(chkapi_ERR, e.what(), "refresh");
    }
}

void Checkers_pdc_interface::request(bool sync)
{
  try {
    cmd.request(sync);
  } catch (std::runtime_error const& e) {
    uicore()->errors.put(chkapi_ERR, e.what(), "request");
  }
}

void Checkers_pdc_interface::sync_step(bool sync)
{
  try {
    cmd.step(sync);
  } catch (std::runtime_error const& e) {
    uicore()->errors.put(chkapi_ERR, e.what(), "sync_step");
  }
}

void Checkers_pdc_interface::sync_resume(bool sync)
{
  try {
    cmd.resume(sync);
  } catch (std::runtime_error const& e) {
    uicore()->errors.put(chkapi_ERR, e.what(), "sync_resume");
  }
}

void Checkers_pdc_interface::verbose(int i)
{
    verb = i > 0;
    cmd.verbose(i);
}

//  enabling hardware breakpoints/watchpoints

inline void hw_break_exceeded_msg(Checkers_uicore* uicore)
{
    std::ostringstream msg;
    msg << "No more hardware breakpoints available, maximum is "
        << pdc_commands::nr_breakpoints;
    if (uicore != nullptr) {
        uicore->errors.put(chkapi_ERR, msg, "enable_hw_break");
    }
}

int Checkers_pdc_interface::remaining_hw_breakpoints() const
{
    int n = 0;
    for (int i = 0; i < pdc_commands::nr_breakpoints; i++) {
        if (hw_break_in_use[i] == -1) { // free hw breakpoint
            n++;
        }
    }
    return n;
}

int Checkers_pdc_interface::enable_hw_break(const Breakpoint_settings* bs)
{
    for (int i = 0; i < pdc_commands::nr_breakpoints; i++)
        if (hw_break_in_use[i] == -1) {  // set new breakpoint
            hw_break_in_use[i] = i;
            cmd.enable_hw_break(i,bs);
            hw_break_instrs[bs->address] = i;
            return i;
        }
    hw_break_exceeded_msg(uicore());
    return -1;  // no more hardware breakpoints available
}

inline bool check_alignment(bool align, int i, int n, int in_use[])
{
    return !align || (n & 1) || (i & 1) == 0 && in_use[i+1] == -1;
}

int Checkers_pdc_interface::enable_hw_break(const Watchpoint_settings* ws)
{
    // get number of required BPUs:
    bool aligned_pairs = false;
    int n = cmd.watch_supported(ws, aligned_pairs);
    if (n == 0) return -1;

     // lookup "n" address registers
    int handle = -1;
    vector<int> nrs;
    for (int i = 0; i < pdc_commands::nr_breakpoints; i++) {
        if ((hw_break_in_use[i] == -1) && check_alignment(aligned_pairs, i, n, hw_break_in_use)) {
            if (handle < 0) handle = i;
            hw_break_in_use[i] = handle;
            nrs.push_back(i);
            if (--n == 0) {
                cmd.enable_hw_break(nrs,ws);
                return handle;
            }
        }
    }
    // mark all following hw_break using this handle as unused:
    if (handle >=0) {
        for (int i = handle; i < pdc_commands::nr_breakpoints; i++) {
            if (hw_break_in_use[i] == handle) hw_break_in_use[i] = -1;
        }
    }
    hw_break_exceeded_msg(uicore());
    return -1;  // no more hardware breakpoints available
}

int Checkers_pdc_interface::disable_hw_break(int handle)
{
    if ((unsigned)handle < pdc_commands::nr_breakpoints) {
        vector<int> nrs;
        for (int i = handle; i < pdc_commands::nr_breakpoints; i++)
            if (hw_break_in_use[i] == handle) {
                nrs.push_back(i);
                hw_break_in_use[i] = -1;
            }
        cmd.disable_hw_break(nrs);
     // cleanup hw_break_instrs map:
        for (auto p = hw_break_instrs.begin(); p != hw_break_instrs.end(); ++p)
            if (p->second == handle) {
                hw_break_instrs.erase(p);
                break;
            }
        return ok;
    }
    return failed;
}

//  software breakpoints: adding/removing and step/resume behaviour

VBitWrapper Checkers_pdc_interface::get_instruction_at(AddressType pc)
{
    DataType instr;
    get_memory_at(cmd.pmem_name,pc,instr);
    return instr;
}

void Checkers_pdc_interface::put_instruction_at(AddressType pc, VBitWrapper instr)
{
    put_memory_at(cmd.pmem_name,pc,instr);
}

int Checkers_pdc_interface::add_sw_break(AddressType pc, bool export_)
{
    if (!pdc_commands::sw_break_enabled)
        return failed;
    if (sw_break_instrs.count(pc)) // sw-break is already present
        return ok;
    pmem_instr_pair p;
    p.orig_instr = get_instruction_at(pc);
    p.sw_break = cmd.sw_break_instr(export_,p.orig_instr);
    put_instruction_at(pc,p.sw_break);
    pdc_commands::instr_type read_back_instr = get_instruction_at(pc);
    if (read_back_instr != p.sw_break) {
        cerr << "PDC IF: read-back instr is not SW break\n"
             <<  "  expected 0x" << p.sw_break.toHex()
             << " got 0x" << read_back_instr.toHex() << "\n";
        return failed; // bug, or non-writable PMEM section
    }
    if (p.orig_instr != p.sw_break)
        sw_break_instrs[pc] = p;
    return ok;
}

int Checkers_pdc_interface::remove_sw_break(AddressType pc)
{
    if (pdc_commands::sw_break_enabled && status != stopped) {
        Core_status cs;
        get_status(&cs);  // force status before removing sw-break
    }
    if (sw_break_instrs.count(pc)) {
        put_instruction_at(pc,sw_break_instrs[pc].orig_instr);
        sw_break_instrs.erase(pc);
        return ok;
    }
    return failed;
}

void process_multi_address_watchpoint_hits(vector<int>* hits, int in_use[])
//  when using secondary address registers only return the handle index
{
    for(auto i = hits->begin(); i < hits->end();) {
        int handle = in_use[*i];
        if (handle < *i && 0 <= handle) {
            i = hits->erase(i);
            if (find(hits->begin(),hits->end(),handle) == hits->end())
                i = hits->insert(i,handle)+1;
        }
        else
            ++i;
    }
}

void Checkers_pdc_interface::get_status(Core_status* cs)
{
  try {
    cmd.get_status(cs);
  } catch (std::runtime_error const& e) {
    uicore()->errors.put(chkapi_ERR, e.what(), "get_status");
  }
    if (cs->running) {
        status = progress;
        return;
    }
    Processor_status prev_status = status;
    status = stopped;
    if (cs->hw_break_nr.size())
        process_multi_address_watchpoint_hits(&cs->hw_break_nr,hw_break_in_use);

    AddressType pc;
    if (pdc_commands::sw_break_enabled) {
        if (cs->sw_break && prev_status == progress) {
            pc = get_program_counter();
            if (!pdc_commands::sw_break_decrements_pc
                && sw_break_instrs.count(pc=prev_instruction(pc)))
                // executed break instruction inserted by software breakpoint,
                // so decrement PC
                put_program_counter(pc);
            if (pdc_commands::sw_break_decrements_pc
                && !sw_break_instrs.count(pc))
                // executed break instruction in user code,
                // so increment PC to get beyond it
                put_program_counter(next_instruction(pc));
        }
        else if (sw_break_instrs.count(get_program_counter())) {
            cs->sw_break = 1;
        }
    }
    if (!cs->hw_break && hw_break_instrs.count(pc = get_program_counter())) {
        cs->hw_break = true;
        cs->hw_break_nr.push_back(hw_break_instrs[pc]);
    }
}

Checkers_debugger::Sync_start_status
Checkers_pdc_interface::prepare_context_for_resume()
{
    Sync_start_status res;
    if (special_step()) {
        Core_status cs;
        get_status(&cs);
        if (cs.hw_break)
            res = at_break_after_step;
        else
            res = ready_after_step;
    }
    else
        res = ready;
    return res;
}

Checkers_debugger::Sync_start_status
Checkers_pdc_interface::prepare_sync_command()
{
    Sync_start_status res = prepare_context_for_resume();
    refresh();
    status = progress;
    return res;
}

int Checkers_pdc_interface::special_step()
//  before step or resume
{
    AddressType pc = get_program_counter();   // force status check
    if (sw_break_instrs.count(pc)) {       // step over software break
        put_instruction_at(pc,sw_break_instrs[pc].orig_instr);
        flush_invalidate();
        try {
          cmd.step_dis_int(false);
        } catch (std::runtime_error const& e) {
          uicore()->errors.put(chkapi_ERR, e.what(), "special_step");
        }
        status = progress;
        put_instruction_at(pc,sw_break_instrs[pc].sw_break);
    }
    else if (hw_break_instrs.count(pc)) {  // step beyond hardware break
        flush_invalidate();
        try {
          cmd.step_dis_int(false);
        } catch (std::runtime_error const& e) {
          uicore()->errors.put(chkapi_ERR, e.what(), "special_step");
        }
        status = progress;
    }
    else
        return false;
    return true;
}

void Checkers_pdc_interface::step()
{
    if (!special_step()) {
        flush_invalidate();
        try {
          cmd.step(false);
        } catch (std::runtime_error const& e) {
          uicore()->errors.put(chkapi_ERR, e.what(), "step");
        }
        status = progress;
    }
}

void Checkers_pdc_interface::step_dis_int()
{
    if (!special_step()) {
        flush_invalidate();
        try {
          cmd.step_dis_int(false);
        } catch (std::runtime_error const& e) {
          uicore()->errors.put(chkapi_ERR, e.what(), "step_dis_int");
        }
        status = progress;
    }
}

void Checkers_pdc_interface::resume()
{
    if (special_step()) {
        Core_status cs;
        get_status(&cs);
        if (cs.hw_break || cs.sw_break || cs.external_break)
            return;
    }
    flush_invalidate();
    try {
      cmd.resume(false);
    } catch (std::runtime_error const& e) {
      uicore()->errors.put(chkapi_ERR, e.what(), "resume");
    }
    status = progress;
}

//  register read access using cache

void Checkers_pdc_interface::load_reg_cache()
{
  try {
    auto& ll = common_scl_regs;
    for (auto p = ll.cbegin() ; p != ll.cend(); ++p)
        cmd.get_register(*p);
    cmd.send_and_receive();
    for (auto p = ll.cbegin() ; p != ll.cend(); ++p)
        reg_cache[*p] = cmd.received_next_reg(*p);
  } catch (std::runtime_error const& e) {
    uicore()->errors.put(chkapi_ERR, e.what(), "load_reg_cache");
  }
}

AddressType Checkers_pdc_interface::get_program_counter()
{
    if (pdc_commands::sw_break_enabled && status != stopped) {
        Core_status cs;
        get_status(&cs);  // force status check before returning PC
    }
    AddressType pc;
    auto p = reg_cache.find(cmd.pc_name);
    if (p != reg_cache.end()) {
        pc = p->second.to_address();
    } else {
      try {
        reg_cache[cmd.pc_name] = pc = cmd.get_program_counter();
      } catch (std::runtime_error const& e) {
        uicore()->errors.put(chkapi_ERR, e.what(), "get_program_counter");
      }
    }
    return pc;
}

int Checkers_pdc_interface::get_register(string nm, DataType& val)
{
    to_lower(nm);
    if (nm == cmd.pc_name) {
        val = get_program_counter();
        return ok;
    }
    if (!reg_cache_loaded) {
        get_program_counter();
        load_reg_cache();
        reg_cache_loaded = true;
    }
    auto p = reg_cache.find(nm);
    try {
      if (p != reg_cache.end()) {
          val = p->second;
      } else if (cmd.get_register(nm,val) == ok) { // non-common register
          reg_cache[nm] = val;
      } else {
          return failed;
      }
    } catch (std::runtime_error const& e) {
      uicore()->errors.put(chkapi_ERR, e.what(), "get_register");
    }
    return ok;
}

//  register write access

int Checkers_pdc_interface::put_program_counter(AddressType val)
{
    if (pdc_commands::sw_break_enabled && status != stopped) {
        Core_status cs;
        get_status(&cs);  // force status check before updating PC
    }
    try {
      if (cmd.put_program_counter(val) == ok) {
          reg_cache[cmd.pc_name] = val;
          cmd.check_buffer_overflow();
          return ok;
      } else {
          return (get_program_counter() == val) ? ok : failed;
      }
    } catch (std::runtime_error const& e) {
      uicore()->errors.put(chkapi_ERR, e.what(), "put_program_counter");
      return failed;
    }
}

int Checkers_pdc_interface::put_register(string nm, const DataType& val)
{
    to_lower(nm);
    if (nm == cmd.pc_name)
        return put_program_counter(val.to_address());
    reg_cache.clear();
    reg_cache_loaded = false;
    try {
      int res = cmd.put_register(nm,val);
      cmd.check_buffer_overflow();
      return res;
    } catch (std::runtime_error const& e) {
      uicore()->errors.put(chkapi_ERR, e.what(), "put_register");
      return failed;
    }
}

template <typename T>
inline bool overlaps(std::vector<T>& v, arange r)
{
    for (auto i = v.begin(); i < v.end(); ++i) {
        if (overlaps(i->first,r))
            return true;
    }
    return false;
}

template <typename MT>
inline typename MT::mapped_type * overlaps(MT& m, string nm, arange r)
{
    auto p = m.find(nm);
    if (p != m.end()) {
        if (overlaps(p->second,r))
          return &p->second;
    }
    return 0;
}

//  scalar memory read access using cache

int Checkers_pdc_interface::get_memory_at(string nm, AddressType addr,
                                          DataType& val)
{
 // when "nm" is a record memory with "vec_sz" words per address increment
    unsigned vec_sz = cmd.vector_size(nm);
    if (vec_sz > 1) {
        return get_memory_at(nm, addr/vec_sz, addr%vec_sz, val);
    }

 // cache-based access
    auto& cache = mem_caches[nm];
    unsigned step = cmd.address_step(nm);
    AddressType indx = pdc_caches::cache_index(addr/step);
    unsigned offs = pdc_caches::cache_offset(addr/step);
    auto p = cache.find(indx);
    if (p != cache.end()) {
        val = p->second[offs];
    } else {
     // load cache line
        auto& line = cache[indx];
        arange r = pdc_caches::line_address_range(addr/step)*step;
        vrb() << "DBG" << nm << ", loading cache line "
              << "addr = " << r.first << ":" << step << ":" << r.last << "\n";
        try {
          for (AddressType i = r.first; i <= r.last; i += step) {
              if (cmd.get_memory_at(nm,i) != ok)
                return failed;
          }
          cmd.send_and_receive();
          auto p = line.begin();
          for (AddressType i = r.first; i <= r.last; i += step)
              *p++ = cmd.received_next_mem(nm);
        } catch (std::runtime_error const& e) {
          uicore()->errors.put(chkapi_ERR, e.what(), "get_memory_at");
        }
        val = line[offs];
    }
    return ok;
}

//  scalar memory write access

int Checkers_pdc_interface::put_memory_at(string nm, AddressType addr,
                                          const DataType& val)
{
    unsigned vec_sz = cmd.vector_size(nm);
    if (vec_sz > 1) {
     // "nm" is record memory with "vec_sz" words per address increment
        return put_memory_at(nm, addr / vec_sz, addr % vec_sz, val);
    }
    mem_caches[nm].erase(pdc_caches::cache_index(addr/cmd.address_step(nm)));
    try {
      int res = cmd.put_memory_at(nm,addr,val);
      cmd.check_buffer_overflow();
      return res;
    } catch (std::runtime_error const& e) {
      uicore()->errors.put(chkapi_ERR, e.what(), "put_memory_at");
      return failed;
    }
}

//  vector memory read access using vector cache

int Checkers_pdc_interface::get_memory_at(string nm, AddressType addr,
                                          unsigned elem, DataType& val)
{
    unsigned vec_sz = cmd.vector_size(nm);
    if (vec_sz <= elem)
        return failed;
    auto& cache = mem_vcaches[nm];
    unsigned step = cmd.address_step(nm);
    AddressType indx = pdc_caches::vcache_index(addr/step,elem,vec_sz);
    unsigned offs = pdc_caches::vcache_offset(addr/step,elem);
    auto p = cache.find(indx);
    if (p != cache.end()) {
        val = p->second[offs];
    } else {
        auto& cache_line = cache[indx];
        arange ar = pdc_caches::vline_address_range(addr/step)*step;
        range er = pdc_caches::vline_elem_range(elem,vec_sz);
        auto& merge_line = write_merge_buffers[nm];
        if (merge_line.covered(ar,er)) {
            vrb() << "DBG: " << nm << ", flushing vector write merge buffer\n";
            merge_line.flush(&cmd,nm);  // flush pending writes
        }
        vrb() << "DBG: " << nm << ", loading vector cache line "
              << "field = " << ar.first << ":" << step << ":" << ar.last << " "
              << "elem = " << er.first << ":1:" << er.last << " "
              << "vec_sz = " << vec_sz << "\n";
        try {
          for (AddressType a = ar.first; a <= ar.last; a += step) {
              if (cmd.get_memory_at(nm,a,er) != ok)
                return failed;
          }
          cmd.send_and_receive();
          vector<DataType> vals(er.length());
          auto p = cache_line.begin();
          for (AddressType a = ar.first; a <= ar.last; a += step) {
              cmd.received_next(nm,er,vals);
              std::copy(vals.begin(),vals.end(),p);
              p += pdc_caches::vline_elem_sz;
          }
        } catch (std::runtime_error const& e) {
          uicore()->errors.put(chkapi_ERR, e.what(), "get_memory_at");
        }
        val = cache_line[offs];
    }
    return ok;
}

//  vector memory write access using write merge line buffer

int Checkers_pdc_interface::put_memory_at(string nm, AddressType addr,
                                          unsigned elem, const DataType& val)
{
    unsigned vec_sz = cmd.vector_size(nm);
    if (vec_sz <= elem)
        return failed;
    auto& vline = write_merge_buffers[nm];
    range r = pdc_caches::vline_elem_range(elem,vec_sz);
    if (!vline.empty() && !vline.same_line(addr,r)) {
        vrb() << "DBG: " << nm << ", flushing vector write merge buffer\n";
        vline.flush(&cmd,nm);
    }
    if (vline.empty()) {
     // clear corresponding cache entry
        auto& cache = mem_vcaches[nm];
        AddressType a = addr / cmd.address_step(nm);
        AddressType indx = pdc_caches::vcache_index(a,elem,vec_sz);
        auto p = cache.find(indx);
        if (p != cache.end()) {
            vline.assign(r,&p->second[pdc_caches::vcache_offset(a,0)]);
            cache.erase(p);
        }
    }
    vline.add(addr,r,elem,val);
    return ok;
}

void write_merge_vline::flush(pdc_commands* cmd, string nm)
{
    vector<DataType> vals(elems.length());
    if (!complete()) {
        // read missing values
        if (for_reg) {
            cmd->get_register(nm,elems);
        } else {
            cmd->get_memory_at(nm,addr,elems);
        }
        cmd->send_and_receive();
        cmd->received_next(nm,elems,vals);
    }
 // overwrite pending stores
    copy_to(vals.begin());
 // write to hardware
    if (for_reg) {
        cmd->put_register(nm,elems,vals);
    } else {
        cmd->put_memory_at(nm,addr,elems,vals);
    }
    cmd->check_buffer_overflow();
    clear();
}

void Checkers_pdc_interface::flush_write_merge_buffers()
{
    for (auto p=write_merge_buffers.begin(); p != write_merge_buffers.end(); ++p) {
        if (!p->second.empty()) {
            vrb() << "DBG: " << p->first << ", flushing write merge buffers\n";
            p->second.flush(&cmd,p->first);
        }
    }
}

//  vector register read/write access using cache and write merge buffer

int Checkers_pdc_interface::load_reg_vcache(const vector<string>& regs, range r)
{
    for (auto p = regs.cbegin(); p != regs.cend(); ++p) {
        if (write_merge_buffers.count(*p)) {
            auto& merge_line = write_merge_buffers[*p];
            if (merge_line.same_line(r)) {
                vrb() << "DBG: " << *p << ", flushing write merge buffer\n";
                merge_line.flush(&cmd,*p);  // flush pending writes
            }
        }
    }
    try {
      for (auto p = regs.cbegin(); p != regs.cend(); ++p) {
          if (cmd.get_register(*p,r) != ok)
            return failed;
      }
      cmd.send_and_receive();
      unsigned indx = pdc_caches::sa_vcache_index(r.first);
      vector<DataType> vals(r.length());
      for (auto p = regs.cbegin(); p != regs.cend(); ++p) {
          auto& cache_line = reg_vcaches[*p][indx];
          cmd.received_next(*p,r,vals);
          std::copy(vals.begin(),vals.end(),cache_line.begin());
      }
    } catch (std::runtime_error const& e) {
      uicore()->errors.put(chkapi_ERR, e.what(), "load_reg_vcache");
    }
    return ok;
}

int Checkers_pdc_interface::get_register(string nm, unsigned elem,
                                         DataType& val)
{
    to_lower(nm);
    unsigned vec_sz = cmd.vector_size(nm);
    if (vec_sz <= elem)
        return failed;
    auto& cache = reg_vcaches[nm];
    unsigned indx = pdc_caches::sa_vcache_index(elem);
    unsigned offs = pdc_caches::sa_vcache_offset(elem);
    auto p = cache.find(indx);
    if (p != cache.end()) {
        val = p->second[offs];
    } else {
        range r = pdc_caches::vline_elem_range(elem,vec_sz);
        auto& regs = common_vec_regs[vec_sz];
        int res;
        if (std::find(regs.begin(),regs.end(),nm) != regs.end())
            res = load_reg_vcache(regs,r);
        else
            res = load_reg_vcache(vector<string>(1,nm),r);
        if (res != ok)
            return failed;
        val = cache[indx][offs];
    }
    return ok;
}

int Checkers_pdc_interface::put_register(string nm, unsigned elem,
                                         const DataType& val)
{
    to_lower(nm);
    unsigned vec_sz = cmd.vector_size(nm);
    if (vec_sz <= elem)
        return failed;
    auto& vline = write_merge_buffers[nm];
    range r = pdc_caches::vline_elem_range(elem,vec_sz);
    if (!vline.empty() && !vline.same_line(r)) {
        vrb() << "DBG: " << nm << ", flushing write merge buffer\n";
        vline.flush(&cmd,nm);
    }

    if (vline.empty()) {
     // clear corresponding cache entry
        unsigned indx = pdc_caches::sa_vcache_index(elem);
        auto& cache = reg_vcaches[nm];
        auto p = cache.find(indx);
        if (p != cache.end()) {
            vline.assign(r,&p->second[0]);
            cache.erase(p);
        }
    }
    vline.add(r,elem,val);
    return ok;
}

void Checkers_pdc_interface::flush_invalidate() {
  if (!write_merge_buffers.empty()) flush_write_merge_buffers();
  mem_caches.clear();
  mem_vcaches.clear();
  reg_vcaches.clear();
  reg_cache.clear();
  reg_cache_loaded = false;
}
