/******************************************************************************/
/*                                                                            */
/*          Simple serial port I/O routines for the LPC17xx ARM MCU           */
/*                                                                            */
/******************************************************************************/

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#undef errno
extern int errno;

#include <lpc17xx_pinsel.h>
#include <lpc17xx_uart.h>

static LPC_UART_TypeDef *UART_TABLE[] =
{
  (LPC_UART_TypeDef *) LPC_UART0,
  (LPC_UART_TypeDef *) LPC_UART1,
  (LPC_UART_TypeDef *) LPC_UART2,
  (LPC_UART_TypeDef *) LPC_UART3
};

/* Initialize serial console */

int serial_init(unsigned port, unsigned long int baudrate)
{
  PINSEL_CFG_Type pinconfig;
  UART_CFG_Type uartconfig;
  UART_FIFO_CFG_Type fifoconfig;

  errno = 0;

// Configure I/O pins

  switch (port)
  {
    case 0 :
      pinconfig.Funcnum = 1;
      pinconfig.OpenDrain = 0;
      pinconfig.Pinmode = 0;
      pinconfig.Pinnum = 2;
      pinconfig.Portnum = 0;
      PINSEL_ConfigPin(&pinconfig);
      pinconfig.Pinnum = 3;
      PINSEL_ConfigPin(&pinconfig);
      break;

    case 1 :
      pinconfig.Funcnum = 2;
      pinconfig.OpenDrain = 0;
      pinconfig.Pinmode = 0;
      pinconfig.Pinnum = 0;
      pinconfig.Portnum = 2;
      PINSEL_ConfigPin(&pinconfig);
      pinconfig.Pinnum = 1;
      PINSEL_ConfigPin(&pinconfig);
      break;

    default :
      errno = ENODEV;
      return -1;
  }

// Configure baud rate

  uartconfig.Baud_rate = baudrate;
  uartconfig.Parity = UART_PARITY_NONE;
  uartconfig.Databits = UART_DATABIT_8;
  uartconfig.Stopbits = UART_STOPBIT_1;
  UART_Init(UART_TABLE[port], &uartconfig);

// Configure FIFO

  UART_FIFOConfigStructInit(&fifoconfig);
  UART_FIFOConfig(UART_TABLE[port], &fifoconfig);

// Enable the UART transmitter

  UART_TxCmd(UART_TABLE[port], ENABLE);

  return 0;
}

/* Register serial port for standard I/O */

int serial_stdio(unsigned port, unsigned long int baudrate)
{
  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return -1;
  }

  serial_init(port, baudrate);

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

  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return -1;
  }

  status = serial_init(port, baudrate);
  if (status) return status;

  memset(name, 0, sizeof(name));
  sprintf(name, "com%d", port);

  device_register_char(name, port, (void *) baudrate,
   (device_init_t) serial_init, serial_write, serial_read, serial_txready, serial_rxready);

  return 0;
}

/* Return TRUE if transmitter is ready to accept data */

int serial_txready(unsigned port)
{
  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return -1;
  }

  if (UART_TABLE[port]->LSR & UART_LSR_THRE)
    return TRUE;
  else
    return FALSE;
}

/* Send a buffer to the serial port */

int serial_write(unsigned port, char *buf, unsigned int count)
{
  int n;

  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return -1;
  }

  for (n = 0; n < count; n++)
  {
    while (!serial_txready(port));
    UART_TABLE[port]->THR = *buf++;
  }

  return count;
}

/* Return TRUE if receive data is available */

int serial_rxready(unsigned port)
{
  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return 0;
  }

  if (UART_TABLE[port]->LSR & UART_LSR_RDR)
    return TRUE;
  else
    return FALSE;
}

/* Read buffer from the serial port */

int serial_read(unsigned port, char *buf, unsigned int count)
{
  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return -1;
  }

  if (serial_rxready(port))
  {
    *buf = UART_TABLE[port]->RBR;
    return 1;
  }
  else
    return 0;
}