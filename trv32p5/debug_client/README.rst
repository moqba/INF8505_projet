Building the Debug Client
=========================

 1) Build hdl/trv32p5_vlog.prx project.

      This step generates pdc_init_bpwp_codes.c and pdc_opcodes.h in the
      hdl/trv32p5_vlog directory.

 2) Run ins2c.tcl.

      Usage: ./ins2c.tcl or tct_tclsh ins2c.tcl

      a) Copies the above mentioned files from hdl/trv32p5_vlog into this
         directory.

      b) Compiles pdc_register_moves.s to pdc_register_moves.x.

      c) Disassembles pdc_register_moves.x to pdc_register_moves.dis.

      d) Extracts instruction encodings from pdc_register_moves.dis. Places them
         into pdc_register_moves.h.

 3) Compile trv32p5_client.prx.


NOTES
=====

This is an example for a debug client. For optimal performance, this code should
be adapted to the hardware. We expose the implementation source code to the
customer. You have full control over this implementation. This is an example
implementation.

Additional features might be demonstrated in debug clients of other example
cores. Contact Synopsys support for more information.

  * The tmicro debug client supports memory range protections.

  * The tmicro debug client supports multiple register contexts.

  * The tmicro debug client, and others, demonstrate how to access status
    registers that have multiple fields (record registers).

  * The Trv32p5 debug client implementation example transfers data to registers
    via the data memory. There are models that directly move data between
    registers and the OCD data register (ocd_data) without the indirection via
    the data memory.