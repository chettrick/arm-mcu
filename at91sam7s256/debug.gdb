# GDB startup script for debugging program in AT91SAM7S256 flash ROM

# $Id: debug.gdb,v 1.1 2008-01-09 21:04:06 cvs Exp $

# Connect to the OpenOCD server

target remote localhost:3333 

# Reset target & gain control

monitor soft_reset_halt
monitor wait_halt

# We can't use software breakpoints because we are running from ROM

monitor arm7_9 force_hw_bkpts enable

# Break at beginning of main()

break main
continue
