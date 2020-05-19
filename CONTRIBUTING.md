# Contributing guide for Pokémon Diamond

**As the repository is in a volatile state, contribution is closed to the public until further notice.**

This is a living document which lays out the procedure for decompiling the game code of Pokémon Diamond Version (5.0-US) for the Nintendo DS.

## Structure of the repository

Nintendo DS games contain separate static binaries and overlays for the ARM7 and ARM9 processors as well as a filesystem. Therefore the repository is laid out as such:

```
root
`- arm9
   `- asm
   `- data
   `- graphics
   `- lib
      `- src
      `- include
   `- modules
      `- 00
         `- asm
         `- src
      `- ...
   `- src
   `- global.inc
   `- arm9.lcf
   `- Makefile
`- arm7
   `- asm
   `- global.inc
   `- arm7.lcf
   `- Makefile
`- files
`- data
`- graphics
`- include
`- include-mw
`- tools
`- Makefile
```

In the above structure, ASM files (.s) in the asm/ directories contains the machine code extracted from the ROM (baserom.nds). They are to be decompiled into C or C++ (.c, .cpp) files in the respective src/ directories. 

## Decompilation of ASM to C

**Decompilation** entails writing C code which the project compiler (mwccarm) will translate to the exact same assembly code. For example, consider this ASM function:

```armasm
    thumb_func_start FUN_0201B578
FUN_0201B578: ; 0x0201B578
    lsl r0, r0, #0x5
    add r0, #0x34
    bx lr
    .balign 4
```

Without knowing anything else about the function prototypes, we can make an educated guess as to what C code would produce this function. Function arguments are passed in registers r0-r2 or r0-r3, and the return value (if any) is held in r0. The `LSL` instruction means "logical shift left", which is equivalent to multiplying the input operand by a power of 2. In this case, the input operand is being shifted left by 5 bits (multiplied by 20h). The following instruction (`ADD r0, #0x34`) adds 34h to that value, and the final instruction `BX lr` returns to the parent routine with the result of the ADD instruction held in r0. Thus we can surmise that the C function
```c
s32 FUN_0201B578(s32 arg0)
{
    return 32 * arg0 + 52;
}
```
will produce that assembly code.

Most functions in the codebase will be longer and more complicated than this.

## Creating a new C file

Section link order is specified in the Linker Command File, arm9/arm9.lcf. Only the basenames of each object (.o) file are specified in the lcf and recognized by the project linker, mwldarm. Therefore, no two compiled objects can have the same name. When decompiling asm/foo.s, please create the C file with a different name (basename minus extension i.e. src/foo_c.c). You must explicitly specify the .text, .data, .rodata, and .bss sections in their respective locations in the lcf. For instance:
```diff
    file1.o (.text)
    file2.o (.text)
+   file3_c.o (.text)
    file3.o (.text)
    file4.o (.text)
--
    file1.o (.rodata)
    file2.o (.rodata)
+   file3_c.o (.rodata)
    file3.o (.rodata)
    file4.o (.rodata)
```

## Testing the build

After placing your C file into the LCF as described above, test your build by running `make`. Here are some common errors you may encounter and how to resolve them:

    Unknown identifier, FUN_0201B578

Append the line `.extern FUN_0201B578` to arm9/global.inc and recompile.

    build/arm9.sbin: FAILED
    build/MODULE_00.sbin: FAILED
    ...

Your attempt was incorrect. Don't be discouraged, this is all part of the process. The following bash script will allow you to compare your code to the original ROM; save it as arm9/asmdiff.sh

```bash
#!/bin/bash

OBJDUMP_ARCH="${OBJDUMP_ARCH:-armv5te}"
OBJDUMP_MODE="${OBJDUMP_MODE:-force-thumb}"
OBJDUMP_VMA="${OBJDUMP_VMA:-0x02000000}"
OBJDUMP="arm-none-eabi-objdump -Drz -bbinary -m${OBJDUMP_ARCH} -M${OBJDUMP_MODE}"
OPTIONS="--start-address=$(($1 + OBJDUMP_VMA)) --stop-address=$(($1 + $2 + OBJDUMP_VMA))"
$OBJDUMP $OPTIONS baserom.sbin > baserom.dump || exit 1
$OBJDUMP $OPTIONS build/arm9.sbin > arm9.dump
diff -u baserom.dump arm9.dump
```
Place a clean version of the ARM9 binary as arm9/baserom.sbin. In your terminal, navigate to the arm9 directory and run `./asmdiff.sh 0 $(wc -c baserom.sbin) | less`, then scroll through to where the grievances begin. Fix any obvious problems in your code/tree, and rerun. If the differences are extensive, you may have induced a shift in the binary either by writing incorrect code or placing it incorrectly into the LCF.  *Tip: you can specify a start address and size to only compare the portion of the ROM you are working on.*

## Decompiling data

**This section describes a target repository specification and does not reflect the current state of the project.**

ASM files may own one or more data/RAM sections. The types of these sections is not guaranteed to be accurate. When decompiling data, you are expected to translate the raw bytes into the actual structures used by the source code. These may be simple values (char, short, word, or pointer), or they could be C structs or unions. Some overlay modules are suspected to contain C++ classes, the handling of which is not yet described.

Because the Nintendo DS architecture is ARM, all data is aligned. This means 16-bit integers are aligned to 2 bytes within a structure, and anything 4 bytes or wider is aligned to 4 bytes (long, long long, float, double, struct, union, void *). All data requiring alignment are padded with 0. For example:
```armasm
u8_var_foo:
    .byte 0x05, 0x00, 0x00, 0x00
ptr_var_bar:
    .word u8_var_foo
```
could have been compiled from
```c
u8 u8_var_foo = 5;
u8 * ptr_var_bar = &u8_var_foo;
```
Notice that the three extra 0 bytes are treated as implicit padding.
