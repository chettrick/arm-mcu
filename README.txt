               ARM Microcontroller Firmware Development Framework

   Here is a framework for developing firmware for a number of [1]ARM
   (Advanced RISC Machine) architecture single chip microcontrollers.

   Each MCU directory includes startup code, linker script, [2]newlib
   syscall bindings, and [3]OpenOCD scripts for debugging and flashing.

   The ARM7 and ARM9 devices supported here must now be considered legacy
   devices. The Cortex-Mx devices are clearly the future for ARM
   microcontrollers. I will therefore be concentrating future efforts on
   the Cortex-Mx microcontroller families.

News

     * 7 June 2011 -- Massive reorganization around MCU families.
     * 8 June 2011 -- Added EFM32 family with support for EFM32-G8XX-STK.
     * 11 June 2011 -- Added abstract LED driver for all targets.
     * 15 June 2011 -- Added abstract GPIO pin driver for all Cortex-M3
       targets.
     * 13 July 2011 -- Validated all targets with GCC 4.6.1.
     * 15 July 2011 -- Moved all FreeRTOS sources to common directory.
     * 31 August 2011 -- Added support for WizNet W5200E01-M3 and its
       STM32F103C8 (the W5200 driver is still WIP).
     * 19 September 2011 -- Fixed longstanding bug with errno handling in
       driver modules like device.c and serial.c.
     * 26 September 2011 -- Created common library directory. Moved common
       source files to it and common include files to the include
       directory.
     * 6 October 2011 -- Added compiler and linker flags to permit dead
       code removal.
     * 20 October 2011 -- Major overhaul of the device abstraction layer.
       Device settings (such as serial port baud rate) can now be appended
       to the device name.
     * 3 November 2011 -- Upgraded GCC to 4.6.2.
     * 4 November 2011 -- Moved the burgeoning number of utility programs
       to a new subdirectory, [4]utilities. Started adding support for the
       STM32F4 Cortex-M4 family.
     * 15 November 2011 -- Upgraded OpenOCD to 0.5.0. Cleaned up a lot of
       the OpenOCD scripts at the same time.
     * 18 November 2011 -- Performed a full regression test, all programs
       on all targets with all flash programming methods. Renamed stm32 to
       stm32f1.
     * 28 November 2011 -- Overhauled all the debug scripts. Debugging
       with GDB and OpenOCD, J-Link, and St-Link now works for all
       targets. Added support for user button(s) for every target board
       that has button(s). Finished porting to the STM32F4 family and the
       STM32F4 Discovery evaluation board.
     * 29 November 2011 -- Another big overhaul of make files. All of the
       various flash and debug rules have been sucked out of ARM.mk and
       the MCU dependent make files and separated into adapter specific
       make files in the include subdirectory.
     * 30 November 2011 -- Did another full regression test, concentrating
       on GDB infrastructure. Corrected a number of minor annoyances.
       OpenOCD is robust. J-Link and ST-Link can be finicky.
     * 2 December 2011 -- Removed CMSIS directories. Replaced each CMSIS
       directory with an import of the MCU's vendor supplied CMSIS and/or
       peripheral library distribution.
     * 7 December 2011 -- Reworked _sbrk_r in syscalls.c and all of the
       linker scripts to bound the heap area.
     * 9 January 2012 -- Downloaded and tested latest [5]Code Sourcery,
       [6]devkitARM, and [7]Yagarto toolchains. Neither devkitARM nor
       Yagarto latest releases appear to work from Cygwin makefiles
       anymore.
     * 28 March 2012 -- Allow building the toolchain with elf or eabi ABI.
       Upgraded GCC to 4.7.0.
     * 16 April 2012 -- Added support for C++ to all the header files.
       Added a C++ suffix rule to ARM.mk
     * 23 April 2012 -- Moved as many test programs as possibile to the
       demos directory.
     * 4 May 2012 -- Fixed the toolchain builder to build Cortex-Mx
       multilibs properly. Changed the default compiler ABI from elf to
       eabi. Fixed a really nasty link problem with EABI toolchains, by
       reordering code sections.
     * 7 May 2012 -- Finished another big regression test, with Code
       Sourcery, my own, and devkitARM toolchains. Both C and C++ programs
       can be built, but C++ iostreams does not work yet. Most testing was
       with GCC 4.7.0.
     * 18 June 2012 -- Switched from reentrant syscalls to namespace clean
       non-reentrant syscalls. These conflict with libsysbase.a in the
       devkitARM toolchain. I haven't figured out how to exclude
       libsysbase.a yet, so the devkitARM toolchain doesn't work anymore.
     * 17 July 2012 -- Implemented system tick emulation for AT91SAM7S,
       LPC23xx, and STR91x targets. Now demos/test_systick.c works on
       these targets.
     * 7 August 2012 -- Changed the EABI toolchain package name to
       "arm-tools" and the target name to "arm-non-eabi".
     * 3 September 2012 -- Added a lightweight console I/O facility.
     * 4 September 2012 -- Fixed some minor alignment issues in each of
       the assembler startup files.
     * 6 September 2012 -- Removed the huge LPC17xx driver library, in
       favor of the much smaller CMSIS library.
     * 14 September 2012 -- I have done a lot of tweaking for the
       lightweight console I/O facility, to absolutely minimize RAM
       consumption. Added support for the [8]LPC1114FN28/102 Cortex-M0
       microcontroller in the 28-pin DIP package. At $1.26 ([9]Avnet
       Express), it is quite a deal, for the first (that I have ever been
       able to buy) socketable 32-bit microcontroller.
     * 3 October 2012 -- Finished the support for the LCP1114FN28.
       Upgraded OpenOCD to 0.6.0.
     * 8 October 2012 -- Upgraded GCC to 4.7.2. Upgraded GDB to 7.5
       Upgraded OpenOCD to 0.6.1.
     * 8 November 2012 -- Upgraded binutils to 2.23.
     * 26 November 2012 -- Added LPC17xx USB serial port device support.
     * 21 December 2012 -- Upgraded binutils to 2.23.1, newlib to 2.0.0,
       and gdb to 7.5.1.
     * 2 January 2013 -- Added STM32F4 USB serial port device support.
       Fixed some bugs in device.c
     * 4 January 2013 -- Enabled USB serial port console by default for
       boards that support it (BlueBoard LPC1768, FEZ Cerb40, STM32F4
       Discovery).
     * 15 January 2013 -- Added copyright and license information to all
       orignal works. See below for the license text. Link to [10]git
       repository on [11]SourceForge.
     * 23 Janauary 2013 -- Cleaned up SPI code. Added SPI slave mode for
       LPC11xx.
     * 25 January 2013 -- Added A/D converter support for LPC11xx. A/D
       support for other processors will follow.
     * 30 January 2013 -- Added Minimal Standard Random Number Generator.
     * 9 February 2013 -- Added lightweight implementations of atoi() and
       strerror() to conio.c. Also added code to issue linker warnings if
       the newlib reentrancy structure or heap are used with the
       lightweight console I/O facility.
     * 22 February 2013 -- Added a high-efficiency pinwise GPIO pin driver
       for the LPC11xx.
     * 4 April 2013 -- Upgraded the STM32F4 peripheral libarary from
       V1.0.1 to V1.1.0.
     * 9 April 2013 -- Cleaned up the makefile structure to make it easier
       to build applications and libraries out of tree.
     * 10 April 2013 -- Added support for Netduino 2 and Netduino Plus 2.
       Added preliminary support for LPC1768-Mini-DK2.
     * 11 April 2013 -- Reworked linker scripts and makefiles to include
       run time startup code in the MCU dependent library. Also did a lot
       of general cleaning up of makefiles. Add RMAKEFLAGS and
       CONSOLEFLAGS macros.
     * 12 April 2013 -- Rationalize the use of stdarg.h, stdbool.h,
       stddef.h, and stdint.h. These are now included in arm.h instead of
       here, there, and everywhere.
     * 15 April 2013 -- Upgraded binutils to 2.23.2 and gcc to 4.7.3. Add
       capability for building a toolchain package for [12]OpenBSD.
     * 26 July 2013 -- Major rework of the conio lightweight console
       library. It now uses services from device.c instead of duplicating
       them. Also cleaned up and rationalized header file includes
       throught. Eliminated some compiler warnings from LPC17xx and
       STM32F4 peripheral libraries.
     * 1 August 2013 -- More major rework of the console libraries. Added
       support for OpenOCD semihosting console. Added support for using
       the conio lightweight I/O library with USB and semihosting.
     * 6 August 2013 -- Upgraded OpenOCD to 0.7.0. Upgraded GCC to 4.8.1.
       Upgraded GDB to 7.6.
     * 7 August 2013 -- Removed support for the obsolete BlueBoard USB
       boot loader. Removed support for the various STM32 programming
       utilities, since OpenOCD works better on the ST-Link adapters
       anyway. Use OpenOCD on ST-Link V2 for all STM32 targets.
     * 14 August 2013 -- Added support for the Mikroelektronika
       [13]MINI-M4-STM32.
     * 24 December 2013 -- Upgraded to binutils 2.24, gcc 4.8.2, newlib
       2.1.0, and gdb 7.6.2. Merry Christmas!

