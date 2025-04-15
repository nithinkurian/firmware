target remote localhost:3333
monitor reset init
monitor flash write_image erase build/scons/stm32h743_nucleo_semi/firmware.elf
monitor arm semihosting enable
monitor reset halt
monitor resume
monitor exit
detach
quit
