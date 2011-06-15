/* Abstract bitwise GPIO services */

// $Id$

#include <assert.h>
#include <cpu.h>

#define MAX_GPIO_PORTS		7
#define PINS_PER_GPIO_PORT	16

static const struct
{
  GPIO_TypeDef *gpiobase;
  unsigned long int peripheral;
} PORTS[] =
{
  { GPIOA, RCC_APB2Periph_GPIOA },
  { GPIOB, RCC_APB2Periph_GPIOB },
  { GPIOC, RCC_APB2Periph_GPIOC },
  { GPIOD, RCC_APB2Periph_GPIOD },
  { GPIOE, RCC_APB2Periph_GPIOE },
  { GPIOF, RCC_APB2Periph_GPIOF },
  { GPIOG, RCC_APB2Periph_GPIOG }
};

void gpiopin_configure(unsigned int pin, gpiopin_direction_t direction)
{
  unsigned int port;
  GPIO_InitTypeDef config;

// Split into port and pin components

  port = pin / PINS_PER_GPIO_PORT;
  pin  = pin % PINS_PER_GPIO_PORT;

// Validate parameters

  assert(port < MAX_GPIO_PORTS);
  assert(direction <= GPIOPIN_OUTPUT);

// Configure peripheral clocks 

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(PORTS[port].peripheral, ENABLE);

// Configure the pin

  GPIO_StructInit(&config);
  config.GPIO_Pin =  1 << pin;
  config.GPIO_Mode = direction ? GPIO_Mode_Out_PP : GPIO_Mode_IN_FLOATING;
  config.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PORTS[port].gpiobase, &config);
}
