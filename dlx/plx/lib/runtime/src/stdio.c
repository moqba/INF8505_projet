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
    clct_mkstemp     = 30, clct_fdopen  = 31, clct_close      = 32
};

struct FILE {
    int stream;
    int in_use;
};

struct Hosted_clib_vars {
    int         call_type;
    int         stream_id;
    int         stream_rt;
    const char* path;
    const char* mode;
    const char* format;
    long        offset;
    int         whence;
    int         eof;
    int         c;
    const char* puts_s;
    char*       gets_s;
    int         size;
    int         nmemb;
    union {
        const void chess_storage(DMb)* write_ptr_dm;
        const void chess_storage(PMb)* write_ptr_pm;
    } write_ptr;
    union {
        void chess_storage(DMb)* read_ptr_dm;
        void chess_storage(PMb)* read_ptr_pm;
    } read_ptr;
    void*       ap; // va_list ap
};

/*static*/ FILE _hosted_clib_files[FOPEN_MAX];
static FILE _stdin  = { 0, 1 };
static FILE _stdout = { 1, 1 };
static FILE _stderr = { 2, 1 };

FILE* stdin = &_stdin;
FILE* stdout = &_stdout;
FILE* stderr = &_stderr;

// Inline assembly function to call the common IO access function and to make
// sure all arguments are written before the breakpoint put on the common IO
// access function is hit. This function must be rewritten for the target
// processor. Provided here with syntax as used for the 'base' processor
inline assembly void _ihosted_clib_io() property(loop_free) clobbers()
{
    asm_begin
        nop
        nop
        nop
.label _hosted_clib_io_brkpt
        nop
    asm_end
}

// One access point for all IO (the ISS/debugger automatically sets a
// breakpoint on this function).
extern "C" void _hosted_clib_io(Hosted_clib_vars* p) property(loop_free)
{
    _ihosted_clib_io();
    p->call_type = clct_none; // Required to get varinfo for p
    return;
}

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
    _hosted_clib_vars.path = path;
    _hosted_clib_vars.mode = mode;
    // Call fopen on host
    _hosted_clib_vars.call_type = clct_fopen;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
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

int fclose(FILE* stream) property(loop_free)
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
    _hosted_clib_io(&_hosted_clib_vars);
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
    _hosted_clib_vars.path = path;
    _hosted_clib_vars.mode = mode;
    _hosted_clib_vars.stream_id = stream->stream;
    // Call fclose on host
    _hosted_clib_vars.call_type = clct_freopen;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains 0 if OK, else stream_rt will contain error code
    if (_hosted_clib_vars.stream_rt) {
        errno = _hosted_clib_vars.stream_rt;
        return 0;
    }
    stream->stream = _hosted_clib_vars.stream_id;
    stream->in_use = 1;
    return stream;
}

int fflush(FILE* stream) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    if (stream == 0) {
        _hosted_clib_vars.stream_id = -1; // Special value to pass NULL to hosted fflush call
    } else {
        _hosted_clib_vars.stream_id = stream->stream;
    }
    // Call fflush on host
    _hosted_clib_vars.call_type = clct_fflush;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains 0 if OK, else stream_rt will contain error code
    if (_hosted_clib_vars.stream_rt) {
        errno = _hosted_clib_vars.stream_rt;
        return EOF;
    }
    return 0;
}

int fseek(FILE *stream, long offset, int whence) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.offset = offset;
    _hosted_clib_vars.whence = whence;
    // Call fseek on host
    _hosted_clib_vars.call_type = clct_fseek;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt returns 0 if OK, else stream_rt will contain error code
    if (_hosted_clib_vars.stream_rt) {
        errno = _hosted_clib_vars.stream_rt;
        return -1;
    }
    return _hosted_clib_vars.stream_rt;
}

long ftell(FILE *stream) property(loop_free)
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
    _hosted_clib_io(&_hosted_clib_vars);
    // offset field returns offset if OK, -1 otherwise and stream_rt will then
    // contain error code
    if (_hosted_clib_vars.offset < 0) {
        errno = _hosted_clib_vars.stream_rt;
        return -1;
    }
    return _hosted_clib_vars.offset;
}

int feof(FILE *stream) property(loop_free)
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
    _hosted_clib_io(&_hosted_clib_vars);
    // eof field returns >= 0 if OK, -1 otherwise and stream_rt will then
    // contain error code
    if (_hosted_clib_vars.eof < 0) {
        errno = _hosted_clib_vars.stream_rt;
        return -1;
    }
    return _hosted_clib_vars.eof;
}

int ferror(FILE *stream) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    // Call ferror on host
    _hosted_clib_vars.call_type = clct_ferror;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt will contain the result
    return _hosted_clib_vars.stream_rt;
}

