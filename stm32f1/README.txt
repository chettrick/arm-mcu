               ST STM32F1 Cortex-M3 ARM Microcontroller Framework

Credits

   The C run time startup code stm32f1xxxx.S and linker script
   stm32f1xxxx.ld were written by myself based on various examples on the
   Internet and in [1]The Definitive Guide to the ARM Cortex-M3.

   Other files are original works by myself.

Memory Map (STM32F107RB)

   Code Flash: 0x00000000 to 0x0003FFFF 256 KB
   Data RAM:   0x20000000 to 0x2000FFFF 64 KB

   The STM32F1 microcontrollers can have any of code flash at 0x08000000,
   system memory (serial boot loader) at 0x1FFFF000, or data ram at
   0x20000000 mapped to address 0x00000000, depending on the BOOT0 and
   BOOT1 pins. This framework assumes BOOT0 is strapped low, mapping code
   flash to 0x00000000.

   This framework assumes a single stack for both thread and handler
   modes, using MSP (Main Stack Pointer) at the top of RAM. The C heap is
   placed at the end of BSS data.

Other Devices

   This framework may be used for other devices in the ST STM32F1 family,
   provided the following files are modified:

   stm32f1xxxx.ld The RAM and ROM sizes must match the device.

Notes

   The limited amount of RAM available in the STM32F100RB on the STM32
   Value Line Discovery board requires using the conio facility instead of
   stdio, so -DCONIO_STDIO is defined in stm32f1.mk.

Test Platform

   This framework is validated on the [2]Olimex STM32-P103, [3]Olimex
   STM32-P107, and [4]STM32 Value Line Discovery development boards.

   Tested on 9 August 2013 with gcc 4.8.1.
     __________________________________________________________________

   Questions or comments to Philip Munts [5]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using the STM32F1 or other microcontrollers.

References

   1. http://www.amazon.com/Definitive-Guide-Cortex-M3-Embedded-Technology/dp/0750685344
   2. http://www.olimex.com/dev/stm32-p103.html
   3. http://www.olimex.com/dev/stm32-p107.html
   4. http://www.st.com/stm32-discovery
   5. mailto:phil@munts.net
