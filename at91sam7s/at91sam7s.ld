/* Linker script for AT91SAM7S ARM MCU */

/* $Id$ */

/* Copyright (C)2013, Philip Munts, President, Munts AM Corp.			*/
/* All rights reserved.								*/
/*										*/
/* Redistribution and use in source and binary forms, with or without		*/
/* modification, are permitted provided that the following conditions are met:	*/
/*										*/
/* * Redistributions of source code must retain the above copyright notice,	*/
/*   this list of conditions and the following disclaimer.			*/
/*										*/
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"	*/
/* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE	*/
/* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE	*/
/* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE	*/
/* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR		*/
/* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF		*/
/* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS	*/
/* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN	*/
/* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)	*/
/* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE	*/
/* POSSIBILITY OF SUCH DAMAGE.							*/

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
  . = 0;				/*  Start at address 0.		*/

  code : {
    KEEP(*(.startup))			/* Startup sections are first.  */
    *(.text*)				/* Program (.text) sections     */
    *(.gnu.linkonce.t.*)
    KEEP(*(.rodata* .gnu.linkonce.r.*))	/* are next, then constant data.*/
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)
    . = ALIGN(4);
    __ctors_start__ = .;
    KEEP(*(.init_array))		/* C++ constructors */
    KEEP(*(.ctors))			/* C++ constructors */
    __ctors_end__ = .;
    . = ALIGN(16);
    __data_beg_src__ = .;		/* Used by startup.	*/
  } >flash

/*  Initialized data, located in ram but a copy is placed	*/
/* in flash so it can be used to init the ram on startup.	*/

  data : ALIGN(16) {
    __data_beg__ = .;			/* Used by startup.	*/
    *(.data)
    *(.gnu.linkonce.d.*)
    __data_end__ = .;			/* Used by startup.	*/
  } >ram AT>flash

/*  Unitialized data, located in ram, no copy in flash needed	*/
/* since startup will zero associated area in RAM.		*/

  bss (NOLOAD) : ALIGN(16) {
    __bss_beg__ = .;			/* Used by startup.	*/
    *(.bss)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    __bss_end__ = .;			/* Used by startup.	*/
  } >ram

/* C++ exception unwinding stuff--needed by some toolchains */

  .ARM.extab : {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } >flash

__exidx_start = .;
  .ARM.exidx : {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } >flash
__exidx_end = .;
}

/* Firmware entry point */

ENTRY(_start)

/* Libraries to link against. */

INPUT( -lat91sam7s )
