
; test_14_dm.s -- assembly test program for testing DM access

.bss_segment DMb 0 64

.text_segment PM 0
.entry_point
        lhi  r2,#0x1234 
        ori  r2,r2,#0x5678 
        ori  r3,r0,#16 
        nop
        nop
        sb r2,0(r3)    
        sb r2,1(r3)    
        sb r2,2(r3)    
        nop
        nop
        sh r2,4(r3)    
        sh r2,6(r3)    
        sh r2,8(r3)    
        nop
        nop
        sw r2,16(r3)    
        sw r2,20(r3)    
        sw r2,24(r3)    
        nop
        nop
        nop


