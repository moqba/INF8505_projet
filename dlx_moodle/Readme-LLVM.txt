
==============================================================================
Notes for the use of the LLVM C front end in DLX.

Version: K-2015.06
Date: Jun 2015

Copyright (c) 2105-2021 Synopsys, Inc. This file and the associated
documentation are proprietary to Synopsys, Inc.  This model may only be
used in accordance with the terms and conditions of a written license
agreement with Synopsys, Inc.  All other use, reproduction, or distribution
of this model are strictly prohibited.
==============================================================================


Since the J-2015.03 release, and continued in the K-2015.06, it is possible to
used LLVM as front end for the Chess compiler.
 
- The LLVM front end is enabled in pre-defined LLVM configurations of the
  processor.  To enable the LLVM front end, use the Release_LLVM or Debug_LLVM
  configurations.


- The LLVM front requires that the compiler-rt library is compiled onto
  the DLX core.  The source code of compiler-rt is processor independent and 
  is not part of the DLX archive.  It is shipped as a separate archive,
  libs-J-2015.03.zip.  This archive must be unpacked as a sibling directory of
  the DLX directory, as follows:


      |---- libs
      |     |---- compiler-rt
      |
      |
      |---- dlx
            |---- lib
                  |---- compiler-rt


- Note that dlx/lib also has a compiler-rt directory, containing only he
  project file compiler-rt.prx and the build directory lib.

  The compiler-rt archive must be generated by building the compiler-rt.prx
  project file.  Note that this build step is part of the dlx/model.prx file. 

   
