CC      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
LD      = arm-none-eabi-ld
OBJDUMP = arm-none-eabi-objdump
OBJCOPY = arm-none-eabi-objcopy

CCFLAGS = -c -Wall
LDFLAGS = -T linker.scr

OBJS    = main.o startup.o

BINDIR = bin

TARGET  = code.elf
DISASM  = code.dis
IMAGE   = code.img

all       :	$(TARGET) $(DISASM) $(IMAGE)

$(TARGET) :	$(OBJS)
			$(CC) $(OBJS) $(CCFLAGS)
			$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET)

$(DISASM) :	$(TARGET)
			$(OBJDUMP) -d $(TARGET) > $(DISASM)

$(IMAGE)  : $(TARGET)
			$(OBJCOPY) -O binary $(TARGET) $(IMAGE)

clear     : 
			rm --force $(OBJS) $(TARGET) $(DISASM) $(IMAGE)

header    :
			$(OBJDUMP) $(TARGET) -h