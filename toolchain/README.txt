                      ARM Microcontroller Toolchain Notes

   This toolchain includes binutils, gcc, newlib, and insight gdb. It may
   be built for Linux, OpenBSD, and Windows (using Cygwin). The Linux,
   OpenBSD, and Windows releases are virtually identical in every respect.
   (This is the reason I created my own toolchain: I routinely flip back
   and forth among Linux, OpenBSD, and Windows development environments.)

   My toolchain builds multilibs for the various Cortex-Mx devices,
   including hardware floating point for the Cortex-M4.

   I build my releases on a Scientific Linux 6 machine.
     __________________________________________________________________

   Questions or comments to Philip Munts [1]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using ARM or other microcontrollers.

References

   1. mailto:phil@munts.net
