/* Simple bit twiddler test program */

// $Id: test_gpio.c,v 1.4 2008-06-26 18:38:58 cvs Exp $

#include <cpu.h>

void main(void)
{
  GPIO_InitTypeDef config;
  volatile unsigned long i;

// Initialize CPU core

  cpu_init(DEFAULT_CPU_FREQ);

// Enable peripheral clock

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);

// Configure PC.12 as output push-pull (LED)

  GPIO_StructInit(&config);
  config.GPIO_Pin =  GPIO_Pin_12;
  config.GPIO_Mode = GPIO_Mode_Out_PP;
  config.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &config);

  for (;;)
  {
    GPIO_SetBits(GPIOC, GPIO_Pin_12);
    for (i = 0; i < 500000; i++);

    GPIO_ResetBits(GPIOC, GPIO_Pin_12);
    for (i = 0; i < 500000; i++);
  }
}
