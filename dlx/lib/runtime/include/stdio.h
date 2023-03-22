/*
-- File: stdio.h
--
-- Contents: ISO C99 Standard, 7.19 Input/output <stdio.h>
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/




#ifndef _STDIO_H
#define _STDIO_H

#include <errno.h>
#include <stdarg.h>
#include <stddef.h>

#if defined(__cplusplus) || defined(__ndl__)
extern "C" {
#endif

struct FILE;
typedef struct FILE FILE;

extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

#ifndef EOF
#define EOF (-1)
#endif

#ifndef EBADF
#define EBADF 9
#endif

#ifndef SEEK_SET
#define SEEK_SET 0
#endif

#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif

#ifndef SEEK_END
#define SEEK_END 2
#endif

#ifndef FOPEN_MAX
#define FOPEN_MAX 16
#endif

#ifndef EMFILE
#define EMFILE 24
#endif

// Operations on files (7.19.4)

extern int remove(const char *pathname) property(loop_free);
extern int rename(const char *oldpath, const char *newpath) property(loop_free);
extern FILE *tmpfile() property(loop_free);
extern int mkstemp(char* s) property(loop_free);
extern FILE* fdopen(int fd, const char* mode) property(loop_free);
extern int close(int fd) property(loop_free);


// File access functions (7.19.5)

extern FILE* fopen(const char* path, const char* mode) property(loop_free);
extern int fclose(FILE* stream) property(loop_free);
extern int fflush(FILE* stream) property(loop_free);
// freopen not supported for stdin, stdout and stderr
extern FILE *freopen(const char *path, const char *mode, FILE *stream) property(loop_free);


// Formatted input/output functions (7.19.6)

extern int vfprintf(FILE* stream, const char* format, va_list ap) property(loop_free);
inline int vprintf(const char* format, va_list ap);
extern int fprintf(FILE* stream, const char* format, ...) property(loop_free);
extern int printf(const char* format, ...) property(loop_free);

extern int vfscanf(FILE* stream, const char* format, va_list ap) property(loop_free);
inline int vscanf(const char* format, va_list ap);
extern int fscanf(FILE* stream, const char* format, ...) property(loop_free);
extern int scanf(const char* format, ...) property(loop_free);

extern int sprintf(char *str, const char *format, ...) property(loop_free);
extern int snprintf(char *str, size_t size, const char *format, ...) property(loop_free);
extern int vsprintf(char *str, const char *format, va_list ap) property(loop_free);
extern int vsnprintf(char *str, size_t size, const char *format, va_list ap) property(loop_free);

extern int sscanf(const char *str, const char *format, ...) property(loop_free);
extern int vsscanf(const char *str, const char *format, va_list ap) property(loop_free);


// Character input/output functions (7.19.7)

extern int fputc(int c, FILE* stream) property(loop_free);
inline int putc(int c, FILE* stream);
inline int putchar(int c);
extern int fputs(const char* s, FILE* stream) property(loop_free);
inline int puts(const char* s);

extern int fgetc(FILE* stream) property(loop_free);
inline int getc(FILE* stream);
inline int getchar();
extern char* fgets(char* s, int n, FILE* stream) property(loop_free);
extern char* gets(char *s) property(loop_free);

extern int ungetc(int c, FILE *stream) property(loop_free);


// Direct input/output functions (7.19.8)

extern size_t fwrite(const void chess_storage(DMb)* ptr, size_t size, size_t nmemb, FILE* stream) property(loop_free);

extern size_t fread(void chess_storage(DMb)* ptr, size_t size, size_t nmemb, FILE* stream) property(loop_free);

//   word-based versions of fread/fwrite, reading/writing 'nword' words (of type
//   int or unsigned), 'size' bytes per word (useful for memories not supporting
//   byte access):

extern size_t fwrite_word(const void chess_storage(DMb)* ptr, size_t size, size_t nword, int lsb_first, FILE* stream) property(loop_free);

extern size_t fread_word(void chess_storage(DMb)* ptr, size_t size, size_t nword, int lsb_first, FILE* stream) property(loop_free);


// File positioning functions (7.19.9)

extern int fseek(FILE* stream, long offset, int whence) property(loop_free);
inline void rewind(FILE* stream);
extern long ftell(FILE* stream) property(loop_free);


// Error-handling functons (7.19.10)

extern int feof(FILE* stream) property(loop_free);
extern int ferror(FILE* stream) property(loop_free);
extern void clearerr(FILE* stream) property(loop_free);
extern void perror(const char *s) property(loop_free);


// Inline definitions :

inline int vprintf(const char *format, va_list ap)
{
    return vfprintf(stdout, format, ap);
}

inline int vscanf(const char *format, va_list ap)
{
    return vfscanf(stdin, format, ap);
}

inline void rewind(FILE* stream)
{
    fseek(stream, 0, SEEK_SET);
}

inline int putc(int c, FILE* stream)
{
    return fputc(c, stream);
}

inline int putchar(int c)
{
    return fputc(c, stdout);
}

inline int puts(const char* s)
{
    int rt = fputs(s, stdout);
    if (rt < 0)
	return rt;
    return fputc('\n', stdout);
}

inline int getc(FILE* stream)
{
    return fgetc(stream);
}

inline int getchar()
{
    return fgetc(stdin);
}

#if defined(__cplusplus) || defined(__ndl__)
} // extern "C"
#endif

#endif
