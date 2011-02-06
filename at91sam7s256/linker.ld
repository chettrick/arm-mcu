/* Linker script for AT91SAM7S256 ARM MCU */

/* $Id$ */

MEMORY {
  flash : ORIGIN = 0x00000000, LENGTH = 256K
  ram : ORIGIN = 0x00200000, LENGTH = 64K
  }

__rom_start__ = 0x00000000;
__rom_size__ = 256K;
__ram_start__ = 0x00200000;
__ram_size__ = 64K;

__STACK_SIZE_FIQ__ = 0x100;
__STACK_SIZE_IRQ__ = 0x100;
__STACK_SIZE_SUPERVISOR__ = 0x4;
__STACK_SIZE_ABORT__ = 0x4;
__STACK_SIZE_UNDEFINED__ = 0x4;

__stack_size__ = 4096;
__stack_end__ = __ram_start__ + __ram_size__ - 4 - __STACK_SIZE_FIQ__ - 
	__STACK_SIZE_IRQ__ - __STACK_SIZE_SUPERVISOR__ - __STACK_SIZE_ABORT__ -
	__STACK_SIZE_UNDEFINED__;
__stack_beg__ = __stack_end__ - __stack_size__;
__stack_end_undefined__ = __ram_start__ + __ram_size__ - 4 - __STACK_SIZE_FIQ__ - 
	__STACK_SIZE_IRQ__ - __STACK_SIZE_SUPERVISOR__ - __STACK_SIZE_ABORT__;
__stack_end_abort__ = __ram_start__ + __ram_size__ - 4 - __STACK_SIZE_FIQ__ - 
	__STACK_SIZE_IRQ__ - __STACK_SIZE_SUPERVISOR__;
__stack_end_supervisor__ = __ram_start__ + __ram_size__ - 4 - __STACK_SIZE_FIQ__ - 
	__STACK_SIZE_IRQ__;
__stack_end_irq__ = __ram_start__ + __ram_size__ - 4 - __STACK_SIZE_FIQ__;
__stack_end_fiq__ = __ram_start__ + __ram_size__ - 4;


SECTIONS {
 . = 0;					/*  Start at address 0.		*/
 startup : { *(.startup)} >flash	/*  Place startup first.	*/

 prog : {				/*  Program (.text) sections 	*/
 	*(.text)			/* are next, then constant data.*/
	*(.rodata)
	*(.rodata*)
	*(.glue_7)
	*(.glue_7t)
	*(.eh_frame)
 	} >flash

/* C++ exception unwinding stuff--needed by Code Sourcery toolchain */

.ARM.extab : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >flash

__exidx_start = .;
.ARM.exidx : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } >flash
__exidx_end = .;

__end_of_text__ = .;			/*  Used by startup to find 	*/
					/* initialized vars.		*/

	/*  Initialized data, located in ram but a copy is placed	*/
	/* in flash so it can be used to init the ram on startup.	*/
 .data : { 
	__data_beg__ = .;			/* Used by startup.	*/
	__data_beg_src__ = __end_of_text__;	/* Used by startup.	*/
 	*(.data)
	__data_end__ = .;			/* Used by startup.	*/
 	} >ram AT>flash

	/*  Unitialized data, located in ram, no copy in flash needed	*/
	/* since startup will zero associated area in RAM.		*/
 .bss : { 
	. = ALIGN(4);
	__bss_beg__ = .;	/*  Used by startup to find start of	*/
				/* unitialized variables.		*/
 	*(.bss)
	*(COMMON)
	. = ALIGN(4);
	__bss_end__ = .;
 	} >ram

. = ALIGN(4);
end = .;
}

/* Libraries to link against. */

INPUT( -lat91sam7s256 )

/* Provide a default vector for any unhandled interrupts. */

PROVIDE(undefined_instruction_exception = endless_loop);
PROVIDE(software_interrupt_exception = endless_loop);
PROVIDE(prefetch_abort_exception = endless_loop);
PROVIDE(data_abort_exception = endless_loop);
PROVIDE(fast_interrupt_exception = endless_loop);
