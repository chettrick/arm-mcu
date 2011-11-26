# GDB startup script for debugging a program in flash ROM

# $Id$

# Connect to the GDB server

target remote localhost:3333

# Display memory regions

info mem

# Break at beginning of main()

break main
continue
