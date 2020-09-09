CC      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
LD      = arm-none-eabi-ld
OBJDUMP = arm-none-eabi-objdump

CFLAGS  = -c -Wall
LDFLAGS = -T linker.scr

OBJS    = main.o startup.o

BINDIR = bin

TARGET  = code.elf
DISASM  = code.dis

all		  :	$(TARGET) $(DISASM)

$(TARGET) :	$(OBJS)
			$(CC) $(OBJS) $(CFLAGS)
			$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET)

$(DISASM) : $(TARGET)
			$(OBJDUMP) -d $(TARGET) > $(DISASM)

clean	  : 
			rm --force $(OBJS) $(TARGET) $(DISASM)

header	  :
			$(OBJDUMP) $(TARGET) -h