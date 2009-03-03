# GDB startup script for debugging program in AT91SAM7S256 flash ROM

# $Id: debug.gdb,v 1.3 2009-03-03 17:19:48 cvs Exp $

# Connect to the OpenOCD server

target remote localhost:3333 
info mem

# Reset target & gain control

monitor soft_reset_halt
monitor wait_halt

# Break at beginning of main()

break main
continue
