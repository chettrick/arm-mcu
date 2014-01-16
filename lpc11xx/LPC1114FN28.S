/* Startup for LPC11xx Cortex-M0 ARM MCU */

// $Id$

// Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
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

		.syntax 	unified
		.thumb
		.section	.startup, "x"

// Export these symbols

		.global		_start
		.global		_vectors

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

// Exception vector table--Common to all Cortex-M0

_vectors: 	.word		__stack_end__
		.word		_start
		IRQ		NMI_Handler
		IRQ		HardFault_Handler
		.word		0
		.word		0
		.word		0
		.word		VectorChecksum
		.word		0
		.word		0
		.word		0
		IRQ		SVC_Handler
		.word		0
		.word		0
		IRQ		PendSV_Handler
		IRQ		SysTick_Handler

// Hardware interrupts specific to the LPC11xx -- Names per "Table 54"

		IRQ		PIO0_0_IRQHandler	// IRQ  0: Start logic interrupt 0
		IRQ		PIO0_1_IRQHandler	// IRQ  1: Start logic interrupt 1
		IRQ		PIO0_2_IRQHandler	// IRQ  2: Start logic interrupt 2
		IRQ		PIO0_3_IRQHandler	// IRQ  3: Start logic interrupt 3
		IRQ		PIO0_4_IRQHandler	// IRQ  4: Start logic interrupt 4
		IRQ		PIO0_5_IRQHandler	// IRQ  5: Start logic interrupt 5
		IRQ		PIO0_6_IRQHandler	// IRQ  6: Start logic interrupt 6
		IRQ		PIO0_7_IRQHandler	// IRQ  7: Start logic interrupt 7
		IRQ		PIO0_8_IRQHandler	// IRQ  8: Start logic interrupt 8
		IRQ		PIO0_9_IRQHandler	// IRQ  9: Start logic interrupt 9
		IRQ		PIO0_10_IRQHandler	// IRQ 10: Start logic interrupt 10
		IRQ		PIO0_11_IRQHandler	// IRQ 11: Start logic interrupt 11
		IRQ		PIO1_0_IRQHandler	// IRQ 12: Start logic interrupt 12
		IRQ		C_CAN_IRQHandler	// IRQ 13: CAN (not present)
		IRQ		SPI1_IRQHandler		// IRQ 14: SPI1 (not present)
		IRQ		I2C_IRQHandler		// IRQ 15: I2C
		IRQ		CT16B0_IRQHandler	// IRQ 16: 16-bit counter/timer 0
		IRQ		CT16B1_IRQHandler	// IRQ 17: 16-bit counter/timer 1
		IRQ		CT32B0_IRQHandler	// IRQ 18: 32-bit counter/timer 0
		IRQ		CT32B1_IRQHandler	// IRQ 19: 32-bit counter/timer 1
		IRQ		SPI0_IRQHandler		// IRQ 20: SPI0
		IRQ		UART_IRQHandler		// IRQ 21: Serial port
		.word		0			// IRQ 22: Reserved
		.word		0			// IRQ 23: Reserved
		IRQ		ADC_IRQHandler		// IRQ 24: A/D converter
		IRQ		WDT_IRQHandler		// IRQ 25: Watchdog timer
		IRQ		BOD_IRQHandler		// IRQ 26: Brown-out detector
		.word		0			// IRQ 27: Reserved
		IRQ		PIO3_IRQHandler		// IRQ 28: Parallel port 3
		IRQ		PIO2_IRQHandler		// IRQ 29: Parallel port 2
		IRQ		PIO1_IRQHandler		// IRQ 30: Parallel port 1
		IRQ		PIO0_IRQHandler		// IRQ 31: Parallel port 0

//=============================================================================

// Default exception handler--does nothing but return

		.thumb_func
Default_Handler: bx		lr

//=============================================================================

// Reset vector: Set up environment to call C main()

		.thumb_func
_start:

// Copy initialized data from flash to RAM

copy_data:	ldr		r1, DATA_BEG
		ldr 		r2, TEXT_END
		ldr 		r3, DATA_END
		subs		r3, r1			// Length of initialized data
		beq		zero_bss		// Skip if none

copy_data_loop: ldrb		r4, [r2]		// Read byte from flash
		strb		r4, [r1]  		// Store byte to RAM
		adds		r2, #1			// Increment pointer
		adds		r1, #1			// Increment pointer
		subs		r3, #1  		// Decrement counter
		bgt 		copy_data_loop		// Repeat until done

// Zero uninitialized data (bss)

zero_bss: 	ldr 		r1, BSS_BEG
		ldr 		r3, BSS_END
		subs 		r3, r1			// Length of uninitialized data
		beq		call_ctors		// Skip if none

		eors 		r2, r2

zero_bss_loop: 	strb		r2, [r1]		// Store zero
		adds		r1, #1			// Increment pointer
		subs		r3, #1			// Decrement counter
		bgt		zero_bss_loop		// Repeat until done

// Call C++ constructors.  The compiler and linker together populate the .ctors
// code section with the addresses of the constructor functions.

call_ctors:	ldr		r0, CTORS_BEG
		ldr		r1, CTORS_END
		subs		r1, r0			// Length of ctors section
		beq		call_main		// Skip if no constructors

ctors_loop:	ldr		r2, [r0]		// Load next constructor address
		push		{r0,r1}			// Save registers
		blx		r2			// Call constructor
		pop		{r0,r1}			// Restore registers
		adds		r0, #4			// Increment pointer
		subs		r1, #4			// Decrement counter
		bgt		ctors_loop		// Repeat until done

// Call main()

call_main:	eors		r0, r0			// argc=0
		eors		r1, r1			// argv=NULL

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
