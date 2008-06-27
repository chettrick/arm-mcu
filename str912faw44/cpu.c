/* Initialize CPU core */

// $Id: cpu.c,v 1.5 2008-06-27 00:10:12 cvs Exp $

#include <cpu.h>

unsigned long int CPUFREQ;

void cpu_init(unsigned long int frequency)
{
  CPUFREQ = DEFAULT_CPU_FREQ;			// Not currently changeable

// Configure for 96 MHz operation

  SCU_PLLFactorsConfig(192, 25, 1);		// PLL = ((25 MHz/25)*192)/2) = 96 MHz
  SCU_PLLCmd(ENABLE);
  SCU_RCLKDivisorConfig(SCU_RCLK_Div1);		// RCLK = PLL = 96 MHz
  SCU_HCLKDivisorConfig(SCU_HCLK_Div1);		// HCLK = PLL = 96 MHz
  SCU_FMICLKDivisorConfig(SCU_FMICLK_Div1);	// FMICLK = PLL = 96 MHz
  SCU_PCLKDivisorConfig(SCU_PCLK_Div2);		// PCLK = PLL/2 = 48 MHz
  SCU_MCLKSourceConfig(SCU_MCLK_PLL);		// MCLK = PLL = 96 MHz
}
