/* Startup for STM32F107 Cortex-M3 ARM MCU */

// $Id$

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
		.extern		__ctors_start__
		.extern		__ctors_end__
		.extern		main

//=============================================================================

// Use Default_handler for all exceptions and interrupts, unless another
// handler is provided elsewhere.

		.macro		IRQ handler
		.word		\handler
		.weak		\handler
		.set		\handler, Default_Handler
		.endm

//=============================================================================

// Exception vector table--Common to all Cortex-M3

_start: 	.word		__stack_end__
		.word		Reset_Handler
		IRQ		NMI_Handler
		IRQ		HardFault_Handler
		IRQ		MemManage_Handler
		IRQ		BusFault_Handler
		IRQ		UsageFault_Handler
		.word		0
		.word		0
		.word		0
		.word		0
		IRQ		SVC_Handler
		IRQ		DebugMon_Handler
		.word		0
		IRQ		PendSV_Handler
		IRQ		SysTick_Handler

// Hardware interrupts specific to the STM32F107

		IRQ		WWDG_IRQHandler
		IRQ		PVD_IRQHandler
		IRQ		TAMPER_IRQHandler
		IRQ		RTC_IRQHandler
		IRQ		FLASH_IRQHandler
		IRQ		RCC_IRQHandler
		IRQ		EXTI0_IRQHandler
		IRQ		EXTI1_IRQHandler
		IRQ		EXTI2_IRQHandler
		IRQ		EXTI3_IRQHandler
		IRQ		EXTI4_IRQHandler
		IRQ		DMA1_Channel1_IRQHandler
		IRQ		DMA1_Channel2_IRQHandler
		IRQ		DMA1_Channel3_IRQHandler
		IRQ		DMA1_Channel4_IRQHandler
		IRQ		DMA1_Channel5_IRQHandler
		IRQ		DMA1_Channel6_IRQHandler
		IRQ		DMA1_Channel7_IRQHandler
		IRQ		ADC1_2_IRQHandler
		IRQ		CAN1_TX_IRQHandler
		IRQ		CAN1_RX0_IRQHandler
		IRQ		CAN1_RX1_IRQHandler
		IRQ		CAN1_SCE_IRQHandler
		IRQ		EXTI9_5_IRQHandler
		IRQ		TIM1_BRK_IRQHandler
		IRQ		TIM1_UP_IRQHandler
		IRQ		TIM1_TRG_COM_IRQHandler
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
		IRQ		RTCAlarm_IRQHandler
		IRQ		OTG_FS_WKUP_IRQHandler
		.word		0
		.word		0
		.word		0
		.word		0
		.word		0
		.word		0
		.word		0
		IRQ		TIM5_IRQHandler
		IRQ		SPI3_IRQHandler
		IRQ		UART4_IRQHandler
		IRQ		UART5_IRQHandler
		IRQ		TIM6_IRQHandler
		IRQ		TIM7_IRQHandler
		IRQ		DMA2_Channel1_IRQHandler
		IRQ		DMA2_Channel2_IRQHandler
		IRQ		DMA2_Channel3_IRQHandler
		IRQ		DMA2_Channel4_IRQHandler
		IRQ		DMA2_Channel5_IRQHandler
		IRQ		ETH_IRQHandler
		IRQ		ETH_WKUP_IRQHandler
		IRQ		CAN2_TX_IRQHandler
		IRQ		CAN2_RX0_IRQHandler
		IRQ		CAN2_RX1_IRQHandler
		IRQ		CAN2_SCE_IRQHandler
		IRQ		OTG_FS_IRQHandler

//=============================================================================

// Default exception handler--does nothing but return

		.thumb_func
Default_Handler: bx		lr

//=============================================================================

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
		beq		call_ctors		// Skip if none

		mov 		r2, #0

zero_bss_loop: 	strb		r2, [r1], #1		// Store zero
		subs		r3, r3, #1		// Decrement counter
		bgt		zero_bss_loop		// Repeat until done

// Call C++ constructors.  The compiler and linker together populate the .ctors
// code section with the addresses of the constructor functions.

call_ctors:	ldr		r0, CTORS_BEG
		ldr		r1, CTORS_END
		subs		r1, r1, r0		// Length of ctors section
		beq		call_main		// Skip if no constructors

ctors_loop:	ldr		r2, [r0], #4		// Load next constructor address
		push		{r0,r1}			// Save registers
		blx		r2			// Call constructor
		pop		{r0,r1}			// Restore registers
		subs		r1, r1, #4		// Decrement counter
		bgt		ctors_loop		// Repeat until done

// Call main()

call_main:	mov		r0, #0			// argc=0
		mov		r1, #0			// argv=NULL

		bl		main 

// main() should never return, but if it does, just do nothing forever.
// Should probably put processor into sleep mode instead.

		b		.

//=============================================================================

// These are filled in by the linker
	
TEXT_END:	.word		__text_end__
DATA_BEG:	.word		__data_beg__
DATA_END:	.word		__data_end__
BSS_BEG:	.word		__bss_beg__ 
BSS_END:	.word		__bss_end__
CTORS_BEG:	.word		__ctors_start__
CTORS_END:	.word		__ctors_end__

//=============================================================================

// libstdc++ needs this

		.bss
__dso_handle:	.word
		.global		__dso_handle
		.weak		__dso_handle

		.end
