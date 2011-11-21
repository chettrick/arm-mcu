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

		.word		WWDG_Handler
		.word		PVD_Handler
		.word		TAMP_STAMP_Handler
		.word		RTC_WKUP_Handler
		.word		FLASH_Handler
		.word		RCC_Handler
		.word		EXTI0_Handler
		.word		EXTI1_Handler
		.word		EXTI2_Handler
		.word		EXTI3_Handler
		.word		EXTI4_Handler
		.word		DMA1_Stream0_Handler
		.word		DMA1_Stream1_Handler
		.word		DMA1_Stream2_Handler
		.word		DMA1_Stream3_Handler
		.word		DMA1_Stream4_Handler
		.word		DMA1_Stream5_Handler
		.word		DMA1_Stream6_Handler
		.word		ADC_Handler
		.word		CAN1_TX_Handler
		.word		CAN1_RX0_Handler
		.word		CAN1_RX1_Handler
		.word		CAN1_SCE_Handler
		.word		EXTI9_5_Handler
		.word		TIM1_BRK_TIM9_Handler
		.word		TIM1_UP_TIM10_Handler
		.word		TIM1_TRG_COM_TIM11_Handler
		.word		TIM1_CC_Handler
		.word		TIM2_Handler
		.word		TIM3_Handler
		.word		TIM4_Handler
		.word		I2C1_EV_Handler
		.word		I2C1_ER_Handler
		.word		I2C2_EV_Handler
		.word		I2C2_ER_Handler
		.word		SPI1_Handler
		.word		SPI2_Handler
		.word		USART1_Handler
		.word		USART2_Handler
		.word		USART3_Handler
		.word		EXTI15_10_Handler
		.word		RTC_Alarm_Handler
		.word		OTG_FS_WKUP_Handler
		.word		TIM8_BRK_TIM12_Handler
		.word		TIM8_UP_TIM13_Handler
		.word		TIM8_TRG_COM_TIM14_Handler
		.word		TIM8_CC_Handler
		.word		DMA1_Stream7_Handler
		.word		FSMC_Handler
		.word		SDIO_Handler
		.word		TIM5_Handler
		.word		SPI3_Handler
		.word		UART4_Handler
		.word		UART5_Handler
		.word		TIM6_DAC_Handler
		.word		TIM7_Handler
		.word		DMA2_Stream0_Handler
		.word		DMA2_Stream1_Handler
		.word		DMA2_Stream2_Handler
		.word		DMA2_Stream3_Handler
		.word		DMA2_Stream4_Handler
		.word		ETH_Handler
		.word		ETH_WKUP_Handler
		.word		CAN2_TX_Handler
		.word		CAN2_RX0_Handler
		.word		CAN2_RX1_Handler
		.word		CAN2_SCE_Handler
		.word		OTG_FS_Handler
		.word		DMA2_Stream5_Handler
		.word		DMA2_Stream6_Handler
		.word		DMA2_Stream7_Handler
		.word		USART6_Handler
		.word		I2C3_EV_Handler
		.word		I2C3_ER_Handler
		.word		OTG_HS_EP1_OU_Handler
		.word		OTG_HS_EP1_IN_Handler
		.word		OTG_HS_WKUP_Handler
		.word		OTG_HS_Handler
		.word		DCMI_Handler
		.word		CRYP_Handler
		.word		HASH_RNG_Handler
		.word		FPU_Handler

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
		IRQ		WWDG_Handler
		IRQ		PVD_Handler
		IRQ		TAMP_STAMP_Handler
		IRQ		RTC_WKUP_Handler
		IRQ		FLASH_Handler
		IRQ		RCC_Handler
		IRQ		EXTI0_Handler
		IRQ		EXTI1_Handler
		IRQ		EXTI2_Handler
		IRQ		EXTI3_Handler
		IRQ		EXTI4_Handler
		IRQ		DMA1_Stream0_Handler
		IRQ		DMA1_Stream1_Handler
		IRQ		DMA1_Stream2_Handler
		IRQ		DMA1_Stream3_Handler
		IRQ		DMA1_Stream4_Handler
		IRQ		DMA1_Stream5_Handler
		IRQ		DMA1_Stream6_Handler
		IRQ		ADC_Handler
		IRQ		CAN1_TX_Handler
		IRQ		CAN1_RX0_Handler
		IRQ		CAN1_RX1_Handler
		IRQ		CAN1_SCE_Handler
		IRQ		EXTI9_5_Handler
		IRQ		TIM1_BRK_TIM9_Handler
		IRQ		TIM1_UP_TIM10_Handler
		IRQ		TIM1_TRG_COM_TIM11_Handler
		IRQ		TIM1_CC_Handler
		IRQ		TIM2_Handler
		IRQ		TIM3_Handler
		IRQ		TIM4_Handler
		IRQ		I2C1_EV_Handler
		IRQ		I2C1_ER_Handler
		IRQ		I2C2_EV_Handler
		IRQ		I2C2_ER_Handler
		IRQ		SPI1_Handler
		IRQ		SPI2_Handler
		IRQ		USART1_Handler
		IRQ		USART2_Handler
		IRQ		USART3_Handler
		IRQ		EXTI15_10_Handler
		IRQ		RTC_Alarm_Handler
		IRQ		OTG_FS_WKUP_Handler
		IRQ		TIM8_BRK_TIM12_Handler
		IRQ		TIM8_UP_TIM13_Handler
		IRQ		TIM8_TRG_COM_TIM14_Handler
		IRQ		TIM8_CC_Handler
		IRQ		DMA1_Stream7_Handler
		IRQ		FSMC_Handler
		IRQ		SDIO_Handler
		IRQ		TIM5_Handler
		IRQ		SPI3_Handler
		IRQ		UART4_Handler
		IRQ		UART5_Handler
		IRQ		TIM6_DAC_Handler
		IRQ		TIM7_Handler
		IRQ		DMA2_Stream0_Handler
		IRQ		DMA2_Stream1_Handler
		IRQ		DMA2_Stream2_Handler
		IRQ		DMA2_Stream3_Handler
		IRQ		DMA2_Stream4_Handler
		IRQ		ETH_Handler
		IRQ		ETH_WKUP_Handler
		IRQ		CAN2_TX_Handler
		IRQ		CAN2_RX0_Handler
		IRQ		CAN2_RX1_Handler
		IRQ		CAN2_SCE_Handler
		IRQ		OTG_FS_Handler
		IRQ		DMA2_Stream5_Handler
		IRQ		DMA2_Stream6_Handler
		IRQ		DMA2_Stream7_Handler
		IRQ		USART6_Handler
		IRQ		I2C3_EV_Handler
		IRQ		I2C3_ER_Handler
		IRQ		OTG_HS_EP1_OU_Handler
		IRQ		OTG_HS_EP1_IN_Handler
		IRQ		OTG_HS_WKUP_Handler
		IRQ		OTG_HS_Handler
		IRQ		DCMI_Handler
		IRQ		CRYP_Handler
		IRQ		HASH_RNG_Handler
		IRQ		FPU_Handler

		.end
