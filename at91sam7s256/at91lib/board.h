// Minimal board.h for AT91SAM7S ARM MCU

// There is just barely enough here to compile at91lib

// $Id$

#ifndef __board_h
#define __board_h

#define at91sam7s256

// Include AT91SAM7S256 register definitions

#include <AT91SAM7S256.h>

// Define some constants necessary to compile at91lib

#define ADC_STARTUP_TIME_MAX		20
#define ADC_TRACK_HOLD_TIME_MIN		600

#endif
