/*
-- File : ffi.v
--
-- Contents : DesignWare wrapper -- floating to integer conversion.
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

// module ffi : ffi
module ffi
  ( input                    ohe_selector_EX,
    input      signed [31:0] ffiA_in, // w32
    output     signed [31:0] ffiC_out // w32
  );

  parameter sig_width       = 15;
  parameter exp_width       = 8;
  parameter data_width      = 1 + exp_width + sig_width;
  parameter ieee_compliance = 1;
  parameter isize           = 32;

  reg    signed [data_width-1:0] ffiA;
  wire   signed [31:0] ffiC;
  wire   signed [ 2:0] ffiRND = 3'b001; // round to zero (truncate) cf. C
  wire   signed [ 7:0] ffiSTAT;  // unused

  always @ (*)

  begin : p_ffi_isolate
    if (ohe_selector_EX == 0)
    begin
      ffiA = 0;
    end
    else
    begin
      ffiA = ffiA_in[data_width-1:0];
    end
  end

  DW_fp_flt2i #(sig_width, exp_width, isize, ieee_compliance)
              dw_ffi (.a(ffiA),
                      .rnd(ffiRND),
                      .z(ffiC),
                      .status(ffiSTAT) );

  assign ffiC_out = ffiC;

endmodule
