/* Abstract bitwise GPIO services */

// $Id$

#include <cpu.h>
#include <errno.h>

#undef errno
extern int errno;

#define MAX_GPIO_PORTS		5
#define PINS_PER_GPIO_PORT	32

static LPC_GPIO_TypeDef * const PORTS[] =
{
  LPC_GPIO0,
  LPC_GPIO1,
  LPC_GPIO2,
  LPC_GPIO3,
  LPC_GPIO4
};

int gpiopin_configure(unsigned int pin, gpiopin_direction_t direction)
{
  unsigned int port;

  errno = 0;

// Split into port and pin components

  port = pin / PINS_PER_GPIO_PORT;
  pin  = pin % PINS_PER_GPIO_PORT;

// Validate parameters

  if (port >= MAX_GPIO_PORTS)
  {
    errno = EINVAL;
    return 1;
  }

  if (direction > GPIOPIN_OUTPUT)
  {
    errno = EINVAL;
    return 1;
  }

// Configure the pin

  PORTS[port]->FIOMASK &= ~(1 << pin);
  PORTS[port]->FIODIR  |= (direction << pin);
  return 0;
}
