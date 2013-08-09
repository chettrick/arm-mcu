       NXP (nee Philips) LPC11xx ARM Cortex-M0 Microcontroller Framework

Credits

   The C run time startup code lpc11xxxx.S and linker script lpc11xxxx.ld
   were written by myself based on various examples on the Internet and in
   [1]The Definitive Guide to the ARM Cortex-M3.

   The [2]CMSIS library came from [3]NXP, with some minor customization by
   myself.

   Other files are original works by myself.

Memory Map (LPC1114/102)

   Code Flash: 0x00000000 to 0x00007FFF 32 KB
   Data RAM:   0x10000000 to 0x10000FFF 4 KB

Other Devices

   This framework may be used for other devices in the NXP LPC11xx family,
   provided the following files are modified:

   lpc11xxxx.ld The RAM size may need be changed.

Notes

   The limited amount of RAM available in these devices requires using the
   conio I/O facility instead of stdio, so -DCONIO_STDIO is defined in
   lpc11xx.mk.

Test Platform

   This framework is validated on the [4]Raspberry Pi LPC1114 I/O
   Processor expansion board and a bare [5]LPC1114FN28/102 plugged into a
   solderless breadboard.

   Tested on 9 August 2013 with gcc 4.8.1.
     __________________________________________________________________

   Questions or comments to Philip Munts [6]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using the LPC11xx or other microcontrollers.

References

   1. http://www.amazon.com/Definitive-Guide-Cortex-M3-Embedded-Technology/dp/0750685344
   2. http://www.arm.com/products/processors/cortex-m/cortex-microcontroller-software-interface-standard.php
   3. http://ics.nxp.com/support/lpcxpresso
   4. http://tech.munts.com/MCU/Frameworks/RaspberryPi/expansion/LPC1114
   5. http://www.nxp.com/products/microcontrollers/cortex_m0/lpc1100_x_l/LPC1114FN28.html
   6. mailto:phil@munts.net
