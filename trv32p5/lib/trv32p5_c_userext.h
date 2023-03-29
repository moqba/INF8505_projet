/*
-- File : trv32p5_c_userext.h
--
-- Contents : Chess Header File Example for User Extensions
--
-- Copyright (c) 2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

// NOTE that all type promotions must be done before any function promotions
//
// * You can put function promotions in this file
// * You can put type promotions in trv32p5_c_userext-types.h

#ifndef INCLUDED_TRV32P5_C_USEREXT_H_
#define INCLUDED_TRV32P5_C_USEREXT_H_

// This files contains some (incomplete) examples on possible extension points

namespace trv32p5_primitive {

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ~~~ Inline Primitive Functions
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//  inline w32 p_inl_userX (w32 a, w32 b, ...) { ... }

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Promoted Intrinsics
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Promote to processor primitives
//promotion int c_user1 (int,int) = w32 p_user1 (w32,32);

// Promote to inline primitives
//promotion int c_userX (int,int) = w32 p_inl_userX (w32,32);


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ Inline Intrinsics
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//inline int c_inl_userY (int a, int b) { ... }

#endif // INCLUDED_TRV32P5_C_USEREXT_H_
