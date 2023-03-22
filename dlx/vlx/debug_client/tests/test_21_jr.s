
; test_21_jr.s -- assembly program for jump instruction

.text_segment PM 0
.entry_point
        addi r2,r0,#1        ;  0
        addi r2,r2,#2        ;
        nop
        ori r13, r0, #La
        jr r13                ; 16
        addi r3,r2,#3        ; (delay slot)
        addi r3,r3,#4        ; (delay slot)
        addi r3,r3,#5        ;
La:     addi r6,r3,#6        ; 32
        nop                ;
        nop                ;
        nop                ;
        nop                ; 48
