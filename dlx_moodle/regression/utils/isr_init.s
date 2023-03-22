/*
-- File : isr_init.s
-- Contents : interrupt initialisation for regression tests.
-- Copyright (c) 2014-2021 Synopsys Inc.
*/

.undef global text counter_isr

;; the interrupt vector table with 8 interrupts, 16 words
.text global 0 _ivt
        j #isr_init                ;  0    -- reset
        nop                        ;
        rti                        ;  1    -- unused
        nop                        ;
        j #counter_isr             ;  2    -- used for counter_isr
        nop                        ;
        rti                        ;  3    -- unused
        nop                        ;
        rti                        ;  4    -- unused
        nop                        ;
        rti                        ;  5    -- unused
        nop                        ;
        rti                        ;  6    -- unused
        nop                        ;
        rti                        ;  7    -- unused
        nop                        ;

.text global 0 isr_init
        ori r1, r1, #_sp_start_DMb
        mv  sr ,r0                ; to avoid don't care in RTL sim
        ori r0,r0, #0
        //ori r1,r0, #0
        ori r2,r0, #0
        ori r3,r0, #0
        ori r4,r0, #0
        ori r5,r0, #0
        ori r6,r0, #0
        ori r7,r0, #0
        ori r8,r0, #255
        mv  im,r8
        ei


