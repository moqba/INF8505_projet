/*
-- File : checkers_pdc_interface.h
--
-- Contents : Implementation of Checkers_debugger interface,
--            in terms of the PDC commands class: pdc_commands.
--
-- Copyright (c) 2014-2018 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/



#ifndef _checkers_pdc_interface_h
#define _checkers_pdc_interface_h

#include <map>
#include <set>
#include <checkers_debugger.h>
#include "pdc_commands.h"

using std::string;
using std::map;

class Checkers_pdc_interface : public Checkers_debugger64 {
public:
    Checkers_pdc_interface(int coreid, string server, int port=41001);
    virtual ~Checkers_pdc_interface();

 // access of special registers :
    virtual void get_status(Core_status*);
    virtual AddressType get_program_counter();
    virtual int put_program_counter(AddressType);

 // reset :
    virtual void reset_pdc();
    virtual void reset_core(bool sync =false);

 // refresh (flush internal buffers and clear caches) :
    virtual void refresh()            { flush_invalidate(); cmd.refresh(); }

 // stop and core-specific step/resume commands :
    virtual void request(bool sync =false)          { cmd.request(sync); }
    virtual void step();
    virtual void step_dis_int();
    virtual void resume();

 // synchronous step/resume commands in multicore context :
#if __tct_release__ >= 1201
    virtual Sync_start_status prepare_sync_command();
#endif
    virtual void sync_step(bool sync =true)         { cmd.step(sync); }
    virtual void sync_resume(bool sync =true)       { cmd.resume(sync); }

 // hardware breakpoints/watchpoints :
    virtual int enable_hw_break(const Breakpoint_settings*);
    virtual int enable_hw_break(const Watchpoint_settings*);
    virtual int disable_hw_break(int nr);

 // software breakpoints (using sw-break instruction) :
    virtual int add_sw_break(AddressType pc, bool export_);
    virtual int remove_sw_break(AddressType pc);

 // access of registers and memories :
    virtual int get_memory_at(string name, AddressType address,DataType&);
    virtual int put_memory_at(string name, AddressType address,const DataType&);
    virtual int get_register(string name, DataType& val);
    virtual int put_register(string name, const DataType& val);

 // element access of vector registers and memories:
    virtual int get_memory_at(string, AddressType addr, unsigned elem,
                              DataType& val);
    virtual int put_memory_at(string, AddressType addr, unsigned elem,
                              const DataType& val);
    virtual int get_register(string name, unsigned elem, DataType& val);
    virtual int put_register(string name, unsigned elem, const DataType& val);

 // verbosity :
    virtual void verbose(int i)       { cmd.verbose(i); }

 // protect memory address range [a,b] from redundant load access
    virtual void protect_memory_at(string name, AddressType a, AddressType b);
    virtual void clear_memory_protections();

 // multiple register contexts
    virtual int get_context();
    virtual int put_context(int);
#if __tct_release__ >= 1201
    virtual Sync_start_status prepare_context_for_resume();
#endif

 // deprecated functions from 11R1 Checkers_debugger interface
    virtual void step(bool)               { return step(); }
    virtual void step_dis_int(bool)       { return step_dis_int(); }
    virtual void resume(bool)             { return resume(); }
    virtual int add_sw_break(unsigned pc) { return add_sw_break(pc,false); }

protected:
    pdc_commands cmd;

 // breakpoints:
    struct pmem_instr_pair {
        pdc_commands::instr_type orig_instr;
        pdc_commands::instr_type sw_break;
    };
    int hw_break_in_use[pdc_commands::nr_breakpoints];
    map<AddressType,pmem_instr_pair> sw_break_instrs;
    map<AddressType,int> hw_break_instrs;
    enum Processor_status { unknown, progress, stopped } status;
    virtual int special_step();
    virtual pdc_commands::instr_type get_instruction_at(AddressType pc);
    virtual void put_instruction_at(AddressType pc, pdc_commands::instr_type);
    virtual AddressType next_instruction(AddressType pc) { return pc+1; }
    virtual AddressType prev_instruction(AddressType pc) { return pc-1; }

 // caching of memory/register get results:
    map<string, map<AddressType,pdc_caches::cache_line> > mem_caches;
    map<string, map<AddressType,pdc_caches::vcache_line> > mem_vcaches;
    map<string, map<unsigned,pdc_caches::sa_vcache_line> > reg_vcaches;
    map<string,DataType> reg_cache;
    bool reg_cache_loaded;
    virtual void load_reg_cache();
    virtual int load_reg_vcache(const std::vector<string>&, pdc_caches::range);

 // write-merge-buffers for vector/record storages:
    map<string,pdc_caches::write_merge_vline> write_merge_buffers;
    void flush_write_merge_buffers();

 // protected memory address ranges
    map<string,std::vector<std::pair<pdc_caches::arange,bool>>> mem_protections;
    std::set<string> scaled_mems;
    pdc_caches::read_once_vline read_once;
    virtual void scale_mem_protections(string, unsigned);
    virtual int get_protect_memory_at(string, AddressType addr, unsigned elem,
                                      DataType& val);

 // use lower case for register names in cache:
    static void to_lower(string& a)
        {
            for (unsigned i = 0; i < a.length(); i++)
                a[i] = tolower(a[i]);
        }

 // when stepping or resuming:
    void flush_invalidate() {
        if (!write_merge_buffers.empty()) flush_write_merge_buffers();
        mem_caches.clear();
        mem_vcaches.clear();
        reg_vcaches.clear();
        reg_cache.clear();
        reg_cache_loaded = false;
        read_once.clear();
    }
};

#endif
