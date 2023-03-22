/*
-- File : trv32p3_int.h
--
-- Contents : Integer application layer for the trv32p3 processor.
--
-- Copyright (c) 2019-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/

#ifndef INCLUDED_TRV32P3_INT_H_
#define INCLUDED_TRV32P3_INT_H_

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ type conversions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// signed char
promotion  operator    signed char  ( unsigned char  ) = { w08(w32),          // store
                                                           w32 sext (w08) };  // load
promotion  operator    signed char  (   signed short ) = { w08(w32) };        // store
promotion  operator    signed char  ( unsigned short ) = { w08(w32) };        // store
promotion  operator    signed char  (   signed int   ) = { w08(w32) };        // store
promotion  operator    signed char  ( unsigned int   ) = { w08(w32) };        // store

// unsigned char
promotion  operator  unsigned char  (   signed char  ) = { w32 zext_08 (w32), // bit-and 0xff
                                                           w08(w32),          // store
                                                           w32 zext (w08) };  // load
promotion  operator  unsigned char  (   signed short ) = { w32 zext_08 (w32), // bit-and 0xff
                                                           w08(w32) };        // store
promotion  operator  unsigned char  ( unsigned short ) = { w32 zext_08 (w32), // bit-and 0xff
                                                           w08(w32) };        // store
promotion  operator  unsigned char  (   signed int   ) = { w32 zext_08 (w32), // bit-and 0xff
                                                           w08(w32) };        // store
promotion  operator  unsigned char  ( unsigned int   ) = { w32 zext_08 (w32), // bit-and 0xff
                                                           w08(w32) };        // store

// signed short
promotion  operator    signed short (   signed char  ) = nil;
promotion  operator    signed short ( unsigned char  ) = nil;
promotion  operator    signed short ( unsigned short ) = { w16(w32),          // store
                                                           w32 sext (w16) };  // load
promotion  operator    signed short (   signed int   ) = { w16(w32) };        // store
promotion  operator    signed short ( unsigned int   ) = { w16(w32) };        // store

// unsigned short
promotion  operator  unsigned short (   signed char  ) = { w16(w32) };        // store
promotion  operator  unsigned short ( unsigned char  ) = nil;
promotion  operator  unsigned short (   signed short ) = { w16(w32),          // store
                                                           w32 zext (w16) };  // load
promotion  operator  unsigned short (   signed int   ) = { w16(w32) };        // store
promotion  operator  unsigned short ( unsigned int   ) = { w16(w32) };        // store

// signed int
promotion  operator    signed int   (   signed char  ) = nil;
promotion  operator    signed int   ( unsigned char  ) = nil;
promotion  operator    signed int   (   signed short ) = nil;
promotion  operator    signed int   ( unsigned short ) = nil;
promotion  operator    signed int   ( unsigned int   ) = nil;

// unsigned int
promotion  operator  unsigned int   (   signed char  ) = nil;
promotion  operator  unsigned int   ( unsigned char  ) = nil;
promotion  operator  unsigned int   (   signed short ) = nil;
promotion  operator  unsigned int   ( unsigned short ) = nil;
promotion  operator  unsigned int   (   signed int   ) = nil;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ pointer conversions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// same size
promotion  operator  void*          (   signed int   ) = nil;
promotion  operator  void*          ( unsigned int   ) = nil;
promotion  operator    signed int   ( void*          ) = nil;
promotion  operator  unsigned int   ( void*          ) = nil;

// widening
promotion  operator  void*          ( unsigned short ) = nil;
promotion  operator  void*          (   signed short ) = nil;
promotion  operator  void*          ( unsigned char  ) = nil;
promotion  operator  void*          (   signed char  ) = nil;

// narrowing - undefined
promotion  operator  unsigned short ( void*          ) = undefined;
promotion  operator    signed short ( void*          ) = undefined;
promotion  operator  unsigned char  ( void*          ) = undefined;
promotion  operator    signed char  ( void*          ) = undefined;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ pointer operators
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

promotion  void*         operator + (void*,  signed int) = w32 add (w32,w32);
promotion  void*         operator - (void*,  signed int) = w32 sub (w32,w32);
promotion    signed int  operator - (void*,void*)        = w32 sub (w32,w32);


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ arithmetic and logical operators
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// 32b
promotion    signed int  operator + (  signed int,  signed int) = w32 add  (w32,w32);
promotion    signed int  operator - (  signed int,  signed int) = w32 sub  (w32,w32);
promotion    signed int  operator & (  signed int,  signed int) = w32 band (w32,w32);
promotion    signed int  operator | (  signed int,  signed int) = w32 bor  (w32,w32);
promotion    signed int  operator ^ (  signed int,  signed int) = w32 bxor (w32,w32);
inline       signed int  operator ~ (  signed int a)            { return (a) ^ -1; }

promotion  unsigned int  operator + (unsigned int,unsigned int) = w32 add  (w32,w32);
promotion  unsigned int  operator - (unsigned int,unsigned int) = w32 sub  (w32,w32);
promotion  unsigned int  operator & (unsigned int,unsigned int) = w32 band (w32,w32);
promotion  unsigned int  operator | (unsigned int,unsigned int) = w32 bor  (w32,w32);
promotion  unsigned int  operator ^ (unsigned int,unsigned int) = w32 bxor (w32,w32);
inline     unsigned int  operator ~ (unsigned int a)            { return (a) ^ -1; }


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ shift operators
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// 32b
promotion    signed int  operator << (  signed int,int) = w32 sll (w32,w32);
promotion    signed int  operator >> (  signed int,int) = w32 sra (w32,w32);
promotion  unsigned int  operator << (unsigned int,int) = w32 sll (w32,w32);
promotion  unsigned int  operator >> (unsigned int,int) = w32 srl (w32,w32);


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ compare operators
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// 32b
promotion  bool  operator <  (  signed int,     signed int)   = bool lt (w32,w32);
promotion  bool  operator >= (  signed int,     signed int)   = bool ge (w32,w32);
promotion  bool  operator == (  signed int,     signed int)   = bool eq (w32,w32);
promotion  bool  operator != (  signed int,     signed int)   = bool ne (w32,w32);
inline     bool  operator >  (  signed int a,   signed int b) { return b < a; }
inline     bool  operator <= (  signed int a,   signed int b) { return b >= a; }

promotion  bool  operator <  (unsigned int,   unsigned int)   = bool ltu (w32,w32);
promotion  bool  operator >= (unsigned int,   unsigned int)   = bool geu (w32,w32);
promotion  bool  operator == (unsigned int,   unsigned int)   = bool eq  (w32,w32);
promotion  bool  operator != (unsigned int,   unsigned int)   = bool ne  (w32,w32);
inline     bool  operator >  (unsigned int a, unsigned int b) { return b < a; }
inline     bool  operator <= (unsigned int a, unsigned int b) { return b >= a; }

// pointers
promotion  bool  operator <  (void*,   void*)                 = bool ltu (w32,w32);
promotion  bool  operator >= (void*,   void*)                 = bool geu (w32,w32);
promotion  bool  operator == (void*,   void*)                 = bool eq  (w32,w32);
promotion  bool  operator != (void*,   void*)                 = bool ne  (w32,w32);
inline     bool  operator >  (void* a, void* b)               { return b < a; }
inline     bool  operator <= (void* a, void* b)               { return b >= a; }

chess_properties {
  complements : bool lt  (w32,w32),  bool ge  (w32,w32);
  complements : bool ltu (w32,w32),  bool geu (w32,w32);
  complements : bool eq  (w32,w32),  bool ne  (w32,w32);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~ multiply
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// 32b
promotion    signed int  operator *  (  signed int,  signed int)                 = w32 mul (w32,w32);
promotion  unsigned int  operator *  (unsigned int,unsigned int)                 = w32 mul (w32,w32);

// LLVM specific
promotion    signed int  mulh        (  signed int,  signed int) property(mulhs) = w32 mulh  (w32,w32);
promotion  unsigned int  mulh        (unsigned int,unsigned int) property(mulhu) = w32 mulhu (w32,w32);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~ divide and modulo
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// 32b
promotion    signed int  operator / (  signed int,  signed int) = w32 divs (w32,w32);
promotion  unsigned int  operator / (unsigned int,unsigned int) = w32 divu (w32,w32);

promotion    signed int  operator % (  signed int,  signed int) = w32 rems (w32,w32);
promotion  unsigned int  operator % (unsigned int,unsigned int) = w32 remu (w32,w32);

#endif // INCLUDED_TRV32P3_INT_H_
