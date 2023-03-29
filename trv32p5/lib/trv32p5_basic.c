/*
-- Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

int main(int argc, char** argv);

extern "C" // for easier referencing in .bcf file
int _start_basic(int argc, char** argv) {
  chess_exit(main(argc,argv));  // run program and stop simulation
  while (1);                    // don't continue
  return 0;                     // (unreachable, but needed by noodle)
}
