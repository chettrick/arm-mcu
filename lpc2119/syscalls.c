/******************************************************************************/
/*                                                                            */
/*        Syscall support functions for newlib console I/O with stdio         */
/*                                                                            */
/******************************************************************************/

// $Id: syscalls.c,v 1.1 2006-12-12 21:57:48 cvs Exp $

#include <unistd.h>
#include <sys/stat.h>

#include "conio.h"

int isatty(int desc)
{
  return 1;
}

extern char end[];
static char *heap_ptr;

void *_sbrk_r(struct _reent *_s_r, ptrdiff_t nbytes)
{
  char  *base;

/* Initialize if first time through. */

  if (!heap_ptr) heap_ptr = end;

  base = heap_ptr;	/*  Point to end of heap.			*/
  heap_ptr += nbytes;	/*  Increase heap.				*/

  return base;		/*  Return pointer to start of new heap area.	*/
}

int _open_r(void *reent, const char *file, int flags, int mode)
{
  return 1;
}

int _close_r(void *reent, int fd)
{
  return 0;
}

off_t _lseek_r(void *reent, int fd, off_t pos, int whence)
{
  return 0;
}

long _read_r(void *reent, int fd, char *buf, size_t cnt)
{
  buf[0] = getch();

  return 1;
}

long _write_r(void *reent, int fd, const char *buf, size_t cnt)
{
  int i;

  for (i = 0; i < cnt; i++)
    putch(buf[i]);

  return cnt;
}

int _fstat_r(void *reent, int file, struct stat *pstat)
{
  pstat->st_mode = S_IFCHR;
  return 0;
}
