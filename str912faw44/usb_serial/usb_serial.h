/* USB serial port encapsulation routines */

// $Id$

#ifndef __USB_SERIAL_H
#define __USB_SERIAL_H

// Initialize USB subsystem

int usb_serial_init(unsigned subdevice, void *settings);

// Register USB serial port driver

int usb_serial_register(void);

// Use USB serial port for standard I/O

int usb_serial_stdio(void);

// Send data to USB host

int usb_serial_write(unsigned subdevice, char *buf, size_t count);

// Receive data from USB host

int usb_serial_read(unsigned subdevice, char *buf, size_t count);

// Return TRUE if receive data is available

int usb_serial_rxready(unsigned subdevice);

// Return TRUE if transmitter is ready for another message

int usb_serial_txready(unsigned subdevice);
#endif
