
                      ARM Microcontroller Toolchain Notes

   This toolchain includes binutils, gcc, newlib, and insight gdb. It may
   be built for Windows (using Cygwin) and for Linux. The Windows and
   Linux releases are virtually identical in every respect. (This is the
   reason I created my own toolchain: I routinely flip back and forth
   between Windows and Linux development environments.)

   My toolchain builds multilibs for the various Cortex-Mx devices,
   including hardware floating point for the Cortex-M4. (I don't bother
   patching the multilibs for the legacy ELF toolchain anymore.)

   I build my releases on a Scientific Linux 6 machine.

   I have now switched to EABI, but it is still possible (as of GCC 4.7.2)
   to build an ELF toolchain with make ABI=elf
   GCCEXTRACONFIG=--enable-obsolete.
     __________________________________________________________________

   Questions or comments to Philip Munts [1]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using ARM or other microcontrollers.

References

   1. mailto:phil@munts.net
