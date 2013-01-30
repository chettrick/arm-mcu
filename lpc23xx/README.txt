
            NXP (nee Philips) LPC23xx ARM Microcontroller Framework

Credits

   The C run time startup code lpc23xx.S and linker script lpc23xx.ld
   originally came from the [1]Aeolus newlib-lpc package. Both have been
   modified by myself and the Aeolus copyright information removed, per
   their instructions.

   The I/O register definition file lpc23xx.h came from NXP.

   Other files are original works by myself.

Memory Map (LPC2368/78)

   Code Flash: 0x00000000 to 0x0007FFFF 512 KB
   Data RAM:   0x40000000 to 0x40007FFF 32 KB

   Although the LPC23xx has provision for remapping the interrupt vectors
   to RAM, I have elected not to use this feature.

Other Devices

   This framework may be used for other devices in the NXP LPC23xx family,
   provided the following files are modified:

   lpc23xx.ld The RAM size may need be changed.

Test Platform

   This framework is validated on the [2]mbed LPC2368 and [3]Olimex
   LPC-P2378 development boards.

   Tested on 21 December 2012 with gcc 4.7.2.

   ARM7 devices like the LPC23xx are now considered legacy devices. The
   newer Cortex-M3 devices are much faster, cheaper, and easier to use. I
   will continue to maintain this framework for the LPC23xx, but will not
   be implementing any new features.
     __________________________________________________________________

   Questions or comments to Philip Munts [4]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using the LPC23xx or other microcontrollers.

References

   1. http://www.aeolusdevelopment.com/Articles/download.html
   2. http://mbed.org/handbook/mbed-NXP-LPC2368
   3. http://www.olimex.com/dev/lpc-p2378.html
   4. mailto:phil@munts.net
