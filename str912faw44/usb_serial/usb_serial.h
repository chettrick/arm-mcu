/* USB serial port encapsulation routines */

// $Id: usb_serial.h,v 1.2 2008-07-09 15:13:33 cvs Exp $

// Connect or disconnect D+ pullup resistor

void USB_Cable_Config(FunctionalState NewState);

// Initialize USB subsystem

void usb_serial_init(void);

// Send data to USB host

void usb_serial_send(void *buf, int len);

// Receive data from USB host

int usb_serial_receive(void *buf, int bufsize);
