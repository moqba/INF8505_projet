TRV32P5 ISS MODELS
------------------

Cycle-Accurate
^^^^^^^^^^^^^^

``trv32p5_ca-fst``

  Fast cycle-accurate ISS without PDG IO interfaces for PM and DM (pm.p, dm.p).

  The absence of these interfaces has no impact on the cycle count. These
  interfaces simply externalize the core-internal memory ports, but do not
  introduce stall cycles. It means that the model accuracy related to the
  cycles performance is identical for trv32p5_ca and trv32p5_ca-fst.

  For fast cycle-accurate simulations, use trv32p5_ca-fst.

  For RTL-vs-ISS comparisons, use trv32p5_ca, which includes the external
  memory interfaces.


``trv32p5_ca``

  Cycle-accurate ISS. Full core simulation. Use to compare against RTL models
  (Verilog, VHDL).


``trv32p5_ca-jit``

  Cycle-accurate ISS with pipeline state based Just-in-Time (JIT) compilation.

  This is essentially trv32p5_ca-fst plus JIT. JIT based simulations have a
  runtime setup overhead, but can be faster for some applications, especially
  for longer simulations that repetitively execute the same code blocks. An
  example is the repeated execution of convolutional kernels, with different
  inputs, for neural network applications.


Instruction-Accurate
^^^^^^^^^^^^^^^^^^^^

``trv32p5_ia``

  Instruction-accurate ISS


``trv32p5_ia-jit``

  Instruction-accurate ISS with encoding and PC based Just-in-Time compilation.


``trv32p5_ia-blockjit``

  Instruction-accurate ISS with block based Just-in-Time compilation.
