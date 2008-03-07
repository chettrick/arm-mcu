/* Startup for STM32F103 Cortex-M3 ARM microcontroller */

// $Id: crt0.S,v 1.1 2008-03-07 13:51:19 cvs Exp $

		.equ		STACK_TOP, 0x20000800
		.text
		.extern		main
		.global		 _start
		.global		_default_handler
		.code		16
		.syntax 	unified
		.type		_reset, function

// Exception vector table

_start: 	.word		STACK_TOP
		.word		_reset
		.extern		NMIException
		.word		NMIException
		.extern		HardFaultException
		.word		HardFaultException
		.extern		MemManageException
		.word		MemManageException
		.extern		BusFaultException
		.word		BusFaultException
		.extern		UsageFaultException
		.word		UsageFaultException
		.word		0, 0, 0, 0
		.extern		SVCHandler
		.word		SVCHandler
		.extern		DebugMonitor
		.word		DebugMonitor
		.word		0
		.extern		PendSVC
		.word		PendSVC
		.extern		SysTickHandler
		.word		SysTickHandler
		.extern		WWDG_IRQHandler
		.word		WWDG_IRQHandler
		.extern		PVD_IRQHandler
		.word		PVD_IRQHandler
		.extern		TAMPER_IRQHandler
		.word		TAMPER_IRQHandler
		.extern		RTC_IRQHandler
		.word		RTC_IRQHandler
		.extern		FLASH_IRQHandler
		.word		FLASH_IRQHandler
		.extern		RCC_IRQHandler
		.word		RCC_IRQHandler
		.extern		EXTI0_IRQHandler
		.word		EXTI0_IRQHandler
		.extern		EXTI1_IRQHandler
		.word		EXTI1_IRQHandler
		.extern		EXTI2_IRQHandler
		.word		EXTI2_IRQHandler
		.extern		EXTI3_IRQHandler
		.word		EXTI3_IRQHandler
		.extern		EXTI4_IRQHandler
		.word		EXTI4_IRQHandler
		.extern		DMAChannel1_IRQHandler
		.word		DMAChannel1_IRQHandler
		.extern		DMAChannel2_IRQHandler
		.word		DMAChannel2_IRQHandler
		.extern		DMAChannel3_IRQHandler
		.word		DMAChannel3_IRQHandler
		.extern		DMAChannel4_IRQHandler
		.word		DMAChannel4_IRQHandler
		.extern		DMAChannel5_IRQHandler
		.word		DMAChannel5_IRQHandler
		.extern		DMAChannel6_IRQHandler
		.word		DMAChannel6_IRQHandler
		.extern		DMAChannel7_IRQHandler
		.word		DMAChannel7_IRQHandler
		.extern		ADC_IRQHandler
		.word		ADC_IRQHandler
		.extern		USB_HP_CAN_TX_IRQHandler
		.word		USB_HP_CAN_TX_IRQHandler
		.extern		USB_LP_CAN_RX0_IRQHandler
		.word		USB_LP_CAN_RX0_IRQHandler
		.extern		CAN_RX1_IRQHandler
		.word		CAN_RX1_IRQHandler
		.extern		CAN_SCE_IRQHandler
		.word		CAN_SCE_IRQHandler
		.extern		EXTI9_5_IRQHandler
		.word		EXTI9_5_IRQHandler
		.extern		TIM1_BRK_IRQHandler
		.word		TIM1_BRK_IRQHandler
		.extern		TIM1_UP_IRQHandler
		.word		TIM1_UP_IRQHandler
		.extern		TIM1_TRG_COM_IRQHandler
		.word		TIM1_TRG_COM_IRQHandler
		.extern		TIM1_CC_IRQHandler
		.word		TIM1_CC_IRQHandler
		.extern		TIM2_IRQHandler
		.word		TIM2_IRQHandler
		.extern		TIM3_IRQHandler
		.word		TIM3_IRQHandler
		.extern		TIM4_IRQHandler
		.word		TIM4_IRQHandler
		.extern		I2C1_EV_IRQHandler
		.word		I2C1_EV_IRQHandler
		.extern		I2C1_ER_IRQHandler
		.word		I2C1_ER_IRQHandler
		.extern		I2C2_EV_IRQHandler
		.word		I2C2_EV_IRQHandler
		.extern		I2C2_ER_IRQHandler
		.word		I2C2_ER_IRQHandler
		.extern		SPI1_IRQHandler
		.word		SPI1_IRQHandler
		.extern		SPI2_IRQHandler
		.word		SPI2_IRQHandler
		.extern		USART1_IRQHandler
		.word		USART1_IRQHandler
		.extern		USART2_IRQHandler
		.word		USART2_IRQHandler
		.extern		USART3_IRQHandler
		.word		USART3_IRQHandler
		.extern		EXTI15_10_IRQHandler
		.word		EXTI15_10_IRQHandler
		.extern		RTCAlarm_IRQHandler
		.word		RTCAlarm_IRQHandler
		.extern		USBWakeUp_IRQHandler
		.word		USBWakeUp_IRQHandler

// Reset vector

_reset:		b		main

// Default exception handler; does nothing

_default_handler: bx		lr
		.end
