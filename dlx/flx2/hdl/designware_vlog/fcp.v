/*
-- File : fcp.v
--
-- Contents : DesignWare wrapper -- floating point comparator.
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

// module fcp : fcp
module fcp
  ( input              [1:0] bin_selector_EX,
    input      signed [31:0] fcpA_in, // w32
    input      signed [31:0] fcpB_in, // w32
    output     signed [31:0] fcpC_out // w32
  );

  parameter sel_sfeq_w32 = 2'b01;
  parameter sel_sfle_w32 = 2'b10;
  parameter sel_sflt_w32 = 2'b11;

  parameter sig_width       = 23;
  parameter exp_width       = 8;
  parameter ieee_compliance = 1;

  reg    signed [31:0] fcpA;
  reg    signed [31:0] fcpB;
  reg    signed [31:0] fcpC;
  wire                 fcpLT;
  wire                 fcpGT;
  wire                 fcpEQ;
  wire                 fcpUO;
  wire                 fcpZ = 0;
  wire   signed [31:0] fcpZ0;
  wire   signed [31:0] fcpZ1;
  wire   signed [ 7:0] fcpS0;
  wire   signed [ 7:0] fcpS1;

  always @ (*)

  begin : p_fcp_isolate
    if (bin_selector_EX == 0)
    begin
      fcpA = 0;
      fcpB = 0;
    end
    else
    begin
      fcpA = fcpA_in;
      fcpB = fcpB_in;
    end
  end

  DW_fp_cmp #(sig_width, exp_width, ieee_compliance)
            dw_fcp(.a(fcpA),
                   .b(fcpB),
                   .zctr(fcpZ),
                   .aeqb(fcpEQ),
                   .altb(fcpLT),
                   .agtb(fcpGT),
                   .unordered(fcpUO),
                   .z0(fcpZ0),
                   .z1(fcpZ1),
                   .status0(fcpS0),
                   .status1(fcpS1) );


  always @ (*)
  begin : p_fcp_result
    fcpC = 32'sb00000000000000000000000000000000;
    case (bin_selector_EX)
      sel_sfle_w32:
          fcpC = (fcpLT | fcpEQ) ? 32'sb00000000000000000000000000000001
                                 : 32'sb00000000000000000000000000000000;
      sel_sflt_w32:
          fcpC = (fcpLT)         ? 32'sb00000000000000000000000000000001
                                 : 32'sb00000000000000000000000000000000;
      sel_sfeq_w32:
          fcpC = (fcpEQ)         ? 32'sb00000000000000000000000000000001
                                 : 32'sb00000000000000000000000000000000;
      default : ; // null
    endcase
  end

  assign fcpC_out = fcpC;
endmodule
