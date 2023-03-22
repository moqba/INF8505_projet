/*
-- File : dlx_div_ext_hdl.p
--
-- Contents : Interface to external RTL for multi-cycle divide unit
--
-- Copyright (c) 2021-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

class uint64  property(64 bit unsigned);

// Behavioural model for IA ISS
#ifdef __checkers__
void divide(w32 numerator, w32 denominator, w32& quotient, w32& remainder)
{
    quotient = (uint32_t)numerator / (uint32_t)denominator;
    remainder = (uint32_t)numerator % (uint32_t)denominator;
}
#endif


/*
This multi-cycle functional unit provides the interface between the custom RTL and
the processor core.  It performs two functions:
  1- create the I/O interface port to connect the top level module of the custom RTL
  2- implement the logic to control the RTL module and provide control/status signals
     back to the processor core
*/

multicycle_fu div
{

//These I/O pins connected to a PDG I/O block which is the connector to the custom RTL
outport div_start<uint1>;
outport div_opA<w32>;
outport div_opB<w32>;
inport div_result<uint64>;
inport div_ready<uint1>;

reg div_busy_reg<uint1>;  hw_init div_busy_reg = 0; //provide a busy register


// Provide interface from external RTL function to processor pipeline

    //set inputs to RTL block
    process set_inputs() {
       //active when divide instruction is in EX stage
        uint1_t start = vd_divide_divA_divB_wl_wh_div_EX_sig;
        div_start = start;
        div_opA = 0;
        div_opB = 0;

        //Set inputs only when divide function is started
        if (start) {
            div_opA = divA;
            div_opB = divB;
        }
      }

    //Read outputs from RTL block
    process read_outputs() {
        uint64_t result = div_result;

        //If done then write result back to core
        if (div_ready) {
            PL = wl = result[31:0];
            PH = wh = result[63:32];
          }
        }

    //Send state to core
    process state_to_core() {

        //active when divide instruction is in EX stage
        uint1_t start = vd_divide_divA_divB_wl_wh_div_EX_sig;

        //these transitories are used by the hw_stall rules
        div_busy = start || div_busy_reg;
        div_busy_raw = start || div_busy_reg;
        div_busy_wb = div_busy_reg;

        //Update the busy status register
        if (start)
          div_busy_reg = 1;  //Set busy when divide started
        if (div_ready)
          div_busy_reg = 0;  //Clear busy when divide complete
       }


}


//Provides the connection to the custom RTL block

io_interface user_div ( div_start,div_opA,div_opB,div_ready,div_result)
{

/*These transitories are defined to allow access to internal signals in the
  verilated RTL model.  They are written in the verilated model wrapper
  so that they can be displayed in chessde
*/
#ifdef __checkers__
trn i_divide__cnt<uint5_t>; //Verilated model -> user_div__DOT__i_divide__DOT__cnt
trn i_divide__PA<uint64_t>; //Verilated model -> user_div__DOT__i_divide__DOT__PA
#endif

 /*
 Empty process with IN/OUT specifier will create:
  - empty RTL module with ports that can be replaced with custom RTL via Go configuration
  - class definition in ISS header file that can be implemented with custom C++ code integrating
    C++ behavior code (generated from Verilator)
 */
  process main (IN div_start, IN div_opA, IN div_opB, OUT div_ready, OUT div_result);
}

