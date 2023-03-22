
; test_10_breakpoints.s -- assembly program for breakpoints

.text_segment PM 0
.entry_point
        ori r1,r0,#1        ;  0
        ori r2,r0,#2        ;  4
        ori r3,r0,#3        ;  8
        ori r4,r0,#4        ; 12
        ori r5,r0,#5        ; 16
        ori r6,r0,#6        ; 20
        nop                ; 24
        nop                ; 28
