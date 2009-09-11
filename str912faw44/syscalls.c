/******************************************************************************/
/*                                                                            */
/*        Syscall support functions for newlib console I/O with stdio         */
/*                                                                            */
/******************************************************************************/

// $Id$

#include <errno.h>
#undef errno

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

/* Initialize if first time through. */

  if (!heap_ptr) heap_ptr = end;

  base = heap_ptr;      /*  Point to end of heap.                       */
  heap_ptr += incr;     /*  Increase heap.                              */

  return base;          /*  Return pointer to start of new heap area.   */
}

#ifdef REENTRANT_SYSCALLS
int _open_r(void *reent, const char *path, int flags, int mode)
#else
int _open(const char *path, int flags, int mode)
#endif
{
  int d;

  if ((d = device_lookup((char *) path)) < 0)
    return -1;

  if (device_table[d].init != NULL)
    if (device_table[d].init(device_table[d].subdevice, device_table[d].settings))
      return -1;

  return d;
}

#ifdef REENTRANT_SYSCALLS
int _close_r(void *reent, int fd)
#else
int _close(int fd)
#endif
{
  return 0;
}

#ifdef REENTRANT_SYSCALLS
int _fstat_r(void *reent, int fd, struct stat *st)
#else
int _fstat(int fd, struct stat *st)
#endif
{
  st->st_mode = S_IFCHR;
  return 0;
}

#ifdef REENTRANT_SYSCALLS
int _isatty_r(struct _reent *r, int fd)
#else
int _isatty(int fd)
#endif
{
  return 1;
}

#ifdef REENTRANT_SYSCALLS
off_t _lseek_r(void *reent, int fd, off_t pos, int whence)
#else
int _lseek(int fd, off_t pos, int whence)
#endif
{
  return 0;
}

#ifdef REENTRANT_SYSCALLS
long _read_r(void *reent, int fd, void *buf, size_t size)
#else
int _read(int fd, char *buf, size_t size)
#endif
{
  if (device_table[fd].name[0] == 0)
  {
    errno = ENODEV;
    return -1;
  }

  if (device_table[fd].read == NULL)
  {
    errno = EIO;
    return -1;
  }

#ifdef CONFIG_RAWREAD
  return device_table[fd].read(device_table[fd].subdevice, buf, size)
#else
  return device_gets(fd, buf, size);
#endif
}

#ifdef REENTRANT_SYSCALLS
long _write_r(void *reent, int fd, const char *src, size_t size)
#else
int _write(int fd, const char *src, size_t size)
#endif
{
  char dst[256];
  int srcidx;
  int dstidx;
  int totalbytes;	// Number of source bytes transferred
  int chunkbytes;	// Number of chunk bytes transferred
  int len;

  if (device_table[fd].name[0] == 0)
  {
    errno = ENODEV;
    return -1;
  }

  if (device_table[fd].write == NULL)
  {
    errno = EIO;
    return -1;
  }

  srcidx = 0;
  totalbytes = 0;

  while (totalbytes < size)
  {
    dstidx = 0;

// Copy data from source buffer to chunk buffer, inserting CR's before LF's

    while ((totalbytes < size) && (dstidx < sizeof(dst)))
    {
      if ((dstidx == sizeof(dst) - 1) && (src[srcidx] == '\n'))
        break;

      if (src[srcidx] == '\n')
      {
        dst[dstidx++] = '\r';
        dst[dstidx++] = '\n';
      }
      else
        dst[dstidx++] = src[srcidx];

      srcidx++;
      totalbytes++;
    }

// Dispatch chunk buffer to device driver

    chunkbytes = 0;

    while (chunkbytes < dstidx)
    {
      len = device_table[fd].write(device_table[fd].subdevice, dst + chunkbytes, dstidx - chunkbytes);
      if (len < 0) return len;
      chunkbytes += len;
    }
  }

  return totalbytes;
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

void __attribute__ ((weak)) abort(void)
{
  for (;;);
}

int __attribute__ ((weak)) isatty(int fd)
{
  return 1;
}
