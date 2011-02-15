/* Startup for LPC1768 Cortex-M3 ARM MCU */

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

// Hardware interrupts specific to the LPC17xx

		.word		WDT_IRQHandler          // 16: Watchdog Timer
		.word		TIMER0_IRQHandler       // 17: Timer0
		.word		TIMER1_IRQHandler       // 18: Timer1
		.word		TIMER2_IRQHandler       // 19: Timer2
		.word		TIMER3_IRQHandler       // 20: Timer3
		.word		UART0_IRQHandler        // 21: UART0
		.word		UART1_IRQHandler        // 22: UART1
		.word		UART2_IRQHandler        // 23: UART2
		.word		UART3_IRQHandler        // 24: UART3
		.word		PWM1_IRQHandler         // 25: PWM1
		.word		I2C0_IRQHandler         // 26: I2C0
		.word		I2C1_IRQHandler         // 27: I2C1
		.word		I2C2_IRQHandler         // 28: I2C2
		.word		SPI_IRQHandler          // 29: SPI
		.word		SSP0_IRQHandler         // 30: SSP0
		.word		SSP1_IRQHandler         // 31: SSP1
		.word		PLL0_IRQHandler         // 32: PLL0 Lock (Main PLL)
		.word		RTC_IRQHandler          // 33: Real Time Clock
		.word		EINT0_IRQHandler        // 34: External Interrupt 0
		.word		EINT1_IRQHandler        // 35: External Interrupt 1
		.word		EINT2_IRQHandler        // 36: External Interrupt 2
		.word		EINT3_IRQHandler        // 37: External Interrupt 3
		.word		ADC_IRQHandler		// 38: A/D Converter
		.word		BOD_IRQHandler		// 39: Brown-Out Detect
		.word		USB_IRQHandler		// 40: USB
		.word		CAN_IRQHandler		// 41: CAN
		.word		DMA_IRQHandler		// 42: General Purpose DMA
		.word		I2S_IRQHandler		// 43: I2S
		.word		ENET_IRQHandler		// 44: Ethernet
		.word		RIT_IRQHandler		// 45: Repetitive Interrupt Timer
		.word		MCPWM_IRQHandler	// 46: Motor Control PWM
		.word		QEI_IRQHandler		// 47: Quadrature Encoder Interface
		.word		PLL1_IRQHandler		// 48: PLL1 Lock (USB PLL)
		.word		USBActivity_IRQHandler	// 49: USB Activity
		.word		CANActivity_IRQHandler	// 50: CAN Activity

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
		IRQ		WDT_IRQHandler
		IRQ		TIMER0_IRQHandler
		IRQ		TIMER1_IRQHandler
		IRQ		TIMER2_IRQHandler
		IRQ		TIMER3_IRQHandler
		IRQ		UART0_IRQHandler
		IRQ		UART1_IRQHandler
		IRQ		UART2_IRQHandler
		IRQ		UART3_IRQHandler
		IRQ		PWM1_IRQHandler
		IRQ		I2C0_IRQHandler
		IRQ		I2C1_IRQHandler
		IRQ		I2C2_IRQHandler
		IRQ		SPI_IRQHandler
		IRQ		SSP0_IRQHandler
		IRQ		SSP1_IRQHandler
		IRQ		PLL0_IRQHandler
		IRQ		RTC_IRQHandler
		IRQ		EINT0_IRQHandler
		IRQ		EINT1_IRQHandler
		IRQ		EINT2_IRQHandler
		IRQ		EINT3_IRQHandler
		IRQ		ADC_IRQHandler
		IRQ		BOD_IRQHandler
		IRQ		USB_IRQHandler
		IRQ		CAN_IRQHandler
		IRQ		DMA_IRQHandler
		IRQ		I2S_IRQHandler
		IRQ		ENET_IRQHandler
		IRQ		RIT_IRQHandler
		IRQ		MCPWM_IRQHandler
		IRQ		QEI_IRQHandler
		IRQ		PLL1_IRQHandler
		IRQ		USBActivity_IRQHandler
		IRQ		CANActivity_IRQHandler

		.end
