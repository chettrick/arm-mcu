/******************************************************************************/
/*                                                                            */
/*          Simple serial port I/O routines for the LPC23xx ARM MCU           */
/*                                                                            */
/******************************************************************************/

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SERIAL_PORTS	4

/* Define relocatable UART register definitions */

static const unsigned long int UARTS[MAX_SERIAL_PORTS] =
{
  UART0_BASE_ADDR,
  UART1_BASE_ADDR,
  UART2_BASE_ADDR,
  UART3_BASE_ADDR,
};

#define UxRBR          (*(volatile unsigned long int *)(UARTS[port] + 0x00))
#define UxTHR          (*(volatile unsigned long int *)(UARTS[port] + 0x00))
#define UxDLL          (*(volatile unsigned long int *)(UARTS[port] + 0x00))
#define UxDLM          (*(volatile unsigned long int *)(UARTS[port] + 0x04))
#define UxIER          (*(volatile unsigned long int *)(UARTS[port] + 0x04))
#define UxIIR          (*(volatile unsigned long int *)(UARTS[port] + 0x08))
#define UxFCR          (*(volatile unsigned long int *)(UARTS[port] + 0x08))
#define UxLCR          (*(volatile unsigned long int *)(UARTS[port] + 0x0C))
#define UxMCR          (*(volatile unsigned long int *)(UARTS[port] + 0x10))
#define UxLSR          (*(volatile unsigned long int *)(UARTS[port] + 0x14))
#define UxMSR          (*(volatile unsigned long int *)(UARTS[port] + 0x18))
#define UxSCR          (*(volatile unsigned long int *)(UARTS[port] + 0x1C))
#define UxACR          (*(volatile unsigned long int *)(UARTS[port] + 0x20))
#define UxICR          (*(volatile unsigned long int *)(UARTS[port] + 0x24))
#define UxFDR          (*(volatile unsigned long int *)(UARTS[port] + 0x28))
#define UxTER          (*(volatile unsigned long int *)(UARTS[port] + 0x30))

/* Lightweight alternative to newlib atoi() */

static int lightweight_atoi(const char *s)
{
  int x = 0;

  while (*s)
  {
    char c = *s++;

    if ((c >= '0') && (c <= '9'))
      x = x*10 + c - '0';
    else
      break;
  }

  return x;
}

/* Map serial port device name to port number */

int serial_name_to_port(char *name)
{
  errno_r = 0;

  if (!strncasecmp(name, "com1:", 5))
    return 0;
  else if (!strncasecmp(name, "com2:", 5))
    return 1;
  else
  {
    errno_r = ENODEV;
    return -1;
  }
}

/* Initialize serial port */

int serial_open(char *name, unsigned int *subdevice)
{
  unsigned int port;
  unsigned int baudrate;
  unsigned short int divisor;

  errno_r = 0;

// Look up serial port number

  port = serial_name_to_port(name);
  if (port < 0) return port;

// Pass up port number, if requested

  if (subdevice != NULL)
    *subdevice = port;

// Extract baud rate from device name

  baudrate = lightweight_atoi(name+5);

  switch (port)
  {
    case 0 :
      PCONP |= (1 << 3);		// Power on UART 0
      PCLKSEL0 &= 0xFFFFFF3F;		// CCLK/4
      PINSEL0 &= 0xFFFFFF0F;		// Enable UART 0 I/O pins
      PINSEL0 |= 0x00000050;
      break;

    case 1 :
      PCONP |= (1 << 4);		// Power on UART 1
      PCLKSEL0 &= 0xFFFFFCFF;		// CCLK/4
      PINSEL0 &= 0x3FFFFFFF;		// Enable UART 1 I/O pins
      PINSEL0 |= 0x40000000;
      PINSEL1 &= 0xFFFFFFFC;
      PINSEL1 |= 0x00000001;
      break;

    case 2 :
      PCONP |= (1 << 24);		// Power on UART 2
      PCLKSEL1 &= 0xFFFCFFFF;		// CCLK/4
      PINSEL0 &= 0xFF0FFFFF;		// Enable UART 2 I/O pins
      PINSEL0 |= 0x00500000;
      break;

    case 3 :
      PCONP |= (1 << 25);		// Power on UART 3
      PCLKSEL1 &= 0xFFF3FFFF;		// CCLK/4
      PINSEL0 &= 0xFFFFFFF0;		// Enable UART 3 I/O pins
      PINSEL0 |= 0x0000000A;
      break;

    default :
      errno_r = ENODEV;			// Unrecognized UART base address
      return -1;			// Return an error
  }

// Configure the serial port

  divisor = SystemCoreClock/78/baudrate; // Calculate baud rate divisor

  UxFDR = 0x92;				// Set fractional divider=1 2/9
  UxLCR = 0x83;				// Enable access to DLL and DLM
  UxDLM = divisor / 256;		// Set baud rate
  UxDLL = divisor % 256;
  UxLCR = 0x03;				// Always 8 bits no parity 1 stop
  UxFCR = 0x07;				// Enable and clear FIFO's
  UxIER = 0x00;				// Disable UART interrupts
  UxACR = 0x00;				// Disable autobaud
  if (port == 3) UxICR = 0x00;		// Disable IRDA
  UxTER = 0x80;				// Enable transmitter

  return 0;
}

/* Register serial port for standard I/O */

int serial_stdio(char *name)
{
  unsigned int subdevice;

  if (serial_open(name, &subdevice))
    return -1;

  // Nuke existing stdin, stdout, stderr

  device_unregister(0);
  device_unregister(1);
  device_unregister(2);

  // Register new stdin, stdout, stderr

  device_register_char_fd(0, subdevice, NULL, serial_read, NULL, serial_rxready);
  device_register_char_fd(1, subdevice, serial_write, NULL, serial_txready, NULL);
  device_register_char_fd(2, subdevice, serial_write, NULL, serial_txready, NULL);

  return 0;
}

/* Register a serial port device */

int serial_register(char *name)
{
  unsigned int port;

// Look up serial port number

  port = serial_name_to_port(name);
  if (port < 0) return port;

  return device_register_char(name, port, serial_open, NULL, serial_write, serial_read, serial_txready, serial_rxready);
}

/* Return TRUE if transmitter is ready to accept data */

int serial_txready(unsigned int port)
{
  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (UxLSR & 0x20)
    return 1;
  else
    return 0;
}

/* Send a buffer to the serial port */

int serial_write(unsigned int port, char *buf, unsigned int count)
{
  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (serial_txready(port))
  {
    UxTHR = *buf++;
    return 1;
  }

  return 0;
}

/* Return TRUE if receive data is available */

int serial_rxready(unsigned int port)
{
  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (UxLSR & 0x01)
    return 1;
  else
    return 0;
}

/* Read buffer from the serial port */

int serial_read(unsigned int port, char *buf, unsigned int count)
{
  errno_r = 0;

  if (port >= MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  if (serial_rxready(port))
  {
    *buf++ = UxRBR;
    return 1;
  }

  return 0;
}
