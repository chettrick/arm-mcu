
                      BlueBoard LPC1768-H USB Boot Loader

   This directory contains an optional secondary USB boot loader
   customized for the [1]NGX BlueBoard LPC1768-H development board. After
   this USB bootloader has been written to the lowest two sectors of
   flash, it will flash an LED and wait for an SW2 button press for a few
   seconds after reset. If a button press is detected, the USB boot loader
   will begin running and turn the BlueBoard into a USB mass storage
   device to which a new user firmware image may be copied.

   This USB boot loader image came from [2]GV's Works, where you can find
   more detailed information about its operation.

   [3]Fedora Linux and other modern Linux distributions automatically
   create a mount point directory under /media when a USB mass storage
   device like the BlueBoard USB boot loader is inserted. The mount point
   directory name is derived from the volume label on the USB mass storage
   device, if available. Unfortunately, this USB boot loader synthesizes
   the volume label on the fly and uses different names depending on CRP
   settings.

   Install [4]50-nxp-lpc-usb-boot.rules to /etc/udev/rules.d and
   [5]50-nxp-lpc-usb-boot.helper to /usr/local/libexec. These [6]udev
   rules and helper script (available in [7]utilities/udev) automatically
   create and delete a symbolic link /media/LPC17xx pointing to the actual
   mount point directory. This allows Makefile's and other automation
   scripts to copy firmware to /media/LPC17xx regardless of the actual
   mount point directory name.
     __________________________________________________________________

   Questions or comments to Philip Munts [8]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using the LPC17xx or other microcontrollers.

References

   1. http://shop.ngxtechnologies.com/product_info.php?products_id=65
   2. http://gvworks.blogspot.com/2010/10/usb-bootloader-for-blueboard.html
   3. http://fedoraproject.org/
   4. file://localhost/storage/home/pmunts/src/ARM/lpc17xx/BlueBoard/50-nxp-lpc-usb-boot.rules
   5. file://localhost/storage/home/pmunts/src/ARM/lpc17xx/BlueBoard/50-nxp-lpc-usb-boot.helper
   6. http://www.kernel.org/pub/linux/utils/kernel/hotplug/udev.html
   7. file://localhost/storage/home/pmunts/src/ARM/utilities/udev
   8. mailto:phil@munts.net
