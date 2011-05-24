/* Simple bit twiddler test program for the STR912FAW44 ARM MCU */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

int main(void)
{
  cpu_init(DEFAULT_CPU_FREQ);

#ifdef BOARD_STMICRO_STR910_EVAL
  GPIO_InitTypeDef config;
  unsigned long int i;

  SCU_APBPeriphClockConfig(__GPIO9, ENABLE);	// Turn on GPIO9 clock
  SCU_APBPeriphReset(__GPIO9, DISABLE);		// Let GPIO9 out of reset
 
  GPIO_StructInit(&config);
  config.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  config.GPIO_Direction = GPIO_PinOutput;	// LED pins are outputs
  config.GPIO_Type = GPIO_Type_PushPull;	// LED pins are push pull outputs
  config.GPIO_Alternate = GPIO_OutputAlt1;	// LED pins are GPIO outputs
  GPIO_Init(GPIO9, &config);

  for (i = 0;; i++)
    GPIO_Write(GPIO9, ~(i >> 18));
#endif
}
