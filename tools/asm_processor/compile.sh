#!/bin/bash

CC="$1"
shift
AS="$1"
shift

temp="$(mktemp)"
../tools/asm_processor/asm_processor.py "$2" --assembler "$AS" > "$temp.c" &&
$CC -c "$temp.c" -o "$1"

prelude=$(mktemp prelude.XXXXXX)
cat ../include/macros.inc >> "$prelude"
cat global.inc >> "$prelude"

../tools/asm_processor/asm_processor.py "$2" --post-process "$1" --assembler "$AS" --asm-prelude "$prelude"
arm-none-eabi-objcopy --remove-section .comment "$1" "$1"
rm "$prelude"
rm "$temp"
