PREFIX=
ARCH=$(PREFIX)arm-none-eabi-
CC=$(ARCH)gcc
OBJCOPY=$(ARCH)objcopy

CFLAGS=-DLM3S3748
LDFLAGS=-nostartfiles
ASFLAGS=-D__ASSEMBLER__

LDSCRIPT=lm3s.ld

main.elf : crt0.S.o

%.S.o : %.S
	$(CC) $(CFLAGS) $(ASFLAGS) -c -o $@ $<

%.c.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.elf :
	$(CC) $(CFLAGS) $(LDFLAGS) -T $(LDSCRIPT) -o $@ $<

.PHONY: clean
clean:
	$(RM) *.o
