/* Abstract bitwise GPIO services */

// $Id$

#include <assert.h>
#include <cpu.h>

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

void gpiopin_configure(unsigned int pin, gpiopin_direction_t direction)
{
  unsigned int port;

// Split into port and pin components

  port = pin / PINS_PER_GPIO_PORT;
  pin  = pin % PINS_PER_GPIO_PORT;

// Validate parameters

  assert(port < MAX_GPIO_PORTS);
  assert(direction <= GPIOPIN_OUTPUT);

// Configure the pin

  PORTS[port]->FIOMASK &= ~(1 << pin);
  PORTS[port]->FIODIR  |= (direction << pin);
}
