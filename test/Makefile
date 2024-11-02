# Variables
CC=arm-none-eabi-gcc                                   # Compiler
CFLAGS=-mcpu=cortex-m3 -mthumb               # Compiler flags

# Pre-processor flags
CPPFLAGS=-DSTM32F103x6  \
    -I ../vendor/CMSIS/CMSIS/Core/Include \
    -I ../vendor/STM32F1/Include \

LINKER_FILE=linker_script.ld
LDFLAGS=-T $(LINKER_FILE)                              # Linker flags

PROJECT_NAME=basic_test
# Directories
BUILD_DIR=build

# Targets
all: $(BUILD_DIR)/$(PROJECT_NAME).elf

$(BUILD_DIR)/$(PROJECT_NAME).elf: $(BUILD_DIR)/main.o $(BUILD_DIR)/startup.o $(BUILD_DIR)/system_stm32f1xx.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/main.o: main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(BUILD_DIR)/startup.o: startup.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(BUILD_DIR)/system_stm32f1xx.o: ../vendor/STM32F1/Source/Templates/system_stm32f1xx.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@


# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

# Flashing
PROGRAMMER=openocd
PROGRAMMER_FLAGS=-f interface/stlink.cfg -f target/stm32f1x.cfg

flash: $(BUILD_DIR)/$(PROJECT_NAME).elf
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program $< verify reset exit"
