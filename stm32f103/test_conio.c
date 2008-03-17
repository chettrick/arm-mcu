/* Simple serial console I/O test program */

// $Id: test_conio.c,v 1.3 2008-03-17 21:16:16 cvs Exp $

#include <conio.h>
#include <cpu.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
  char buf[32];

  cpu_init(DEFAULT_CPU_FREQ);
  conio_init(2, 19200);

  puts("\033[H\033[2JSTM32F103 Console I/O Test\n");

  for (;;)
  {
    printf("Enter a string: ");
    fgets(buf, sizeof(buf), stdin);
    if (strlen(buf)) if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
    printf("You entered %d bytes, '%s'\n", strlen(buf), buf);
  }
}
