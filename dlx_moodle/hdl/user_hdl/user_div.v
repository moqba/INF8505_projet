
//User Verilog code for divide function

`timescale 1ns/1ps

//`include "divide.v"

//Wrapper for divide module to allow different port names

module user_div
  ( input                    reset,
    input                    clock,
    input                    div_start,
    input      signed [31:0] div_opA,
    input      signed [31:0] div_opB,
    output                   div_ready,
    output            [63:0] div_result
  );


//Instantiate and connect the divide module

divide i_divide (
    
    .clock(clock),
    .reset(reset),
    .start(div_start),
    .opA(div_opA),
    .opB(div_opB),
    .ready(div_ready),
    .result(div_result)
);

endmodule // user_div

