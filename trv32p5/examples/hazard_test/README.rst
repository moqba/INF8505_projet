
Steps for Release
=================

.. code-block:: bash

    chessmk ../../model -m

    chessmk ../../hdl/trv32p5_vlog +e

    chessmk build_oneliners

    hazard_test oneliners/Release . 10 "*"

Provide initializations in hglobals.h

.. code-block:: bash

    chessmk test

    chessmk test +C rcd -S

    chessmk test -H

    chessmk test -C Native

    chessmk test -C Native -S -s > test.gcc

    regression_compare --v2 test.gcc test.gcc Release/test.trv32p5_ca.mem

    rcd_compare Release/test.trv32p5_ca.rcd Release/test.trv32p5_vlog.rcd



Steps for Release_LLVM
======================

.. code-block:: bash

    chessmk ../../model_llvm -m

    chessmk ../../hdl/trv32p5_vlog +e

    chessmk build_oneliners -C Release_LLVM

    hazard_test oneliners/Release_LLVM . 10 "*"

Provide initializations in hglobals.h

.. code-block:: bash

    chessmk test -C Release_LLVM

    chessmk test -C Release_LLVM +C rcd -S

    chessmk test -C Release_LLVM -H

    chessmk test -C Native

    chessmk test -C Native -S -s > test.gcc

    regression_compare --v2 test.gcc test.gcc Release_LLVM/test.trv32p5_ca.mem

    rcd_compare Release_LLVM/test.trv32p5_ca.rcd Release_LLVM/test.trv32p5_vlog.rcd

