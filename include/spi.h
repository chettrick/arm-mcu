/* Simple SPI master routines */

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

#ifndef _SPI_H
#define _SPI_H

_BEGIN_STD_C

#define SPI_MSBFIRST		1
#define SPI_LSBFIRST		0

// Initialize SPI port for bidirectional master mode

int spi_master_init(uint32_t port,
                    uint32_t wordsize,
                    uint32_t clockmode,
                    uint32_t speed,
                    uint32_t bitorder);

// Initialize SPI port for bidirectional slave mode

int spi_slave_init(uint32_t port,
                   uint32_t wordsize,
                   uint32_t clockmode,
                   uint32_t bitorder);

// Transmit command and/or receive result in bidirectional master mode

int spi_master_transfer(uint32_t port,
                        uint8_t *txbuf,
                        uint32_t txcount,
                        uint8_t *rxbuf,
                        uint32_t rxcount);

_END_STD_C
#endif
