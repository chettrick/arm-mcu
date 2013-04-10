               ST STM32F4 Cortex-M4 ARM Microcontroller Framework

Credits

   The C run time startup code stm32f4xxxx.S and linker script
   stm32f4xxxx.ld were written by myself based on various examples on the
   Internet and in [1]The Definitive Guide to the ARM Cortex-M3.

   Other files are original works by myself.

Memory Map (STM32F407VG)

   Code Flash: 0x00000000 to 0x000FFFFF 1024 KB
   Data RAM:   0x20000000 to 0x2001FFFF 128 KB
   CCM RAM:    0x10000000 to 0x1000FFFF 64 KB

   The STM32F4 microcontrollers can have any of code flash at 0x08000000,
   system memory (serial boot loader) at 0x1FFF0000, or data ram at
   0x20000000 mapped to address 0x00000000, depending on the BOOT0 and
   BOOT1 pins. This framework assumes BOOT0 is strapped low, mapping code
   flash to 0x00000000.

   This framework assumes a single stack for both thread and handler
   modes, using MSP (Main Stack Pointer) at the top of RAM. The C heap is
   placed at the end of BSS data.

   Note: CCM RAM is inaccessible to peripherals (DMA/Ethernet/USB).

Other Devices

   This framework may be used for other devices in the ST STM32F4 family,
   provided the following files are modified:

   stm32f4xxxx.ld The RAM and ROM sizes must match the device.

Test Platform

   This framework is validated on the [2]STM32F4 Discovery, [3]FEZ Cerb40,
   and [4]Netduino Plus 2 development boards.

   Tested on 10 April 2013 with gcc 4.7.2.
     __________________________________________________________________

   Questions or comments to Philip Munts [5]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using the STM32F4 or other microcontrollers.

References

   1. http://www.amazon.com/Definitive-Guide-Cortex-M3-Embedded-Technology/dp/0750685344
   2. http://www.st.com/internet/evalboard/product/252419.jsp
   3. http://www.ghielectronics.com/catalog/product/353
   4. http://netduino.com/netduinoplus2/specs.htm
   5. mailto:phil@munts.net
