/* Initialize CPU core */

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>

unsigned long int CPUFREQ;

void cpu_init(unsigned long int frequency)
{
  __use_custom_syscalls();

// Switch MCLK to oscillator input while we reprogram the PLL

  SCU_MCLKSourceConfig(SCU_MCLK_OSC);		// MCLK = OSC

// Configure PLL for 48 MHz operation

  SCU_PLLCmd(DISABLE);
  SCU_PLLFactorsConfig(192, 25, 3);		// PLL = ((25 MHz/25)*2*192)/8) = 48 MHz
  SCU_PLLCmd(ENABLE);

// Switch MCLK to PLL

  SCU_MCLKSourceConfig(SCU_MCLK_PLL);		// MCLK = PLL = 48 MHz

// Configure various subordinate clock dividers

  SCU_BRCLKDivisorConfig(SCU_BRCLK_Div1);	// BRCLK = MCLK = 48 MHz
  SCU_RCLKDivisorConfig(SCU_RCLK_Div1);		// RCLK = MCLK = 48 MHz
  SCU_USBCLKConfig(SCU_USBCLK_MCLK);		// USBCLK = MCLK = 48 MHz

  SCU_FMICLKDivisorConfig(SCU_FMICLK_Div1);	// FMICLK = RCLK = 48 MHz
  SCU_HCLKDivisorConfig(SCU_HCLK_Div1);		// HCLK = RCLK = 48 MHz
  SCU_PCLKDivisorConfig(SCU_PCLK_Div1);		// PCLK = RCLK = 48 MHz

  CPUFREQ = 48000000;
}
