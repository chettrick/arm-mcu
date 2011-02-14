/* Simple bit twiddler test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

#ifdef BOARD_MBED_LPC1768
#define LED1	18
#define LED2	20
#define LED3	21
#define LED4	23

#define LEDMASK	((1 << LED1)|(1 << LED2)|(1 << LED3)|(1 << LED4))
#endif

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef BOARD_MBED_LPC1768
  LPC_GPIO1->FIOMASK = !LEDMASK;
  LPC_GPIO1->FIODIR = LEDMASK;

  for (i = 0;; i ++)
    LPC_GPIO1->FIOPIN = i;
#endif
}
