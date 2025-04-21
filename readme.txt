ToDo
------------	
version control :git
build system 	: scons,make
- build using make
- build same using scons
- automate loading using gdb
Abstraction with HAL
x86 version also
clock/clock init
semi hosting
fault handling/ handlers
targets in sconstruct
custom rtos
x86 version of rtos


task create apis to be created and used
idle task to be moved inside, may be weak, config to enable
continue m3m4
debug -> semi , release : merge targets
need to add support for make
target dll

freertos
osal should be added osal.h
timer 
UART
I2C
SPI
USB
pc test
may be qemu
freertos simulator
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
MQTT over USB
debugging microcontroller using gdb, souce file visualization
SWV over commandline

RTOS support : https://en.wikipedia.org/wiki/Comparison_of_real-time_operating_systems
	custom
	FreeRTOS
	μC/OS-III
	ThreadX
	Zephyr
	Mynewt
OSAL layer is needed

