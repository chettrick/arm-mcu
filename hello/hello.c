/* Simple "Hello, world" application */

// $Id: hello.c,v 1.1 2008-01-03 10:37:57 cvs Exp $

#include <conio.h>
#include <cpu.h>
#include <stdio.h>

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);
  conio_init(UART0_BASE_ADDR, 19200);

  puts("\033[H\033[2JHello, world");
  for (;;);
}
