/*
-- File : fas.v
--
-- Contents : DesignWare wrapper -- floating point adder.
--
-- Copyright (c) 2018-2021 Synopsys, Inc. This Synopsys processor model
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

  parameter sig_width       = 23;
  parameter exp_width       = 8;
  parameter ieee_compliance = 1;

  reg    signed [31:0] fasA;
  reg    signed [31:0] fasB;
  wire   signed [31:0] fasC;
  reg                  fasM;
  wire   signed [ 2:0] fasRND = 3'b000; // round to nearest (even)
  wire   signed [ 7:0] fasSTAT;  // unused

  reg    signed [31:0] fasC_DLY1;

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
      fasA = fasA_in;
      fasB = fasB_in;
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

  always @ (posedge clock)
  begin : p_ms_fas
    fasC_DLY1 <= fasC;
  end

  assign fasC_out = fasC_DLY1;

endmodule
