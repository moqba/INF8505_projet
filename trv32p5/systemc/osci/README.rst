OSCI SystemC Models
-------------------

``ca_pin``

  Examples demonstrating the use of a pin-accurate OSCI SystemC wrapper
  around the cycle-accurate ISS of the Trv32p5 model


``ca_tlm2_lt``

  Examples demonstrating the use of a TLM2-LT OSCI SystemC wrapper over
  the cycle-accurate ISS of the Trv32p5 model


``ia_tlm2_lt``

  Examples demonstrating the use of a TLM2-LT OSCI SystemC wrapper over
  the instruction-accurate ISS of the Trv32p5 model


``trv32p5_sc.prx``

  Default SystemC model with GUI and Tcl support.


``trv32p5_sc_nogui.prx``

  SystemC model with no GUI support and no Tcl support.


How to Build
------------

Build the corresponding prx file.

  .. code-block:: bash

      chessmk ca_pin/trv32p5_sc.prx


How to Run
----------

The ``run.tcl`` script runs the model.

  .. code-block:: bash

      ./run.tcl ca_pin/trv32p5_sc ../../examples/sort/Release/sort
