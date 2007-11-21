/******************************************************************************/
/*                                                                            */
/*        Syscall support functions for newlib console I/O with stdio         */
/*                                                                            */
/******************************************************************************/

// $Id: syscalls.c,v 1.1 2007-11-21 08:12:28 cvs Exp $

#include <conio.h>
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
  return 1;
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

int isatty(int fd)
{
  return 1;
}

int _lseek(int fd, off_t pos, int whence)
{
  return 0;
}

int _read(int fd, char *buf, size_t cnt)
{
  *buf = getch();

  return 1;
}

int _write(int fd, const char *buf, size_t cnt)
{
  int i;

  for (i = 0; i < cnt; i++)
    putch(buf[i]);

  return cnt;
}
