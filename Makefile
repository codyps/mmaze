PREFIX?=
ARCH=$(PREFIX)arm-none-eabi-
CC=$(ARCH)gcc
OBJCOPY=$(ARCH)objcopy

CFLAGS=
LDFLAGS=

main.elf : init.c.o

%.c.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

%.elf :
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<
