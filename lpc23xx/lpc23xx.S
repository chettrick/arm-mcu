// Startup for LPC23xx ARM MCU

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

	.section .startup, "x"
	.code 32
	.align 4

	.extern	main 		/*  Usual C startup.			*/

	/*  Defined in link script so startup knows where everything 	*/
	/* is.								*/
	.extern	__bss_beg__	
	.extern	__bss_end__
	.extern __stack_beg__
	.extern __stack_end__
	.extern __data_beg__
	.extern __data_end__
	.extern __data_beg_src__
	.extern	__ctors_start__
	.extern	__ctors_end__

	.global	_start
	.global _vectors

	.set INIT_FIQ_MODE,		0x11
	.set INIT_IRQ_MODE,		0x12
	.set INIT_SUPERVISOR_MODE,	0x13
	.set INIT_ABORT_MODE,		0x17
	.set INIT_UNDEFINED_MODE,	0x1B
	.set INIT_SYSTEM_MODE,		0x1F

	/**** Exception/Interrupt vector table ****/

_vectors:
	b	_start
	b	undefined_instruction_exception
	b	software_interrupt_exception
	b	prefetch_abort_exception
	b	data_abort_exception
	nop
	ldr	pc,[pc,#-0x120]	    	/* Vector via VIC		*/
	b	fast_interrupt_exception

/********************* start ********************************************/
/*  start (AKA _start, _mainCRTStartup) -- Gains control on reset and	*/
/* set up environment before running the operating C program. 		*/

_start:

	/*  Start by setting up a stack					*/
	msr	cpsr_c, #INIT_FIQ_MODE
	ldr	sp, =__stack_end_fiq__
	msr	cpsr_c, #INIT_IRQ_MODE
	ldr	sp, =__stack_end_irq__
	msr	cpsr_c, #INIT_SUPERVISOR_MODE
	ldr	sp, =__stack_end_supervisor__
	msr	cpsr_c, #INIT_ABORT_MODE
	ldr	sp, =__stack_end_abort__
	msr	cpsr_c, #INIT_UNDEFINED_MODE
	ldr	sp, =__stack_end_undefined__
	msr	cpsr_c, #INIT_SYSTEM_MODE
	ldr	sp, =__stack_end__
	ldr	sl, =__stack_beg__

	mov 	a2, #0		/* Fill value 				*/
	mov	fp, a2		/* Null frame pointer 			*/
	mov	r7, a2		/* Null frame pointer for Thumb 	*/
	
	ldr 	r1, .LC1	/*  __bss_beg__ set in link script to 	*/
				/* point at beginning of uninitialized	*/
				/* ram.					*/
	ldr 	r3, .LC2	/*  __bss_beg__ set in link script to 	*/
				/* point at end of uninitialized ram.	*/
	subs 	r3, r3, r1	/*  Subtract two to find length of 	*/
				/* uninitialized ram.			*/
	beq	.end_clear_loop	/*  If no uninitialzed ram skip init.	*/

	mov 	r2, #0		/*  Value used to init ram.		*/

.clear_loop:
	strb	r2, [r1], #1	/*  Clear byte at r1, advance to next	*/
	subs	r3, r3, #1	/*  One less to do			*/
	bgt	.clear_loop	/*  If not done go the next.		*/

.end_clear_loop:
	
	ldr	r1, .LC3	/*  __data_beg__ set in link script to 	*/
				/* point at beginning of initialized ram*/
	ldr 	r2, .LC4	/*  __data_beg_src__ set in link script	*/
				/* to point to beginning of flash copy 	*/
				/* of the initial values of initialized	*/
				/* variables.				*/
	ldr 	r3, .LC5	/*  __data_end__ set in link script to 	*/
				/* point at end of initialized ram	*/
	subs	r3, r3, r1	/*  Calculate length of area in ram	*/
				/* holding initialzed variables.	*/
	beq	.end_set_loop	/*  If no initialized vars skip init.	*/

.set_loop:
	ldrb	r4, [r2], #1	/* Read byte from flash (increment ptr),*/
	strb	r4, [r1], #1  	/* store it in ram (increment ptr) and, */
	subs	r3, r3, #1  	/* reduce bytes to copy by 1.		*/
	bgt 	.set_loop	/* Continue until all copied.		*/

.end_set_loop:

// Call C++ constructors.  The compiler and linker together populate the .ctors
// code section with the addresses of the constructor functions.

call_ctors:     ldr             r0, CTORS_BEG
                ldr             r1, CTORS_END
                subs            r1, r1, r0              // Length of ctors section
                beq             ctors_done              // Skip if no constructors

ctors_loop:     push            {r0,r1}                 // Save registers
		mov		r14, #ctors_pop		// Load return address
		ldr             pc, [r0]                // Load next constructor address
ctors_pop:      pop             {r0,r1}                 // Restore registers
		add		r0, r0, #4		// Advance pointer
                subs            r1, r1, #4              // Decrement counter
                bgt             ctors_loop              // Repeat until done
ctors_done:

	/*  Set up arguments to main and call.				*/

	mov		r0, #0		/*  no arguments  */
	mov		r1, #0		/* no argv either */

	bl		main

	/*  Returning from main in this environment is really an error.	*/
	/* Go into a dead loop.						*/
endless_loop:
	b		endless_loop

	/* For Thumb, constants must be after the code since only
	positive offsets are supported for PC relative addresses. */
	
	.align 4
.LC1:
.word	__bss_beg__
.LC2:
.word	__bss_end__
.LC3:
.word	__data_beg__
.LC4:
.word	__data_beg_src__
.LC5:
.word	__data_end__

CTORS_BEG:      .word           __ctors_start__
CTORS_END:      .word           __ctors_end__

//=============================================================================

// Use endless_loop for all exceptions and interrupts, unless another
// handler is provided elsewhere.

	.macro	IRQ handler
	.weak	\handler
	.set	\handler, endless_loop
	.endm

	IRQ	undefined_instruction_exception
	IRQ	software_interrupt_exception
	IRQ	prefetch_abort_exception
	IRQ	data_abort_exception
	IRQ	fast_interrupt_exception

// libstdc++ needs this

		.bss
__dso_handle:	.word
		.global		__dso_handle
		.weak		__dso_handle

		.end
