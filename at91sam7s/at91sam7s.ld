/* Linker script for AT91SAM7S ARM MCU */

/* $Id$ */

MEMORY {
  flash : ORIGIN = 0x00000000, LENGTH = 512K
  ram : ORIGIN = 0x00200000, LENGTH = 64K
  }

__rom_start__ = ORIGIN(flash);
__rom_size__ = LENGTH(flash);
__ram_start__ = ORIGIN(ram);
__ram_size__ = LENGTH(ram);

__STACK_SIZE_FIQ__ = 0x100;
__STACK_SIZE_IRQ__ = 0x100;
__STACK_SIZE_SUPERVISOR__ = 0x4;
__STACK_SIZE_ABORT__ = 0x4;
__STACK_SIZE_UNDEFINED__ = 0x4;

__stack_size__ = 16K;
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

__heap_start__ = __bss_end__; /* Heap is between bss and stack */
__heap_end__ = __stack_beg__;

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
	. = ALIGN(4);
	__ctors_start__ = .;
	KEEP(*(.init_array));		/* C++ constructors */
	KEEP(*(.ctors));		/* C++ constructors */
	__ctors_end__ = .;
	} >flash

/* C++ exception unwinding stuff--needed by Code Sourcery toolchain */

.ARM.extab : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >flash

__exidx_start = .;
.ARM.exidx : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } >flash
__exidx_end = .;

. = ALIGN(4);
__data_beg_src__ = .;				/* Used by startup.	*/

	/*  Initialized data, located in ram but a copy is placed	*/
	/* in flash so it can be used to init the ram on startup.	*/
 .data : {
	. = ALIGN(4);
	__data_beg__ = .;			/* Used by startup.	*/
 	*(.data)
	. = ALIGN(4);
	__data_end__ = .;			/* Used by startup.	*/
 	} >ram AT>flash

	/*  Unitialized data, located in ram, no copy in flash needed	*/
	/* since startup will zero associated area in RAM.		*/
 .bss : {
	. = ALIGN(4);
	__bss_beg__ = .;			/* Used by startup.	*/
 	*(.bss)
	*(COMMON)
	. = ALIGN(4);
	__bss_end__ = .;			/* Used by startup.	*/
 	} >ram

. = ALIGN(4);
end = .;
}

/* Libraries to link against. */

INPUT( -lat91sam7s )
