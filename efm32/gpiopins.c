/* Abstract bitwise GPIO services */

// $Id$

#include <assert.h>
#include <cpu.h>

#define MAX_GPIO_PORTS		6
#define PINS_PER_GPIO_PORT	16

void gpiopin_configure(unsigned int pin, gpiopin_direction_t direction)
{
  unsigned int port;

// Split into port and pin components

  port = pin / PINS_PER_GPIO_PORT;
  pin  = pin % PINS_PER_GPIO_PORT;

// Validate parameters

  assert(port < MAX_GPIO_PORTS);
  assert(direction <= GPIOPIN_OUTPUT);

// Enable GPIO peripheral clock

  CMU_ClockEnable(cmuClock_GPIO, true);

// Configure the pin

  GPIO_PinModeSet(port, pin, gpioModePushPull, direction);
}
