/* USB serial port encapsulation routines */

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

#ifndef __USB_SERIAL_H
#define __USB_SERIAL_H

_BEGIN_STD_C

// Initialize USB subsystem

int usb_serial_open(char *name, unsigned int *subdevice);

// Register USB serial port driver

int usb_serial_register(char *name);

// Use USB serial port for standard I/O

int usb_serial_stdio(char *name);

// Send data to USB host

int usb_serial_write(unsigned subdevice, char *buf, unsigned int count);

// Receive data from USB host

int usb_serial_read(unsigned subdevice, char *buf, unsigned int count);

// Return true if receive data is available

int usb_serial_rxready(unsigned subdevice);

// Return true if transmitter is ready for another message

int usb_serial_txready(unsigned subdevice);

_END_STD_C
#endif
