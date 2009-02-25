# GDB startup script for debugging program in STR912FAW44 flash ROM

# $Id: debug.gdb,v 1.4 2009-02-25 18:06:02 cvs Exp $

# Connect to the OpenOCD server

target remote localhost:3333 

# Reset target & gain control

monitor soft_reset_halt
monitor wait_halt

# Bump up JTAG speed

monitor jtag_khz 3000

# Break at beginning of main()

break main
continue
