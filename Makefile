CC=arm-none-eabi-gcc
MACH=cortex-m7
SRC_DIR=src
DST_DIR=build/make
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T $(SRC_DIR)/stm32_ls.ld -Wl,-Map=$(DST_DIR)/firmware.map

all: $(DST_DIR)/$(SRC_DIR)/main.o  $(DST_DIR)/$(SRC_DIR)/stm32_startup.o $(DST_DIR)/$(SRC_DIR)/syscalls.o $(DST_DIR)/firmware.elf

$(DST_DIR)/$(SRC_DIR)/main.o: $(SRC_DIR)/main.c
	mkdir -p $(DST_DIR)/$(SRC_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(DST_DIR)/$(SRC_DIR)/stm32_startup.o: $(SRC_DIR)/stm32_startup.c
	mkdir -p $(DST_DIR)/$(SRC_DIR)
	$(CC) $(CFLAGS) -o $@ $^
	
$(DST_DIR)/$(SRC_DIR)/syscalls.o: $(SRC_DIR)/syscalls.c
	mkdir -p $(DST_DIR)/$(SRC_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(DST_DIR)/firmware.elf: $(DST_DIR)/$(SRC_DIR)/main.o $(DST_DIR)/$(SRC_DIR)/stm32_startup.o $(DST_DIR)/$(SRC_DIR)/syscalls.o
	mkdir -p $(DST_DIR)/$(SRC_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf $(DST_DIR)/*.o $(DST_DIR)/*.elf $(DST_DIR)/*.map $(DST_DIR)/$(SRC_DIR)/*.o $(DST_DIR)/$(SRC_DIR)/*.elf
	
openocd:
	openocd -f board/st_nucleo_h743zi.cfg
load:
	arm-none-eabi-gdb --command=flash_make.gdb
