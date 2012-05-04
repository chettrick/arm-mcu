/* Linker script for STM32F407VG Cortex-M4 ARM MCU */

/* $Id$ */

MEMORY
{
  flash (rx)  : ORIGIN = 0x00000000, LENGTH = 1024K
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
  ccm (rwx) : ORIGIN = 0x10000000, LENGTH = 64K
}

__rom_start__	= ORIGIN(flash);
__rom_size__	= LENGTH(flash);
__ram_start__	= ORIGIN(ram);
__ram_size__	= LENGTH(ram);
__ram_end__     = __ram_start__ + __ram_size__;
__stack_end__   = __ram_end__;          /* Top of RAM */
__stack_size__  = 16K;
__stack_start__ = __stack_end__ - __stack_size__;
__heap_start__  = __bss_end__;          /* Between bss and stack */
__heap_end__    = __stack_start__;
__ccm_start__	= ORIGIN(ccm);
__ccm_size__	= LENGTH(ccm);

SECTIONS
{
  . = 0;

  .text : {
  *(.text*)				/* Program code */
  KEEP(*(.rodata*))			/* Read only data */
  *(.glue_7)
  *(.glue_7t)
  *(.eh_frame)
  . = ALIGN(4);
  __ctors_start__ = .;
  KEEP(*(.init_array));			/* C++ constructors */
  KEEP(*(.ctors));			/* C++ constructors */
  __ctors_end__ = .;
  . = ALIGN(16);
  __text_end__ = .;
  } >flash

  .data : ALIGN(16) {
  __data_beg__ = .;			/* Used in crt0.S */
  *(.data)				/* Initialized data */
  __data_end__ = .;			/* Used in crt0.S */
  } >ram AT > flash 

  .bss : ALIGN(16) {
  __bss_beg__ = .;			/* Used in crt0.S */
  *(.bss)				/* Uninitialized data */
  *(COMMON)				/* Common data */
  __bss_end__ = .;			/* Used in crt0.S */
  } >ram

/* C++ exception unwinding stuff--needed by some toolchains */

  .ARM.extab : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >flash

  __exidx_start = .;
  .ARM.exidx : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } >flash
  __exidx_end = .;
}  

/*  Libraries to link against. */

INPUT( -lstm32f407vg )
