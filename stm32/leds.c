/* Abstract services for controlling LED's */

// $Id$

#include <cpu.h>
#include <leds.h>

#ifdef STM32_VALUE_LINE_DISCOVERY
#define MAX_LEDS	2
static const char LED_PINS[MAX_LEDS] = { 8, 9 };	// All are on GPIOC pins
#endif

// Initialize the LED's (to the off state)

void LEDS_initialize(void)
{
#ifdef STM32_VALUE_LINE_DISCOVERY
  int i;
  GPIO_InitTypeDef config;

// Enable GPIOC peripheral clock

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);

// Configure LED pins as output push-pull

  for (i = 0; i < MAX_LEDS; i++)
  {
    GPIO_StructInit(&config);
    config.GPIO_Pin =  (1 << LED_PINS[i]);
    config.GPIO_Mode = GPIO_Mode_Out_PP;
    config.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &config);
  }
#endif

#ifdef OLIMEX_STM32_P103
  GPIO_InitTypeDef config;

// Enable GPIOC peripheral clock

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);

// Configure LED pin as output push-pull

  GPIO_StructInit(&config);
  config.GPIO_Pin =  GPIO_Pin_12;
  config.GPIO_Mode = GPIO_Mode_Out_PP;
  config.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &config);
#endif

  LEDS_set(0);						// Turn off all LEDs at startup
}

// Get LED states.  A 1 bit in the result indicates the LED is on.
// A 0 bit in the result indicates the LED is off.

unsigned long int LEDS_get(void)
{
  unsigned long int result = 0;

#ifdef STM32_VALUE_LINE_DISCOVERY
  int i;

  for (i = 0; i < MAX_LEDS; i++)
  {
    if (GPIO_ReadOutputDataBit(GPIOC, (1 << LED_PINS[i])))
      result |= (1 << i);
  }
#endif

#ifdef OLIMEX_STM32_P103
  result = !GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_12);
#endif

  return result;
}

// Set LED states.  A 1 bit in the mask indicates the LED should be turned on. 
// A 0 bit in the mask indicates the LED should be turned off.

void LEDS_set(unsigned long int mask)
{
#ifdef STM32_VALUE_LINE_DISCOVERY
  int i;

  for (i = 0; i < MAX_LEDS; i++)
  {
    if (mask & 0x01)
      GPIO_SetBits(GPIOC, (1 << LED_PINS[i]));
    else
      GPIO_ResetBits(GPIOC, (1 << LED_PINS[i]));

    mask >>= 1;
  }
#endif

#ifdef OLIMEX_STM32_P103
  if (mask & 0x01)
    GPIO_ResetBits(GPIOC, GPIO_Pin_12);
  else
    GPIO_SetBits(GPIOC, GPIO_Pin_12);
#endif
}
