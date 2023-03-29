/*/*
-- File : undefined.c
--
-- Contents : stub unimplemented functions
--
-- Copyright (c) 2014-2020 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#if defined(__cplusplus) || defined(__ndl__)
extern "C" {
#endif

#define DEF_UNDEFINED(x) void x() { abort(); }

extern void abort();

DEF_UNDEFINED(_Unwind_DeleteException);
DEF_UNDEFINED(_Unwind_GetIP);
DEF_UNDEFINED(_Unwind_GetLanguageSpecificData);
DEF_UNDEFINED(_Unwind_GetRegionStart);
DEF_UNDEFINED(_Unwind_RaiseException);
DEF_UNDEFINED(_Unwind_Resume);
DEF_UNDEFINED(_Unwind_SetGR);
DEF_UNDEFINED(_Unwind_SetIP);

// to be fixed in newlib
DEF_UNDEFINED(sigprocmask);
DEF_UNDEFINED(posix_memalign);

#if defined(__cplusplus) || defined(__ndl__)
} // extern "C"
#endif
