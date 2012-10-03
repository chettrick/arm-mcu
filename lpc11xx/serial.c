/******************************************************************************/
/*                                                                            */
/*          Simple serial port I/O routines for the LPC11xx ARM MCU           */
/*                                                                            */
/******************************************************************************/

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <errno.h>
#include <string.h>

#define MAX_SERIAL_PORTS	1

static LPC_UART_TypeDef * const UARTS[MAX_SERIAL_PORTS] =
{
  (LPC_UART_TypeDef *) LPC_UART,
};

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
      LPC_IOCON->PIO1_6 = 0x00000031;		// RXD, pull-up, hysteresis
      LPC_IOCON->PIO1_7 = 0x00000001;		// TXD, push-pull output
      LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 12);	// Enable UART
      LPC_SYSCON->UARTCLKDIV = 4;		// CLK/4
      break;

    default :
      errno_r = ENODEV;
      return -1;
  }

// Configure the serial port

  divisor = SystemCoreClock/104/baudrate;	// Calculate baud rate divisor

  UARTS[port]->FDR = 0x85;			// Set fractional divider=1 5/8
  UARTS[port]->LCR = 0x83;			// Enable access to DLL and DLM
  UARTS[port]->DLM = divisor / 256;		// Set baud rate
  UARTS[port]->DLL = divisor % 256;
  UARTS[port]->LCR = 0x03;			// Always 8 bits no parity 1 stop
  UARTS[port]->FCR = 0x07;			// Enable and clear FIFO's
  UARTS[port]->IER = 0x00;			// Disable UART interrupts
  UARTS[port]->ACR = 0x00;			// Disable autobaud
  UARTS[port]->TER = 0x80;			// Enable transmitter

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

// Register the serial port driver

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

  if (UARTS[port]->LSR & 0x20)
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
    UARTS[port]->THR = *buf++;
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

  if (UARTS[port]->LSR & 0x01)
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
    *buf++ = UARTS[port]->RBR;
    return 1;
  }

  return 0;
}
