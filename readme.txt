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
rtos sources to seperate script
rtos : freertos
need to create gdb script also
delay until
notification
Queue
Software timer


need to improve timer_manager in custom
continue
timer 
UART
I2C
SPI
USB
pc test
need to add support for make : haerachial make
free rtos simulator
target dll
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
debugging using IDE
Emacs + GDB
Need to add trace support
named pipe for hal simulation.
another application to connect over named pipe to visualize