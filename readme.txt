ToDo
------------	
version control :git
build system 	: scons,make

- build using make
- build same using scons

- automate loading
	make load 
	gdb commands
		arm-none-eabi-gdb
			(gdb) target remote localhost:3333
			(gdb) monitor reset init
			(gdb) monitor flash write_image erase gpio_test.elf
			(gdb) monitor reset halt
			(gdb) monitor resume
			(gdb) monitor halt

minimal SEM32H743 application
Abstraction with HAL
Event driven pc testing
UART intergration
Serial Protocol for communication to PC
bootloader over UART
BinaryLoader component runs in mcu for writting binary to flash 
BinaryFlasher PC tool for flashing
USB support for Bootloader
PC Tool for symbol viewing : Symbol Viewer Tool
PC Tool Parameter Viewer Tool
Wireshark pluggin to sniff
CI-CD
