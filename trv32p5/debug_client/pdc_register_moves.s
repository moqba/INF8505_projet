// Register moves to and from debugger

#include "pdc_data_address.h"
#include "trv32p5_define.h"

.text_segment PM 0
.entry_point

//
// See ins2c.tcl
//
// These instructions are used by the debug client.
// The clients sends the instructions to the core for execution.
// We use assembler -> disassembler to identify the instruction encodings.
// The disassembly needs to be post-processed (ins2c.tcl) to extract the
// encodings and store them for the client, before compiling the client.

l_reg_get_x0: sw x0, PDC_DATA_ADDRESS(x0)
l_reg_get_x1: sw x1, PDC_DATA_ADDRESS(x0)
l_reg_get_x2: sw x2, PDC_DATA_ADDRESS(x0)
l_reg_get_x3: sw x3, PDC_DATA_ADDRESS(x0)
l_reg_get_x4: sw x4, PDC_DATA_ADDRESS(x0)
l_reg_get_x5: sw x5, PDC_DATA_ADDRESS(x0)
l_reg_get_x6: sw x6, PDC_DATA_ADDRESS(x0)
l_reg_get_x7: sw x7, PDC_DATA_ADDRESS(x0)
l_reg_get_x8: sw x8, PDC_DATA_ADDRESS(x0)
l_reg_get_x9: sw x9, PDC_DATA_ADDRESS(x0)

l_reg_get_x10: sw x10, PDC_DATA_ADDRESS(x0)
l_reg_get_x11: sw x11, PDC_DATA_ADDRESS(x0)
l_reg_get_x12: sw x12, PDC_DATA_ADDRESS(x0)
l_reg_get_x13: sw x13, PDC_DATA_ADDRESS(x0)
l_reg_get_x14: sw x14, PDC_DATA_ADDRESS(x0)
l_reg_get_x15: sw x15, PDC_DATA_ADDRESS(x0)

l_reg_get_x16: sw x16, PDC_DATA_ADDRESS(x0)
l_reg_get_x17: sw x17, PDC_DATA_ADDRESS(x0)
l_reg_get_x18: sw x18, PDC_DATA_ADDRESS(x0)
l_reg_get_x19: sw x19, PDC_DATA_ADDRESS(x0)

l_reg_get_x20: sw x20, PDC_DATA_ADDRESS(x0)
l_reg_get_x21: sw x21, PDC_DATA_ADDRESS(x0)
l_reg_get_x22: sw x22, PDC_DATA_ADDRESS(x0)
l_reg_get_x23: sw x23, PDC_DATA_ADDRESS(x0)
l_reg_get_x24: sw x24, PDC_DATA_ADDRESS(x0)
l_reg_get_x25: sw x25, PDC_DATA_ADDRESS(x0)
l_reg_get_x26: sw x26, PDC_DATA_ADDRESS(x0)
l_reg_get_x27: sw x27, PDC_DATA_ADDRESS(x0)
l_reg_get_x28: sw x28, PDC_DATA_ADDRESS(x0)
l_reg_get_x29: sw x29, PDC_DATA_ADDRESS(x0)

l_reg_get_x30: sw x30, PDC_DATA_ADDRESS(x0)
l_reg_get_x31: sw x31, PDC_DATA_ADDRESS(x0)

l_reg_put_x0: lw x0, PDC_DATA_ADDRESS(x0)
l_reg_put_x1: lw x1, PDC_DATA_ADDRESS(x0)
l_reg_put_x2: lw x2, PDC_DATA_ADDRESS(x0)
l_reg_put_x3: lw x3, PDC_DATA_ADDRESS(x0)
l_reg_put_x4: lw x4, PDC_DATA_ADDRESS(x0)
l_reg_put_x5: lw x5, PDC_DATA_ADDRESS(x0)
l_reg_put_x6: lw x6, PDC_DATA_ADDRESS(x0)
l_reg_put_x7: lw x7, PDC_DATA_ADDRESS(x0)
l_reg_put_x8: lw x8, PDC_DATA_ADDRESS(x0)
l_reg_put_x9: lw x9, PDC_DATA_ADDRESS(x0)

l_reg_put_x10: lw x10, PDC_DATA_ADDRESS(x0)
l_reg_put_x11: lw x11, PDC_DATA_ADDRESS(x0)
l_reg_put_x12: lw x12, PDC_DATA_ADDRESS(x0)
l_reg_put_x13: lw x13, PDC_DATA_ADDRESS(x0)
l_reg_put_x14: lw x14, PDC_DATA_ADDRESS(x0)
l_reg_put_x15: lw x15, PDC_DATA_ADDRESS(x0)

l_reg_put_x16: lw x16, PDC_DATA_ADDRESS(x0)
l_reg_put_x17: lw x17, PDC_DATA_ADDRESS(x0)
l_reg_put_x18: lw x18, PDC_DATA_ADDRESS(x0)
l_reg_put_x19: lw x19, PDC_DATA_ADDRESS(x0)

l_reg_put_x20: lw x20, PDC_DATA_ADDRESS(x0)
l_reg_put_x21: lw x21, PDC_DATA_ADDRESS(x0)
l_reg_put_x22: lw x22, PDC_DATA_ADDRESS(x0)
l_reg_put_x23: lw x23, PDC_DATA_ADDRESS(x0)
l_reg_put_x24: lw x24, PDC_DATA_ADDRESS(x0)
l_reg_put_x25: lw x25, PDC_DATA_ADDRESS(x0)
l_reg_put_x26: lw x26, PDC_DATA_ADDRESS(x0)
l_reg_put_x27: lw x27, PDC_DATA_ADDRESS(x0)
l_reg_put_x28: lw x28, PDC_DATA_ADDRESS(x0)
l_reg_put_x29: lw x29, PDC_DATA_ADDRESS(x0)

l_reg_put_x30: lw x30, PDC_DATA_ADDRESS(x0)
l_reg_put_x31: lw x31, PDC_DATA_ADDRESS(x0)

l_swbrk32: swbrk

l_jalr_x3: jalr x3,x3,0