void clearerr(FILE *stream) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    // Call ferror on host
    _hosted_clib_vars.call_type = clct_clearerr;
    _hosted_clib_io(&_hosted_clib_vars);
}

void perror(const char *s) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.puts_s = s;
    _hosted_clib_vars.c = errno;
    // Call perror on host
    _hosted_clib_vars.call_type = clct_perror;
    _hosted_clib_io(&_hosted_clib_vars);
}

inline int _vfprintf(FILE* stream, const char *format, va_list ap)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.format = format;
    _hosted_clib_vars.ap = ap;
    // Call vfprintf on host
    _hosted_clib_vars.call_type = clct_vfprintf;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = -1;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains number of characters written or -1 if an error was
    // encoutered
    return _hosted_clib_vars.stream_rt;
}

int vfprintf(FILE* stream, const char *format, va_list ap) property(loop_free)
{
    return _vfprintf(stream, format, ap);
}

int fprintf(FILE* stream, const char *format, ...) property(loop_free)
{
    va_list ap;
    va_start(ap, format);
    int rt = _vfprintf(stream, format, ap);
    va_end(ap);
    return rt;
}

int printf(const char *format, ...) property(loop_free)
{
    va_list ap;
    va_start(ap, format);
    int rt = vprintf(format, ap);
    va_end(ap);
    return rt;
}

inline int _vfscanf(FILE* stream, const char *format, va_list ap)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.format = format;
    _hosted_clib_vars.ap = ap;
    // Call vfscanf on host
    _hosted_clib_vars.call_type = clct_vfscanf;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EOF;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains number of performed conversions or EOF
    return _hosted_clib_vars.stream_rt;
}

int vfscanf(FILE* stream, const char *format, va_list ap) property(loop_free)
{
    return _vfscanf(stream, format, ap);
}

int fscanf(FILE* stream, const char *format, ...) property(loop_free)
{
    va_list ap;
    va_start(ap, format);
    int rt = _vfscanf(stream, format, ap);
    va_end(ap);
    return rt;
}

int scanf(const char *format, ...) property(loop_free)
{
    va_list ap;
    va_start(ap, format);
    int rt = vscanf(format, ap);
    va_end(ap);
    return rt;
}

int fputc(int c, FILE *stream) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.c = c;
    // Call fputc on host
    _hosted_clib_vars.call_type = clct_fputc;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EOF;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains c if OK or EOF if an error was encountered
    return _hosted_clib_vars.stream_rt;
}

int ungetc(int c, FILE *stream) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.c = c;
    // Call fputc on host
    _hosted_clib_vars.call_type = clct_ungetc;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EOF;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains c if OK or EOF if an error was encountered
    return _hosted_clib_vars.stream_rt;
}

int fputs(const char* s, FILE* stream) property(loop_free)
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
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt >= 0 if OK or EOF if an error was encountered
    return _hosted_clib_vars.stream_rt;
}

int fgetc(FILE *stream) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    // Call fgetc on host
    _hosted_clib_vars.call_type = clct_fgetc;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EOF;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains char read if OK or EOF if an error was encountered
    return _hosted_clib_vars.stream_rt;
}

char* fgets(char* s, int size, FILE* stream) property(loop_free)
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
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt == 0 if OK, else error
    if (_hosted_clib_vars.stream_rt)
        return 0; // C99: NULL;
    return s;
}

char* gets(char* s) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.gets_s = s;
    // Call fgetc on host
    _hosted_clib_vars.call_type = clct_gets;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = EBADF;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt == 0 if OK, else error
    if (_hosted_clib_vars.stream_rt)
        return 0; // C99: NULL;
    return s;
}

int fwrite(const void chess_storage(DMb)* ptr, int size, int nmemb, FILE* stream) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.write_ptr.write_ptr_dm = ptr;
    _hosted_clib_vars.size = size;
    _hosted_clib_vars.nmemb = nmemb;
    _hosted_clib_vars.path = "DMb";
    // Call fwrite on host
    _hosted_clib_vars.call_type = clct_fwrite;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains number of items written
    return _hosted_clib_vars.stream_rt;
}

int fread(void chess_storage(DMb)* ptr, int size, int nmemb, FILE* stream) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.read_ptr.read_ptr_dm = ptr;
    _hosted_clib_vars.size = size;
    _hosted_clib_vars.nmemb = nmemb;
    _hosted_clib_vars.path = "DMb";
    // Call fread on host
    _hosted_clib_vars.call_type = clct_fread;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains number of items written
    return _hosted_clib_vars.stream_rt;
}

