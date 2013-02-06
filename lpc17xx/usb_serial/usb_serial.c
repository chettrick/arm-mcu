/* USB serial port library encapsulation routines */

// $Id$

// Copyright (C)2013, Philip Munts, President, Munts AM Corp.
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

#include <cpu.h>
#include <errno.h>

#include "usbSerial.h"
#include "usb_serial.h"

extern fifo_t txfifo;
extern fifo_t rxfifo;

// Initialize USB subsystem

int usb_serial_open(char *name, unsigned int *subdevice)
{
  return usbSerialInit();
}

// Register USB serial port device for standard I/O

int usb_serial_stdio(char *name)
{
  unsigned int subdevice;

  errno_r = 0;

  if (usb_serial_open(name, &subdevice))
    return -1;

  // Nuke existing stdin, stdout, stderr

  device_unregister(0);
  device_unregister(1);
  device_unregister(2);

  // Register new stdin, stdout, stderr

  device_register_char_fd(0, subdevice, NULL, usb_serial_read, NULL, usb_serial_rxready);
  device_register_char_fd(1, subdevice, usb_serial_write, NULL, usb_serial_txready, NULL);
  device_register_char_fd(2, subdevice, usb_serial_write, NULL, usb_serial_txready, NULL);

  return 0;
}

// Register USB serial port device

int usb_serial_register(char *name)
{
  return device_register_char(name, 0, usb_serial_open, NULL, usb_serial_write, usb_serial_read, usb_serial_txready, usb_serial_rxready);
}

// Return TRUE if USB system is ready to accept another transmit message

int usb_serial_txready(unsigned subdevice)
{
  return fifo_free(&txfifo);
}

// Return TRUE if USB subsystem has receive data available

int usb_serial_rxready(unsigned subdevice)
{
  return fifo_avail(&rxfifo);
}

// Send data to USB host

int usb_serial_write(unsigned subdevice, char *buf, unsigned int count)
{
  int room;
  int i;

  if (count == 0) return 0;

  room = fifo_free(&txfifo);
  if (room == 0) return 0;

  if (count > room)
    count = room;

  for (i = 0; i < count; i++)
    VCOM_putchar(*buf++);

  return count;
}

// Receive data from USB host

int usb_serial_read(unsigned subdevice, char *buf, unsigned int count)
{
  int avail;
  int i;

  if (count == 0) return 0;

  avail = fifo_avail(&rxfifo);
  if (avail == 0) return 0;

  if (count > avail)
    count = avail;

  for (i = 0; i < count; i++)
    *buf++ = VCOM_getchar();

  return count;
}
