CC      = arm-none-eabi-g++
AS      = arm-none-eabi-as
LD      = arm-none-eabi-ld
OBJDUMP = arm-none-eabi-objdump
OBJCOPY = arm-none-eabi-objcopy
WRITER  = "C:/Program Files (x86)/STMicroelectronics/STM32 ST-LINK Utility/ST-LINK Utility/ST-LINK_CLI.exe"

LINKERSCR = linker.scr

CCFLAGS = -c -Wall -march=armv7e-m+fp -mcpu=cortex-m4 -mthumb -fno-exceptions

CODES   = main.cpp vector.s vector_handler.s LED.cpp Startup.cpp Timer.cpp SerialHandler.cpp
OBJ     = *.o

BINDIR = bin

TARGET  = code.elf
DISASM  = code.dis
IMAGE   = code.bin

all       :	$(TARGET) $(DISASM) $(IMAGE)

$(TARGET) :	$(CODES) $(LINKERSCR)
			$(CC) $(CODES) $(CCFLAGS)
			$(LD) $(OBJ) -T $(LINKERSCR) -o $(TARGET)

$(DISASM) :	$(TARGET)
			$(OBJDUMP) -d $(TARGET) > $(DISASM)

$(IMAGE)  :	$(TARGET)
			$(OBJCOPY) -O binary $(TARGET) $(IMAGE)

clean     : 
			rm --force $(OBJ) $(TARGET) $(DISASM) $(IMAGE)

header    : 
			$(OBJDUMP) $(TARGET) -h

sym       :
			$(OBJDUMP) $(TARGET) -t | grep \.data
			$(OBJDUMP) $(TARGET) -t | grep \.bss

write     : $(IMAGE)
			$(WRITER) -P $(IMAGE) 0x08000000
			$(WRITER) -Rst