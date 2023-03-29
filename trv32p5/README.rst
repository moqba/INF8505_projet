TRV32P5 Core README file
========================

Getting Started
---------------

1. Build the core and supporting software libraries

   .. code-block:: bash

       chessmk model.prx -m

2. Try compiling and running an example application

   .. code-block:: bash

       chessde examples/sort/sort.prx

3. Run the regression tests

   * Run all

     .. code-block:: bash

         cd regression
         ./domake diff

   * Run a single test

     .. code-block:: bash

         cd regression/C00_simple_report
         make -f ../Makefile.test clean diff


Batch Projects
--------------

1. Noodle front-end with light-weight runtime stack. For input/output
   functionality, formatting and buffering is done on the host.

   .. code-block:: bash

       chessmk model.prx -m

2. LLVM front-end with light-weight runtime stack. This includes a light C++
   standard library. For input/output functionality, formatting and buffering
   is done on the host.

   .. code-block:: bash

       chessmk model_llvm.prx -m

3. LLVM front-end with full-featured runtime stack. This includes a
   full-featured C++ standard library and uses the full-featured C library
   'newlib'. For the input/output functionality, all formatting and buffering
   is done on the target processor.

   .. code-block:: bash

       chessmk model_llvm_full.prx -m


Coremark
--------

Use the application project

    benchmarks/coremark_v1.0/performance_run.prx

and the compile configuration

    Release_LLVM_tuned


1. Compile LLVM SDK

   .. code-block:: bash

       chessmk model_llvm.prx -m

2. Compile Coremark for Release_LLVM_tuned configuration

   .. code-block:: bash

       chessmk benchmarks/coremark_v1.0/performance_run.prx -C Release_LLVM_tuned

3. Simulate Coremark compiled for Release_LLVM_tuned configuration

   .. code-block:: bash

       chessmk benchmarks/coremark_v1.0/performance_run.prx -C Release_LLVM_tuned -S

