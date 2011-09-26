/******************************************************************************/
/*                                                                            */
/*          Simple serial port I/O routines for the LPC23xx ARM MCU           */
/*                                                                            */
/******************************************************************************/

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_SERIAL_PORTS	4

/* Define relocatable UART register definitions */

static const unsigned long int UARTS[MAX_SERIAL_PORTS] =
{
  UART0_BASE_ADDR,
  UART1_BASE_ADDR,
  UART2_BASE_ADDR,
  UART3_BASE_ADDR,
};

#define UxRBR          (*(volatile unsigned long *)(UARTS[port] + 0x00))
#define UxTHR          (*(volatile unsigned long *)(UARTS[port] + 0x00))
#define UxDLL          (*(volatile unsigned long *)(UARTS[port] + 0x00))
#define UxDLM          (*(volatile unsigned long *)(UARTS[port] + 0x04))
#define UxIER          (*(volatile unsigned long *)(UARTS[port] + 0x04))
#define UxIIR          (*(volatile unsigned long *)(UARTS[port] + 0x08))
#define UxFCR          (*(volatile unsigned long *)(UARTS[port] + 0x08))
#define UxLCR          (*(volatile unsigned long *)(UARTS[port] + 0x0C))
#define UxMCR          (*(volatile unsigned long *)(UARTS[port] + 0x10))
#define UxLSR          (*(volatile unsigned long *)(UARTS[port] + 0x14))
#define UxMSR          (*(volatile unsigned long *)(UARTS[port] + 0x18))
#define UxSCR          (*(volatile unsigned long *)(UARTS[port] + 0x1C))
#define UxACR          (*(volatile unsigned long *)(UARTS[port] + 0x20))
#define UxICR          (*(volatile unsigned long *)(UARTS[port] + 0x24))
#define UxFDR          (*(volatile unsigned long *)(UARTS[port] + 0x28))
#define UxTER          (*(volatile unsigned long *)(UARTS[port] + 0x30))

/* Initialize serial console */

int serial_init(unsigned port, unsigned long int baudrate)
{
  unsigned short int b;

  errno_r = 0;

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

    default :				// Unrecognized UART base address
      errno_r = ENODEV;
      return -1;			// Do nothing
  }

  UxFDR = 0x49;				// Set fractional divider

  b = CPUFREQ/208/baudrate;

  UxLCR = 0x03;				// Enable access to IER
  UxIER = 0x00;				// Disable UART interrupts
  UxLCR = 0x83;				// Enable access to DLL and DLM
  UxDLM = b / 256;
  UxDLL = b % 256;
  UxLCR = 0x03;				// Always 8 bits no parity 1 stop
  UxFCR = 0x07;				// Enable and clear FIFO's
  UxACR = 0x00;				// Disable autobaud
  if (port == 3) UxICR = 0x00;		// Disable IRDA
  UxTER = 0x80;				// Enable transmitter

  return 0;
}

/* Register serial port for standard I/O */

int serial_stdio(unsigned port, unsigned long int baudrate)
{
  int status;

  errno_r = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  status = serial_init(port, baudrate);
  if (status) return status;

  device_register_char_fd(NULL, 0, port, (void *) baudrate, (device_init_t) serial_init, NULL, serial_read, NULL, serial_rxready);
  device_register_char_fd(NULL, 1, port, (void *) baudrate, (device_init_t) serial_init, serial_write, NULL, serial_txready, NULL);
  device_register_char_fd(NULL, 2, port, (void *) baudrate, (device_init_t) serial_init, serial_write, NULL, serial_txready, NULL);

  return 0;
}

/* Register a serial port device */

int serial_register(unsigned port, unsigned long int baudrate)
{
  int status;
  char name[DEVICE_NAME_SIZE];

  errno_r = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno_r = ENODEV;
    return -1;
  }

  status = serial_init(port, baudrate);
  if (status) return status;

  memset(name, 0, sizeof(name));
  siprintf(name, "com%d", port);

  device_register_char(name, port, (void *) baudrate,
   (device_init_t) serial_init, serial_write, serial_read, serial_txready, serial_rxready);

  return 0;
}

/* Return TRUE if transmitter is ready to accept data */

int serial_txready(unsigned port)
{
  errno_r = 0;

  if (port+1 > MAX_SERIAL_PORTS)
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

int serial_write(unsigned port, char *buf, unsigned int count)
{
  errno_r = 0;

  if (port+1 > MAX_SERIAL_PORTS)
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

int serial_rxready(unsigned port)
{
  errno_r = 0;

  if (port+1 > MAX_SERIAL_PORTS)
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

int serial_read(unsigned port, char *buf, unsigned int count)
{
  errno_r = 0;

  if (port+1 > MAX_SERIAL_PORTS)
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
