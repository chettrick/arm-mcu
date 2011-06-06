/* Simple bit twiddler test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

// Flash MBED-LPC1768 LED's

#ifdef BOARD_MBED_LPC1768
#define LED1	18
#define LED2	20
#define LED3	21
#define LED4	23

#define LEDMASK	((1 << LED1)|(1 << LED2)|(1 << LED3)|(1 << LED4))

  LPC_GPIO1->FIOMASK &= ~LEDMASK;
  LPC_GPIO1->FIODIR |= LEDMASK;

  for (i = 0;; i++)
    LPC_GPIO1->FIOPIN = i;
#endif

// Flash BlueBoard LPC1768-H test LED

#ifdef BOARD_BLUEBOARD_LPC1768_H
#define LED1	29

#define LEDMASK	((1 << LED1))

  LPC_GPIO1->FIOMASK &= ~LEDMASK;
  LPC_GPIO1->FIODIR |= LEDMASK;

  for (i = 0;; i++)
    LPC_GPIO1->FIOPIN = i << 7;
#endif
}
