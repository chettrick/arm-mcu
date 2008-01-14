/* Simple "Hello, world" application */

// $Id: hello.c,v 1.2 2008-01-14 11:13:38 cvs Exp $

#include <conio.h>
#include <cpu.h>
#include <stdio.h>

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);
  conio_init(0, 19200);

  puts("\033[H\033[2JHello, world");
  for (;;);
}
