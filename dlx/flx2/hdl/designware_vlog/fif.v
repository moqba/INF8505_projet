/*
-- File : fif.v
--
-- Contents : DesignWare wrapper -- integer to float conversion.
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

// module fif : fif
module fif
  ( input                    ohe_selector_EX,
    input      signed [31:0] fifA_in, // w32
    output     signed [31:0] fifC_out // w32
  );

  parameter sig_width       = 23;
  parameter exp_width       = 8;
  parameter isize           = 32;
  parameter isign           = 1;

  reg    signed [31:0] fifA;
  wire   signed [31:0] fifC;
  wire   signed [ 2:0] fifRND = 3'b000; // round to nearest (even)
  wire   signed [ 7:0] fifSTAT;  // unused

  always @ (*)
  begin : p_fif_isolate
    if (ohe_selector_EX == 0)
    begin
      fifA = 0;
    end
    else
    begin
      fifA = fifA_in;
    end
  end

  DW_fp_i2flt #(sig_width, exp_width, isize, isign)
              dw_fif(.a(fifA),
                     .rnd(fifRND),
                     .z(fifC),
                     .status(fifSTAT) );

  assign fifC_out = fifC;

endmodule