int fwrite_word(const void chess_storage(DMb)* ptr, int size, int nword, int lsb_first, FILE* stream) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.write_ptr.write_ptr_dm = ptr;
    _hosted_clib_vars.size = size;
    _hosted_clib_vars.nmemb = nword;
    _hosted_clib_vars.whence = lsb_first;
    _hosted_clib_vars.path = "DMb";
    // Call fwrite on host
    _hosted_clib_vars.call_type = clct_fwrite_word;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains number of items written
    return _hosted_clib_vars.stream_rt;
}

int fread_word(void chess_storage(DMb)* ptr, int size, int nword, int lsb_first, FILE* stream) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.stream_id = stream->stream;
    _hosted_clib_vars.read_ptr.read_ptr_dm = ptr;
    _hosted_clib_vars.size = size;
    _hosted_clib_vars.nmemb = nword;
    _hosted_clib_vars.whence = lsb_first;
    _hosted_clib_vars.path = "DMb";
    // Call fread on host
    _hosted_clib_vars.call_type = clct_fread_word;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains number of items written
    return _hosted_clib_vars.stream_rt;
}

int remove(const char* path) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.path = path;
    // Call fread on host
    _hosted_clib_vars.call_type = clct_remove;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains errno if error otherwise 0
    if (_hosted_clib_vars.stream_rt) {
        errno = _hosted_clib_vars.stream_rt;
        return -1;
    }
    return 0;
}

int rename(const char* oldpath, const char* newpath) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.path = newpath;
    _hosted_clib_vars.mode = oldpath;
    // Call fread on host
    _hosted_clib_vars.call_type = clct_rename;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
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
    _hosted_clib_io(&_hosted_clib_vars);
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

int mkstemp(char* s) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    _hosted_clib_vars.puts_s = s;
    _hosted_clib_vars.gets_s = s;
    _hosted_clib_vars.call_type = clct_mkstemp;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    return _hosted_clib_vars.stream_rt;
}

FILE* fdopen(int fd, const char* mode) property(loop_free)
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
    _hosted_clib_vars.mode = mode;
    _hosted_clib_vars.call_type = clct_fdopen;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
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

int close(int fd) property(loop_free)
{
    Hosted_clib_vars _hosted_clib_vars;
    _hosted_clib_vars.stream_id = fd;
    _hosted_clib_vars.call_type = clct_close;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = 0;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    return _hosted_clib_vars.stream_rt;
}

inline int _vsprintf(char *str, const char *format, va_list ap)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.gets_s = str;
    _hosted_clib_vars.format = format;
    _hosted_clib_vars.ap = ap;
    // Call vsprintf on host
    _hosted_clib_vars.call_type = clct_vsprintf;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = -1;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains return value
    return _hosted_clib_vars.stream_rt;
}

inline int _vsnprintf(char *str, int size, const char *format, va_list ap)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.gets_s = str;
    _hosted_clib_vars.size = size;
    _hosted_clib_vars.format = format;
    _hosted_clib_vars.ap = ap;
    // Call vsnprintf on host
    _hosted_clib_vars.call_type = clct_vsnprintf;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = -1;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains return value
    return _hosted_clib_vars.stream_rt;
}

int sprintf(char *str, const char *format, ...) property(loop_free)
{
    va_list ap;
    va_start(ap, format);
    int rt = _vsprintf(str, format, ap);
    va_end(ap);
    return rt;
}

int snprintf(char *str, int size, const char *format, ...) property(loop_free)
{
    va_list ap;
    va_start(ap, format);
    int rt = _vsnprintf(str, size, format, ap);
    va_end(ap);
    return rt;
}

int vsprintf(char *str, const char *format, va_list ap) property(loop_free)
{
    return _vsprintf(str, format, ap);
}

int vsnprintf(char *str, int size, const char *format, va_list ap) property(loop_free)
{
    return _vsnprintf(str, size, format, ap);
}

inline int _vsscanf(const char *str, const char *format, va_list ap)
{
    Hosted_clib_vars _hosted_clib_vars;
    // Pass arguments to host
    _hosted_clib_vars.puts_s = str;
    _hosted_clib_vars.format = format;
    _hosted_clib_vars.ap = ap;
    // Call vsscanf on host
    _hosted_clib_vars.call_type = clct_vsscanf;
#ifdef STDIO_SAFE_NOHOSTED
    _hosted_clib_vars.stream_rt = -1;
#endif
    _hosted_clib_io(&_hosted_clib_vars);
    // stream_rt contains number of performed conversions or EOF
    return _hosted_clib_vars.stream_rt;
}

int sscanf(const char *str, const char *format, ...) property(loop_free)
{
    va_list ap;
    va_start(ap, format);
    int rt = _vsscanf(str, format, ap);
    va_end(ap);
    return rt;
}

int vsscanf(const char *str, const char *format, va_list ap) property(loop_free)
{
    return _vsscanf(str, format, ap);
}
