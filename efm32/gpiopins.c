/* Abstract bitwise GPIO services */

// $Id$

#include <cpu.h>
#include <errno.h>

#define MAX_GPIO_PORTS		6
#define PINS_PER_GPIO_PORT	16

int gpiopin_configure(unsigned int pin, gpiopin_direction_t direction)
{
  unsigned int port;

// Split into port and pin components

  port = pin / PINS_PER_GPIO_PORT;
  pin  = pin % PINS_PER_GPIO_PORT;

// Validate parameters

  if (port >= MAX_GPIO_PORTS)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

  if (direction > GPIOPIN_OUTPUT)
  {
    errno_r = EINVAL;
    return __LINE__ - 3;
  }

// Enable GPIO peripheral clock

  CMU_ClockEnable(cmuClock_GPIO, true);

// Configure the pin

  GPIO_PinModeSet(port, pin, gpioModePushPull, direction);
  return 0;
}
