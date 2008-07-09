/* USB serial port library encapsulation routines */

// $Id: usb_serial.c,v 1.2 2008-07-09 15:13:33 cvs Exp $

#include <string.h>

#include <91x_lib.h>

#include <usb_lib.h>
#include <usb_serial.h>

#include <str912faw44/interrupt.h>

// The following are defined in the USB library code from ST.COM

extern u32 count_out;
extern u8 buffer_out[];
extern void USB_Istr(void);
extern void CTR_HP(void);

// Connect or disconnect D+ pullup resistor

void USB_Cable_Config(FunctionalState NewState)
{
  if (NewState == ENABLE)
    GPIO_WriteBit(GPIO0, GPIO_Pin_1, Bit_RESET);
  else
    GPIO_WriteBit(GPIO0, GPIO_Pin_1, Bit_SET);
}

// Initialize USB subsystem

void usb_serial_init(void)
{
  GPIO_InitTypeDef config_gpio;
  
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

void usb_serial_send(void *src, int len)
{
  UserToPMABufferCopy(src, ENDP1_TXADDR, len);
  SetEPTxCount(ENDP1, len);
  SetEPTxValid(ENDP1);
}

// Receive data from USB host

int usb_serial_receive(void *dst, int dstsize)
{
  int len = 0;

  if (count_out)
  {
    len = count_out;
    memset(dst, 0, dstsize);
    memcpy(dst, buffer_out, count_out);
    count_out = 0;
  }

  return len;  
}

/* USB Low Priority Interrupt Service Routine */

__attribute__ ((__interrupt__)) void USBLP_IRQHandler(void)
{
  USB_Istr();
  VIC0->VAR = 0;
}
