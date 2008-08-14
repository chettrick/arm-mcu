/******************************************************************************/
/*                                                                            */
/*        Simple serial port I/O routines for the STR912FAW44 ARM MCU         */
/*                                                                            */
/******************************************************************************/

// $Id: serial.c,v 1.1 2008-08-14 20:08:18 cvs Exp $

#include <cpu.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#undef errno
extern int errno;

static UART_TypeDef *UARTS[MAX_SERIAL_PORTS] =
{
  (UART_TypeDef *) UART0_BASE,
  (UART_TypeDef *) UART1_BASE,
  (UART_TypeDef *) UART2_BASE
};

/* Initialize serial port */

int serial_init(unsigned port, unsigned long int baudrate)
{
  GPIO_InitTypeDef config_pin;
  UART_InitTypeDef config_uart;

/* We assume the UART pin configuration of the STR910-EVAL board: */

/*   UART0 RxD is P51 alt in  1 */
/*   UART0 TxD is P34 alt out 3 */
/*   UART1 RxD is P32 alt in  1 */
/*   UART1 TxD is P33 alt out 2 */
/*   UART2 RxD is P31 alt in  1 */
/*   UART2 TxD is P35 alt out 3 */

  switch(port)
  {
    case 0:

// Turn on UART clock

      SCU_APBPeriphClockConfig(__UART0, ENABLE);

// Let UART out of reset

      SCU_APBPeriphReset(__UART0, DISABLE);

// Disable IRDA mode

      SCU_UARTIrDASelect(SCU_UART0, SCU_UARTMode_UART);

// Turn on GPIO clock

      SCU_APBPeriphClockConfig(__GPIO3, ENABLE);
      SCU_APBPeriphClockConfig(__GPIO5, ENABLE);

// Let GPIO out of reset

      SCU_APBPeriphReset(__GPIO3, DISABLE);
      SCU_APBPeriphReset(__GPIO5, DISABLE);

// Configure RxD on P51 alt in 1

      GPIO_StructInit(&config_pin);
      config_pin.GPIO_Pin = GPIO_Pin_1;
      config_pin.GPIO_Direction = GPIO_PinInput;
      config_pin.GPIO_Type = GPIO_Type_PushPull;
      config_pin.GPIO_IPInputConnected = GPIO_IPInputConnected_Enable;
      config_pin.GPIO_Alternate = GPIO_InputAlt1;
      GPIO_Init(GPIO5, &config_pin);

// Configure TxD on P34 alt out 3

      GPIO_StructInit(&config_pin);
      config_pin.GPIO_Pin = GPIO_Pin_4;
      config_pin.GPIO_Direction = GPIO_PinOutput;
      config_pin.GPIO_Type = GPIO_Type_PushPull;
      config_pin.GPIO_Alternate = GPIO_OutputAlt3;
      GPIO_Init(GPIO3, &config_pin);
      break;

    case 1:

// Turn on UART clock

      SCU_APBPeriphClockConfig(__UART1, ENABLE);

// Let UART out of reset

      SCU_APBPeriphReset(__UART1, DISABLE);

// Disable IRDA mode

      SCU_UARTIrDASelect(SCU_UART1, SCU_UARTMode_UART);

// Turn on GPIO clock

      SCU_APBPeriphClockConfig(__GPIO3, ENABLE);

// Let GPIO out of reset

      SCU_APBPeriphReset(__GPIO3, DISABLE);

// Configure RxD on P32 alt in 1

      GPIO_StructInit(&config_pin);
      config_pin.GPIO_Pin = GPIO_Pin_2;
      config_pin.GPIO_Direction = GPIO_PinInput;
      config_pin.GPIO_Type = GPIO_Type_PushPull;
      config_pin.GPIO_IPInputConnected = GPIO_IPInputConnected_Enable;
      config_pin.GPIO_Alternate = GPIO_InputAlt1;
      GPIO_Init(GPIO3, &config_pin);

// Configure TxD on P33 alt out 2

      GPIO_StructInit(&config_pin);
      config_pin.GPIO_Pin = GPIO_Pin_3;
      config_pin.GPIO_Direction = GPIO_PinOutput;
      config_pin.GPIO_Type = GPIO_Type_PushPull;
      config_pin.GPIO_Alternate = GPIO_OutputAlt2;
      GPIO_Init(GPIO3, &config_pin);
      break;

    case 2:

// Turn on UART clock

      SCU_APBPeriphClockConfig(__UART2, ENABLE);

// Let UART out of reset

      SCU_APBPeriphReset(__UART2, DISABLE);

// Disable IRDA mode

      SCU_UARTIrDASelect(SCU_UART2, SCU_UARTMode_UART);

// Turn on GPIO clock

      SCU_APBPeriphClockConfig(__GPIO3, ENABLE);

// Let GPIO out of reset

      SCU_APBPeriphReset(__GPIO3, DISABLE);

// Configure RxD on P31 alt in 1

      GPIO_StructInit(&config_pin);
      config_pin.GPIO_Pin = GPIO_Pin_1;
      config_pin.GPIO_Direction = GPIO_PinInput;
      config_pin.GPIO_Type = GPIO_Type_PushPull;
      config_pin.GPIO_IPInputConnected = GPIO_IPInputConnected_Enable;
      config_pin.GPIO_Alternate = GPIO_InputAlt1;
      GPIO_Init(GPIO3, &config_pin);

// Configure TxD on P35 alt out 3

      GPIO_StructInit(&config_pin);
      config_pin.GPIO_Pin = GPIO_Pin_5;
      config_pin.GPIO_Direction = GPIO_PinOutput;
      config_pin.GPIO_Type = GPIO_Type_PushPull;
      config_pin.GPIO_Alternate = GPIO_OutputAlt3;
      GPIO_Init(GPIO3, &config_pin);
      break;

    default :
      errno = ENODEV;
      return -1;
  }

// Reset UART

  UART_DeInit(UARTS[port]);

// Configure UART

  UART_StructInit(&config_uart);
  config_uart.UART_WordLength = UART_WordLength_8D;
  config_uart.UART_StopBits = UART_StopBits_1;
  config_uart.UART_Parity = UART_Parity_No;
  config_uart.UART_BaudRate = baudrate;
  config_uart.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
  config_uart.UART_Mode = UART_Mode_Tx_Rx;
  config_uart.UART_FIFO = UART_FIFO_Enable;
  config_uart.UART_TxFIFOLevel = UART_FIFOLevel_1_2;
  config_uart.UART_RxFIFOLevel = UART_FIFOLevel_1_2;
  UART_Init(UARTS[port], &config_uart);

// Enable UART

  UART_Cmd(UARTS[port], ENABLE);
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
  return !(UARTS[port]->FR & 0x20);
}

/* Send 1 byte to the serial port */

static void serial_putch(unsigned port, char c)
{
  if (c == '\n') serial_putch(port, '\r');	// Insert CR before LF

  while (!serial_txready(port));
  UARTS[port]->DR = c;
}

/* Send a buffer to the serial port */

int serial_write(unsigned port, char *buf, size_t count)
{
  int n;

  for (n = 0; n < count; n++)
    serial_putch(port, *buf++);

  return count;
}

/* Return TRUE if receive data is available */

int serial_rxready(unsigned port)
{
  return !(UARTS[port]->FR & 0x10);
}

/* Read buffer from the serial port */

int serial_read(unsigned port, char *buf, size_t count)
{
  if (serial_rxready(port))
  {
    *buf = UARTS[port]->DR;
    return 1;
  }
  else
    return 0;
}
