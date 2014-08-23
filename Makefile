all::

CROSS_COMPILE = arm-none-eabi-

OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump

# Re-enable when we have asan support or use -fsanitize-undefined-trap-on-error
NO_SANITIZE = 1

ALL_CPPFLAGS += -mcpu=cortex-m3 -I.
ALL_CFLAGS  += $(ALL_CPPFLAGS) -std=gnu11 -Wno-main
ALL_LDFLAGS += -nostartfiles -Wl,-O1,--print-gc-sections,--gc-sections -Lld
ALL_ASFLAGS += -D__ASSEMBLER__=1

obj-libubsan.a = ubsan_simple.c.o

LDSCRIPT = ld/armv7m.lds

lds_S = $(wildcard ld/*.lds.S)
lds = $(lds_S:.S=)

TARGETS = main.elf
obj-main.elf = init_vector.o init.o lm3s/adc.o lm3s/clock.o main.o
main.elf : $(lds)
ALL_CPPFLAGS += -DLM3S3748=1 -include config/lm3s.h
ALL_LDFLAGS += -T $(LDSCRIPT)

define do-lst
all:: $(1).lst
TRASH += $(1).lst
endef


ON_EACH_OBJ += do-lst

all :: main.bin main.elf.lst

define extra-rules
$(call debug,extra-rules)

$(2)/%.lds : %.lds.S
	$(CPP) $(ALL_CPPFLAGS) -P -C -o $@ $<

$(2)/%.bin : $(2)/%.elf
	$(OBJCOPY) -F binary $< $@

$(2)/%.o.lst : $(2)/%.o
	$(OBJDUMP) -d $< > $@

$(2)/%.elf.lst : $(2)/%.elf
	$(OBJDUMP) -d $< > $@
endef

ON_EACH_VARIANT += extra-rules

include base.mk
ALL_CFLAGS  += -Wextra -Os
