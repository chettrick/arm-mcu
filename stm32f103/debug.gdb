# GDB startup script for debugging program in STM32F103 flash ROM

# $Id: debug.gdb,v 1.3 2009-03-03 17:32:36 cvs Exp $

# Connect to the OpenOCD server

target remote localhost:3333 

# Reset target & gain control

monitor soft_reset_halt
monitor wait_halt
info mem

# Break at beginning of main()

break main
continue
