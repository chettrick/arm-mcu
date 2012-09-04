/* Startup for LPC17xx Cortex-M3 ARM MCU */

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
		.word		VectorChecksum
		.word		0
		.word		0
		.word		0
		IRQ		SVC_Handler
		IRQ		DebugMon_Handler
		.word		0
		IRQ		PendSV_Handler
		IRQ		SysTick_Handler

// Hardware interrupts specific to the LPC17xx

		IRQ		WDT_IRQHandler          // 16: Watchdog Timer
		IRQ		TIMER0_IRQHandler       // 17: Timer0
		IRQ		TIMER1_IRQHandler       // 18: Timer1
		IRQ		TIMER2_IRQHandler       // 19: Timer2
		IRQ		TIMER3_IRQHandler       // 20: Timer3
		IRQ		UART0_IRQHandler        // 21: UART0
		IRQ		UART1_IRQHandler        // 22: UART1
		IRQ		UART2_IRQHandler        // 23: UART2
		IRQ		UART3_IRQHandler        // 24: UART3
		IRQ		PWM1_IRQHandler         // 25: PWM1
		IRQ		I2C0_IRQHandler         // 26: I2C0
		IRQ		I2C1_IRQHandler         // 27: I2C1
		IRQ		I2C2_IRQHandler         // 28: I2C2
		IRQ		SPI_IRQHandler          // 29: SPI
		IRQ		SSP0_IRQHandler         // 30: SSP0
		IRQ		SSP1_IRQHandler         // 31: SSP1
		IRQ		PLL0_IRQHandler         // 32: PLL0 Lock (Main PLL)
		IRQ		RTC_IRQHandler          // 33: Real Time Clock
		IRQ		EINT0_IRQHandler        // 34: External Interrupt 0
		IRQ		EINT1_IRQHandler        // 35: External Interrupt 1
		IRQ		EINT2_IRQHandler        // 36: External Interrupt 2
		IRQ		EINT3_IRQHandler        // 37: External Interrupt 3
		IRQ		ADC_IRQHandler		// 38: A/D Converter
		IRQ		BOD_IRQHandler		// 39: Brown-Out Detect
		IRQ		USB_IRQHandler		// 40: USB
		IRQ		CAN_IRQHandler		// 41: CAN
		IRQ		DMA_IRQHandler		// 42: General Purpose DMA
		IRQ		I2S_IRQHandler		// 43: I2S
		IRQ		ENET_IRQHandler		// 44: Ethernet
		IRQ		RIT_IRQHandler		// 45: Repetitive Interrupt Timer
		IRQ		MCPWM_IRQHandler	// 46: Motor Control PWM
		IRQ		QEI_IRQHandler		// 47: Quadrature Encoder Interface
		IRQ		PLL1_IRQHandler		// 48: PLL1 Lock (USB PLL)
		IRQ		USBActivity_IRQHandler	// 49: USB Activity
		IRQ		CANActivity_IRQHandler	// 50: CAN Activity

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

		.align		4
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
		.align		4
__dso_handle:	.word
		.global		__dso_handle
		.weak		__dso_handle

		.end
