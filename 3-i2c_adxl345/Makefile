# Variables
CC=arm-none-eabi-gcc                                   # Compiler
CFLAGS=-mcpu=cortex-m3 -mthumb -nostdlib               # Compiler flags

# Pre-processor flags
CPPFLAGS=-DSTM32F103x6  \
    -I ../vendor/CMSIS/CMSIS/Core/Include \
    -I ../vendor/STM32F1/Include \
    -I i2c/include \
	-I adxl345/include

LINKER_FILE=linker_script.ld
LDFLAGS=-T $(LINKER_FILE)                              # Linker flags

PROJECT_NAME=i2c_adxl345
# Directories
BUILD_DIR=build

# Targets
all: $(BUILD_DIR)/$(PROJECT_NAME).elf

$(BUILD_DIR)/$(PROJECT_NAME).elf: $(BUILD_DIR)/main.o $(BUILD_DIR)/startup.o $(BUILD_DIR)/system_stm32f1xx.o $(BUILD_DIR)/i2c.o $(BUILD_DIR)/adxl345.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/main.o: main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(BUILD_DIR)/startup.o: startup.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(BUILD_DIR)/system_stm32f1xx.o: ../vendor/STM32F1/Source/Templates/system_stm32f1xx.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

# Use the correct path for the i2c.c file
$(BUILD_DIR)/i2c.o: i2c/i2c.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(BUILD_DIR)/adxl345.o: adxl345/adxl345.c | $(BUILD_DIR)
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
