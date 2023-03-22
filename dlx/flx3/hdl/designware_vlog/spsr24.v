
// File generated by Go version P-2019.03#56468a4891#181207, Mon Dec 10 09:54:02 2018
// Copyright 2014-2019 Synopsys, Inc. All rights reserved.
// go -B -I../lib -F -p -I../lib -I../lib/../../pde/lib -DADE -DPDE_IO_TST -Verilog -oade_vlog -cgo_options.cfg -Iade_vlog/tmp_pdg -updg -updg_controller ade



`timescale 1ns/1ps

// module spsr : spsr
module spsr24 (
    input      signed [31:0] spsrAf_in, // w32
    output     signed [31:0] spsrRf_out // w32
  );

  wire    [ 2:0] fpuRND = 3'b000; // round to nearest (even)
  wire    [ 7:0] fpuSTAT;  // unused

  DW_fp_sqrt #(
      .sig_width(15),
      .exp_width(8),
      .ieee_compliance(1))
    U1 (
      .a(spsrAf_in[23:0]),
      .rnd(fpuRND),
      .z(spsrRf_out[23:0]),
      .status(fpuSTAT) );


endmodule