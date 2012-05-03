/* Startup for EFM32G890F128 Cortex-M3 ARM MCU */

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

// Exception vector table--Common to all Cortex-M3

_start: 	.word		__stack_end__
		.word		Reset_Handler		// Reset Handler
		.word		NMI_Handler             // NMI Handler
		.word		HardFault_Handler       // Hard Fault Handler
		.word		MemManage_Handler       // MPU Fault Handler
		.word		BusFault_Handler        // Bus Fault Handler
		.word		UsageFault_Handler      // Usage Fault Handler
		.word		0
		.word		0
		.word		0
		.word		0
		.word		SVC_Handler             // SVCall Handler
		.word		DebugMon_Handler        // Debug Monitor Handler
		.word		0
		.word		PendSV_Handler          // PendSV Handler
		.word		SysTick_Handler         // SysTick Handler

// Hardware interrupts specific to the EFM32G890F128

		.word		DMA_IRQHandler
		.word		GPIO_EVEN_IRQHandler
		.word		TIMER0_IRQHandler
		.word		USART0_RX_IRQHandler
		.word		USART0_TX_IRQHandler
		.word		ACMP0_IRQHandler
		.word		ADC0_IRQHandler
		.word		DAC0_IRQHandler
		.word		I2C0_IRQHandler
		.word		GPIO_ODD_IRQHandler
		.word		TIMER1_IRQHandler
		.word		TIMER2_IRQHandler
		.word		USART1_RX_IRQHandler
		.word		USART1_TX_IRQHandler
		.word		USART2_RX_IRQHandler
		.word		USART2_TX_IRQHandler
		.word		UART0_RX_IRQHandler
		.word		UART0_TX_IRQHandler
		.word		LEUART0_IRQHandler
		.word		LEUART1_IRQHandler
		.word		LETIMER0_IRQHandler
		.word		PCNT0_IRQHandler
		.word		PCNT1_IRQHandler
		.word		PCNT2_IRQHandler
		.word		RTC_IRQHandler
		.word		CMU_IRQHandler
		.word		VCMP_IRQHandler
		.word		LCD_IRQHandler
		.word		MSC_IRQHandler
		.word		AES_IRQHandler

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

// These are filled in by the linker
	
TEXT_END:	.word		__text_end__
DATA_BEG:	.word		__data_beg__
DATA_END:	.word		__data_end__
BSS_BEG:	.word		__bss_beg__ 
BSS_END:	.word		__bss_end__
CTORS_BEG:	.word		__ctors_start__
CTORS_END:	.word		__ctors_end__

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
		IRQ		DMA_IRQHandler
		IRQ		GPIO_EVEN_IRQHandler
		IRQ		TIMER0_IRQHandler
		IRQ		USART0_RX_IRQHandler
		IRQ		USART0_TX_IRQHandler
		IRQ		ACMP0_IRQHandler
		IRQ		ADC0_IRQHandler
		IRQ		DAC0_IRQHandler
		IRQ		I2C0_IRQHandler
		IRQ		GPIO_ODD_IRQHandler
		IRQ		TIMER1_IRQHandler
		IRQ		TIMER2_IRQHandler
		IRQ		USART1_RX_IRQHandler
		IRQ		USART1_TX_IRQHandler
		IRQ		USART2_RX_IRQHandler
		IRQ		USART2_TX_IRQHandler
		IRQ		UART0_RX_IRQHandler
		IRQ		UART0_TX_IRQHandler
		IRQ		LEUART0_IRQHandler
		IRQ		LEUART1_IRQHandler
		IRQ		LETIMER0_IRQHandler
		IRQ		PCNT0_IRQHandler
		IRQ		PCNT1_IRQHandler
		IRQ		PCNT2_IRQHandler
		IRQ		RTC_IRQHandler
		IRQ		CMU_IRQHandler
		IRQ		VCMP_IRQHandler
		IRQ		LCD_IRQHandler
		IRQ		MSC_IRQHandler
		IRQ		AES_IRQHandler

// libstdc++ needs this

		.bss
__dso_handle:	.word
		.global		__dso_handle
		.weak		__dso_handle

		.end
