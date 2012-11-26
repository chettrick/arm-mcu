/* USB serial port encapsulation routines */

// $Id$

#ifndef __USB_SERIAL_H
#define __USB_SERIAL_H

#include <_ansi.h>

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

// Return TRUE if receive data is available

int usb_serial_rxready(unsigned subdevice);

// Return TRUE if transmitter is ready for another message

int usb_serial_txready(unsigned subdevice);

_END_STD_C
#endif
