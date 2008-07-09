/* USB serial port encapsulation routines */

// $Id: usb_serial.h,v 1.3 2008-07-09 18:57:13 cvs Exp $

// Connect or disconnect D+ pullup resistor

void USB_Cable_Config(FunctionalState NewState);

// Initialize USB subsystem

void usb_serial_init(void);

// Send data to USB host

int usb_serial_send(void *buf, int len);

// Receive data from USB host

int usb_serial_receive(void *buf, int bufsize);
