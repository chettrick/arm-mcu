/******************************************************************************/
/*                                                                            */
/*             Syscall shim functions for newlib file system I/O              */
/*                                                                            */
/******************************************************************************/

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

extern char __heap_start__[];	// Beginning of heap, address set by linker
extern char __heap_end__[];	// End of heap, address set by linker

static char *freespace;		// Pointer to free space (unclaimed heap area)

// Calling this function from cpu_init() tricks the linker into using these
// syscall functions instead of those in libc.a.

void __use_custom_syscalls(void)
{
}

// Rudimentary heap area manager.  The dynamic memory allocator in newlib
// (malloc() and friends) calls this function to claim some or all of the
// free space allocated for heap by the linker.  The heap area is bounded
// by __heap_start__ and __heap_end__ which are set by the linker.  Note that
// the memory allocator will never release memory it has claimed.

char *_sbrk_r(struct _reent *reent, size_t bytes)
{
  char  *base;

/* Initialize free space pointer if first time through. */

  if (!freespace)
  {
    freespace = __heap_start__;
    memset(__heap_start__, 0, __heap_end__ - __heap_start__);
  }

/* Check for enough free space available */

  if (freespace + bytes > __heap_end__)
  {
    reent->_errno = ENOMEM;
    return NULL;
  }

  base = freespace;	// Get address of free space

  freespace += bytes;	// Claim heap area memory / Advance free space pointer

  reent->_errno = 0;
  return base;		// Return pointer to claimed heap area
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
  return device_isatty(fd);
}

void __attribute__ ((weak)) _exit(int status)
{
  for (;;);
}
