PREFIX=
ARCH=$(PREFIX)arm-none-eabi-

CC=$(ARCH)gcc
RM=rm -rf
CCLD=$(CC)
OBJCOPY=$(ARCH)objcopy
OBJDUMP=$(ARCH)objdump

ARCH_CFLAGS = -DLM3S3748=1 -mcpu=cortex-m3 -mthumb

override CFLAGS  = -Wall -Wextra -ggdb3 -Os
override LDFLAGS = -nostartfiles -Wl,-O1,--print-gc-sections,--gc-sections
ASFLAGS=-D__ASSEMBLER__

ALL_CFLAGS = $(ARCH_CFLAGS) $(CFLAGS)
ALL_LDFLAGS = $(LDFLAGS)

ifneq ($(LTO),)
ALL_CFLAGS += -flto
ALL_LDFLAGS += $(CFLAGS) -fwhole-program -fuse-linker-plugin
endif


LDSCRIPT=armv7m.ld

.SECONDARY:

all : main.elf
main.elf : init_vector.c.o init.c.o adc.c.o clock.c.o main.c.o

%.S.o : %.S
	$(CC) $(ALL_CFLAGS) $(ASFLAGS) -c -o $@ $<

%.c.o : %.c
	$(CC) $(ALL_CFLAGS) -c -o $@ $<

%.elf : $(LDSCRIPT)
	$(CCLD) $(ALL_LDFLAGS) -T $(LDSCRIPT) -o $@ $(filter-out $(LDSCRIPT),$^)

%.bin : %.elf
	$(OBJCOPY) -F binary $< $@

%.lst : %.bin
	$(OBJDUMP) -d $< > $@

%.elf.lst : %.elf
	$(OBJDUMP) -d $< > $@

.PHONY: clean
clean:
	$(RM) *.o *.elf *.bin *.lst
