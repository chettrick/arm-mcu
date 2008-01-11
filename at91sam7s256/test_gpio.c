/* Simple bit twiddler test program */

// $Id: test_gpio.c,v 1.3 2008-01-11 11:18:50 cvs Exp $

#include <cpu.h>

int main(void)
{
  volatile unsigned int i;

  cpu_init(DEFAULT_CPU_FREQ);

/* Configure GPIO's */

  *AT91C_PMC_PCER	= 0x00000004;	// Enable Port A peripheral clock

  *AT91C_PIOA_PER	= 0xFFFFFFFF;	// Port A is all GPIO
  *AT91C_PIOA_OER	= 0xFFFFFFFF;	// Port A is all output
  *AT91C_PIOA_OWER	= 0xFFFFFFFF;	// Port A all ODSR enabled
  *AT91C_PIOA_MDDR	= 0xFFFFFFFF;	// Port A all push pull

/* Trivial main program */

  for (i = 0xFFFFFFFF;; i++)
    *AT91C_PIOA_ODSR = i;		// Update PORT B outputs
}
