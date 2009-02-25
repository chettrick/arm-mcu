# GDB startup script for debugging program in AT91SAM7S256 flash ROM

# $Id: debug.gdb,v 1.2 2009-02-25 18:47:18 cvs Exp $

# Connect to the OpenOCD server

target remote localhost:3333 

# Reset target & gain control

monitor soft_reset_halt
monitor wait_halt

# Break at beginning of main()

break main
continue
