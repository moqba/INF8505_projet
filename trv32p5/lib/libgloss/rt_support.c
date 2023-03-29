/*
-- File : rt_support.c
--
-- Contents : Implementation of IO system calls (through hosted IO)
--
-- Copyright (c) 2014-2021 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#define STDIO_SAFE_NOHOSTED

#include <errno.h>
#include <stddef.h>

#if defined(__cplusplus) || defined(__ndl__)
extern "C" {
#endif

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
    clct_vfscanf_alt  = 36, clct_vsscanf_alt = 37,

    clct_open        = 38, clct_lseek   = 39, clct_read       = 40,
    clct_write       = 41,

    clct_gettimeofday = 42
};

typedef struct {
    int         call_type;
    int         filedes; // also used a indicator if ptimeval for gettimeofday is non zero
    int         err;
    union {
        const char* path;
        const char* mem;
    } str_arg1;
    union {
        const char* mode;
        const char* oldpath;
    } str_arg2;
    const char* format;
    long        offset;  // also used for timeval.tv_sec
    union {
        int     whence;
        int     lsb_first;
        int     oflag;
    } int_arg1;
    int         eof; // also used for timeval.tv_usec
    union {
        int     c;
        int     err;
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
int hosted_io_with_err(Hosted_clib_vars* p) {
#ifdef STDIO_SAFE_NOHOSTED
    p->err = EBADF;
#endif
    chess_hosted_io(p);
    if (p->err) errno = p->err;
    return p->err;
}

int _close(int filedes) {
    Hosted_clib_vars vars;
    vars.filedes = filedes;
    vars.call_type = clct_close;
    if (hosted_io_with_err(&vars) != 0)
        return -1;
    return 0;
}

int _open(const char* path, int oflag, int mode) {
    Hosted_clib_vars vars;
    vars.str_arg1.path = path;
    vars.int_arg1.oflag = oflag;
    vars.int_arg2.mode = mode;
    vars.call_type = clct_open;
    if (hosted_io_with_err(&vars) != 0)
        return -1;
    return vars.filedes;
}

long _lseek(int filedes, long offset, int whence) {
    Hosted_clib_vars vars;
    vars.filedes = filedes;
    vars.offset = offset;
    vars.int_arg1.whence = whence;
    vars.call_type = clct_lseek;
    if (hosted_io_with_err(&vars) != 0)
        return -1;
    return vars.offset;
}

int _read(int filedes, void* buf, unsigned nbyte) {
    Hosted_clib_vars vars;
    vars.filedes = filedes;
    vars.read_ptr.read_ptr_dm = (void chess_storage(DMb)*)buf;
    vars.size = nbyte;
    vars.str_arg1.mem = "DMb";
    vars.call_type = clct_read;
    if (hosted_io_with_err(&vars) != 0)
        return -1;
    return vars.size;
}

int _write(int filedes, const void* buf, unsigned nbyte) {
    Hosted_clib_vars vars;
    vars.filedes = filedes;
    vars.write_ptr.write_ptr_dm = (const void chess_storage(DMb)*)buf;
    vars.size = nbyte;
    vars.str_arg1.mem = "DMb";
    vars.call_type = clct_write;
    if (hosted_io_with_err(&vars) != 0)
        return -1;
    return vars.size;
}

int _rename(const char* oldpath, const char* newpath) {
    Hosted_clib_vars vars;
    vars.str_arg1.path = newpath;
    vars.str_arg2.oldpath = oldpath;
    vars.call_type = clct_rename;
    if (hosted_io_with_err(&vars) != 0)
        return -1;
    return 0;
}

void _exit(int rc) {
    chess_exit(rc);

    while (1) ;
}

#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>

//#define STOP_UNIMPL

int _unlink(const char* path) {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
};

int _chown(const char *path,  uid_t owner, gid_t group) {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
}

int _execve(char  *name, char **argv, char **env) {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
}

int _fcntl(int fd, int cmd, ...) {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
}

int _fork() {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
}

int _fstat(int fildes, struct stat *st) {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
}

int _getpid() {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
}

int _gettimeofday(struct timeval  *ptimeval,  void *ptimezone) {
    Hosted_clib_vars vars;
    vars.call_type = clct_gettimeofday;
    vars.eof = ptimeval != NULL;
    if (hosted_io_with_err(&vars) != 0) {
        errno = vars.err;
        return -1;
    }
    if (ptimeval != NULL) {
        ptimeval->tv_sec = vars.offset;
        ptimeval->tv_usec = vars.eof;
    }
    errno = vars.err;
    return vars.filedes;
}

int _isatty(int file) {
    if (file < 3) {
        return 1;
    } else {
        errno = ENOSYS;
#ifdef STOP_UNIMPL
        chess_stop();
#endif
        return 0;
    }
}

int _kill(int pid, int sig) {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
}

int _link(char *existing, char *new) {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
}

int _mkdir(const char* path, int mode) {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
}

int _readlink(const char *path, char *buf, size_t bufsize) {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
}

int _stat(const char  *file, struct stat *st) {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
}

int _symlink(const char *path1, const char *path2) {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
}

int _times(struct tms *buf) {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
}

int _wait(int  *status) {
    errno = ENOSYS;
#ifdef STOP_UNIMPL
    chess_stop();
#endif
    return -1;
}

#if defined(__cplusplus) || defined(__ndl__)
} // extern "C"
#endif
