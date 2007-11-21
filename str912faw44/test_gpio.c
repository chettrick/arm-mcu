/* Simple bit twiddler test program */

// $Id: test_gpio.c,v 1.1 2007-11-21 08:21:56 cvs Exp $

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

  GPIO8_DIR = 0xFF;
  GPIO9_DIR = 0xFF;

  for (i = 0;; i++)
  {
    GPIO8_DATA = i;
    GPIO9_DATA = i;
  }
}
