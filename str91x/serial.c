/******************************************************************************/
/*                                                                            */
/*        Simple serial port I/O routines for the STR91x ARM MCU              */
/*                                                                            */
/******************************************************************************/

// $Id$

static const char revision[] = "$Id$";

#include <cpu.h>
#include <errno.h>
#include <string.h>

#define MAX_SERIAL_PORTS	3

static UART_TypeDef * const UARTS[MAX_SERIAL_PORTS] =
{
  (UART_TypeDef *) UART0_BASE,
  (UART_TypeDef *) UART1_BASE,
  (UART_TypeDef *) UART2_BASE
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
  else if (!strncasecmp(name, "com2:", 5))
    return 1;
  else if (!strncasecmp(name, "com3:", 5))
    return 2;
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
  GPIO_InitTypeDef config_pin;
  UART_InitTypeDef config_uart;

  errno_r = 0;

// Look up serial port number

  port = serial_name_to_port(name);
  if (port < 0) return port;

// Pass up port number, if requested

  if (subdevice != NULL)
    *subdevice = port;

// Extract baud rate from device name

  baudrate = lightweight_atoi(name+5);

/* We assume the UART pin configuration of the STR910-EVAL board: */

/*   UART0 RxD is P51 alt in  1 */
/*   UART0 TxD is P34 alt out 3 */
/*   UART1 RxD is P32 alt in  1 */
/*   UART1 TxD is P33 alt out 2 */
/*   UART2 RxD is P31 alt in  1 */
/*   UART2 TxD is P35 alt out 3 */

  switch (port)
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
      errno_r = ENODEV;
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

  if (!(UARTS[port]->FR & 0x20))
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
    UARTS[port]->DR = *buf++;
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

  if (!(UARTS[port]->FR & 0x10))
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
    *buf++ = UARTS[port]->DR;
    return 1;
  }

  return 0;
}
