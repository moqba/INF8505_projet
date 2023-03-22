/*
-- File : fml.v
--
-- Contents : DesignWare wrapper -- floating point multiplier.
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

// module fml : fml
module fml
  ( input                clock,
    input                ohe_selector_EX,
    input  signed [31:0] fmlA_in, // w32
    input  signed [31:0] fmlB_in, // w32
    output signed [31:0] fmlC_out // w32
  );

  // synopsys dc_tcl_script_begin
  // set_optimize_registers
  // synopsys dc_tcl_script_end

  parameter sig_width       = 23;
  parameter exp_width       = 8;
  parameter ieee_compliance = 1;

  reg    signed [31:0] fmlA;
  reg    signed [31:0] fmlB;
  wire   signed [31:0] fmlC;
  wire   signed [ 2:0] fmlRND = 3'b000; // round to nearest (even)
  wire   signed [ 7:0] fmlSTAT;  // unused

  reg    signed [31:0] fmlC_DLY1;

  always @ (*)

  begin : p_fml_isolate
    if (ohe_selector_EX == 0)
    begin
      fmlA = 0;
      fmlB = 0;
    end
    else
    begin
      fmlA = fmlA_in;
      fmlB = fmlB_in;
    end
  end

  DW_fp_mult #(sig_width, exp_width, ieee_compliance)
             dw_spmp(.a(fmlA),
                     .b(fmlB),
                     .rnd(fmlRND),
                     .z(fmlC),
                     .status(fmlSTAT) );

  always @ (posedge clock)
  begin : p_ms_fml
    fmlC_DLY1 <= fmlC;
  end

  assign fmlC_out = fmlC_DLY1;

endmodule
