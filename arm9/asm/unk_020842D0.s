    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020FCA3C

	.text

	thumb_func_start FUN_020842D0
FUN_020842D0: ; 0x020842D0
	ldr r0, _020842D4 ; =UNK_020FCA3C
	bx lr
	.balign 4
_020842D4: .word UNK_020FCA3C

	thumb_func_start FUN_020842D8
FUN_020842D8: ; 0x020842D8
	mov r0, #0x9
	bx lr
