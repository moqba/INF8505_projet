
// Register moves to and from debugger

#include "flx_define.h"
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
        sw r16,PDC_DATA_ADDRESS(r0)
        sw r17,PDC_DATA_ADDRESS(r0)
        sw r18,PDC_DATA_ADDRESS(r0)
        sw r19,PDC_DATA_ADDRESS(r0)
        sw r20,PDC_DATA_ADDRESS(r0)
        sw r21,PDC_DATA_ADDRESS(r0)
        sw r22,PDC_DATA_ADDRESS(r0)
        sw r23,PDC_DATA_ADDRESS(r0)

        sw r24,PDC_DATA_ADDRESS(r0)
        sw r25,PDC_DATA_ADDRESS(r0)
        sw r26,PDC_DATA_ADDRESS(r0)
        sw r27,PDC_DATA_ADDRESS(r0)
        sw r28,PDC_DATA_ADDRESS(r0)
        sw r29,PDC_DATA_ADDRESS(r0)
        sw r30,PDC_DATA_ADDRESS(r0)
        sw r31,PDC_DATA_ADDRESS(r0)

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
        lw r16,PDC_DATA_ADDRESS(r0)
        lw r17,PDC_DATA_ADDRESS(r0)
        lw r18,PDC_DATA_ADDRESS(r0)
        lw r19,PDC_DATA_ADDRESS(r0)
        lw r20,PDC_DATA_ADDRESS(r0)
        lw r21,PDC_DATA_ADDRESS(r0)
        lw r22,PDC_DATA_ADDRESS(r0)
        lw r23,PDC_DATA_ADDRESS(r0)

        lw r24,PDC_DATA_ADDRESS(r0)
        lw r25,PDC_DATA_ADDRESS(r0)
        lw r26,PDC_DATA_ADDRESS(r0)
        lw r27,PDC_DATA_ADDRESS(r0)
        lw r28,PDC_DATA_ADDRESS(r0)
        lw r29,PDC_DATA_ADDRESS(r0)
        lw r30,PDC_DATA_ADDRESS(r0)
        lw r31,PDC_DATA_ADDRESS(r0)
        swbrk

        jr r1
        nop
        nop

