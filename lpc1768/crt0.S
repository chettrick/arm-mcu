/* Startup for LPC1768 Cortex-M3 ARM MCU */

// $Id$

		.text
		.extern		main
		.global		 _start
		.global		_default_handler
		.code		16
		.syntax 	unified
		.type		_reset, function

		.extern		__bss_beg__
		.extern		__bss_end__
		.extern		__data_beg__
		.extern		__data_end__
		.extern		__text_end__
		.extern		STACK_TOP

// Exception vector table

_start: 	.word		STACK_TOP
		.word		_reset
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

_reset:

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

// main() should never return, but if it does just do nothing forever
// Should probably put processor into sleep mode instead.

endless_loop:	b		endless_loop

// These are filled in by the linker
	
TEXT_END:	.word		__text_end__
DATA_BEG:	.word		__data_beg__
DATA_END:	.word		__data_end__
BSS_BEG:	.word		__bss_beg__ 
BSS_END:	.word		__bss_end__

//=============================================================================

// Default exception handler; does nothing

_default_handler: bx		lr

		.weak		NMI_Handler
		.weak		HardFault_Handler
		.weak		MemManage_Handler
		.weak		BusFault_Handler
		.weak		UsageFault_Handler
		.weak		SVC_Handler
		.weak		DebugMon_Handler
		.weak		PendSV_Handler
		.weak		SysTick_Handler
		.weak		WDT_IRQHandler
		.weak		TIMER0_IRQHandler
		.weak		TIMER1_IRQHandler
		.weak		TIMER2_IRQHandler
		.weak		TIMER3_IRQHandler
		.weak		UART0_IRQHandler
		.weak		UART1_IRQHandler
		.weak		UART2_IRQHandler
		.weak		UART3_IRQHandler
		.weak		PWM1_IRQHandler
		.weak		I2C0_IRQHandler
		.weak		I2C1_IRQHandler
		.weak		I2C2_IRQHandler
		.weak		SPI_IRQHandler
		.weak		SSP0_IRQHandler
		.weak		SSP1_IRQHandler
		.weak		PLL0_IRQHandler
		.weak		RTC_IRQHandler
		.weak		EINT0_IRQHandler
		.weak		EINT1_IRQHandler
		.weak		EINT2_IRQHandler
		.weak		EINT3_IRQHandler
		.weak		ADC_IRQHandler
		.weak		BOD_IRQHandler
		.weak		USB_IRQHandler
		.weak		CAN_IRQHandler
		.weak		DMA_IRQHandler
		.weak		I2S_IRQHandler
		.weak		ENET_IRQHandler
		.weak		RIT_IRQHandler
		.weak		MCPWM_IRQHandler
		.weak		QEI_IRQHandler
		.weak		PLL1_IRQHandler
		.weak		USBActivity_IRQHandler
		.weak		CANActivity_IRQHandler

		NMI_Handler		= _default_handler
		HardFault_Handler	= _default_handler
		MemManage_Handler	= _default_handler
		BusFault_Handler	= _default_handler
		UsageFault_Handler	= _default_handler
		SVC_Handler		= _default_handler
		DebugMon_Handler	= _default_handler
		PendSV_Handler		= _default_handler
		SysTick_Handler		= _default_handler
		WDT_IRQHandler		= _default_handler
		TIMER0_IRQHandler	= _default_handler
		TIMER1_IRQHandler	= _default_handler
		TIMER2_IRQHandler	= _default_handler
		TIMER3_IRQHandler	= _default_handler
		UART0_IRQHandler	= _default_handler
		UART1_IRQHandler	= _default_handler
		UART2_IRQHandler	= _default_handler
		UART3_IRQHandler	= _default_handler
		PWM1_IRQHandler		= _default_handler
		I2C0_IRQHandler		= _default_handler
		I2C1_IRQHandler		= _default_handler
		I2C2_IRQHandler		= _default_handler
		SPI_IRQHandler		= _default_handler
		SSP0_IRQHandler		= _default_handler
		SSP1_IRQHandler		= _default_handler
		PLL0_IRQHandler		= _default_handler
		RTC_IRQHandler		= _default_handler
		EINT0_IRQHandler	= _default_handler
		EINT1_IRQHandler	= _default_handler
		EINT2_IRQHandler	= _default_handler
		EINT3_IRQHandler	= _default_handler
		ADC_IRQHandler		= _default_handler
		BOD_IRQHandler		= _default_handler
		USB_IRQHandler		= _default_handler
		CAN_IRQHandler		= _default_handler
		DMA_IRQHandler		= _default_handler
		I2S_IRQHandler		= _default_handler
		ENET_IRQHandler		= _default_handler
		RIT_IRQHandler		= _default_handler
		MCPWM_IRQHandler	= _default_handler
		QEI_IRQHandler		= _default_handler
		PLL1_IRQHandler		= _default_handler
		USBActivity_IRQHandler	= _default_handler
		CANActivity_IRQHandler	= _default_handler

		.end
