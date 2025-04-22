target remote localhost:3333
monitor reset init
monitor flash write_image erase build/scons/STM32H743N_CUSTR_001/firmware.elf
monitor reset halt
monitor resume
monitor exit
detach
quit
