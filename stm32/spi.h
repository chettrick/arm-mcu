/* Simple SPI master routines for STM32 */

// $Id$

#include <stdint.h>

// STM32 SPI ports count from 1 (SPI1, SPI2)

#define MAX_SPI_PORTS		3

int spimaster_init(uint32_t port,
                   uint32_t clockmode,
                   uint32_t speed,
                   uint32_t wordsize,
                   uint32_t bigendian);
