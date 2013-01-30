
                    ST STR91x ARM Microcontroller Framework

Credits

   The C run time startup code str912faw44.S and linker script
   str912faw44.ld originally came from the [1]Aeolus newlib-lpc package.
   Both have been modified by myself and the Aeolus copyright information
   removed, per their instructions.

   The support library in FWLib came from [2]www.st.com.

   The USB library in usb_serial also came from [3]www.st.com, with some
   modifications and additions by myself.

   Other files are original works by myself.

Memory Map (STR912FAW44)

   Code Flash: 0x00000000 to 0x0007FFFF 512 KB
   Data RAM:   0x04000000 to 0x04017FFF 96 KB

   The STR91x has two flash banks (main and secondary), either of which
   can be mapped to the reset vector at 0x00000000. I have elected to map
   the larger main flash bank to 0x00000000.

Other Devices

   This framework may be used for other devices in the ST STR91x family,
   provided the following files are modified:

   str91xxxx.ld The RAM and/or ROM sizes must match the device.
   str91xxxx.flashocd The parameters for the str9x flash_config command
   must match the device.
   str91xxxx.openocd The parameters for the flash command must match the
   device.

Test Platform

   This framework is validated on the [4]STMicro STR910-EVAL development
   board.

   Tested on 21 December 2012 with gcc 4.7.2.

   ARM9 devices like the STR91x are now considered legacy devices. The
   newer Cortex-M3 devices are much faster, cheaper, and easier to use. I
   will continue to maintain this framework for the STR91x, but will not
   be implementing any new features.
     __________________________________________________________________

   Questions or comments to Philip Munts [5]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using the STR91x or other microcontrollers.

References

   1. http://www.aeolusdevelopment.com/Articles/download.html
   2. http://www.st.com/
   3. http://www.st.com/
   4. http://www.st.com/internet/evalboard/product/116931.jsp
   5. mailto:phil@munts.net
