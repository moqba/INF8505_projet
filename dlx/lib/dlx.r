#include "dlx_define.h"

// for use in (inline) assembly

// immediate for 'mv ze, imm', 'mv zs, imm'. chess_pc_offset = 2 instr
0 : (((symbol_addr_AR  + addend )  - item_addr_AR )  - 8 )  :  int16 [15..0]@0 in w08[4]

