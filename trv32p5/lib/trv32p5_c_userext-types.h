/*
-- File : trv32p5_c_userext.h
--
-- Contents : Chess Header File Example for User Extensions - User Types
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
// * You can put type promotions in this file
// * You can put function promotions in trv32p5_c_userext.h

#ifndef INCLUDED_TRV32P5_C_USEREXT_TYPES_H_
#define INCLUDED_TRV32P5_C_USEREXT_TYPES_H_

// This files contains some (incomplete) examples on possible extension points

#if 0
// basic vector type
class v8uint8_t  property (vector int [8]) {
  v8uint8_t(int); // broadcast
  v8uint8_t(int,int,int,int,int,int,int,int); // init
}

chess_properties {
  representation v8uint8_t : w64;
}

// only for constants, as an example
promotion v8uint8_t(int) = undefined;
promotion v8uint8_t(int,int,int,int,int,int,int,int) = undefined;

// undefined values (dont_care values)
promotion inline  v8uint8_t undef_v8uint8_t() property(dont_care) = undefined;
#endif

#if 0
class mytype property ( 32 bit signed );
chess_properties {
  promotion mytype : strong { w32 } ...;
}
#endif

#if 0
chess_properties {

//  reserved: ...; // reserved registers

}
#endif

#endif // INCLUDED_TRV32P5_C_USEREXT_TYPES_H_
