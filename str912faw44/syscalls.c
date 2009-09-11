/******************************************************************************/
/*                                                                            */
/*        Syscall support functions for newlib console I/O with stdio         */
/*                                                                            */
/******************************************************************************/

// $Id$

#include <errno.h>
#undef errno
extern int errno;

#include <cpu.h>
#include <string.h>
#include <sys/stat.h>

extern char end[];
static char *heap_ptr;

void * _sbrk(ptrdiff_t incr)
{
  char  *base;

/* Initialize if first time through. */

  if (!heap_ptr) heap_ptr = end;

  base = heap_ptr;      /*  Point to end of heap.                       */
  heap_ptr += incr;     /*  Increase heap.                              */

  return base;          /*  Return pointer to start of new heap area.   */
}

int _open(const char *path, int flags, ...)
{
  int d;

  if ((d = device_lookup((char *) path)) < 0)
    return -1;

  if (device_table[d].init != NULL)
    if (device_table[d].init(device_table[d].subdevice, device_table[d].settings))
      return -1;

  return d;
}

int _close(int fd)
{
  return 0;
}

int _fstat(int fd, struct stat *st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

int _isatty(int fd)
{
  return 1;
}

int isatty(int fd)
{
  return 1;
}

int _lseek(int fd, off_t pos, int whence)
{
  return 0;
}

int _read(int fd, char *buf, size_t size)
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
  return device_table[fd].read(device_table[fd].subdevice, buf, size);
#else
  return device_gets(fd, buf, size);
#endif
}

int _write(int fd, const char *src, size_t size)
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

pid_t _getpid(void)
{
  return 1;
}

int _kill(int pid, int sig)
{
  errno = EINVAL;
  return -1;
}
