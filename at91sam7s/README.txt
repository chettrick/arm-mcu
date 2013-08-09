                 Atmel AT91SAM7S ARM Microcontroller Framework

Credits

   The C run time startup code at91sam7s.S and linker script at91sam7s.ld
   originally came from the [1]Aeolus newlib-lpc package. Both have been
   modified by myself and the Aeolus copyright information removed, per
   their instructions.

   The support library in at91lib came from [2]www.at91.com.

   Other files are original works by myself.

Memory Map (AT91SAM7S512)

   Code Flash: 0x00000000 to 0x0007FFFF 512 KB
   Data RAM:   0x00200000 to 0x0020FFFF 64 KB

   Although the AT91SAM7S has provision for remapping the RAM to
   0x00000000 and flash to 0x00100000 after system startup, I have elected
   not to use this feature.

Other Devices

   This framework may be used for the AT91SAM7S256 and AT91SAM7S512
   devices. It may be used for other devices in the Atmel AT91SAM7S
   family, provided the following files are modified:

   at91sam7s.ld The RAM size may need be changed.

Test Platform

   This framework is validated on an [3]Olimex SAM7-P256 development
   board.

   Tested on 9 August 2013 with gcc 4.8.1.

Legacy Status

   ARM7 devices like the AT91SAM7S are now considered legacy devices. The
   newer Cortex-M3 devices are much faster, cheaper, and easier to use. I
   will continue to maintain this framework for the AT91SAM7S, but will
   not be implementing any new features.
     __________________________________________________________________

   Questions or comments to Philip Munts [4]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using the AT91SAM7S or other microcontrollers.

References

   1. http://www.aeolusdevelopment.com/Articles/download.html
   2. http://www.at91.com/
   3. http://www.olimex.com/dev/sam7-p256.html
   4. mailto:phil@munts.net
