/* Initialize CPU core */

// $Id$

// Copyright (C)2013, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification,are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// * Neither the name of Munts AM Corp. nor the names of its contributors may
//   be used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

static const char revision[] = "$Id$";

#include <cpu.h>

unsigned long int SystemCoreClock;

void cpu_init(unsigned long int frequency)
{

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

  SystemCoreClock = 48000000;
}

// Emulate Cortex-M3 system tick timer

_BEGIN_STD_C

__attribute__ ((weak)) void SysTick_Handler(void)	// Satisfy linker
{
}

__attribute__ ((__interrupt__)) void TIM1_IRQHandler(void)
{
  SysTick_Handler();

  TIM1->SR = 0x0000;		// Clear OCF1
  TIM1->CNTR = 0x0000;		// Reset counter
  VIC0->VAR = 0;		// Signal end of interrupt
}

unsigned long int SysTick_Config(unsigned long int ticks)
{
  TIM_InitTypeDef config_timer;

/* Configure VIC */

  SCU_AHBPeriphClockConfig(__VIC, ENABLE);	// Enable VIC clock
  SCU_AHBPeriphReset(__VIC, DISABLE);		// Let VIC out of reset

/* Configure timer 1 to interrupt 10 times a second */

  SCU_APBPeriphClockConfig(__TIM01, ENABLE);	// Turn on timer 1 clock
  SCU_APBPeriphReset(__TIM01, DISABLE);		// Let timer 1 out of reset

  TIM_StructInit(&config_timer);
  config_timer.TIM_Mode = TIM_OCM_CHANNEL_1;	// Select OC1 match
  config_timer.TIM_OC1_Modes = TIM_TIMING;	// Select OC1 timing mode
  config_timer.TIM_Clock_Source = TIM_CLK_APB;	// Select PCLK as source
  config_timer.TIM_Prescaler = 99;		// Select PCLK/100
  config_timer.TIM_Pulse_Length_1 = ticks/100;	// Configure period
  TIM_Init(TIM1, &config_timer);
  TIM_CounterCmd(TIM1, TIM_CLEAR);		// Clear the counter
  TIM_ITConfig(TIM1, TIM_IT_OC1, ENABLE);	// Enable OC1 interrupt
  TIM_CounterCmd(TIM1, TIM_START);		// Start the counter

/* Configure timer 1 interrupt */

  DISABLE_INTERRUPTS(IRQ);

  VIC_Config(TIM1_ITLine, VIC_IRQ, 0);		// Configure timer 1 interrupt
  VIC_ITCmd(TIM1_ITLine, ENABLE);		// Enable timer 1 interrupt

  ENABLE_INTERRUPTS(IRQ);

  return 0;
}

_END_STD_C
