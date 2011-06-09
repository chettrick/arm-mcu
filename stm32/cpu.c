/* Initialize CPU core */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

#define NVIC_CCR ((volatile unsigned long *)(0xE000ED14))

unsigned long int CPUFREQ;

void cpu_init(unsigned long int frequency)
{
  *NVIC_CCR = *NVIC_CCR | 0x200;	/* Set STKALIGN in NVIC */

// Interrupt vectors are in flash

  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

// Turn on crystal oscillator

  RCC_HSEConfig(RCC_HSE_ON);
  while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

// Configure flash timing

#ifdef MCU_stm32f103rb
  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
  FLASH_SetLatency(FLASH_Latency_2);	// 2 wait states
#endif

// Configure subsystem clock dividers

#ifdef MCU_stm32f100rb
  RCC_HCLKConfig(RCC_SYSCLK_Div1);	// HCLK = SYSCLK
  RCC_PCLK1Config(RCC_HCLK_Div1);	// PCLK1 = HCLK
  RCC_PCLK2Config(RCC_HCLK_Div1);	// PCLK2 = HCLK
#endif

#ifdef MCU_stm32f103rb
  RCC_HCLKConfig(RCC_SYSCLK_Div1);	// HCLK = SYSCLK
  RCC_PCLK1Config(RCC_HCLK_Div2);	// PCLK1 = HCLK/2
  RCC_PCLK2Config(RCC_HCLK_Div1);	// PCLK2 = HCLK
#endif

#ifdef MCU_stm32f100rb
// Configure PLL for 24 MHz

  RCC_PREDIV1Config(RCC_PREDIV1_Source_HSE, RCC_PREDIV1_Div2);
  RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_6);
#endif

#ifdef MCU_stm32f103rb
// Configure PLL for 72 MHz

  RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); // 8 MHz * 9 = 72 MHz
#endif

  RCC_PLLCmd(ENABLE);
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

// Select PLL for SYSCLK source

  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  while(RCC_GetSYSCLKSource() != 0x08);

  CPUFREQ = SystemCoreClock;		// Not currently changeable
}
