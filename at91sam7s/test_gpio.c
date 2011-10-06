/* Simple bit twiddler test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

int main(void)
{
  volatile unsigned int i;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef OLIMEX_SAM7_P256
#define LED1PIN		18
#define LED2PIN		17

  *AT91C_PMC_PCER	= 0x00000004;	// Enable Port A peripheral clock
  *AT91C_PIOA_PER	= 1 << LED1PIN;	// LED1 pin is GPIO
  *AT91C_PIOA_PPUDR	= 1 << LED1PIN;	// LED1 pin does not need internal pullup
  *AT91C_PIOA_OER	= 1 << LED1PIN;	// LED1 pin is output
  *AT91C_PIOA_OWER	= 1 << LED1PIN;	// LED1 pin is synchronous output
  *AT91C_PIOA_MDER	= 1 << LED1PIN;	// LED1 pin is open drain output

  *AT91C_PIOA_PER	= 1 << LED2PIN;	// LED2 pin is GPIO
  *AT91C_PIOA_PPUDR	= 1 << LED2PIN;	// LED2 pin does not need internal pullup
  *AT91C_PIOA_OER	= 1 << LED2PIN;	// LED2 pin is output
  *AT91C_PIOA_OWER	= 1 << LED2PIN;	// LED2 pin is synchronous output
  *AT91C_PIOA_MDER	= 1 << LED2PIN;	// LED2 pin is open drain output

  for (i = 0;; i++)
  {
    *AT91C_PIOA_ODSR = i >> 2;		// Update LED's
  }
#endif
}
