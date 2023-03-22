/*
-- File : fas.v
--
-- Contents : DesignWare wrapper -- floating point adder.
--
-- Copyright (c) 2018-2019 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

`timescale 1ns/1ps

// module fas : fas
module fas
  ( input                clock,
    input                ohe_selector_EX,
    input  signed [31:0] fasA_in, // w32
    input  signed [31:0] fasB_in, // w32
    input                fasM_in, // uint1
    output signed [31:0] fasC_out // w32
  );

  // synopsys dc_tcl_script_begin
  // set_optimize_registers
  // synopsys dc_tcl_script_end

  parameter sig_width       = 15;
  parameter exp_width       = 8;
  parameter data_width      = 1 + exp_width + sig_width;
  parameter ieee_compliance = 1;

  reg    signed [data_width-1:0] fasA;
  reg    signed [data_width-1:0] fasB;
  wire   signed [data_width-1:0] fasC;
  reg                  fasM;
  wire   signed [ 2:0] fasRND = 3'b000; // round to nearest (even)
  wire   signed [ 7:0] fasSTAT;  // unused

  reg    signed [data_width-1:0] fasC_DLY1;

  always @ (*)

  begin : p_fas_isolate
    // operand isolation
    if (ohe_selector_EX == 0)
    begin
      fasA = 0;
      fasB = 0;
      fasM = 0;
    end
    else
    begin
      fasA = fasA_in[data_width-1:0];
      fasB = fasB_in[data_width-1:0];
      fasM = fasM_in;
    end
  end

  DW_fp_addsub #(sig_width, exp_width, ieee_compliance)
               dw_fas(.a(fasA),
                      .b(fasB),
                      .rnd(fasRND),
                      .op(fasM),
                      .z(fasC),
                      .status(fasSTAT) );

`ifdef VERILATOR_COMBINATORIAL_VIEW
  assign fasC_out = { 8'b0, fasC };
`else // Pipelined implementation view
  always @ (posedge clock)
  begin : p_ms_fas
    fasC_DLY1 <= fasC;
  end
  assign fasC_out = { 8'b0, fasC_DLY1 };
`endif

endmodule
