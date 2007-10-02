/******************************************************************************/
/*                                                                            */
/*        Syscall support functions for newlib console I/O with stdio         */
/*                                                                            */
/******************************************************************************/

// $Id: syscalls.c,v 1.2 2007-10-02 20:36:06 cvs Exp $

#include <unistd.h>
#include <sys/stat.h>

#include "conio.h"

extern char end[];
static char *heap_ptr;

caddr_t _sbrk(int nbytes)
{
  char  *base;

/* Initialize if first time through. */

  if (!heap_ptr) heap_ptr = end;

  base = heap_ptr;      /*  Point to end of heap.                       */
  heap_ptr += nbytes;   /*  Increase heap.                              */

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

int _lseek(int fd, int offset, int whence)
{
  return 0;
}

int _read(int fd, char *buf, int len)
{
  *buf = getch();

  return 1;
}

int _write(int fd, const char *buf, int len)
{
  int i;

  for (i = 0; i < len; i++)
    putch(buf[i]);

  return len;
}
