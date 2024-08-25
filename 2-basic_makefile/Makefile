#arm-none-eabi-gcc main.c startup.c ../vendor/STM32F1/Source/Templates/system_stm32f1xx.c -T linker_script.ld -o blink.elf -I ../vendor/CMSIS/CMSIS/Core/Include -I ../vendor/STM32F1/Include -mcpu=cortex-m3 -mthumb -nostdlib -DSTM32F103x6


CC=arm-none-eabi-gcc									#Compiler
CFLAGS=-mcpu=cortex-m3 -mthumb -nostdlib 				#Compiler flags

#Pre-processor flags
CPPFLAGS=-DSTM32F103x6	\
	-I ../vendor/CMSIS/CMSIS/Core/Include	\
	-I ../vendor/STM32F1/Include

LINKER_FILE=linker_script.ld
LDFLAGS=-T $(LINKER_FILE)								#Linker flags

all: blink.elf

blink.elf: main.o startup.o system_stm32f1xx.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o blink.elf

main.o: main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) main.c -c

startup.o: startup.c
	$(CC) $(CFLAGS) $(CPPFLAGS) startup.c -c

system_stm32f1xx.o: ../vendor/STM32F1/Source/Templates/system_stm32f1xx.c
	$(CC) $(CFLAGS) $(CPPFLAGS) ../vendor/STM32F1/Source/Templates/system_stm32f1xx.c -c
	

clean:
	rm -f *.o *.elf


# flashing

PROGRAMMER=openocd
PROGRAMMER_FLAGS=-f interface/stlink.cfg -f target/stm32f1x.cfg

flash: blink.elf
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program blink.elf verify reset exit"
