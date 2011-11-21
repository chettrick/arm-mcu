/* Abstract bitwise GPIO services */

// $Id: gpiopins.c 3111 2011-10-06 13:27:38Z svn $

#include <cpu.h>
#include <errno.h>

#define MAX_GPIO_PORTS		7
#define PINS_PER_GPIO_PORT	16

static const struct
{
  GPIO_TypeDef *gpiobase;
  unsigned long int peripheral;
} PORTS[] =
{
  { GPIOA, RCC_AHB1Periph_GPIOA },
  { GPIOB, RCC_AHB1Periph_GPIOB },
  { GPIOC, RCC_AHB1Periph_GPIOC },
  { GPIOD, RCC_AHB1Periph_GPIOD },
  { GPIOE, RCC_AHB1Periph_GPIOE },
  { GPIOF, RCC_AHB1Periph_GPIOF },
  { GPIOG, RCC_AHB1Periph_GPIOG }
};

int gpiopin_configure(unsigned int pin, gpiopin_direction_t direction)
{
  unsigned int port;
  GPIO_InitTypeDef config;

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

// Configure peripheral clock 

  RCC_AHB1PeriphClockCmd(PORTS[port].peripheral, ENABLE);

// Configure the pin

  GPIO_StructInit(&config);
  config.GPIO_Pin =  1 << pin;
  config.GPIO_Mode = direction ? GPIO_Mode_OUT : GPIO_Mode_IN;
  config.GPIO_Speed = GPIO_Speed_50MHz;
  config.GPIO_OType = GPIO_OType_PP;
  config.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(PORTS[port].gpiobase, &config);
  return 0;
}
