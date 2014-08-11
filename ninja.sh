#! /bin/sh

: ${CC:=arm-none-eabi-gcc}

CFLAGS="-I. ${CFLAGS}"
LDFLAGS="-L ld -nostartfiles ${LDFLAGS}"

exec >build.ninja

cat <<EOF
cc = $CC
cflags = -Wall $CFLAGS
ldflags = $LDFLAGS

rule cc
  command = \$cc \$cflags -MMD -MF \$out.d  -c \$in -o \$out
  depfile = \$out.d

rule ccld
  command = \$cc \$ldflags -o \$out \$in
EOF

to_obj () {
	for i in "$@"; do
		printf "%s " ".build-$out/$i.o"
	done
}

_ev () {
	eval echo "\${$1}"
}

bin () {
	out="$1"
	shift
	out_var="${out/./_}"

	for s in "$@"; do
		echo build $(to_obj $s): cc $s
		echo "  cflags = \$cflags $(_ev cflags_${out_var})"
	done

	cat <<EOF
build $out : ccld $(to_obj "$@")
  ldflags = \$ldflags $(_ev ldflags_${out_var})
EOF
	BINS="$BINS $out"
}
BINS=""
  
cflags_main_elf="-DLM3S3748=1 -include config/lm3s.h"
ldflags_main_elf="-T lm3s.ld"
bin main.elf init_vector.c init.c lm3s/adc.c lm3s/clock.c main.c

cat <<EOF
rule ninja_gen
  command = $0
  generator = yes
build build.ninja : ninja_gen $0
EOF

echo default ${BINS}
