all::

CROSS_COMPILE = arm-none-eabi-

OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump

# Re-enable when we have asan support or use -fsanitize-undefined-trap-on-error
NO_SANITIZE = 1

ALL_CFLAGS  += -mcpu=cortex-m3 -mthumb -I.
ALL_LDFLAGS += -nostartfiles -Wl,-O1,--print-gc-sections,--gc-sections -Lld
ALL_ASFLAGS += -D__ASSEMBLER__=1

LDSCRIPT = ld/lm3s.ld

TARGETS = main.elf
obj-main.elf = init_vector.o init.o adc.o clock.o main.o
main.elf : $(LDSCRIPT) 
cflags-main.elf = -DLM3S3748=1 -include config/lm3s.h
ldflags-main.elf = -T $(LDSCRIPT)

define do-lst
all:: $(1).lst
TRASH += $(1).lst
endef

$(foreach obj,$(obj-main.elf),$(eval $(call do-lst,$(obj))))

all :: main.bin main.elf.lst

%.bin : %.elf
	$(OBJCOPY) -F binary $< $@

%.o.lst : %.o
	$(OBJDUMP) -d $< > $@

%.elf.lst : %.elf
	$(OBJDUMP) -d $< > $@

include base.mk
ALL_CFLAGS  += -Wextra -Os
