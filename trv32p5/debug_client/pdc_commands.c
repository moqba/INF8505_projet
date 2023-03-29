/*
-- File : pdc_commands.c
--
-- Contents : Implementation of PDC command class.
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#include "pdc_commands.h"
#include "pdc_data_address.h"
#include <stdlib.h>
#include <sstream>

using std::string;
using std::cerr;

#include "pdc_init_bpwp_codes.c"
#include "pdc_register_moves.h"

string pdc_commands::pc_name = "pc";   // lower case for use in register cache
string pdc_commands::pmem_name = "PMb";

#define vrb() if (unlikely(verb)) std::cerr

pdc_commands::pdc_commands(int coreid, string server, int port)
    : cbl(coreid,server, port)
{
    init_bpwp_codes(coreid);
    init_pdc_codes(coreid);
    init_instr_codes();

    if (cbl.open() != 0) {
        std::cerr << "Cannot establish connection with server " << server << "\n";
        exit(1);
    }
}

pdc_commands::~pdc_commands()
{
    flush_buffer();
    cbl.close();
}

void pdc_commands::init_instr_codes() {
  std::map<std::string, VBitWrapper> instr;
  get_instr_map(instr);

  // split
  std::string reg_get = "reg_get_";
  std::string reg_put = "reg_put_";
  std::string swbrk = "swbrk";
  std::string jalr = "jalr_x3";
  for (const auto& kv: instr) {
    auto& lbl = kv.first;
    auto& enc = kv.second;
    if (lbl.compare(0, reg_get.size(), reg_get) == 0) {
      reg_get_code[lbl.substr(reg_get.size())] = enc;
      vrb() << "Loaded reg_get_code for " << lbl.substr(reg_get.size())
            << ": 0x" << enc.toHex() << "\n";
    }
    if (lbl.compare(0, reg_put.size(), reg_put) == 0) {
      reg_put_code[lbl.substr(reg_put.size())] = enc;
      vrb() << "Loaded reg_put_code for " << lbl.substr(reg_put.size())
            << ": 0x" << enc.toHex() << "\n";
    }
    if (lbl.compare(0, swbrk.size(), swbrk) == 0) {
      swbrk_code[std::stoi(lbl.substr(swbrk.size()))] = enc;
      vrb() << "Loaded swbrk code for " << lbl
            << ": 0x" << enc.toHex()  << "\n";
    }
    if (lbl.compare(0, jalr.size(), jalr) == 0) {
      jalr_x3_instr = enc;
      vrb() << "Loaded jalr code for " << lbl << ": 0x" << enc.toHex()  << "\n";
    }
  }
}

// PDC op codes have following format: iiiiixxxxxxxxxxx
//     iiiii       is a 5 bit core ID
//     xxxxxxxxxxx is the 11 bit opcode

void pdc_commands::init_pdc_codes(int core_id)
{
    if (core_id > max_core_id) {
        std::cerr << "invalid core_id (maximum coreid = " << max_core_id << "): "
             << core_id << "\n";
        exit(1);
    }

    // core ID
    int cid = core_id << 11;

    // instruction opcodes
    request_instr  = cid | DBG_REQUEST_INSTR;
    resume_instr   = cid | DBG_RESUME_INSTR;
    reset_instr    = cid | DBG_RESET_INSTR;
    step_instr     = cid | DBG_STEP_INSTR;
    stepdi_instr   = cid | DBG_STEPDI_INSTR;
    execute_instr  = cid | DBG_EXECUTE_INSTR;

    // load/store instruction codes: 000010mmmmi
    mem_instr["DMb"]  = pdc_mem_instr(cid | DBG_DMb_LOAD_INSTR,
                                      cid | DBG_DMb_STORE_INSTR,false);
    mem_instr["PMb"]  = pdc_mem_instr(cid | DBG_PMb_LOAD_INSTR,
                                      cid | DBG_PMb_STORE_INSTR, true);

    reg_access_via_mem.name = "DMb";
    reg_access_via_mem.addr = PDC_DATA_ADDRESS;
}

// status reg bits
//    8   7    6    5    4    3    2    1    0
//    SWB BO   BI   HIT  BP3  BP2  BP1  BP0  MODE

inline bool debug_mode(VBitWrapper const& sreg) { return sreg.getBit(DBG_MODE_INDX); }
inline bool hit_set   (VBitWrapper const& sreg) { return sreg.getBit(DBG_BP_HIT_INDX); }
inline bool bi_set    (VBitWrapper const& sreg) { return sreg.getBit(DBG_BREAKIN_INDX); }
inline bool swb_set   (VBitWrapper const& sreg) { return sreg.getBit(DBG_SWBREAK_INDX); }
inline bool bpi_set   (VBitWrapper const& sreg, int i) { return sreg.getBit(DBG_MODE_INDX + 1 + i); }

std::string vrb_fmt_core_status(VBitWrapper const& sreg) {
  std::stringstream msg;
  msg << "Core status for sreg=0b" << sreg.toBin() << "\n"
      << "  dbg_mode " << debug_mode(sreg) << "\n"
      << "  hit_set  " << hit_set(sreg)    << "\n"
      << "  bi_set   " << bi_set(sreg)     << "\n"
      << "  swb_set  " << swb_set(sreg)    << "\n";
  if (hit_set(sreg)) {
      for (int i = 0; i < (DBG_BP_HIT_INDX - 1 - DBG_MODE_INDX); i++)
          if (bpi_set(sreg,i))
              msg << "  HW break #" << i << "\n";
  }
  return msg.str();
}

void pdc_commands::get_status(Core_status* cs)
{
    VBitWrapper sreg;
    vrb() << "PDC get status register ...\n";
    cbl.add_dread(ocd_cable::stat);
    send_and_receive();
    cbl.get_next_data(sreg);

    vrb() << " read: " << sreg << "\n";
    *cs = Core_status();   // initialise "cs" to running.
    if (debug_mode(sreg))
        cs->running = false;
    if (hit_set(sreg)) {
        cs->hw_break = true;
        for (int i = 0; i < nr_breakpoints; i++)
            if (bpi_set(sreg,i))
                cs->hw_break_nr.push_back(i);
    }
    if (bi_set(sreg))
        cs->external_break = true;
    if (swb_set(sreg))
        cs->sw_break = true;
    vrb() << vrb_fmt_core_status(sreg);
}

// memory and register access

int pdc_commands::put_memory_at(string nm, AddressType address,
                                const DataType& value)
{
    std::map<string,pdc_mem_instr>::iterator p = mem_instr.find(nm);
    if (p == mem_instr.end())
        return Checkers_debugger::failed;

    vrb() << "PDC put memory: " << nm << ", " << address
          << ", 0x" << value.toHex() << "\n";
    put_address_register(address);
    if (p->second.via_inst_reg) {
        cbl.add_dwrite(ocd_cable::inst,value);
    } else {
        cbl.add_dwrite(ocd_cable::data,value);
    }
    execute_ldst_instr(p->second.st_instr,p->second.addr_incr);
    return Checkers_debugger::ok;
}

int pdc_commands::get_memory_at(string nm, AddressType address)
{
    std::map<string,pdc_mem_instr>::iterator p = mem_instr.find(nm);
    if (p == mem_instr.end())
        return Checkers_debugger::failed;

    vrb() << "PDC get memory: " << nm << ", " << address << "\n";
    put_address_register(address);
    execute_ldst_instr(p->second.ld_instr,p->second.addr_incr);
    if (p->second.via_inst_reg) {
        cbl.add_dread(ocd_cable::inst);
    } else {
        cbl.add_dread(ocd_cable::data);
    }
    return Checkers_debugger::ok;
}

int pdc_commands::put_register(string name, const DataType& value)
{
    if (!reg_put_code.count(name))
        return Checkers_debugger::failed;

    vrb() << "PDC put_register: " << name << ", " << value << "\n";
    // put value to memory (in 4 consecutive bytes)
    for (int i = 0; i < 4; i++) {  // LITTLE endian
        VBitWrapper byte(value.extract((i+1)*8-1,i*8).to<VBit<8,false>>());
        put_memory_at(reg_access_via_mem.name, reg_access_via_mem.addr+i, byte);
    }
    // load register move instruction in instruction register
    cbl.add_dwrite(ocd_cable::inst,reg_put_code[name]);
    // execute move instruction (memory load)
    cbl.add_iwrite(execute_instr);
    return Checkers_debugger::ok;
}

int pdc_commands::get_register(string name)
{
    if (!reg_get_code.count(name))
        return Checkers_debugger::failed;

    vrb() << "PDC get_register: " << name << "\n";
    // load register move instruction in instruction register
    cbl.add_dwrite(ocd_cable::inst,reg_get_code[name]);
    // execute move instruction (memory store)
    cbl.add_iwrite(execute_instr);
    // get value from memory (4 consecutive bytes)
    for (int i = 0; i < 4; i++) {
        get_memory_at(reg_access_via_mem.name,reg_access_via_mem.addr+i);
    }
    return Checkers_debugger::ok;
}

int pdc_commands::put_program_counter(AddressType a)
{
 // backup x3 and write new pc value to it
    get_register("x3");
    put_register("x3",a);
 // load "goto r3" in instruction register, and execute instruction
    cbl.add_dwrite(ocd_cable::inst,jalr_x3_instr);
    cbl.add_iwrite(execute_instr);
    send_and_receive();
 // restore x3
    put_register("x3",received_next_reg("x3"));
    vrb() << "PDC put PC: " << a << "\n";
    return Checkers_debugger::ok;
}

// vector register and memory access
// (only for PM which is accessed as 4 byte vector)

int pdc_commands::get_register(string, pdc_caches::range)
{
    return Checkers_debugger::failed;
}

int pdc_commands::get_memory_at(string nm, AddressType addr, pdc_caches::range)
{
    if (nm == "PMb") {
      return get_memory_at(nm,addr*4);
    } else {
      std::cerr << "ERROR: get_memory_at(" << nm << ") vector version called\n";
      exit(1);
    }
}

void pdc_commands::received_next(string nm, pdc_caches::range,
                                 std::vector<DataType>& vals)
{
    if (nm == "PMb") {
        DataType val = received_next(); // LITTLE endian
        vals[0] = VBitWrapper(val.extract(7,0).to<VBit<8,false>>());
        vals[1] = VBitWrapper(val.extract(15,8).to<VBit<8,false>>());
        vals[2] = VBitWrapper(val.extract(23,16).to<VBit<8,false>>());
        vals[3] = VBitWrapper(val.extract(31,24).to<VBit<8,false>>());
    } else {
        std::cerr << "ERROR: received_next(" << nm << ") vector version called\n";
        exit(1);
    }
}

int pdc_commands::put_register(string, pdc_caches::range,
                               const std::vector<DataType>&)
{
    return Checkers_debugger::failed;
}

int pdc_commands::put_memory_at(string nm, AddressType addr, pdc_caches::range,
                                const std::vector<DataType>& vals)
{
    if (nm == "PMb") {
        VBitWrapper val = VBit<32,false>(0); // LTTLE endian
        val.deposit(vals[0],7,0);
        val.deposit(vals[1],15,8);
        val.deposit(vals[2],23,16);
        val.deposit(vals[3],31,24);
        return put_memory_at(nm,addr*4,val);
    } else {
        std::cerr << "ERROR: put_memory_at(" << nm << ") vector version called\n";
        exit(1);
    }
}


void pdc_commands::request(bool sync)
{
    vrb() << "PDC " << (sync ? "sync request\n" : "request\n");
    cbl.add_iwrite(sync ? DBG_SYNC_REQUEST_INSTR : request_instr);
    send_and_receive();
}

void pdc_commands::resume(bool sync)
{
    vrb() << "PDC " << (sync ? "sync resume\n" : "resume\n");
    cbl.add_iwrite(sync ? DBG_SYNC_RESUME_INSTR : resume_instr);
    send_and_receive();
}

void pdc_commands::step(bool sync)
{
    vrb() << "PDC " << (sync ? "sync step\n" : "step\n");
    cbl.add_iwrite(sync ? DBG_SYNC_STEP_INSTR : step_instr);
    send_and_receive();
}

void pdc_commands::step_dis_int(bool sync)
{
    vrb() << "PDC " << (sync ? "sync step_dis_int\n":"step_dis_int\n");
    cbl.add_iwrite(sync ? DBG_SYNC_STEPDI_INSTR : stepdi_instr);
    send_and_receive();
}

void pdc_commands::reset_core(bool sync)
{
    vrb() << "PDC " << (sync ? "sync reset core\n" : "reset core\n");
    cbl.add_iwrite(sync ? DBG_SYNC_RESET_INSTR : reset_instr);
    send_and_receive();
    ocd_address_set = false;
}

void pdc_commands::enable_hw_break(int nr, const Breakpoint_settings* bs)
{
    vrb() << "PDC enable breakpoint " << nr << "\n";
    put_address_register(bs->address);
    cbl.add_iwrite(bp_enable_instr[nr]);
    if (bs->export_)
        cbl.add_iwrite(bp_export_instr[nr]);
    send_and_receive();
}

int pdc_commands::watch_supported(const Watchpoint_settings* ws, bool& aligned_pairs)
{
    std::string mem = bp_root_mem[ws->memory];
    if ((ws->on_write && bp_watch_store_instr.count(mem) == 0)
        || (ws->on_read && bp_watch_load_instr.count(mem) == 0)
        || (ws->block_size > 1 && DBG_RANGE_WATCHPOINTS == 0))
        return 0;

    int nr = 0;  // number of address registers required
    aligned_pairs = false;
    if (ws->on_write) nr = 1;
    if (ws->on_read) nr = (DBG_LDST_WATCHPOINTS) ? 1 : nr + 1;
    if (ws->block_size > 1) {
        nr *= 2;
        aligned_pairs = true;
    }
    return nr;
}

void pdc_commands::enable_hw_break(const std::vector<int>& nrs,
                                          const Watchpoint_settings* ws)
{
    std::string mem = bp_root_mem[ws->memory];
    if (ws->block_size > 1) {
        // assuming range_watchpoints && ldst_watchpoints
        // configuration using data register
        // bit n..4: memory-id
        // bit 3: export
        // bit 2: range wp
        // bit 1: store wp
        // bit 0: read wp
        int config = bp_mem_nr[mem] << 4 |
                     static_cast<int>(ws->export_) << 3 |
                     1 << 2 |
                     static_cast<int>(ws->on_write) << 1 |
                     static_cast<int>(ws->on_read);
        put_address_register(ws->address);
        cbl.add_dwrite(ocd_cable::data,config);
        cbl.add_iwrite(bpu_config_instr[nrs.front()]);
        put_address_register(ws->address + ws->block_size - 1);
        cbl.add_iwrite(bpu_config_instr[nrs.back()]);
        cbl.add_iwrite(bpu_enable_instr[nrs.front()]);
        vrb() << "PDC enable range watchpoint " << nrs.front() << "/" << nrs.back()
              << " (" << ((ws->on_read)? " read ":"") << ((ws->on_write)? " write ":"") << ")\n";
    } else {
        // configuration using bp_watch_load/store opcodes
        put_address_register(ws->address);
        if (ws->on_read) {
            vrb() << "PDC enable read watchpoint " << nrs.front() << "\n";
            cbl.add_iwrite(bp_watch_load_instr[mem][nrs.front()]);
            if (ws->export_) cbl.add_iwrite(bp_export_instr[nrs.front()]);
        }
        if (ws->on_write) {
            vrb() << "PDC enable write watchpoint " << nrs.back() << "\n";
            cbl.add_iwrite(bp_watch_store_instr[mem][nrs.back()]);
            if (ws->export_) cbl.add_iwrite(bp_export_instr[nrs.back()]);
        }
    }
    send_and_receive();
}

void pdc_commands::disable_hw_break(const std::vector<int>& nrs)
{
    for (unsigned i = 0; i < nrs.size(); i++) {
        vrb() << "PDC disable breakpoint " << nrs[i] << "\n";
        cbl.add_iwrite(bp_disable_instr[nrs[i]]);
    }
    send_and_receive();
}

AddressType pdc_commands::get_program_counter()
{
    AddressType val = current_address;  // restore addr_reg
    cbl.add_dwrite_dread(ocd_cable::addr,val);
    send_and_receive();
    val = received_next().to_address();
    vrb() << "PDC read PC: " << val << "\n";
    return val;
}

pdc_commands::instr_type pdc_commands::sw_break_instr(bool export_, instr_type orig)
{
  unsigned ilen = orig.getBitSize();

  if (swbrk_code.count(ilen) == 0) {
    std::cerr << "ERROR: Found no software break instruction of length "
              << ilen << " bits\n";
    return instr_type();
  }

  vrb() << "INFO: Using swbrk" << ilen << " instruction for original instr: "
        << "0x" << orig.toHex() << "\n";

  return swbrk_code[ilen];
}

DataType pdc_commands::received_next()
{
    DataType v;
    if (cbl.get_next_data(v) != 0) {
        std::cerr << "PDC read answer failed\n";
        throw std::runtime_error("PDC read answer failed");
        //chkapi_errorsp->put(chkapi_ERR, "PDC read answer failed", "pdc_commands::received_next");
    }
    return v;
}

DataType pdc_commands::received_next_reg(std::string)
//  a register read is done by doing 4 consecutive byte memory loads
{
    VBit<32,false> v = 0;
    for (int i = 0; i < 4; i++)   // LITTLE endian
        v.deposit(received_next().to<VBit<8,false>>(), (i+1)*8-1, i*8);
    return v;
}

void pdc_commands::check_buffer_overflow()
{
    if (cbl.buffer_overflow_imminent()) send_and_receive();
}

void pdc_commands::flush_buffer()
{
    if (!cbl.buffer_is_empty()) send_and_receive();
}

void pdc_commands::put_address_register(AddressType a) {
  if (a != current_address || !ocd_address_set) {
    vrb() << "PDC put address register: " << a << "\n";
    cbl.add_dwrite(ocd_cable::addr,a);
    current_address = a;
    ocd_address_set = true;
  }
}

void pdc_commands::put_data_register(const DataType& dat) {
  vrb() << "PDC put data register: " << dat << "\n";
  cbl.add_dwrite(ocd_cable::data,dat);
}

void pdc_commands::execute_ldst_instr(int ldst_instr, int incr) {
  cbl.add_iwrite(ldst_instr);
  current_address += incr;
}

unsigned pdc_commands::vector_size(std::string name) {
  return name == "PMb" ? 4 : 0;
}

unsigned pdc_commands::address_step(std::string) {
  return 1;
}

void pdc_commands::send_and_receive() {
  cbl.send_and_receive();
}

int pdc_commands::get_register(std::string name, DataType& value) {
  if (get_register(name) == Checkers_debugger::ok) {
    send_and_receive();
    value = received_next_reg(name);
    return Checkers_debugger::ok;
  }
  return Checkers_debugger::failed;
}

int pdc_commands::get_memory_at(std::string name, AddressType address, DataType& value) {
  if (get_memory_at(name,address) == Checkers_debugger::ok) {
    send_and_receive();
    value = received_next_mem(name);
    return Checkers_debugger::ok;
  }
  return Checkers_debugger::failed;
}

DataType pdc_commands::received_next_mem(std::string) {
  return received_next();
}

void pdc_commands::refresh() {
  flush_buffer();
}

void pdc_commands::verbose(int lvl) {
  if (lvl > 0) {
    verb = true;
    cbl.set_verbose(lvl-1);
  }
}
