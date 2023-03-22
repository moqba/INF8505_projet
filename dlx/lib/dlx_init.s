.direct_eval >>,&,(,)

 // initialisation before entering the main function.
.text global 0 _main_init
        lhi r1, #(_sp_start_DMb>>16)
        ori r1,r1,#(_sp_start_DMb&0xffff)
        nop                             
.undef global data _sp_start_DMb


; area to load main(argc,char* argv[]) arguments 
.bss global 0 _main_argv_area DMb 256
