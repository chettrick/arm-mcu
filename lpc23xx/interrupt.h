// Interrupt definitions for LPC23xx ARM MCU

// $Id$

#ifndef LPC23xx_INTERRUPT__H
#define LPC23xx_INTERRUPT__H

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

static inline unsigned GetCPSR(void)
{
  unsigned retval;
  asm volatile (" mrs %0, cpsr" : "=r" (retval) : );
  return retval;
}

// Write CPSR

static inline void PutCPSR(unsigned x)
{
  asm volatile (" msr cpsr, %0" : : "r" (x) );
}

// Define macros for disabling and enabling interrupts

#define FIQ	0x40
#define IRQ	0x80

#define DISABLE_INTERRUPTS(mask)	PutCPSR(GetCPSR() | mask)
#define ENABLE_INTERRUPTS(mask)		PutCPSR(GetCPSR() & ~mask)

#endif // LPC23xx_INTERRUPT__H
