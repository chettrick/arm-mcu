// Interrupt definitions for LPC2119

// $Id$

#ifndef LPC2119_INTERRUPT__H
#define LPC2119_INTERRUPT__H

// Interrupt sources

#define INT_WDT 	0	// Watchdog timer
#define INT_SW		1	// Software interrupt
#define INT_DBGCOMMRX	2	// Debug comm receive
#define INT_DBGCOMMTX	3	// Debug comm transmit
#define INT_TIMER0	4	// Timer 0
#define INT_TIMER1	5	// Timer 1
#define INT_UART0	6	// UART 0
#define INT_UART1	7	// UART 1
#define INT_PWM0	8	// PWM
#define INT_I2C		9	// IIC
#define INT_SPI		10	// SPI 0
#define INT_SPI0	10	// SPI 0
#define INT_SPI1	11	// SPI 1
#define INT_PLL		12	// PLL
#define INT_RTC		13	// Real time clock
#define INT_EINT0	14	// External int 0
#define INT_EINT1	15	// External int 1
#define INT_EINT2	16	// External int 2
#define INT_EINT3	17	// External int 3
#define INT_A2D		18	// A/D Convertor
#define INT_CANACCFILT	19	// CAN Acceptance Filter
#define INT_CAN1TX	20	// CAN 1 Tx
#define INT_CAN2TX	21	// CAN 2 Tx
#define INT_CAN3TX	22	// CAN 3 Tx
#define INT_CAN4TX	23	// CAN 4 Tx
#define INT_CAN1RX	26	// CAN 1 Rx
#define INT_CAN2RX	27	// CAN 2 Rx
#define INT_CAN3RX	28	// CAN 3 Rx
#define INT_CAN4RX	29	// CAN 4 Rx

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

#endif // LPC2119_INTERRUPT__H
