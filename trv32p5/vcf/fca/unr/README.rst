
Unreachability Analysis (UNR) using VC Formal (VCF) Formal Coverage Analyzer (FCA)
==================================================================================

Basic Example
^^^^^^^^^^^^^

1. Prepare a file list

   .. code-block:: bash

       echo "+incdir+$(readlink -f ../../../hdl/trv32p5_vlog/trv32p5/prim" > main.f
       tct_gcpp3 -P -w ../../../hdl/trv32p5_vlog/main.fof >> main.f

2. Open VC Formal

   .. code-block:: bash

       vcf -verdi -f fca.tcl

3. In the VCF GUI, start the UNR analysis