/* Simple bit twiddler test program */

// $Id: test_gpio.c 3199 2011-10-18 11:28:12Z svn $

static const char revision[] = "$Id: test_gpio.c 3199 2011-10-18 11:28:12Z svn $";

#include <cpu.h>

int main(void)
{
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

#ifdef STM32F4_DISCOVERY
  gpiopin_configure(GPIOPIN0, GPIOPIN_INPUT);		// PA0
  gpiopin_configure(GPIOPIN60, GPIOPIN_OUTPUT);		// PD12
  gpiopin_configure(GPIOPIN61, GPIOPIN_OUTPUT);		// PD13
  gpiopin_configure(GPIOPIN62, GPIOPIN_OUTPUT);		// PD14
  gpiopin_configure(GPIOPIN63, GPIOPIN_OUTPUT);		// PD15

  for (i = 0;; i++)
  {
    // Speed up flashing if user button is pressed

    if (GPIOPIN0IN)
    {
      GPIOPIN60OUT = i >> 18;
      GPIOPIN61OUT = i >> 19;
      GPIOPIN62OUT = i >> 20;
      GPIOPIN63OUT = i >> 21;
    }

    // Flash LED's at normal speed

    else
    {
      GPIOPIN60OUT = i >> 19;
      GPIOPIN61OUT = i >> 20;
      GPIOPIN62OUT = i >> 21;
      GPIOPIN63OUT = i >> 22;
    }
  }
#endif

#ifdef FEZ_CERB40
  gpiopin_configure(GPIOPIN38, GPIOPIN_OUTPUT);		// PC6
  gpiopin_configure(GPIOPIN39, GPIOPIN_OUTPUT);		// PC7
  gpiopin_configure(GPIOPIN40, GPIOPIN_OUTPUT);		// PC8
  gpiopin_configure(GPIOPIN41, GPIOPIN_OUTPUT);		// PC9

  for (i = 0;; i++)
  {
    GPIOPIN38OUT = i >> 18;
    GPIOPIN39OUT = i >> 19;
    GPIOPIN40OUT = i >> 20;
    GPIOPIN41OUT = i >> 21;
  }
#endif
}
