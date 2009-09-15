/******************************************************************************/
/*                                                                            */
/*        Syscall support functions for newlib console I/O with stdio         */
/*                                                                            */
/******************************************************************************/

// $Id$

#include <cpu.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#undef errno
int errno;

extern char end[];
static char *heap_ptr;

char *_sbrk_r(void *reent, size_t incr)
{
  char  *base;

  errno = 0;

/* Initialize if first time through. */

  if (!heap_ptr) heap_ptr = end;

  base = heap_ptr;      /*  Point to end of heap.                       */
  heap_ptr += incr;     /*  Increase heap.                              */

  return base;          /*  Return pointer to start of new heap area.   */
}

int _open_r(void *reent, char *path, int flags, int mode)
{
  errno = 0;
  return device_open(path, flags, mode);
}

int _close_r(void *reent, int fd)
{
  errno = 0;
  return device_close(fd);
}

long _read_r(void *reent, int fd, void *dst, size_t size)
{
  errno = 0;
  return device_read(fd, dst, size);
}

long _write_r(void *reent, int fd, char *src, size_t size)
{
  errno = 0;
  return device_write(fd, src, size);
}

// The following are just dummy routines

int _fstat_r(void *reent, int fd, struct stat *st)
{
  errno = 0;
  st->st_mode = S_IFCHR;
  return 0;
}

int _isatty_r(struct _reent *r, int fd)
{
  errno = 0;
  return 1;
}

off_t _lseek_r(void *reent, int fd, off_t pos, int whence)
{
  errno = 0;
  return 0;
}

pid_t _getpid_r(struct _reent *r)
{
  errno = 0;
  return 1;
}

int _kill_r(struct _reent *r, int pid, int sig)
{
  errno = EINVAL;
  return -1;
}

// Only certain toolchains require the following so we mark them weak

void __attribute__ ((weak)) abort(void)
{
  for (;;);
}

int __attribute__ ((weak)) isatty(int fd)
{
  return 1;
}

void __attribute__ ((weak)) _exit(int status)
{
  for (;;);
}
