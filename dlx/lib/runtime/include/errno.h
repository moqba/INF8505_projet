/*
-- File: errno.h
--
-- Contents: ISO C99 Standard, 7.5 Errors <errno.h>
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/



#ifndef _ERRNO_H
#define _ERRNO_H

extern int errno;

// Macros required for hosted IO

#define EBADF            9      /* Bad file number. */
#define EMFILE          24      /* Too many open files. */

// Macros required for dynamic memory allocation 

#define ENOMEM          12      /* Out of memory */

// Macros required by ISO C99 

#define EDOM            33      /* Math argument out of domain of function. */
#define EILSEQ          84      /* Illegal byte sequence. */
#define ERANGE          34      /* Result too large. */

#endif /* errno.h */
