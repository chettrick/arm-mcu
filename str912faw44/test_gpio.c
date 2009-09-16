/* Simple bit twiddler test program for the STR912FAW44 ARM MCU */

// $Id$

#include <cpu.h>

int main(void)
{
  GPIO_InitTypeDef config;
  unsigned long int i;

  cpu_init(DEFAULT_CPU_FREQ);

  SCU_APBPeriphClockConfig(__GPIO6, ENABLE);	// Turn on GPIO6 clock
  SCU_APBPeriphReset(__GPIO6, DISABLE);		// Let GPIO6 out of reset
 
  GPIO_StructInit(&config);
  config.GPIO_Pin = GPIO_Pin_All;
  config.GPIO_Direction = GPIO_PinOutput;	// GPIO6 pins are all outputs
  config.GPIO_Type = GPIO_Type_PushPull;	// GPIO6 pins are all push pull outputs
  config.GPIO_Alternate = GPIO_OutputAlt1;	// GPIO6 pins are all GPIO outputs
  GPIO_Init(GPIO6, &config);

  for (i = 0;; i++)
    GPIO_Write(GPIO6, i);
}
