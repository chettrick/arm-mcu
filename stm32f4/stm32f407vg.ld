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
__ccm_start__	= ORIGIN(ccm);
__ccm_size__	= LENGTH(ccm);

__heap_start__	= __ccm_start__;
__stack_end__	= __ccm_start__ + __ccm_size__;

SECTIONS
{
  . = 0;

  .text : {
  *(.text)				/* Program code */
  *(.rodata)				/* Read only data */
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

  . = ALIGN(4);
  __text_end__ = .;

  .data : {
  . = ALIGN(4);
  __data_beg__ = .;			/* Used in crt0.S */
  *(.data)				/* Initialized data */
  . = ALIGN(4);
  __data_end__ = .;			/* Used in crt0.S */
  } >ram AT > flash 

  .bss : {
  . = ALIGN(4);
  __bss_beg__ = .;			/* Used in crt0.S */
  *(.bss)				/* Uninitialized data */
  *(COMMON)				/* Common data */
  . = ALIGN(4);
  __bss_end__ = .;			/* Used in crt0.S */
  } >ram

  . = ALIGN(4);
  end = .;
}  

/*  Libraries to link against. */

INPUT( -lstm32f407vg )
