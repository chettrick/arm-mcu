# GDB startup script for debugging program in STR91x flash ROM

# $Id$

# Connect to the OpenOCD server

target remote localhost:3333

# Reset target & gain control

monitor reset halt
monitor wait_halt
info mem

# Bump up JTAG speed

monitor jtag_khz 3000

# Break at beginning of main()

break main
continue
