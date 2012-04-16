// Interrupt definitions for STR912FA

// $Id$

#ifndef STR912FA_INTERRUPT_H
#define STR912FA_INTERRUPT_H

#include <_ansi.h>

_BEGIN_STD_C

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
#endif // STR912FA_INTERRUPT_H
