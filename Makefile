CC      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
LD      = arm-none-eabi-ld
OBJDUMP = arm-none-eabi-objdump
OBJCOPY = arm-none-eabi-objcopy

LINKERSCR = linker.scr

CCFLAGS = -c -Wall

OBJS    = main.o startup.o

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
