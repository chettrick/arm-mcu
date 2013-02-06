/* USB serial port library encapsulation routines */

// $Id$

// Copyright (C)2013, Philip Munts, President, Munts AM Corp.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <cpu.h>
#include <errno.h>

#include <usb_serial.h>
#include <usb_core.h>
#include <usbd_core.h>
#include <usbd_usr.h>
#include <usbd_desc.h>
#include <usbd_cdc_core.h>
#include <usbd_cdc_vcp.h>

// Misnamed receive buffer pointers follow
extern uint32_t APP_tx_ptr_head;
extern uint32_t APP_tx_ptr_tail;

extern uint32_t USBD_OTG_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);

#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED
extern uint32_t USBD_OTG_EP1IN_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);
extern uint32_t USBD_OTG_EP1OUT_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);
#endif

static USB_OTG_CORE_HANDLE USB_OTG_dev;

#ifdef USE_USB_OTG_FS
void OTG_FS_WKUP_IRQHandler(void)
{
  if(USB_OTG_dev.cfg.low_power)
  {
    *(uint32_t *)(0xE000ED10) &= 0xFFFFFFF9 ;
    SystemInit();
    USB_OTG_UngateClock(&USB_OTG_dev);
  }
  EXTI_ClearITPendingBit(EXTI_Line18);
}
#endif

/**
  * @brief  This function handles EXTI15_10_IRQ Handler.
  * @param  None
  * @retval None
  */
#ifdef USE_USB_OTG_HS
void OTG_HS_WKUP_IRQHandler(void)
{
  if(USB_OTG_dev.cfg.low_power)
  {
    *(uint32_t *)(0xE000ED10) &= 0xFFFFFFF9 ;
    SystemInit();
    USB_OTG_UngateClock(&USB_OTG_dev);
  }
  EXTI_ClearITPendingBit(EXTI_Line20);
}
#endif

/**
  * @brief  This function handles OTG_HS Handler.
  * @param  None
  * @retval None
  */
#ifdef USE_USB_OTG_HS
void OTG_HS_IRQHandler(void)
#else
void OTG_FS_IRQHandler(void)
#endif
{
  USBD_OTG_ISR_Handler (&USB_OTG_dev);
}

#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED
/**
  * @brief  This function handles EP1_IN Handler.
  * @param  None
  * @retval None
  */
void OTG_HS_EP1_IN_IRQHandler(void)
{
  USBD_OTG_EP1IN_ISR_Handler (&USB_OTG_dev);
}

/**
  * @brief  This function handles EP1_OUT Handler.
  * @param  None
  * @retval None
  */
void OTG_HS_EP1_OUT_IRQHandler(void)
{
  USBD_OTG_EP1OUT_ISR_Handler (&USB_OTG_dev);
}
#endif

// Initialize USB subsystem

int usb_serial_open(char *name, unsigned int *subdevice)
{
  errno_r = 0;
  USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb);
  return 0;
}

// Register USB serial port device for standard I/O

int usb_serial_stdio(char *name)
{
  unsigned int subdevice;

  errno_r = 0;

  if (usb_serial_open(name, &subdevice))
    return -1;

  // Nuke existing stdin, stdout, stderr

  device_unregister(0);
  device_unregister(1);
  device_unregister(2);

  // Register new stdin, stdout, stderr

  device_register_char_fd(0, subdevice, NULL, usb_serial_read, NULL, usb_serial_rxready);
  device_register_char_fd(1, subdevice, usb_serial_write, NULL, usb_serial_txready, NULL);
  device_register_char_fd(2, subdevice, usb_serial_write, NULL, usb_serial_txready, NULL);

  return 0;
}

// Register USB serial port device

int usb_serial_register(char *name)
{
  return device_register_char(name, 0, usb_serial_open, NULL, usb_serial_write, usb_serial_read, usb_serial_txready, usb_serial_rxready);
}

// Return TRUE if USB system is ready to accept another transmit message

int usb_serial_txready(unsigned subdevice)
{
  return TRUE;
}

// Return TRUE if USB subsystem has receive data available

int usb_serial_rxready(unsigned subdevice)
{
  return !(APP_tx_ptr_head == APP_tx_ptr_tail);
}

// Send data to USB host

int usb_serial_write(unsigned subdevice, char *buf, unsigned int count)
{
  VCP_send_buffer((uint8_t *) buf, count);
  return count;
}

// Receive data from USB host

int usb_serial_read(unsigned subdevice, char *buf, unsigned int count)
{
  unsigned int len = 0;

  if (count == 0) return 0;

  while (usb_serial_rxready(0) && (len < count))
  {
    VCP_get_char((uint8_t *) buf);

    buf++;
    len++;
  }

  return len;
}
