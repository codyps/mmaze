#! /bin/sh

: ${CC:=arm-none-eabi-gcc}

CFLAGS="-I. -DLM3S3748=1 -include config/lm3s.h ${CFLAGS}"
LDFLAGS="-L ld -T lm3s.ld -nostartfiles ${LDFLAGS}"

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
		printf "%s " "${i%%.c}.o"
	done
}

bin () {
	out="$1"
	shift

	for s in "$@"; do
		echo build $s.o: cc $s
	done

	echo build $out : ccld $(to_obj "$@")
}

bin main.elf init_vector.c init.c lm3s/adc.c clock.c main.c

cat <<EOF
rule ninja_gen
  command = $0
  generator = yes
build build.ninja : ninja_gen $0
EOF

echo default main.elf
