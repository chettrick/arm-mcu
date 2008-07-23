# GDB startup script for debugging program in STR912FAW44 flash ROM

# $Id: debug.gdb,v 1.3 2008-07-23 20:42:29 cvs Exp $

# Connect to the OpenOCD server

target remote localhost:3333 

# Reset target & gain control

monitor soft_reset_halt
monitor wait_halt

# Bump up JTAG speed

monitor jtag_khz 3000

# We can't use software breakpoints because we are running from ROM

monitor arm7_9 force_hw_bkpts enable

# Break at beginning of main()

break main
continue
