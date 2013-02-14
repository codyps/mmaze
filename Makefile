PREFIX=
ARCH=$(PREFIX)arm-none-eabi-

CC=$(ARCH)gcc
RM=rm -rf
CCLD=$(CC)
OBJCOPY=$(ARCH)objcopy
OBJDUMP=$(ARCH)objdump

override CFLAGS=-DLM3S3748 -Wall -Wextra -ggdb -Wno-main -Os -mcpu=cortex-m3 -mthumb -flto
LDFLAGS=-nostartfiles -Wl,-O1,--print-gc-sections,--gc-sections -flto -fwhole-program
ASFLAGS=-D__ASSEMBLER__

LDSCRIPT=lm3s.ld

.SECONDARY:

all : main.elf
main.elf : crt0.S.o init.c.o adc.c.o clock.c.o main.c.o

%.S.o : %.S
	$(CC) $(CFLAGS) $(ASFLAGS) -c -o $@ $<

%.c.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.elf :
	$(CCLD) $(CFLAGS) $(LDFLAGS) -T $(LDSCRIPT) -o $@ $^

%.bin : %.elf
	$(OBJCOPY) -F binary $< $@

%.lst : %.bin
	$(OBJDUMP) -d $< > $@

%.elf.lst : %.elf
	$(OBJDUMP) -d $< > $@

.PHONY: clean
clean:
	$(RM) *.o *.elf *.bin *.lst
