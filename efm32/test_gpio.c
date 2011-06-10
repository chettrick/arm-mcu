/* Simple bit twiddler test program */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);

#ifdef EFM32_G8XX_STK
  unsigned long int i;

  /* Enable GPIO */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Configure GPIO port C 0-3 as LED control outputs */
  GPIO_PinModeSet(gpioPortC, 0, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortC, 1, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortC, 2, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortC, 3, gpioModePushPull, 1);

  for (i = 0;; i++)
    GPIO_PortOutSetVal(gpioPortC, i >> 16, 0xf);
#endif
}
