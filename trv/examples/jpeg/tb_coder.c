/*
-- File : tb_coder.c
--
-- Contents: Testbench for BMP truecolor to JPEG encoder
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/


#include "coder.h"

int main()
{
    struct image in_img;
    int result;
    
    init_input(&in_img);

    // set size of input image
    SOF0info.width  = in_img.width;
    SOF0info.height = in_img.height;
    
parsection: // labels for parallelization with MPD
    {
jpg_open:
        {
            init_output();  
            write_headers();
        }

        main_encoder(&in_img);

jpg_close:
        {
            writeword(0xFFD9); // End-Of-Image (EOI)
            result = fini_output();  
        }
    } // end parsection


    fini_input(&in_img);


    return result;
}
