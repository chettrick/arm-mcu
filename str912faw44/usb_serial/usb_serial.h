/* USB serial port encapsulation routines */

// $Id: usb_serial.h,v 1.5 2008-07-10 20:34:00 cvs Exp $

#ifndef __USB_SERIAL_H
#define __USB_SERIAL_H

// Initialize USB subsystem

void usb_serial_init(void);

// Send data to USB host

int usb_serial_send(void *buf, int len);

// Receive data from USB host

int usb_serial_receive(void *buf, int bufsize);
#endif
