# 1.Board
- STM32H743ZI Nucleo
- PC

# 2.RTOS
RTOS support : https://en.wikipedia.org/wiki/Comparison_of_real-time_operating_systems

## 2.1 Supported Features
- notification
- Queue
- Software timer
- semaphores
- delay
- delay until

### *2.1.1 Planned*
- task priority

## 2.2 Supported RTOSes
- custom
- FreeRTOS
- x86 pthread

### *2.2.1 Planned*
- μC/OS-III
- ThreadX
- Zephyr
- Mynewt


# 3. Build Environment

## 3.1 Build System
- scons
- make

## 3.2 Loading
- automated loading using gdb

## 3.3 Debugging
- Loading and debugging using gdb

## 3.4 Planned
- PC test
- rtos simulator
- target dll
- Event driven pc testing
- make : haerachial make - fix make
- Emacs + GDB
- trace support
- SWV over commandline
- debugging using IDE
- named pipe for hal simulation.


# 4. Firmware Features
- Abstraction with HAL
- clock/clock init
- semi hosting
- fault handling/ handlers

## *4.2 Plannned*
- bootloader over UART,USB
- Serial Protocol for communication to PC
- Need to improve x86 tick interval to ms


# 5. Peripherals
## 5.1 Planned
- GPIO
- Timer
- UART
- I2C
- SPI
- USB

# 6. Tools
## 6.1 Planned
- PC Tool for symbol viewing : Symbol Viewer Tool
- PC Tool Parameter Viewer Tool
- Wireshark pluggin to sniff
- GUI application to connect over named pipe to visualize
- BinaryFlasher PC tool for flashing over boot loader

# 7. CI-CD
TBD

# Links
https://www.markdownguide.org/cheat-sheet/


