/* Simple SPI master routines for STM32 */

// $Id$

#include <stdint.h>

// STM32 SPI ports count from 1 (SPI1, SPI2)

#define MAX_SPI_PORTS		3

#define SPI_BIGENDIAN		1
#define SPI_LITTLEENDIAN	0

// Initialize SPI port for bidirection master mode

int spimaster_init(uint32_t port,
                   uint32_t clockmode,
                   uint32_t speed,
                   uint32_t bigendian);

// Transmit command and/or receive result in bidirectional master mode

int spimaster_transfer(uint32_t port,
                       uint8_t *txbuf,
                       uint32_t txcount,
                       uint8_t *rxbuf,
                       uint32_t rxcount);
