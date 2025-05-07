# 1.Board
- STM32H743ZI Nucleo
- PC

# 2.RTOS

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
- Custom RTOS
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

## *3.4 Planned*
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
- Testing source to seperate place


# 4. Firmware Features
- Abstraction with HAL
- clock/clock init
- semi hosting
- fault handling/ handlers

## *4.2 Planned*
- bootloader over UART,USB
- Serial Protocol for communication to PC
- Need to improve x86 tick interval to ms
- C++


# 5. Peripherals
## 5.1 Planned
- GPIO
- UART
- Timer
- I2C
- SPI
- USB
- DMA
- FLASH
- RTC
- Ethernet
- CRC
- Hardware Semaphore
- TCM
- Watch dog

# 6. Tools
## *6.1 Planned*
- PC Tool for symbol viewing : Symbol Viewer Tool
- PC Tool Parameter Viewer Tool
- Wireshark pluggin to sniff
- GUI application to connect over named pipe to visualize
- BinaryFlasher PC tool for flashing over boot loader

# 7. CI-CD
TBD

# Links
[Mark Down Cheatsheet](https://www.markdownguide.org/cheat-sheet/)

[Mark Down Sublime Package](https://packagecontrol.io/packages/MarkdownLivePreview)

[RTOS support](https://en.wikipedia.org/wiki/Comparison_of_real-time_operating_systems)