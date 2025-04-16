target remote localhost:3333
monitor reset init
monitor flash write_image erase build/scons/STH7N001S/firmware.elf
monitor arm semihosting enable
monitor reset halt
monitor resume
monitor exit
detach
quit
