/***********************************************************************//**
 * @file		lpc17xx_libcfg_default.h
 * @brief		Default Library configuration header file
 * @version		2.0
 * @date		21. May. 2010
 * @author		NXP MCU SW Application Team
 **************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **************************************************************************/

/* Library Configuration group ----------------------------------------------------------- */
/** @defgroup LIBCFG_DEFAULT LIBCFG_DEFAULT
 * @ingroup LPC1700CMSIS_FwLib_Drivers
 * @{
 */

#ifndef LPC17XX_LIBCFG_DEFAULT_H_
#define LPC17XX_LIBCFG_DEFAULT_H_

/* Includes ------------------------------------------------------------------- */
#include <assert.h>
#include "lpc_types.h"


/* Public Macros -------------------------------------------------------------- */
/** @defgroup LIBCFG_DEFAULT_Public_Macros LIBCFG_DEFAULT Public Macros
 * @{
 */


/******************* PERIPHERAL FW LIBRARY CONFIGURATION DEFINITIONS ***********************/
/* Comment the line below to disable the specific peripheral inclusion */

/* GPIO ------------------------------- */
#define _GPIO

/* EXTI ------------------------------- */
#define _EXTI

/* UART ------------------------------- */
#define _UART
#define _UART0
#define _UART1
#define _UART2
#define _UART3

/* SPI ------------------------------- */
#define _SPI

/* SYSTICK --------------------------- */
#define _SYSTICK

/* SSP ------------------------------- */
#define _SSP
#define _SSP0
#define _SSP1


/* I2C ------------------------------- */
#define _I2C
#define _I2C0
#define _I2C1
#define _I2C2

/* TIMER ------------------------------- */
#define _TIM

/* WDT ------------------------------- */
#define _WDT


/* GPDMA ------------------------------- */
#define _GPDMA


/* DAC ------------------------------- */
#define _DAC

/* DAC ------------------------------- */
#define _ADC


/* PWM ------------------------------- */
#define _PWM
#define _PWM1

/* RTC ------------------------------- */
#define _RTC

/* I2S ------------------------------- */
#define _I2S

/* USB device ------------------------------- */
#define _USBDEV
#define _USB_DMA

/* QEI ------------------------------- */
#define _QEI

/* MCPWM ------------------------------- */
#define _MCPWM

/* CAN--------------------------------*/
#define _CAN

/* RIT ------------------------------- */
#define _RIT

/* EMAC ------------------------------ */
#define _EMAC

/************************** GLOBAL/PUBLIC MACRO DEFINITIONS *********************************/

#define CHECK_PARAM(expr) assert(expr)

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @defgroup LIBCFG_DEFAULT_Public_Functions LIBCFG_DEFAULT Public Functions
 * @{
 */

/**
 * @}
 */

#endif /* LPC17XX_LIBCFG_DEFAULT_H_ */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
