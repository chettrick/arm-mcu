# GDB startup script for debugging program in STM32F103 flash ROM

# $Id$

# Connect to the OpenOCD server

target remote localhost:3333

# Reset target & gain control

monitor soft_reset_halt
monitor wait_halt
info mem

# Break at beginning of main()

break main
continue
