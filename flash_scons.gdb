target remote localhost:3333
monitor reset init
monitor flash write_image erase build/scons/firmware.elf
monitor reset halt
monitor resume
monitor exit
detach
quit
