/******************************************************************************/
/*                                                                            */
/*          Simple serial port I/O routines for the LPC2366 ARM MCU           */
/*                                                                            */
/******************************************************************************/

// $Id$

#include <cpu.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#undef errno
extern int errno;

/* Define relocatable UART register definitions */

static unsigned long int UARTBASE = UART0_BASE_ADDR;

#define UxRBR          (*(volatile unsigned long *)(UARTBASE + 0x00))
#define UxTHR          (*(volatile unsigned long *)(UARTBASE + 0x00))
#define UxDLL          (*(volatile unsigned long *)(UARTBASE + 0x00))
#define UxDLM          (*(volatile unsigned long *)(UARTBASE + 0x04))
#define UxIER          (*(volatile unsigned long *)(UARTBASE + 0x04))
#define UxIIR          (*(volatile unsigned long *)(UARTBASE + 0x08))
#define UxFCR          (*(volatile unsigned long *)(UARTBASE + 0x08))
#define UxLCR          (*(volatile unsigned long *)(UARTBASE + 0x0C))
#define UxMCR          (*(volatile unsigned long *)(UARTBASE + 0x10))
#define UxLSR          (*(volatile unsigned long *)(UARTBASE + 0x14))
#define UxMSR          (*(volatile unsigned long *)(UARTBASE + 0x18))
#define UxSCR          (*(volatile unsigned long *)(UARTBASE + 0x1C))
#define UxACR          (*(volatile unsigned long *)(UARTBASE + 0x20))
#define UxICR          (*(volatile unsigned long *)(UARTBASE + 0x24))
#define UxFDR          (*(volatile unsigned long *)(UARTBASE + 0x28))
#define UxTER          (*(volatile unsigned long *)(UARTBASE + 0x30))

/* Initialize serial console */

int serial_init(unsigned port, unsigned long int baudrate)
{
  unsigned short int b;

  errno = 0;

  switch (port)
  {
    case 0 :
      UARTBASE = UART0_BASE_ADDR;
      PINSEL0 &= 0xFFFFFF0F;		// Enable UART 0 I/O pins
      PINSEL0 |= 0x00000050;
      break;

    case 1 :
      UARTBASE = UART1_BASE_ADDR;
      PINSEL0 &= 0x3FFFFFFF;		// Enable UART 1 I/O pins
      PINSEL0 |= 0x40000000;
      PINSEL1 &= 0xFFFFFFFC;
      PINSEL1 |= 0x00000001;
      break;

    case 2 :
      UARTBASE = UART2_BASE_ADDR;
      PINSEL0 &= 0xFF0FFFFF;		// Enable UART 2 I/O pins
      PINSEL0 |= 0x00500000;
      break;

    case 3 :
      UARTBASE = UART3_BASE_ADDR;
      PINSEL0 &= 0xFFFFFFF0;		// Enable UART 3 I/O pins
      PINSEL0 |= 0x0000000A;
      break;

    default :				// Unrecognized UART base address
      errno = ENODEV;
      return -1;			// Do nothing
  }

  UxFDR = 0x49;				// Scale peripheral clock by 4/13

  b = CPUFREQ/208/baudrate;

  UxIER = 0x00;				// Disable UART interrupts
  UxLCR = 0x80;
  UxDLM = b / 256;
  UxDLL = b % 256;
  UxLCR = 0x03;				// Always 8 bits no parity 1 stop
  UxFCR = 0x01;				// Enable FIFO's

  return 0;
}

/* Register serial port for standard I/O */

int serial_stdio(unsigned port, unsigned long int baudrate)
{
  serial_init(port, baudrate);

  device_unregister("stdin");
  device_unregister("stdout");
  device_unregister("stderr");

  device_register_fd("stdin",  0, port, (void *) baudrate, (device_init_t) serial_init,
                     serial_write, serial_read, serial_txready, serial_rxready);

  device_register_fd("stdout", 1, port, (void *) baudrate, (device_init_t) serial_init,
                     serial_write, serial_read, serial_txready, serial_rxready);

  device_register_fd("stderr", 2, port, (void *) baudrate, (device_init_t) serial_init,
                     serial_write, serial_read, serial_txready, serial_rxready);

  return 0;
}

/* Return TRUE if transmitter is ready to accept data */

int serial_txready(unsigned port)
{
  return UxLSR & 0x20;
}

/* Send 1 byte to the serial port */

static void serial_putch(unsigned port, char c)
{
  while (!serial_txready(port));
  UxTHR = c;
}

/* Send a buffer to the serial port */

int serial_write(unsigned port, char *buf, unsigned int count)
{
  int n;

  for (n = 0; n < count; n++)
    serial_putch(port, *buf++);

  return count;
}

/* Return TRUE if receive data is available */

int serial_rxready(unsigned port)
{
  return UxLSR & 0x01;
}

/* Read buffer from the serial port */

int serial_read(unsigned port, char *buf, unsigned int count)
{
  if (serial_rxready(port))
  {
    *buf = UxRBR;
    return 1;
  }
  else
    return 0;
}
