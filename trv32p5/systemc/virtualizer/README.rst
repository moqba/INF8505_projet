Virtualizer SystemC Models
--------------------------

``ca_pin``

  Example demonstrating the use of a pin-accurate Virtualizer SystemC wrapper
  around the cycle-accurate ISS of the Trv32p5 model


``ca_tlm2_lt``

  Example demonstrating the use of a TLM2-LT Virtualizer SystemC wrapper over
  the cycle-accurate ISS of the Trv32p5 model


``ia_tlm2_lt``

  Example demonstrating the use of a TLM2-LT Virtualizer SystemC wrapper over
  the instruction-accurate ISS of the Trv32p5 model


``ia_tlm2_ft``

  Example demonstrating the use of a TLM2-FT Virtualizer SystemC wrapper over
  the instruction-accurate ISS of the Trv32p5 model. This uses the customized
  FT(AXI) adapter to communicate with the memories on the FT(AXI) bus


``ca_adapter``

  Example demonstrating how you can attach your own adapter with the TLM2
  SystemC wrapper. The default TLM-LT adapter has been used as an example.


How to Build
------------

The ``build.tcl`` script builds the ISS and the Virtualizer platform.

  .. code-block:: bash

      ./build.tcl ca_pin


How to Run
----------

The ``run.tcl`` script runs the model.

  .. code-block:: bash

      ./run.tcl ca_pin ../examples/sort/Release/sort
