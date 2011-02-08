/******************************************************************************/
/*                                                                            */
/*             Syscall shim functions for newlib file system I/O              */
/*                                                                            */
/******************************************************************************/

// $Id$

static const char syscalls_revision[] = "$Id$";

#include <cpu.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#undef errno
int errno;

extern char end[];
static char *heap_ptr;

char *_sbrk_r(struct _reent *reent, size_t incr)
{
  char  *base;

/* Initialize if first time through. */

  if (!heap_ptr) heap_ptr = end;

  base = heap_ptr;      /*  Point to end of heap.                       */
  heap_ptr += incr;     /*  Increase heap.                              */

  reent->_errno = 0;
  return base;          /*  Return pointer to start of new heap area.   */
}

// Basic I/O services

int _open_r(struct _reent *reent, char *path, int flags, int mode)
{
  reent->_errno = 0;
  return device_open(path, flags, mode);
}

int _close_r(struct _reent *reent, int fd)
{
  reent->_errno = 0;
  return device_close(fd);
}

long _read_r(struct _reent *reent, int fd, void *dst, size_t size)
{
  reent->_errno = 0;
  return device_read(fd, dst, size);
}

long _write_r(struct _reent *reent, int fd, void *src, size_t size)
{
  reent->_errno = 0;
  return device_write(fd, src, size);
}

// File system support services

int _fstat_r(struct _reent *reent, int fd, struct stat *st)
{
  reent->_errno = 0;
  return device_stat(fd, st);
}

int _isatty_r(struct _reent *reent, int fd)
{
  reent->_errno = 0;
  return device_isatty(fd);
}

off_t _lseek_r(struct _reent *reent, int fd, off_t pos, int whence)
{
  reent->_errno = 0;
  return device_seek(fd, pos, whence);
}

// The following are just dummy routines

pid_t _getpid_r(struct _reent *reent)
{
  reent->_errno = 0;
  return 1;
}

int _kill_r(struct _reent *reent, int pid, int sig)
{
  reent->_errno = EINVAL;
  return -1;
}

// Only certain toolchains require the following so we mark them weak

void __attribute__ ((weak)) abort(void)
{
  for (;;);
}

int __attribute__ ((weak)) isatty(int fd)
{
  errno = 0;
  return device_isatty(fd);
}

void __attribute__ ((weak)) _exit(int status)
{
  for (;;);
}
