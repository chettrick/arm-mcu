/* Startup for STM32F407 Cortex-M4 ARM MCU */

// $Id: stm32f107rb.S 3315 2011-11-16 15:08:01Z svn $

		.syntax 	unified
		.thumb
		.text

// Export these symbols

		.global		_start
		.global		Reset_Handler
		.global		Default_Handler

// Import these symbols

		.extern		__text_end__
		.extern		__data_beg__
		.extern		__data_end__
		.extern		__bss_beg__
		.extern		__bss_end__
		.extern		__stack_end__
		.extern		main

// Exception vector table--Common to all Cortex-M3

_start: 	.word		__stack_end__
		.word		Reset_Handler
		.word		NMI_Handler
		.word		HardFault_Handler
		.word		MemManage_Handler
		.word		BusFault_Handler
		.word		UsageFault_Handler
		.word		0
		.word		0
		.word		0
		.word		0
		.word		SVC_Handler
		.word		DebugMon_Handler
		.word		0
		.word		PendSV_Handler
		.word		SysTick_Handler

// Hardware interrupts specific to the STM32F407

		.word		WWDG_IRQHandler
		.word		PVD_IRQHandler
		.word		TAMP_STAMP_IRQHandler
		.word		RTC_WKUP_IRQHandler
		.word		FLASH_IRQHandler
		.word		RCC_IRQHandler
		.word		EXTI0_IRQHandler
		.word		EXTI1_IRQHandler
		.word		EXTI2_IRQHandler
		.word		EXTI3_IRQHandler
		.word		EXTI4_IRQHandler
		.word		DMA1_Stream0_IRQHandler
		.word		DMA1_Stream1_IRQHandler
		.word		DMA1_Stream2_IRQHandler
		.word		DMA1_Stream3_IRQHandler
		.word		DMA1_Stream4_IRQHandler
		.word		DMA1_Stream5_IRQHandler
		.word		DMA1_Stream6_IRQHandler
		.word		ADC_IRQHandler
		.word		CAN1_TX_IRQHandler
		.word		CAN1_RX0_IRQHandler
		.word		CAN1_RX1_IRQHandler
		.word		CAN1_SCE_IRQHandler
		.word		EXTI9_5_IRQHandler
		.word		TIM1_BRK_TIM9_IRQHandler
		.word		TIM1_UP_TIM10_IRQHandler
		.word		TIM1_TRG_COM_TIM11_IRQHandler
		.word		TIM1_CC_IRQHandler
		.word		TIM2_IRQHandler
		.word		TIM3_IRQHandler
		.word		TIM4_IRQHandler
		.word		I2C1_EV_IRQHandler
		.word		I2C1_ER_IRQHandler
		.word		I2C2_EV_IRQHandler
		.word		I2C2_ER_IRQHandler
		.word		SPI1_IRQHandler
		.word		SPI2_IRQHandler
		.word		USART1_IRQHandler
		.word		USART2_IRQHandler
		.word		USART3_IRQHandler
		.word		EXTI15_10_IRQHandler
		.word		RTC_Alarm_IRQHandler
		.word		OTG_FS_WKUP_IRQHandler
		.word		TIM8_BRK_TIM12_IRQHandler
		.word		TIM8_UP_TIM13_IRQHandler
		.word		TIM8_TRG_COM_TIM14_IRQHandler
		.word		TIM8_CC_IRQHandler
		.word		DMA1_Stream7_IRQHandler
		.word		FSMC_IRQHandler
		.word		SDIO_IRQHandler
		.word		TIM5_IRQHandler
		.word		SPI3_IRQHandler
		.word		UART4_IRQHandler
		.word		UART5_IRQHandler
		.word		TIM6_DAC_IRQHandler
		.word		TIM7_IRQHandler
		.word		DMA2_Stream0_IRQHandler
		.word		DMA2_Stream1_IRQHandler
		.word		DMA2_Stream2_IRQHandler
		.word		DMA2_Stream3_IRQHandler
		.word		DMA2_Stream4_IRQHandler
		.word		ETH_IRQHandler
		.word		ETH_WKUP_IRQHandler
		.word		CAN2_TX_IRQHandler
		.word		CAN2_RX0_IRQHandler
		.word		CAN2_RX1_IRQHandler
		.word		CAN2_SCE_IRQHandler
		.word		OTG_FS_IRQHandler
		.word		DMA2_Stream5_IRQHandler
		.word		DMA2_Stream6_IRQHandler
		.word		DMA2_Stream7_IRQHandler
		.word		USART6_IRQHandler
		.word		I2C3_EV_IRQHandler
		.word		I2C3_ER_IRQHandler
		.word		OTG_HS_EP1_OU_IRQHandler
		.word		OTG_HS_EP1_IN_IRQHandler
		.word		OTG_HS_WKUP_IRQHandler
		.word		OTG_HS_IRQHandler
		.word		DCMI_IRQHandler
		.word		CRYP_IRQHandler
		.word		HASH_RNG_IRQHandler
		.word		FPU_IRQHandler

