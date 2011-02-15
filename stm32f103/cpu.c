/* Initialize CPU core */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

#define NVIC_CCR ((volatile unsigned long *)(0xE000ED14))

unsigned long int CPUFREQ;

void cpu_init(unsigned long int frequency)
{
  CPUFREQ = DEFAULT_CPU_FREQ;		// Not currently changeable
	
  *NVIC_CCR = *NVIC_CCR | 0x200;	/* Set STKALIGN in NVIC */

// Turn on crystal oscillator

  RCC_HSEConfig(RCC_HSE_ON);
  while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

// Configure flash timing

  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
  FLASH_SetLatency(FLASH_Latency_2);	// 2 wait states

// Configure clocks

  RCC_HCLKConfig(RCC_SYSCLK_Div1);	// HCLK = SYSCLK
  RCC_PCLK1Config(RCC_HCLK_Div2);	// PCLK1 = HCLK/2
  RCC_PCLK2Config(RCC_HCLK_Div1);	// PCLK2 = HCLK

// Configure PLL for 72 MHz

  RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); // 8 MHz * 9 = 72 MHz
  RCC_PLLCmd(ENABLE);
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

// Select PLL for SYSCLK source

  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  while(RCC_GetSYSCLKSource() != 0x08);
}
