/*
-- File: stdio.c
--
-- Contents: C library, Input/output.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/



#define STDIO_SAFE_NOHOSTED

#ifdef __clang__
#define CLIB_HOSTEDIO_ALT
#endif

#include <errno.h>
#include <stdio.h>

enum Checkers_clib_call_type {
    clct_fopen       =  0, clct_fclose  =  1, clct_vfprintf   =  2,
    clct_vfscanf     =  3, clct_fseek   =  4, clct_ftell      =  5,
    clct_feof        =  6, clct_fputc   =  7, clct_fgetc      =  8,
    clct_fflush      =  9, clct_fputs   = 10, clct_fgets      = 11,
    clct_fread       = 12, clct_fwrite  = 13, clct_ferror     = 14,
    clct_clearerr    = 15, clct_none    = 16, clct_fread_word = 17,
    clct_fwrite_word = 18, clct_remove  = 19, clct_rename     = 20,
    clct_tmpfile     = 21, clct_tmpnam  = 22, clct_vsprintf   = 23,
    clct_vsnprintf   = 24, clct_vsscanf = 25, clct_freopen    = 26,
    clct_ungetc      = 27, clct_perror  = 28, clct_gets       = 29,
    clct_mkstemp     = 30, clct_fdopen  = 31, clct_close      = 32,

    clct_vfprintf_alt = 33, clct_vsprintf_alt = 34, clct_vsnprintf_alt = 35,
    clct_vfscanf_alt  = 36, clct_vsscanf_alt = 37
};

typedef struct {
    int         call_type;
    int         stream_id;
    int         stream_rt;
    union {
        const char* path;
        const char* mem;
    } str_arg1;
    union {
        const char* mode;
        const char* oldpath;
    } str_arg2;
    const char* format;
    long        offset;
    union {
        int     whence;
        int     lsb_first;
        int     oflag;
    } int_arg1;
    int         eof;
    union {
        int     c;
        int     errno;
        int     mode;
    } int_arg2;
    const char* puts_s;
    char*       gets_s;
    size_t      size;
    size_t      nmemb;
    union {
        const void chess_storage(DMb)* write_ptr_dm;
        const void chess_storage(PMb)* write_ptr_pm;
    } write_ptr;
    union {
        void chess_storage(DMb)* read_ptr_dm;
        void chess_storage(PMb)* read_ptr_pm;
    } read_ptr;
    void*       ap; // va_list ap
} Hosted_clib_vars;

static
#ifdef __clang__
__attribute__((noinline))
#endif
void clib_hosted_io(Hosted_clib_vars* p)
{
    chess_hosted_io(p);
}


struct FILE {
    int stream;
    int in_use;
};

static FILE _hosted_clib_files[FOPEN_MAX];
static FILE _stdin  = { 0, 1 };
static FILE _stdout = { 1, 1 };
static FILE _stderr = { 2, 1 };

FILE* stdin = &_stdin;
FILE* stdout = &_stdout;
FILE* stderr = &_stderr;


FILE* fopen(const char *path, const char *mode)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Look for free FILE object
    int idx;
    for(idx = 0; idx < FOPEN_MAX; idx++)
	if (!_hosted_clib_files[idx].in_use)
	    break;
    if (idx >= FOPEN_MAX) {
	errno = EMFILE;
	return 0;
    }
    // Pass arguments to host
    _hosted_clib_vars.str_arg1.path = path;
    _hosted_clib_vars.str_arg2.mode = mode;
    // Call fopen on host
    _hosted_clib_vars.call_type = clct_fopen;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains 0 if OK, else stream_rt will contain error code
    if (_hosted_clib_vars.stream_rt) {
	errno = _hosted_clib_vars.stream_rt;
	return 0;
    }
    // If fopen ended without errors, stream_id contains id of opened stream
    _hosted_clib_files[idx].stream = _hosted_clib_vars.stream_id;
    _hosted_clib_files[idx].in_use = 1;
    return &_hosted_clib_files[idx];
}

int fclose(FILE* stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    if (!stream->in_use) {
	errno = EBADF;
	return EOF;
    }
    // free FILE object
    stream->in_use = 0;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    // Call fclose on host
    _hosted_clib_vars.call_type = clct_fclose;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains 0 if OK, else stream_rt will contain error code
    if (_hosted_clib_vars.stream_rt) {
	errno = _hosted_clib_vars.stream_rt;
	return EOF;
    }
    return 0;
}

FILE *freopen(const char *path, const char *mode, FILE *stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.str_arg1.path = path;
    _hosted_clib_vars.str_arg2.mode = mode;
    _hosted_clib_vars.stream_id = stream->stream;
    // Call fclose on host
    _hosted_clib_vars.call_type = clct_freopen;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains 0 if OK, else stream_rt will contain error code
    if (_hosted_clib_vars.stream_rt) {
	errno = _hosted_clib_vars.stream_rt;
	return 0;
    }
    stream->stream = _hosted_clib_vars.stream_id;
    stream->in_use = 1;
    return stream;
}

int fflush(FILE* stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    // Call fflush on host
    _hosted_clib_vars.call_type = clct_fflush;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains 0 if OK, else stream_rt will contain error code
    if (_hosted_clib_vars.stream_rt) {
	errno = _hosted_clib_vars.stream_rt;
	return EOF;
    }
    return 0;
}

int fseek(FILE *stream, long offset, int whence)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.offset = offset;
    _hosted_clib_vars.int_arg1.whence = whence;
    // Call fseek on host
    _hosted_clib_vars.call_type = clct_fseek;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt returns 0 if OK, else stream_rt will contain error code
    if (_hosted_clib_vars.stream_rt) {
	errno = _hosted_clib_vars.stream_rt;
	return -1;
    }
    return _hosted_clib_vars.stream_rt;
}

long ftell(FILE *stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    // Call fseek on host
    _hosted_clib_vars.call_type = clct_ftell;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
    _hosted_clib_vars.offset = -1;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // offset field returns offset if OK, -1 otherwise and stream_rt will then
    // contain error code
    if (_hosted_clib_vars.offset < 0) {
	errno = _hosted_clib_vars.stream_rt;
	return -1;
    }
    return _hosted_clib_vars.offset;
}

int feof(FILE *stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    // Call feof on host
    _hosted_clib_vars.call_type = clct_feof;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
    _hosted_clib_vars.eof = -1;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // eof field returns >= 0 if OK, -1 otherwise and stream_rt will then
    // contain error code
    if (_hosted_clib_vars.eof < 0) {
	errno = _hosted_clib_vars.stream_rt;
	return -1;
    }
    return _hosted_clib_vars.eof;
}

int ferror(FILE *stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    // Call ferror on host
    _hosted_clib_vars.call_type = clct_ferror;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt will contain the result
    return _hosted_clib_vars.stream_rt;
}

void clearerr(FILE *stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    // Call ferror on host
    _hosted_clib_vars.call_type = clct_clearerr;
    clib_hosted_io(&_hosted_clib_vars);
}

void perror(const char *s)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.puts_s = s;
    _hosted_clib_vars.int_arg2.errno = errno;
    // Call perror on host
    _hosted_clib_vars.call_type = clct_perror;
    clib_hosted_io(&_hosted_clib_vars);
}

inline
#ifdef __clang__
__attribute__((always_inline))
#endif
int _vfprintf(FILE* stream, const char *format, va_list ap)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.format = format;
    _hosted_clib_vars.ap = ap;
    // Call vfprintf on host
#ifdef CLIB_HOSTEDIO_ALT
    _hosted_clib_vars.call_type = clct_vfprintf_alt;
#else
    _hosted_clib_vars.call_type = clct_vfprintf;
#endif
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = -1;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains number of characters written or -1 if an error was
    // encoutered
    return _hosted_clib_vars.stream_rt;
}

int vfprintf(FILE* stream, const char *format, va_list ap)
{
    return _vfprintf(stream, format, ap);
}

int fprintf(FILE* stream, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int rt = _vfprintf(stream, format, ap);
    va_end(ap);
    return rt;
}

int printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int rt = vprintf(format, ap);
    va_end(ap);
    return rt;
}

inline
#ifdef __clang__
__attribute__((always_inline))
#endif
int _vfscanf(FILE* stream, const char *format, va_list ap)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.format = format;
    _hosted_clib_vars.ap = ap;
    // Call vfscanf on host
#ifdef CLIB_HOSTEDIO_ALT
    _hosted_clib_vars.call_type = clct_vfscanf_alt;
#else
    _hosted_clib_vars.call_type = clct_vfscanf;
#endif
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EOF;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains number of performed conversions or EOF
    return _hosted_clib_vars.stream_rt;
}

int vfscanf(FILE* stream, const char *format, va_list ap)
{
    return _vfscanf(stream, format, ap);
}

int fscanf(FILE* stream, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int rt = _vfscanf(stream, format, ap);
    va_end(ap);
    return rt;
}

int scanf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int rt = vscanf(format, ap);
    va_end(ap);
    return rt;
}

int fputc(int c, FILE *stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.int_arg2.c = c;
    // Call fputc on host
    _hosted_clib_vars.call_type = clct_fputc;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EOF;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains c if OK or EOF if an error was encountered
    return _hosted_clib_vars.stream_rt;
}

int ungetc(int c, FILE *stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.int_arg2.c = c;
    // Call fputc on host
    _hosted_clib_vars.call_type = clct_ungetc;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EOF;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains c if OK or EOF if an error was encountered
    return _hosted_clib_vars.stream_rt;
}

int fputs(const char* s, FILE* stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.puts_s = s;
    // Call fgetc on host
    _hosted_clib_vars.call_type = clct_fputs;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EOF;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt >= 0 if OK or EOF if an error was encountered
    return _hosted_clib_vars.stream_rt;
}

int fgetc(FILE *stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    // Call fgetc on host
    _hosted_clib_vars.call_type = clct_fgetc;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EOF;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains char read if OK or EOF if an error was encountered
    return _hosted_clib_vars.stream_rt;
}

char* fgets(char* s, int size, FILE* stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.gets_s = s;
    _hosted_clib_vars.size = size;
    // Call fgetc on host
    _hosted_clib_vars.call_type = clct_fgets;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt == 0 if OK, else error
    if (_hosted_clib_vars.stream_rt)
	return 0; // C99: NULL;
    return s;
}

char* gets(char* s)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.gets_s = s;
    // Call fgetc on host
    _hosted_clib_vars.call_type = clct_gets;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt == 0 if OK, else error
    if (_hosted_clib_vars.stream_rt)
	return 0; // C99: NULL;
    return s;
}

size_t fwrite(const void chess_storage(DMb)* ptr, size_t size, size_t nmemb, FILE* stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.write_ptr.write_ptr_dm = ptr;
    _hosted_clib_vars.size = size;
    _hosted_clib_vars.nmemb = nmemb;
    _hosted_clib_vars.str_arg1.mem = "DMb";
    // Call fwrite on host
    _hosted_clib_vars.call_type = clct_fwrite;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains number of items written
    return _hosted_clib_vars.stream_rt;
}

size_t fread(void chess_storage(DMb)* ptr, size_t size, size_t nmemb, FILE* stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.read_ptr.read_ptr_dm = ptr;
    _hosted_clib_vars.size = size;
    _hosted_clib_vars.nmemb = nmemb;
    _hosted_clib_vars.str_arg1.mem = "DMb";
    // Call fread on host
    _hosted_clib_vars.call_type = clct_fread;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains number of items written
    return _hosted_clib_vars.stream_rt;
}

size_t fwrite_word(const void chess_storage(DMb)* ptr, size_t size, size_t nword, int lsb_first, FILE* stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.write_ptr.write_ptr_dm = ptr;
    _hosted_clib_vars.size = size;
    _hosted_clib_vars.nmemb = nword;
    _hosted_clib_vars.int_arg1.lsb_first = lsb_first;
    _hosted_clib_vars.str_arg1.mem = "DMb";
    // Call fwrite on host
    _hosted_clib_vars.call_type = clct_fwrite_word;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains number of items written
    return _hosted_clib_vars.stream_rt;
}

size_t fread_word(void chess_storage(DMb)* ptr, size_t size, size_t nword, int lsb_first, FILE* stream)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.read_ptr.read_ptr_dm = ptr;
    _hosted_clib_vars.size = size;
    _hosted_clib_vars.nmemb = nword;
    _hosted_clib_vars.int_arg1.lsb_first = lsb_first;
    _hosted_clib_vars.str_arg1.mem = "DMb";
    // Call fread on host
    _hosted_clib_vars.call_type = clct_fread_word;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains number of items written
    return _hosted_clib_vars.stream_rt;
}

int remove(const char* path)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.str_arg1.path = path;
    // Call fread on host
    _hosted_clib_vars.call_type = clct_remove;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains errno if error otherwise 0
    if (_hosted_clib_vars.stream_rt) {
	errno = _hosted_clib_vars.stream_rt;
	return -1;
    }
    return 0;
}

int rename(const char* oldpath, const char* newpath)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.str_arg1.path = newpath;
    _hosted_clib_vars.str_arg2.mode = oldpath;
    // Call fread on host
    _hosted_clib_vars.call_type = clct_rename;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains errno if error otherwise 0
    if (_hosted_clib_vars.stream_rt) {
	errno = _hosted_clib_vars.stream_rt;
	return -1;
    }
    return 0;
}

FILE* tmpfile()
{
    Hosted_clib_vars _hosted_clib_vars;
    // Look for free FILE object
    int idx;
    for(idx = 0; idx < FOPEN_MAX; idx++)
	if (!_hosted_clib_files[idx].in_use)
	    break;
    if (idx >= FOPEN_MAX) {
	errno = EMFILE;
	return 0;
    }
    // No arguments
    // Call fopen on host
    _hosted_clib_vars.call_type = clct_tmpfile;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains 0 if OK, else stream_rt will contain error code
    if (_hosted_clib_vars.stream_rt) {
	errno = _hosted_clib_vars.stream_rt;
	return 0;
    }
    // If fopen ended without errors, stream_id contains id of opened stream
    _hosted_clib_files[idx].stream = _hosted_clib_vars.stream_id;
    _hosted_clib_files[idx].in_use = 1;
    return &_hosted_clib_files[idx];
}

int mkstemp(char* s)
{
    Hosted_clib_vars _hosted_clib_vars;
    _hosted_clib_vars.puts_s = s;
    _hosted_clib_vars.gets_s = s;
    _hosted_clib_vars.call_type = clct_mkstemp;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    return _hosted_clib_vars.stream_rt;
}

FILE* fdopen(int fd, const char* mode)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Look for free FILE object
    int idx;
    for(idx = 0; idx < FOPEN_MAX; idx++)
	if (!_hosted_clib_files[idx].in_use)
	    break;
    if (idx >= FOPEN_MAX) {
	errno = EMFILE;
	return 0;
    }
    // Pass arguments to host
    _hosted_clib_vars.stream_id = fd;
    _hosted_clib_vars.str_arg2.mode = mode;
    _hosted_clib_vars.call_type = clct_fdopen;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains 0 if OK, else stream_rt will contain error code
    if (_hosted_clib_vars.stream_rt) {
	errno = _hosted_clib_vars.stream_rt;
	return 0;
    }
    // If fdopen ended without errors, stream_id contains id of opened stream
    _hosted_clib_files[idx].stream = _hosted_clib_vars.stream_id;
    _hosted_clib_files[idx].in_use = 1;
    return &_hosted_clib_files[idx];
}

int close(int fd)
{
    Hosted_clib_vars _hosted_clib_vars;
    _hosted_clib_vars.stream_id = fd;
    _hosted_clib_vars.call_type = clct_close;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    if (_hosted_clib_vars.stream_rt) {
	errno = _hosted_clib_vars.stream_rt;
	return -1;
    }
    return 0;
}

inline
#ifdef __clang__
__attribute__((always_inline))
#endif
int _vsprintf(char *str, const char *format, va_list ap)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.gets_s = str;
    _hosted_clib_vars.format = format;
    _hosted_clib_vars.ap = ap;
    // Call vsprintf on host
#ifdef CLIB_HOSTEDIO_ALT
    _hosted_clib_vars.call_type = clct_vsprintf_alt;
#else
    _hosted_clib_vars.call_type = clct_vsprintf;
#endif
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = -1;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains return value
    return _hosted_clib_vars.stream_rt;
}

inline
#ifdef __clang__
__attribute__((always_inline))
#endif
int _vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.gets_s = str;
    _hosted_clib_vars.size = size;
    _hosted_clib_vars.format = format;
    _hosted_clib_vars.ap = ap;
    // Call vsnprintf on host
#ifdef CLIB_HOSTEDIO_ALT
    _hosted_clib_vars.call_type = clct_vsnprintf_alt;
#else
    _hosted_clib_vars.call_type = clct_vsnprintf;
#endif
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = -1;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains return value
    return _hosted_clib_vars.stream_rt;
}

int sprintf(char *str, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int rt = _vsprintf(str, format, ap);
    va_end(ap);
    return rt;
}

int snprintf(char *str, size_t size, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int rt = _vsnprintf(str, size, format, ap);
    va_end(ap);
    return rt;
}

int vsprintf(char *str, const char *format, va_list ap)
{
    return _vsprintf(str, format, ap);
}

int vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
    return _vsnprintf(str, size, format, ap);
}

inline
#ifdef __clang__
__attribute__((always_inline))
#endif
int _vsscanf(const char *str, const char *format, va_list ap)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.puts_s = str;
    _hosted_clib_vars.format = format;
    _hosted_clib_vars.ap = ap;
    // Call vsscanf on host
#ifdef CLIB_HOSTEDIO_ALT
    _hosted_clib_vars.call_type = clct_vsscanf_alt;
#else
    _hosted_clib_vars.call_type = clct_vsscanf;
#endif
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = -1;
#endif
    clib_hosted_io(&_hosted_clib_vars);
    // stream_rt contains number of performed conversions or EOF
    return _hosted_clib_vars.stream_rt;
}

int sscanf(const char *str, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int rt = _vsscanf(str, format, ap);
    va_end(ap);
    return rt;
}

int vsscanf(const char *str, const char *format, va_list ap)
{
    return _vsscanf(str, format, ap);
}
