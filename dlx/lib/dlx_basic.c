int main(int argc, char** argv);

extern "C"
int _start_basic(int argc, char** argv) {
    chess_exit(main(argc,argv));  // run program and stop simulation
    while (1) ;                                        // don't continue
}
