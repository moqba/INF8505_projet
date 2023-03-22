
// Register moves to and from debugger

#include "vlx_define.h"
#include "pdc_data_address.h"

.text_segment PM 0
.entry_point

        sw r0,PDC_DATA_ADDRESS(r0)
        sw r1,PDC_DATA_ADDRESS(r0)
        sw r2,PDC_DATA_ADDRESS(r0)
        sw r3,PDC_DATA_ADDRESS(r0)
        sw r4,PDC_DATA_ADDRESS(r0)
        sw r5,PDC_DATA_ADDRESS(r0)
        sw r6,PDC_DATA_ADDRESS(r0)
        sw r7,PDC_DATA_ADDRESS(r0)

        sw r8, PDC_DATA_ADDRESS(r0)
        sw r9, PDC_DATA_ADDRESS(r0)
        sw r10,PDC_DATA_ADDRESS(r0)
        sw r11,PDC_DATA_ADDRESS(r0)
        sw r12,PDC_DATA_ADDRESS(r0)
        sw r13,PDC_DATA_ADDRESS(r0)
        sw r14,PDC_DATA_ADDRESS(r0)
        sw r15,PDC_DATA_ADDRESS(r0)

        lw r0,PDC_DATA_ADDRESS(r0)
        lw r1,PDC_DATA_ADDRESS(r0)
        lw r2,PDC_DATA_ADDRESS(r0)
        lw r3,PDC_DATA_ADDRESS(r0)
        lw r4,PDC_DATA_ADDRESS(r0)
        lw r5,PDC_DATA_ADDRESS(r0)
        lw r6,PDC_DATA_ADDRESS(r0)
        lw r7,PDC_DATA_ADDRESS(r0)

        lw r8,PDC_DATA_ADDRESS(r0)
        lw r9,PDC_DATA_ADDRESS(r0)
        lw r10,PDC_DATA_ADDRESS(r0)
        lw r11,PDC_DATA_ADDRESS(r0)
        lw r12,PDC_DATA_ADDRESS(r0)
        lw r13,PDC_DATA_ADDRESS(r0)
        lw r14,PDC_DATA_ADDRESS(r0)
        lw r15,PDC_DATA_ADDRESS(r0)
        swbrk

        jr r1
        nop
        nop

