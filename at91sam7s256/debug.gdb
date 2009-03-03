# GDB startup script for debugging program in AT91SAM7S256 flash ROM

# $Id: debug.gdb,v 1.4 2009-03-03 17:29:17 cvs Exp $

# Connect to the OpenOCD server

target remote localhost:3333 

# Reset target & gain control

monitor soft_reset_halt
monitor wait_halt
info mem

# Break at beginning of main()

break main
continue
