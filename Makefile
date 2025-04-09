CC=arm-none-eabi-gcc
MACH=cortex-m7
SRC_DIR=src
HAL_DIR=BSP/STM32H743
DST_DIR=build/make
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0 -g3 -ggdb -I$(SRC_DIR)/$(HAL_DIR)
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T $(SRC_DIR)/stm32_ls.ld -Wl,-Map=$(DST_DIR)/firmware.map

all: $(DST_DIR)/$(SRC_DIR)/main.o  $(DST_DIR)/$(SRC_DIR)/stm32_startup.o $(DST_DIR)/$(SRC_DIR)/syscalls.o $(DST_DIR)/$(SRC_DIR)/led.o $(DST_DIR)/$(SRC_DIR)/$(HAL_DIR)/hal_gpio.o $(DST_DIR)/firmware.elf

$(DST_DIR)/$(SRC_DIR)/main.o: $(SRC_DIR)/main.c
	mkdir -p $(DST_DIR)/$(SRC_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(DST_DIR)/$(SRC_DIR)/stm32_startup.o: $(SRC_DIR)/stm32_startup.c
	mkdir -p $(DST_DIR)/$(SRC_DIR)
	$(CC) $(CFLAGS) -o $@ $^
	
$(DST_DIR)/$(SRC_DIR)/syscalls.o: $(SRC_DIR)/syscalls.c
	mkdir -p $(DST_DIR)/$(SRC_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(DST_DIR)/$(SRC_DIR)/led.o: $(SRC_DIR)/led.c
	mkdir -p $(DST_DIR)/$(SRC_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(DST_DIR)/$(SRC_DIR)/$(HAL_DIR)/hal_gpio.o: $(SRC_DIR)/$(HAL_DIR)/hal_gpio.c
	mkdir -p $(DST_DIR)/$(SRC_DIR)/$(HAL_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(DST_DIR)/firmware.elf: $(DST_DIR)/$(SRC_DIR)/main.o $(DST_DIR)/$(SRC_DIR)/stm32_startup.o $(DST_DIR)/$(SRC_DIR)/syscalls.o $(DST_DIR)/$(SRC_DIR)/led.o $(DST_DIR)/$(SRC_DIR)/$(HAL_DIR)/hal_gpio.o
	mkdir -p $(DST_DIR)/$(SRC_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf $(DST_DIR)/*.o $(DST_DIR)/*.elf $(DST_DIR)/*.map $(DST_DIR)/$(SRC_DIR)/*.o $(DST_DIR)/$(SRC_DIR)/$(HAL_DIR)/*.o $(DST_DIR)/$(SRC_DIR)/*.elf
	
openocd:
	openocd -f board/st_nucleo_h743zi.cfg
load:
	arm-none-eabi-gdb --command=flash_make.gdb
