
                           ST-LINK Utility for Linux

   The STM32 Value Line Discovery board contains a secondary MCU
   programmed with the ST-LINK module code. The stlink-v1-flash program
   here may be used to flash the target MCU from Linux. It came from
   [1]here.
Usage: stlink-v1-flash /dev/stlink-v1  ...

Commands are:
  info version blink
  debug reg wreg= regs reset run step status
  erase= erase=all
  read write=
  flash:r: flash:w: flash:v:

Note: The STLink firmware does a flawed job of pretending to be a USB
 storage devices.  It may take several minutes after plugging in before
 it is usable.
 To speed up the process unplug the STLink and do:
sudo modprobe -r usb-storage &&
sudo modprobe usb-storage quirks=483:3744:lrwsro

   The ST-LINK module emulates a USB mass storage device, but does so in a
   very buggy and imperfect fashion. For a more detailed discussion, read
   [2]here.
     __________________________________________________________________

   Questions or comments to Philip Munts [3]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using the STM32F100R or other microcontrollers.

References

   1. http://code.google.com/p/arm-utilities/
   2. http://comments.gmane.org/gmane.linux.usb.general/34815
   3. mailto:phil@munts.net
