# GDB startup script for debugging program in STM32F103 flash ROM

# $Id: debug.gdb,v 1.2 2009-02-25 19:10:14 cvs Exp $

# Connect to the OpenOCD server

target remote localhost:3333 

# Reset target & gain control

monitor soft_reset_halt
monitor wait_halt

# Break at beginning of main()

break main
continue
