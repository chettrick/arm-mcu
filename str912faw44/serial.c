/******************************************************************************/
/*                                                                            */
/*        Simple serial port I/O routines for the STR91x ARM MCU              */
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

  errno = 0;

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
  int status;

  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
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

  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
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
  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return -1;
  }

  if (!(UARTS[port]->FR & 0x20))
    return 1;
  else
    return 0;
}

/* Send a buffer to the serial port */

int serial_write(unsigned port, char *buf, unsigned int count)
{
  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
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

int serial_rxready(unsigned port)
{
  errno = 0;

  if (port+1 > MAX_SERIAL_PORTS)
  {
    errno = ENODEV;
    return -1;
  }

  if (!(UARTS[port]->FR & 0x10))
    return 1;
  else
    return 0;
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
    *buf++ = UARTS[port]->DR;
    return 1;
  }

  return 0;
}
