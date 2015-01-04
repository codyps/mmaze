all::

CROSS_COMPILE = arm-none-eabi-

OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump

# Re-enable when we have asan support or use -fsanitize-undefined-trap-on-error
NO_SANITIZE = 1

ALL_CPPFLAGS += -mcpu=cortex-m3 -mthumb -I.
ALL_CFLAGS  += $(ALL_CPPFLAGS) -std=gnu11 -Wno-main
ALL_LDFLAGS += -nostartfiles -Wl,-O1,--print-gc-sections,--gc-sections -Lld
ALL_ASFLAGS += -D__ASSEMBLER__=1

obj-libubsan.a = ubsan_simple.c.o

LDSCRIPT = ld/armv7m.lds

lds_S = $(wildcard ld/*.lds.S)
lds = $(lds_S:.S=)

TARGET_BIN = main.elf
obj-main.elf = init_vector.c.o init.c.o lm3s/adc.c.o lm3s/clock.c.o main.c.o
main.elf : $(lds)
ALL_CPPFLAGS += -DLM3S3748=1 -include config/lm3s.h
ALL_LDFLAGS += -T $(LDSCRIPT)

define do-lst
all:: $(1).lst
TRASH += $(1).lst
endef
ON_EACH_OBJ += do-lst

define var-target
all :: $(2)/main.bin $(2)/main.elf.lst
endef
ON_EACH_VARIANT += var-target

define extra-rules
$(call debug,extra-rules)

$(2)/%.lds : %.lds.S
	$$(call q,LDS,$$@)$$(CPP) $$(ALL_CPPFLAGS) -P -C -o $$@ $$<

$(2)/%.bin : $(2)/%.elf
	$$(call q,OBJCOPY,$$@)$$(OBJCOPY) -F binary $$< $$@

$(2)/%.c.o.lst : $(2)/%.c.o
	$$(call q,OBJDUMP,$$@)$$(OBJDUMP) -d $$< > $$@

$(2)/%.elf.lst : $(2)/%.elf
	$$(call q,OBJDUMP,$$@)$$(OBJDUMP) -d $$< > $$@
endef
ON_EACH_VARIANT += extra-rules

include base.mk
ALL_CFLAGS  += -Wextra -Os
