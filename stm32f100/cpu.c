/* Initialize CPU core */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
//#include <stm32f10x_rcc.h>

#define NVIC_CCR ((volatile unsigned long *)(0xE000ED14))

unsigned long int CPUFREQ;

void cpu_init(unsigned long int frequency)
{
  *NVIC_CCR = *NVIC_CCR | 0x200;	/* Set STKALIGN in NVIC */

// Turn on crystal oscillator

  RCC_HSEConfig(RCC_HSE_ON);
  while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

// Configure clocks

  RCC_HCLKConfig(RCC_SYSCLK_Div1);	// HCLK = SYSCLK
  RCC_PCLK1Config(RCC_HCLK_Div1);	// PCLK1 = HCLK
  RCC_PCLK2Config(RCC_HCLK_Div1);	// PCLK2 = HCLK

// Configure PLL for 24 MHz

  RCC_PREDIV1Config(RCC_PREDIV1_Source_HSE, RCC_PREDIV1_Div2);
  RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_6);
  RCC_PLLCmd(ENABLE);
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

// Select PLL for SYSCLK source

  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  while(RCC_GetSYSCLKSource() != 0x08);

  CPUFREQ = SystemCoreClock;		// Not currently changeable
}
