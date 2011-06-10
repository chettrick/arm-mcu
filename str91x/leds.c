/* Abstract services for controlling LED's */

// $Id$

#include <cpu.h>

#define MAX_LEDS	4

// Initialize the LED's (to the off state)

void LEDS_initialize(void)
{
#ifdef STMICRO_STR910_EVAL
  GPIO_InitTypeDef config;

  SCU_APBPeriphClockConfig(__GPIO9, ENABLE);		// Turn on GPIO9 clock
  SCU_APBPeriphReset(__GPIO9, DISABLE);			// Let GPIO9 out of reset
 
  GPIO_StructInit(&config);
  config.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  config.GPIO_Direction = GPIO_PinOutput;		// LED pins are outputs
  config.GPIO_Type = GPIO_Type_PushPull;		// LED pins are push pull outputs
  config.GPIO_Alternate = GPIO_OutputAlt1;		// LED pins are GPIO outputs
  GPIO_Init(GPIO9, &config);
#endif

  LEDS_set(0);						// Turn off all LEDs at startup
}

// Get LED states.  A 1 bit in the result indicates the LED is on.
// A 0 bit in the result indicates the LED is off.

unsigned long int LEDS_get(void)
{
  unsigned long int result = 0;

#ifdef STMICRO_STR910_EVAL
  result = (~GPIO_Read(GPIO9)) & 0x0F;
#endif

  return result;
}

// Set LED states.  A 1 bit in the mask indicates the LED should be turned on. 
// A 0 bit in the mask indicates the LED should be turned off.

void LEDS_set(unsigned long int mask)
{
#ifdef STMICRO_STR910_EVAL
  int i;

  for (i = 0; i < MAX_LEDS; i++)
  {
    if (mask & 0x01)
    {
      GPIO_WriteBit(GPIO9, (1 << i), Bit_RESET);
    }
    else
    {
      GPIO_WriteBit(GPIO9, (1 << i), Bit_SET);
    }

    mask >>= 1;
  }
#endif
}
