    .include "asm/macros.inc"
    .include "global.inc"

    .bss

	.global errno
errno: ; 0x021D74A8
	.space 0x4
    .size errno,.-errno