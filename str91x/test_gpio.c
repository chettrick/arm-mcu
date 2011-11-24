/* Simple bit twiddler test program for the STR91x ARM MCU */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);

#ifdef STMICRO_STR910_EVAL
  GPIO_InitTypeDef config;
  unsigned long int i;

  SCU_APBPeriphClockConfig(__GPIO7, ENABLE);	// Turn on GPIO7 clock
  SCU_APBPeriphReset(__GPIO7, DISABLE);		// Let GPIO7 out of reset

  SCU_APBPeriphClockConfig(__GPIO9, ENABLE);	// Turn on GPIO9 clock
  SCU_APBPeriphReset(__GPIO9, DISABLE);		// Let GPIO9 out of reset

  // Initialize LED output pins
 
  GPIO_StructInit(&config);
  config.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  config.GPIO_Direction = GPIO_PinOutput;	// LED pins are outputs
  config.GPIO_Type = GPIO_Type_PushPull;	// LED pins are push pull outputs
  config.GPIO_Alternate = GPIO_OutputAlt1;	// LED pins are GPIO outputs
  GPIO_Init(GPIO9, &config);

  // Initialize joystick input pins

  GPIO_StructInit(&config);
  config.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  config.GPIO_Direction = GPIO_PinInput;	// Joystick pins are inputs
  config.GPIO_Alternate = GPIO_InputAlt1;	// Joystick pins are GPIO inputs
  config.GPIO_IPInputConnected = GPIO_IPInputConnected_Disable;
  GPIO_Init(GPIO7, &config);

  for (i = 0;; i++)
  {
    // Speed up flashing if joystick is UP

    if ((GPIO_Read(GPIO7) >> 4) == 8)
    {
      GPIO_Write(GPIO9, ~(i >> 15));
    }

    // Slow down flashing if joystick is DOWN

    else if ((GPIO_Read(GPIO7) >> 4) == 2)
    {
      GPIO_Write(GPIO9, ~(i >> 17));
    }

    // Turn off LED's if PB3 is pressed

    else if ((GPIO_Read(GPIO7) >> 4) == 10)
    {
      GPIO_Write(GPIO9, 0xFF);
    }

    // Normal flashing

    else
    {
      GPIO_Write(GPIO9, ~(i >> 16));
    }
  }
#endif
}
