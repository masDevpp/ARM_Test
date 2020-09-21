CC      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
LD      = arm-none-eabi-ld
OBJDUMP = arm-none-eabi-objdump
OBJCOPY = arm-none-eabi-objcopy

LINKERSCR = linker.scr

CCFLAGS = -c -Wall -march=armv7e-m -mcpu=cortex-m4 -mthumb

OBJS    = main.o vector.o vector_handler.o

BINDIR = bin

TARGET  = code.elf
DISASM  = code.dis
IMAGE   = code.img

all       :	$(TARGET) $(DISASM) $(IMAGE)

$(TARGET) :	$(OBJS) $(LINKERSCR)
			$(CC) $(OBJS) $(CCFLAGS)
			$(LD) $(OBJS) -T $(LINKERSCR) -o $(TARGET)

$(DISASM) :	$(TARGET)
			$(OBJDUMP) -d $(TARGET) > $(DISASM)

$(IMAGE)  :	$(TARGET)
			$(OBJCOPY) -O binary $(TARGET) $(IMAGE)

clean     : 
			rm --force $(OBJS) $(TARGET) $(DISASM) $(IMAGE)

header    : 
			$(OBJDUMP) $(TARGET) -h
