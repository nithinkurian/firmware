target remote localhost:3333
monitor reset init
monitor flash write_image erase build/make/stm32h743_nucleo/firmware.elf
monitor reset halt
monitor resume
monitor exit
detach
quit
