/* Linker script for STR912FAW44 microcontroller */

/* $Id: linker.ld,v 1.9 2008-08-20 13:45:15 cvs Exp $ */

MEMORY {
  flash : ORIGIN = 0x00000000, LENGTH = 512K
  ram : ORIGIN = 0x04000000, LENGTH = 96K
  }

__rom_start__ = 0x00000000;
__rom_size__ = 512K;
__ram_start__ = 0x04000000;
__ram_size__ = 96K;

__STACK_SIZE_FIQ__ = 0x100;
__STACK_SIZE_IRQ__ = 0x100;
__STACK_SIZE_SUPERVISOR__ = 0x4;
__STACK_SIZE_ABORT__ = 0x4;
__STACK_SIZE_UNDEFINED__ = 0x4;

__stack_end__ = __ram_start__ + __ram_size__ - 4 - __STACK_SIZE_FIQ__ - 
	__STACK_SIZE_IRQ__ - __STACK_SIZE_SUPERVISOR__ - __STACK_SIZE_ABORT__ -
	__STACK_SIZE_UNDEFINED__;
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

INPUT( -lstr912faw44 )

/* The following interrupt service routines have been extracted from 91x_it.h */

PROVIDE(Undefined_Handler = endless_loop);
PROVIDE(SWI_Handler = endless_loop);
PROVIDE(Prefetch_Handler = endless_loop);
PROVIDE(Abort_Handler = endless_loop);
PROVIDE(FIQ_Handler = endless_loop);
PROVIDE(WDG_IRQHandler = endless_loop);
PROVIDE(SW_IRQHandler = endless_loop);
PROVIDE(ARMRX_IRQHandler = endless_loop);
PROVIDE(ARMTX_IRQHandler = endless_loop);
PROVIDE(TIM0_IRQHandler = endless_loop);
PROVIDE(TIM1_IRQHandler = endless_loop);
PROVIDE(TIM2_IRQHandler = endless_loop);
PROVIDE(TIM3_IRQHandler = endless_loop);
PROVIDE(USBHP_IRQHandler = endless_loop);
PROVIDE(USBLP_IRQHandler = endless_loop);
PROVIDE(SCU_IRQHandler = endless_loop);
PROVIDE(ENET_IRQHandler = endless_loop);
PROVIDE(DMA_IRQHandler = endless_loop);
PROVIDE(CAN_IRQHandler = endless_loop);
PROVIDE(MC_IRQHandler = endless_loop);
PROVIDE(ADC_IRQHandler = endless_loop);
PROVIDE(UART0_IRQHandler = endless_loop);
PROVIDE(UART1_IRQHandler = endless_loop);
PROVIDE(UART2_IRQHandler = endless_loop);
PROVIDE(I2C0_IRQHandler = endless_loop);
PROVIDE(I2C1_IRQHandler = endless_loop);
PROVIDE(SSP0_IRQHandler = endless_loop);
PROVIDE(SSP1_IRQHandler = endless_loop);
PROVIDE(LVD_IRQHandler = endless_loop);
PROVIDE(RTC_IRQHandler = endless_loop);
PROVIDE(WIU_IRQHandler = endless_loop);
PROVIDE(EXTIT0_IRQHandler = endless_loop);
PROVIDE(EXTIT1_IRQHandler = endless_loop);
PROVIDE(EXTIT2_IRQHandler = endless_loop);
PROVIDE(EXTIT3_IRQHandler = endless_loop);
PROVIDE(EXTIT4_IRQHandler = endless_loop);
PROVIDE(USBWU_IRQHandler = endless_loop);
PROVIDE(PFQBC_IRQHandler = endless_loop);
PROVIDE(DefaultVector_Handler = endless_loop);

/* Some toolchains require _isatty() */

PROVIDE(_isatty = isatty);
