CC=arm-none-eabi-gcc
MACH=cortex-m7
SRC_DIR=src
HAL_DIR=bsp/stm32h743_nucleo
OUT_DIR=build/make
DST_DIR=build/make/$(SRC_DIR)
HAL_INC_DIR=$(SRC_DIR)/bsp/include
HAL_SRC_DIR=$(SRC_DIR)/$(HAL_DIR)
HAL_DST_DIR=$(DST_DIR)/$(HAL_DIR)
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0 -g3 -ggdb -Isrc/include -I$(HAL_INC_DIR)
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T $(SRC_DIR)/stm32_ls.ld -Wl,-Map=$(OUT_DIR)/firmware.map

all: $(DST_DIR)/main.o  $(DST_DIR)/stm32_startup.o $(DST_DIR)/syscalls.o $(DST_DIR)/led.o $(HAL_DST_DIR)/hal_gpio.o  $(HAL_DST_DIR)/hal_cpu.o $(OUT_DIR)/firmware.elf

$(DST_DIR)/main.o: $(SRC_DIR)/main.c
	mkdir -p $(DST_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(DST_DIR)/stm32_startup.o: $(SRC_DIR)/stm32_startup.c
	mkdir -p $(DST_DIR)
	$(CC) $(CFLAGS) -o $@ $^
	
$(DST_DIR)/syscalls.o: $(SRC_DIR)/syscalls.c
	mkdir -p $(DST_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(DST_DIR)/led.o: $(SRC_DIR)/led.c
	mkdir -p $(DST_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(HAL_DST_DIR)/hal_gpio.o: $(HAL_SRC_DIR)/hal_gpio.c
	mkdir -p $(HAL_DST_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(HAL_DST_DIR)/hal_cpu.o: $(HAL_SRC_DIR)/hal_cpu.c
	mkdir -p $(HAL_DST_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OUT_DIR)/firmware.elf: $(DST_DIR)/main.o $(DST_DIR)/stm32_startup.o $(DST_DIR)/syscalls.o $(DST_DIR)/led.o $(HAL_DST_DIR)/hal_gpio.o $(HAL_DST_DIR)/hal_cpu.o
	mkdir -p $(DST_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf $(DST_DIR)/*.o $(DST_DIR)/*.elf $(DST_DIR)/*.map $(DST_DIR)/*.o $(HAL_DST_DIR)/*.o $(DST_DIR)/*.elf
	
openocd:
	openocd -f board/st_nucleo_h743zi.cfg
load:
	arm-none-eabi-gdb --command=flash_make.gdb
