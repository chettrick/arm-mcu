/* USB serial port library encapsulation routines */

// $Id: usb_serial.c,v 1.3 2008-07-09 18:57:40 cvs Exp $

#include <string.h>
#include <91x_lib.h>
#include <usb_lib.h>
#include <usb_serial.h>
#include <str912faw44/interrupt.h>

extern void USB_Istr(void);

#define RINGBUFFER_SIZE 256

static volatile bool txready = TRUE;

// Define a ring buffer data structure

typedef struct
{
  int head;
  int tail;
  int count;
  unsigned char data[RINGBUFFER_SIZE];
} ringbuffer_t;

static volatile ringbuffer_t rxbuf;

// Enqueue data into a ring buffer

static int ringbuffer_enqueue(unsigned char *src, ringbuffer_t *dst, int count)
{
  int result = 0;

  while ((dst->count < RINGBUFFER_SIZE) && count--)
  {
    dst->data[dst->tail++] = *src++;
    if (dst->tail == RINGBUFFER_SIZE) dst->tail = 0;
    dst->count++;
    result++;
  }

  return result;
}

// Dequeue data from a ring buffer

static int ringbuffer_dequeue(ringbuffer_t *src, unsigned char *dst, int count)
{
  int result = 0;

  while ((src->count > 0) && count--)
  {
    *dst++ = src->data[src->head++];
    if (src->head == RINGBUFFER_SIZE) src->head = 0;
    DISABLE_INTERRUPTS(IRQ);
    src->count--;
    ENABLE_INTERRUPTS(IRQ);
    result++;
  }

  return result;
}

// Initialize USB subsystem

void usb_serial_init(void)
{
  GPIO_InitTypeDef config_gpio;

// Initialize transmit done flag

  txready = TRUE;

// Initialize the receive ring buffer

  memset((void *) &rxbuf, 0, sizeof(ringbuffer_t));

// Enable VIC subsystem

  SCU_AHBPeriphClockConfig(__VIC,ENABLE);
  SCU_AHBPeriphReset(__VIC,DISABLE);

// Enable GPIO0 subsystem

  SCU_APBPeriphClockConfig(__GPIO0, ENABLE);
  SCU_APBPeriphReset(__GPIO0, DISABLE);

// Configure P0.1 to control USB D+ pullup resistor

  GPIO_DeInit(GPIO0);
  config_gpio.GPIO_Direction = GPIO_PinOutput;
  config_gpio.GPIO_Pin = GPIO_Pin_1;
  config_gpio.GPIO_Type = GPIO_Type_PushPull;
  config_gpio.GPIO_IPInputConnected = GPIO_IPInputConnected_Enable;
  config_gpio.GPIO_Alternate = GPIO_OutputAlt1;
  GPIO_Init(GPIO0, &config_gpio);

// Enable USB subsystem

  SCU_AHBPeriphClockConfig(__USB,ENABLE);
  SCU_AHBPeriphReset(__USB,DISABLE);
  SCU_AHBPeriphClockConfig(__USB48M,ENABLE);

// Configure USB interrupt

  DISABLE_INTERRUPTS(IRQ);

  VIC_Config(USBLP_ITLine, VIC_IRQ, 1);
  VIC_ITCmd(USBLP_ITLine, ENABLE);

  ENABLE_INTERRUPTS(IRQ);

// Initialize USB subsystem

  USB_Init();
}

// Send data to USB host

int usb_serial_send(void *src, int count)
{
  if (!txready) return 0;
  txready = FALSE;

  UserToPMABufferCopy(src, ENDP1_TXADDR, count);
  SetEPTxCount(ENDP1, count);
  SetEPTxValid(ENDP1);

  return count;
}

// Receive data from USB host

int usb_serial_receive(void *dst, int count)
{
  return ringbuffer_dequeue((ringbuffer_t *) &rxbuf, dst, count);
}

// Connect or disconnect D+ pullup resistor

void USB_Cable_Config(FunctionalState NewState)
{
  if (NewState == ENABLE)
    GPIO_WriteBit(GPIO0, GPIO_Pin_1, Bit_RESET);
  else
    GPIO_WriteBit(GPIO0, GPIO_Pin_1, Bit_SET);
}

// USB Low Priority Interrupt Service Routine

__attribute__ ((__interrupt__)) void USBLP_IRQHandler(void)
{
  USB_Istr();		// Call USB ISR
  VIC0->VAR = 0;	// End of interrupt
}

// This function is called from the USB ISR when data has been received from the USB host

void EP3_OUT_Callback(void)
{
  ringbuffer_enqueue((unsigned char *) (PMAAddr + ENDP3_RXADDR), (ringbuffer_t *) &rxbuf, GetEPRxCount(ENDP3));
  SetEPRxValid(ENDP3);
}

// This function is called from the USB ISR when data has been sent to the USB host

void EP1_IN_Callback(void)
{
  txready = TRUE;
}
