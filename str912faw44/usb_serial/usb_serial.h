/* USB serial port encapsulation routines */

// $Id: usb_serial.h,v 1.1 2008-07-08 23:04:35 cvs Exp $

// Initialize USB subsystem

void usb_serial_init(void);

// Send data to USB host

void usb_serial_send(void *buf, int len);

// Receive data from USB host

int usb_serial_receive(void *buf, int bufsize);
