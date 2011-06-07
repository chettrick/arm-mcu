# GDB startup script for debugging program in AT91SAM7S flash ROM

# $Id$

# Start the OpenOCD server

shell make startocd

# Connect to the OpenOCD server

target remote localhost:3333

# Reset target & gain control

monitor gdb_breakpoint_override hard
monitor soft_reset_halt
monitor wait_halt
info mem

# Break at beginning of main()

break main
continue
