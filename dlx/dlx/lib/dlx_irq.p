/*
-- File : dlx_irq.p
--
-- Contents : PDG description of the interrupt I/O interface of the DLX processor
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



// Bookkeeping of external interrupt requests including edge detection

io_interface interrupt_io(ireq_pcu_inp, iack_pcu_out) {
//  external ports
    inport  ireq_inp<uint16>;      // external interrupt request
    outport iack_out<uint16>;      // external interrupt acknowledge

// local registers
    reg reg_ireq0<uint16>;         // registered interrupt request port
    reg reg_ireq1<uint16>;         // delayed reg_ireq0 (edge detection)
    reg reg_ipend<uint16>;         // pending interrupt requests register
    trn      ireq<uint16>;         // interrupt requests sent to the PCU

//  process functions
    process process_result() {
        reg_ireq0 = ireq_inp;
        reg_ireq1 = reg_ireq0;
        ireq = reg_ipend | (reg_ireq0 & ~reg_ireq1);
            // pending interrupts ORed with edge detection incoming interrupts
        ireq_pcu_inp = ireq;
    }
    process process_request() {
        uint8 iack = (in_wait_cycle()) ? 0 : iack_pcu_out;
            // discard PCU acknowledge in wait cycles
        iack_out = iack;
        reg_ipend = ireq & ~iack;
    }
}


// Part of testbench (cf. external module in hdl/go_options.cfg)
// toggle third interrupt pin, so (new) interrupt is always pending

io_interface tb_irq_inp(ireq_inp) {
    reg toggle<uint16>;
    process process_result () { ireq_inp = toggle; }
    process process_request() { toggle ^= 0b0000000000000100; }
}