// Reset vector: Set up environment to call C main()

		.thumb_func
Reset_Handler:

// Copy initialized data from flash to RAM

copy_data:	ldr		r1, DATA_BEG
		ldr 		r2, TEXT_END
		ldr 		r3, DATA_END
		subs		r3, r3, r1		// Length of initialized data
		beq		zero_bss		// Skip if none

copy_data_loop: ldrb		r4, [r2], #1		// Read byte from flash
		strb		r4, [r1], #1  		// Store byte to RAM
		subs		r3, r3, #1  		// Decrement counter
		bgt 		copy_data_loop		// Repeat until done

// Zero uninitialized data (bss)

zero_bss: 	ldr 		r1, BSS_BEG
		ldr 		r3, BSS_END
		subs 		r3, r3, r1		// Length of uninitialized data
		beq		call_main		// Skip if none

		mov 		r2, #0

zero_bss_loop: 	strb		r2, [r1], #1		// Store zero
		subs		r3, r3, #1		// Decrement counter
		bgt		zero_bss_loop		// Repeat until done

// Call main()

call_main:	mov		r0, #0			// argc=0
		mov		r1, #0			// argv=NULL

		bl		main 

// main() should never return, but if it does, just do nothing forever.
// Should probably put processor into sleep mode instead.

		b		.

// These are filled in by the linker
	
TEXT_END:	.word		__text_end__
DATA_BEG:	.word		__data_beg__
DATA_END:	.word		__data_end__
BSS_BEG:	.word		__bss_beg__ 
BSS_END:	.word		__bss_end__

//=============================================================================

// Default exception handler--does nothing but return

		.thumb_func
Default_Handler: bx		lr

//=============================================================================

