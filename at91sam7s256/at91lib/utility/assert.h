// Minimal utility/assert.h for AT91SAM7S256 ARM MCU

// Provide dummy ASSERT and SANITY_CHECK macros to allow compiling at91lib

// $Id$

#ifndef __assert_h
#define __assert_h

#include <assert.h>

#define ASSERT(condition, ...)  assert(condition)

#define SANITY_CHECK(...)

#endif
