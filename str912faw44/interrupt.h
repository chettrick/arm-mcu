// Interrupt definitions for STR912FA

// $Id: interrupt.h,v 1.1 2007-11-23 12:53:10 cvs Exp $

#ifndef STR912FA_INTERRUPT_H
#define STR912FA_INTERRUPT_H

// VIC0 (primary) interrupt sources

#define INT_WDT 	0	// Watchdog timer
#define INT_SW		1	// Software interrupt
#define INT_DBGCOMMRX	2	// Debug comm receive
#define INT_DBGCOMMTX	3	// Debug comm transmit
#define INT_TIMER0	4	// Timer 0
#define INT_TIMER1	5	// Timer 1
#define INT_TIMER2	6	// Timer 2
#define INT_TIMER3	7	// Timer 3
#define INT_USBHIGH	8	// USB high priority
#define INT_USBLOW	9	// USB low priority
#define INT_SCU		10	// System Control Unit
#define INT_ENET	11	// Ethernet
#define INT_DMA		12	// DMA controller
#define INT_CAN		13	// CAN controller
#define INT_MC		14	// Motor controller
#define INT_ADC		15	// Analog to Digital Converter

// VIC1 (cascade) interrupt sources
// Note: ISR must read VIC1_VAR!!!

#define INT_UART0	0	// UART 0
#define INT_UART1	1	// UART 1
#define INT_UART2	2	// UART 2
#define INT_I2C0	3	// I2C controller 0
#define INT_I2C1	4	// I2C controller 1
#define INT_SSP0	5	// Synchronous Serial Peripheral 0
#define INT_SSP1	6	// Synchronous Serial Peripheral 1
#define INT_LVD		7	// Low Voltage Detect (brownout)
#define INT_RTC		8	// Real Time Clock
#define INT_WIU		9	// Wakeup Interrupt Unit
#define INT_WIUGROUP0	10	// Wakeup Interrupt Unit Group 0
#define INT_WIUGROUP1	11	// Wakeup Interrupt Unit Group 1
#define INT_WIUGROUP2	12	// Wakeup Interrupt Unit Group 2
#define INT_WIUGROUP3	13	// Wakeup Interrupt Unit Group 3
#define INT_USBWAKE	14	// USB bus resume wakeup
#define INT_PFQBC	15	// Prefetch Queue and Branch Cache

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

#endif // STR912FA_INTERRUPT_H
