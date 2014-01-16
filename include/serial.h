/******************************************************************************/
/*                                                                            */
/*                      Simple serial port I/O routines                       */
/*                                                                            */
/******************************************************************************/

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

#ifndef _SERIAL_H
#define _SERIAL_H

_BEGIN_STD_C

/* Map serial port name to port number (subdevice) */

int serial_name_to_port(char *name);

/* Initialize serial port */

int serial_open(char *name, unsigned int *subdevice);

/* Register serial port for standard I/O */

int serial_stdio(char *name);

/* Register a serial port device */

int serial_register(char *name);

/* Return true if transmitter is ready to accept data */

int serial_txready(unsigned int port);

/* Write data to the serial port */

int serial_write(unsigned int port, char *buf, unsigned int count);

/* Return true if receive data is available */

int serial_rxready(unsigned int port);

/* Read data from the serial port */

int serial_read(unsigned int port, char *buf, unsigned int count);

_END_STD_C
#endif
