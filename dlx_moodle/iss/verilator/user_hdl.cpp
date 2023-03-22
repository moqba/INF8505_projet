/*
-- File : user_hdl.cpp
--
-- Contents : C++ implementation for connection of custom RTL blocks to verilator models
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- stricfly prohibited. 
*/

/*
-- File : user_hdl.cpp
--
-- Contents : C++ ISS interface methods for the user_div class
--
-- Copyright (c) 2021-2021 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/


#include <verilated.h>          
#include "verilated_hdl_models/Vuser_div.h"
#include "Mdl_dlx.h"
#include "dlx_inline_primitives.h"


namespace dlx_primitive {

    //Constructor - put initialization (reset) functions here
    user_div::user_div(dlx* p) : mdl(p) {

    //Instantiate the verilator model code
    p->user_div_model = new Vuser_div();

    //Reset the verilator model
    p->user_div_model->reset = 0;
    p->user_div_model->eval(); 
    p->user_div_model->clock = 1; 
    p->user_div_model->reset = 1;
    p->user_div_model->eval(); 
    p->user_div_model->clock = 0; 
    p->user_div_model->reset = 0;

    }


    //Combinational process (IN/OUT analyzed by checkers for delta cycles - so this may be called multiple times every cycle)
    void user_div::main() {

        //Set inputs to verilator model
        mdl->user_div_model->div_start      =  mdl->div_start.to_unsigned();
        mdl->user_div_model->div_opA        =  mdl->div_opA.to_unsigned();
        mdl->user_div_model->div_opB        =  mdl->div_opB.to_unsigned();

        //Run the model for a single combinational (delta) cycle
        mdl->user_div_model->eval();            

        //Copy outputs back to ASIP model
        mdl->div_ready.write(mdl->user_div_model->div_ready);
        mdl->div_result.write(mdl->user_div_model->div_result);

        //set debug signals
        mdl->user_div__i_divide__cnt.write(mdl->user_div_model->user_div__DOT__i_divide__DOT__cnt);
        mdl->user_div__i_divide__PA.write(mdl->user_div_model->user_div__DOT__i_divide__DOT__PA);

    }

    //This is called once at end of cycle to upate clock - so this process toggles clock on verilator model 
    void user_div::update_status() {
    
        mdl->user_div_model->clock = 1; 
        mdl->user_div_model->eval(); 
        mdl->user_div_model->clock = 0; 

    }

    //This method is not used so can be empty
    void user_div::clear_update() {}


} // end namespace  dlx_primitive

// End of simulation function

//Connect to ISS model - called when ISS finishes
void verilator_fini(dlx* proc) { 
 
// coprocessor final

    proc->user_div_model->final();
}

