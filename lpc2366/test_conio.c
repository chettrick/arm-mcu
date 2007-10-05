/* Simple serial console I/O test program */

// $Id: test_conio.c,v 1.2 2007-10-05 15:57:30 cvs Exp $

#include <lpc2366/conio.h>
#include <lpc2366/cpu.h>
#include <lpc2366/io.h>

#include <stdio.h>
#include <string.h>

int main(void)
{
  char buf[32];

  cpu_init();
  conio_init(19200);

  puts("\033[H\033[2JLPC2366 Console I/O Test\n");

  for (;;)
  {
    printf("Enter a string: ");
    fgets(buf, sizeof(buf), stdin);
    if (strlen(buf)) if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
    printf("You entered %ld bytes, '%s'\n", strlen(buf), buf);
  }
}
