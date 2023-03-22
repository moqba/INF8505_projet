#include <systemc>

#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

#include "dlx_ca_tlm2_systemc.h"

Tcl_Interp* sc_interp=0;

template<int sz, int w>
SC_MODULE(Memory)
{
    tlm_utils::simple_target_socket<Memory, w> socket;
    int mem[sz];

    SC_CTOR(Memory) : socket("socket") {
        socket.register_b_transport(this, &Memory::b_transport);
        socket.register_transport_dbg(this, &Memory::transport_dbg);
        socket.register_get_direct_mem_ptr(this, &Memory::get_direct_mem_ptr);
    }

    void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay) {
        sc_dt::uint64 adr = trans.get_address();
        unsigned char* ptr = trans.get_data_ptr();
        unsigned int len = trans.get_data_length();
        switch(trans.get_command()) {
        case tlm::TLM_READ_COMMAND:  memcpy(ptr, &mem[adr], len); break;
        case tlm::TLM_WRITE_COMMAND: memcpy(&mem[adr], ptr, len); break;
        }
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
    }

    unsigned transport_dbg(tlm::tlm_generic_payload& trans) {
        sc_dt::uint64 adr = trans.get_address();
        unsigned char* ptr = trans.get_data_ptr();
        unsigned int len = trans.get_data_length();
        switch(trans.get_command()) {
        case tlm::TLM_READ_COMMAND:  memcpy(ptr, &mem[adr], len); break;
        case tlm::TLM_WRITE_COMMAND: memcpy(&mem[adr], ptr, len); break;
        }
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
        return len;
    }

    bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi &dmi_properties) {
        dmi_properties.allow_read_write();
        dmi_properties.set_start_address(0);
        dmi_properties.set_end_address(sz-1);
        dmi_properties.set_dmi_ptr((unsigned char*)&mem[0]);
        dmi_properties.set_read_latency(sc_core::sc_time(0, sc_core::SC_NS));
        dmi_properties.set_write_latency(sc_core::sc_time(0, sc_core::SC_NS));
        return true;
    }
};

int sc_main(int argc, char** argv)
{
    if (argc != 1) {
        std::cerr << "Usage: dlx_ca_tlm2" << std::endl;
        return 1;
    }

    // Modules
    Memory<0x100000, 8> dm("DM");
    dlx_sc dlx("dlx");

    // signals
    sc_clock clock;
    sc_signal<bool> reset;
    sc_signal<sc_uint<16>> iack_out;

    // connections
    dlx.clock(clock);
    dlx.reset(reset);
    dlx.iack_out(iack_out);

    dlx.p_DMb.bind(dm.socket);

    // wait for the debugger to join before the actual run
    ChkrsOSCIDebugControl::instance()->startAfterDebuggerJoins();

    // Run the simulation
    reset = 0;
    sc_start(sc_time(100, SC_NS));
    reset = 1;
    sc_start();

    return 0;
}

