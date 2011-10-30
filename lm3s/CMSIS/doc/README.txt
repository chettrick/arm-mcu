This directory contains the CMSIS core files from Keil, version 1.10.
These files were modified by Luminary Micro in order to allow compilation
using gcc if the ansi or c99 standard switches are used.  The modifications
that were made are shown below:


Index: core_cm3.c
===================================================================
--- core_cm3.c    (revision 15)
+++ core_cm3.c    (working copy)
@@ -35,7 +35,7 @@
   #define __nop           __no_operation   /*!< no operation intrinsic in iarcc */

 #elif defined (  __GNUC__  )
-  #define __ASM             asm            /*!< asm keyword for gcc            */
+  #define __ASM             __asm          /*!< asm keyword for gcc            */
   #define __INLINE          inline         /*!< inline keyword for gcc         */
 #endif

Index: core_cm3.h
===================================================================
--- core_cm3.h    (revision 15)
+++ core_cm3.h    (working copy)
@@ -297,7 +297,7 @@
   #define __NOP           __no_operation                              /*!< no operation intrinsic in IAR Compiler */

 #elif defined   (  __GNUC__  )
-  #define __ASM            asm                                        /*!< asm keyword for GNU Compiler          */
+  #define __ASM            __asm                                      /*!< asm keyword for GNU Compiler          */
   #define __INLINE         inline                                     /*!< inline keyword for GNU Compiler       */

 #endif