Git Repository

   The source code is hosted on [14]SourceForge at
   [15]http://sourceforge.net/p/arm-mcu/code.

   Use one of the following commands to clone it:
git clone --depth 1 git://git.code.sf.net/p/arm-mcu/code  ARM
git clone --depth 1 http://git.code.sf.net/p/arm-mcu/code ARM

Copyright:

   Original works herein are copyrighted as follows:

Copyright (C)2013-2014, Philip Munts, President, Munts AM Corp.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

   Redistributed works herein are copyrighted and/or licensed by their
   respective authors.
     __________________________________________________________________

   Questions or comments to Philip Munts [16]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using these ARM microcontrollers.

References

   1. http://www.arm.com/
   2. http://sourceware.org/newlib/
   3. http://openocd.sourceforge.net/
   4. http://tech.munts.com/MCU/Frameworks/ARM/utilities
   5. http://www.mentor.com/embedded-software/sourcery-tools/sourcery-codebench/editions/lite-edition
   6. http://sourceforge.net/projects/devkitpro/files/devkitARM
   7. http://sourceforge.net/projects/yagarto
   8. http://www.nxp.com/products/microcontrollers/cortex_m0/lpc1100_x_l/LPC1114FN28.html
   9. http://avnetexpress.avnet.com/store/em/EMController/_/A-5003286402656/An-0?action=part
  10. http://git-scm.com/
  11. http://sourceforge.net/
  12. http://www.openbsd.org/
  13. http://www.mikroe.com/mini/stm32
  14. http://sourceforge.net/
  15. http://sourceforge.net/p/arm-mcu/code
  16. mailto:phil@munts.net

