target remote localhost:3333
monitor reset init
monitor flash write_image erase ##Firmware##
monitor reset halt
monitor resume
