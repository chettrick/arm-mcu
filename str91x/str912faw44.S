// Startup for STR912FAW44 ARM MCU

// $Id$

	.text
	.code 32 
	.align 	0

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
	.extern __ram_size__
	.extern __rom_size__
	.extern	__ctors_start__
	.extern	__ctors_end__

	.global	_start 

	.set INIT_FIQ_MODE,		0x11
	.set INIT_IRQ_MODE,		0x12
	.set INIT_SUPERVISOR_MODE,	0x13
	.set INIT_ABORT_MODE,		0x17
	.set INIT_UNDEFINED_MODE,	0x1B
	.set INIT_SYSTEM_MODE,		0x1F

	/**** Exception/Interrupt table ****/

	/*  defaults are defined in the link script.  The reserved	*/
	/* exception should be overridden by the download program 	*/

	b	_start
	b	Undefined_Handler
	b	SWI_Handler
	b	Prefetch_Handler
	b	Abort_Handler
	nop
	ldr	pc,[pc,#-0xFF0]	    	/* Vector via VIC		*/
	b	FIQ_Handler

/********************* start ********************************************/
/*  start (AKA _start, _mainCRTStartup) -- Gains control on reset and	*/
/* set up environment before running the operating C program. 		*/
_start: 

/* Configure SRAM size, based on what the linker tells us */

	ldr	r1, =0x5C002034		// SCU_SCR0
	ldr	r2, [r1]
	and	r2, r2, #0xFFFFFFE7
	ldr	r3, =__ram_size__
	sub	r3, r3, #32768
	orr	r2, r2, r3, LSR #12
	str	r2, [r1]

/* Configure ROM size, based on what the linker tells us */
/* We are only using the main flash blank for now */

	ldr	r1, =0x54000000		// FMI_BBSR
	ldr	r2, =__rom_size__
	ldr	r3, blocksize
	add	r2, r2, r3
	mov	r2, r2, LSR #15
	ldr	r3, =bbsrtable
	ldrb	r4, [r3, r2]
	str	r4, [r1]

	ldr	r1, =0x5400000C		// FMI_BBADR
	mov	r2, #0
	str	r2, [r1]

	ldr	r1, =0x54000018		// FMI_CR
	mov	r2, #8
	str	r2, [r1]

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
	
	.align 0
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

blocksize:
	.word 32767

bbsrtable:
	.byte 0, 0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4
	.byte 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5

//=============================================================================

// Use endless_loop for all exceptions and interrupts, unless another
// handler is provided elsewhere.

	.macro	IRQ handler
	.weak	\handler
	.set	\handler, endless_loop
	.endm

	IRQ	Undefined_Handler
	IRQ	SWI_Handler
	IRQ	Prefetch_Handler
	IRQ	Abort_Handler
	IRQ	FIQ_Handler
	IRQ	WDG_IRQHandler
	IRQ	SW_IRQHandler
	IRQ	ARMRX_IRQHandler
	IRQ	ARMTX_IRQHandler
	IRQ	TIM0_IRQHandler
	IRQ	TIM1_IRQHandler
	IRQ	TIM2_IRQHandler
	IRQ	TIM3_IRQHandler
	IRQ	USBHP_IRQHandler
	IRQ	USBLP_IRQHandler
	IRQ	SCU_IRQHandler
	IRQ	ENET_IRQHandler
	IRQ	DMA_IRQHandler
	IRQ	CAN_IRQHandler
	IRQ	MC_IRQHandler
	IRQ	ADC_IRQHandler
	IRQ	UART0_IRQHandler
	IRQ	UART1_IRQHandler
	IRQ	UART2_IRQHandler
	IRQ	I2C0_IRQHandler
	IRQ	I2C1_IRQHandler
	IRQ	SSP0_IRQHandler
	IRQ	SSP1_IRQHandler
	IRQ	LVD_IRQHandler
	IRQ	RTC_IRQHandler
	IRQ	WIU_IRQHandler
	IRQ	EXTIT0_IRQHandler
	IRQ	EXTIT1_IRQHandler
	IRQ	EXTIT2_IRQHandler
	IRQ	EXTIT3_IRQHandler
	IRQ	EXTIT4_IRQHandler
	IRQ	USBWU_IRQHandler
	IRQ	PFQBC_IRQHandler
	IRQ	DefaultVector_Handler