// Use Default_handler for all exceptions and interrupts, unless another
// handler is provided elsewhere.

		.macro		IRQ handler
		.weak		\handler
		.set		\handler, Default_Handler
		.endm

		IRQ		NMI_Handler
		IRQ		HardFault_Handler
		IRQ		MemManage_Handler
		IRQ		BusFault_Handler
		IRQ		UsageFault_Handler
		IRQ		SVC_Handler
		IRQ		DebugMon_Handler
		IRQ		PendSV_Handler
		IRQ		SysTick_Handler
		IRQ		WWDG_IRQHandler
		IRQ		PVD_IRQHandler
		IRQ		TAMP_STAMP_IRQHandler
		IRQ		RTC_WKUP_IRQHandler
		IRQ		FLASH_IRQHandler
		IRQ		RCC_IRQHandler
		IRQ		EXTI0_IRQHandler
		IRQ		EXTI1_IRQHandler
		IRQ		EXTI2_IRQHandler
		IRQ		EXTI3_IRQHandler
		IRQ		EXTI4_IRQHandler
		IRQ		DMA1_Stream0_IRQHandler
		IRQ		DMA1_Stream1_IRQHandler
		IRQ		DMA1_Stream2_IRQHandler
		IRQ		DMA1_Stream3_IRQHandler
		IRQ		DMA1_Stream4_IRQHandler
		IRQ		DMA1_Stream5_IRQHandler
		IRQ		DMA1_Stream6_IRQHandler
		IRQ		ADC_IRQHandler
		IRQ		CAN1_TX_IRQHandler
		IRQ		CAN1_RX0_IRQHandler
		IRQ		CAN1_RX1_IRQHandler
		IRQ		CAN1_SCE_IRQHandler
		IRQ		EXTI9_5_IRQHandler
		IRQ		TIM1_BRK_TIM9_IRQHandler
		IRQ		TIM1_UP_TIM10_IRQHandler
		IRQ		TIM1_TRG_COM_TIM11_IRQHandler
		IRQ		TIM1_CC_IRQHandler
		IRQ		TIM2_IRQHandler
		IRQ		TIM3_IRQHandler
		IRQ		TIM4_IRQHandler
		IRQ		I2C1_EV_IRQHandler
		IRQ		I2C1_ER_IRQHandler
		IRQ		I2C2_EV_IRQHandler
		IRQ		I2C2_ER_IRQHandler
		IRQ		SPI1_IRQHandler
		IRQ		SPI2_IRQHandler
		IRQ		USART1_IRQHandler
		IRQ		USART2_IRQHandler
		IRQ		USART3_IRQHandler
		IRQ		EXTI15_10_IRQHandler
		IRQ		RTC_Alarm_IRQHandler
		IRQ		OTG_FS_WKUP_IRQHandler
		IRQ		TIM8_BRK_TIM12_IRQHandler
		IRQ		TIM8_UP_TIM13_IRQHandler
		IRQ		TIM8_TRG_COM_TIM14_IRQHandler
		IRQ		TIM8_CC_IRQHandler
		IRQ		DMA1_Stream7_IRQHandler
		IRQ		FSMC_IRQHandler
		IRQ		SDIO_IRQHandler
		IRQ		TIM5_IRQHandler
		IRQ		SPI3_IRQHandler
		IRQ		UART4_IRQHandler
		IRQ		UART5_IRQHandler
		IRQ		TIM6_DAC_IRQHandler
		IRQ		TIM7_IRQHandler
		IRQ		DMA2_Stream0_IRQHandler
		IRQ		DMA2_Stream1_IRQHandler
		IRQ		DMA2_Stream2_IRQHandler
		IRQ		DMA2_Stream3_IRQHandler
		IRQ		DMA2_Stream4_IRQHandler
		IRQ		ETH_IRQHandler
		IRQ		ETH_WKUP_IRQHandler
		IRQ		CAN2_TX_IRQHandler
		IRQ		CAN2_RX0_IRQHandler
		IRQ		CAN2_RX1_IRQHandler
		IRQ		CAN2_SCE_IRQHandler
		IRQ		OTG_FS_IRQHandler
		IRQ		DMA2_Stream5_IRQHandler
		IRQ		DMA2_Stream6_IRQHandler
		IRQ		DMA2_Stream7_IRQHandler
		IRQ		USART6_IRQHandler
		IRQ		I2C3_EV_IRQHandler
		IRQ		I2C3_ER_IRQHandler
		IRQ		OTG_HS_EP1_OU_IRQHandler
		IRQ		OTG_HS_EP1_IN_IRQHandler
		IRQ		OTG_HS_WKUP_IRQHandler
		IRQ		OTG_HS_IRQHandler
		IRQ		DCMI_IRQHandler
		IRQ		CRYP_IRQHandler
		IRQ		HASH_RNG_IRQHandler
		IRQ		FPU_IRQHandler

		.end
