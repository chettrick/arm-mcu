/******************************************************************************/
/*                                                                            */
/*        Syscall support functions for newlib console I/O with stdio         */
/*                                                                            */
/******************************************************************************/

// $Id$

#include <errno.h>
#undef errno

#define REENTRANT_SYSCALLS 1

#ifdef REENTRANT_SYSCALLS
int errno;
#else
extern int errno;
#endif

#include <cpu.h>
#include <string.h>
#include <sys/stat.h>

extern char end[];
static char *heap_ptr;

#ifdef REENTRANT_SYSCALLS
char *_sbrk_r(void *reent, size_t incr)
#else
char * _sbrk(ptrdiff_t incr)
#endif
{
  char  *base;

  errno = 0;

/* Initialize if first time through. */

  if (!heap_ptr) heap_ptr = end;

  base = heap_ptr;      /*  Point to end of heap.                       */
  heap_ptr += incr;     /*  Increase heap.                              */

  return base;          /*  Return pointer to start of new heap area.   */
}

#ifdef REENTRANT_SYSCALLS
int _open_r(void *reent, char *path, int flags, int mode)
#else
int _open(char *path, int flags, int mode)
#endif
{
  errno = 0;
  return device_open(path, flags, mode);
}

#ifdef REENTRANT_SYSCALLS
int _close_r(void *reent, int fd)
#else
int _close(int fd)
#endif
{
  errno = 0;
  return device_close(fd);
}

#ifdef REENTRANT_SYSCALLS
long _read_r(void *reent, int fd, void *dst, size_t size)
#else
int _read(int fd, char *dst, size_t size)
#endif
{
  errno = 0;
  return device_read(fd, dst, size);
}

#ifdef REENTRANT_SYSCALLS
long _write_r(void *reent, int fd, char *src, size_t size)
#else
int _write(int fd, char *src, size_t size)
#endif
{
  errno = 0;
  return device_write(fd, src, size);
}

// The following are just dummy routines

#ifdef REENTRANT_SYSCALLS
int _fstat_r(void *reent, int fd, struct stat *st)
#else
int _fstat(int fd, struct stat *st)
#endif
{
  errno = 0;
  st->st_mode = S_IFCHR;
  return 0;
}

#ifdef REENTRANT_SYSCALLS
int _isatty_r(struct _reent *r, int fd)
#else
int _isatty(int fd)
#endif
{
  errno = 0;
  return 1;
}

#ifdef REENTRANT_SYSCALLS
off_t _lseek_r(void *reent, int fd, off_t pos, int whence)
#else
int _lseek(int fd, off_t pos, int whence)
#endif
{
  errno = 0;
  return 0;
}

void _exit(int status)
{
  for (;;);
}

#ifdef REENTRANT_SYSCALLS
pid_t _getpid_r(struct _reent *r)
#else
pid_t _getpid(void)
#endif
{
  errno = 0;
  return 1;
}

#ifdef REENTRANT_SYSCALLS
int _kill_r(struct _reent *r, int pid, int sig)
#else
int _kill(int pid, int sig)
#endif
{
  errno = EINVAL;
  return -1;
}

// Only certain toolchains require the following so we mark them weak

#if 0
void __attribute__ ((weak)) abort(void)
{
  for (;;);
}

int __attribute__ ((weak)) isatty(int fd)
{
  return 1;
}
#endif
