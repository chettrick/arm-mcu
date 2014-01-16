// Interrupt definitions for LPC23xx ARM MCU

// $Id$

// Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
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

#ifndef LPC23xx_INTERRUPT__H
#define LPC23xx_INTERRUPT__H

_BEGIN_STD_C

// Interrupt sources

#define INT_WDT		0	// Watchdog timer
#define INT_SW		1	// Software interrupt
#define INT_DBGCOMMRX	2	// Debug comm receive
#define INT_DBGCOMMTX	3	// Debug comm transmit
#define INT_TIMER0	4	// Timer 0
#define INT_TIMER1	5	// Timer 1
#define INT_UART0	6	// UART 0
#define INT_UART1	7	// UART 1
#define INT_PWM1	8	// PWM 1
#define INT_I2C0	9	// IIC 0
#define INT_SPI		10	// SPI
#define INT_SSP0	10	// SSP 0
#define INT_SSP1	11	// SSP 1
#define INT_PLL		12	// PLL
#define INT_RTC		13	// Real time clock
#define INT_EINT0	14	// External int 0
#define INT_EINT1	15	// External int 1
#define INT_EINT2	16	// External int 2
#define INT_EINT3	17	// External int 3
#define INT_A2D		18	// A/D Convertor
#define INT_I2C1	19	// IIC 1
#define INT_BOD		20	// Brown out detect
#define INT_ETHERNET	21	// Ethernet
#define INT_USB		22	// Universal Serial Bus
#define INT_CAN		23	// CAN common
#define INT_SDMMC	24	// SD/MMC interface
#define INT_DMA		25	// DMA controller
#define INT_TIMER2	26	// Timer 2
#define INT_TIMER3	27	// Timer 3
#define INT_UART2	28	// UART 2
#define INT_UART3	29	// UART 3
#define INT_I2C2	30	// IIC 2
#define INT_I2S		31	// I2S

#define VIC_SIZE	32

#define VECT_ADDR_INDEX	0x100
#define VECT_CNTL_INDEX	0x200

// Read CPSR

static inline unsigned int GetCPSR(void)
{
  unsigned int retval;
  asm volatile (" mrs %0, cpsr" : "=r" (retval) : );
  return retval;
}

// Write CPSR

static inline void PutCPSR(unsigned int x)
{
  asm volatile (" msr cpsr, %0" : : "r" (x) );
}

// Define macros for disabling and enabling interrupts

#define FIQ	0x40
#define IRQ	0x80

#define DISABLE_INTERRUPTS(mask)	PutCPSR(GetCPSR() | mask)
#define ENABLE_INTERRUPTS(mask)		PutCPSR(GetCPSR() & ~mask)

_END_STD_C
#endif // LPC23xx_INTERRUPT__H
