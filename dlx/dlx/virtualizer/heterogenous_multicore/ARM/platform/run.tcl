vpx::start_simulation ./Debug/sim . --cwr_wait 120 test.log test.err
vpx::continue_simulation
vpx::wait_interrupted 180
vpx::stop_simulation
