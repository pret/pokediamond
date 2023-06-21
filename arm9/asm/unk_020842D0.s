	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020FCA3C
UNK_020FCA3C: ; 0x020FCA3C
	.word ov73_021D8EA8, ov73_021D907C, 0x00000000
	.word ov73_021D8EB4, ov73_021D907C, 0x00000000
	.word ov73_021D8EC0, ov73_021D9084, 0x00000000
	.word ov73_021D8EFC, ov73_021D9088, 0x00000000
	.word ov73_021D8F8C, ov73_021D908C, 0x00000000
	.word ov73_021D8FA8, ov73_021D9090, 0x00000000
	.word ov73_021D8FC8, sub_02027E30, 0x00000000
	.word ov73_021D8FE0, ov73_021D9080, 0x00000000
	.word ov73_021D9000, ov73_021D9080, 0x00000000

	.text

	thumb_func_start sub_020842D0
sub_020842D0: ; 0x020842D0
	ldr r0, _020842D4 ; =UNK_020FCA3C
	bx lr
	.balign 4
_020842D4: .word UNK_020FCA3C

	thumb_func_start sub_020842D8
sub_020842D8: ; 0x020842D8
	mov r0, #0x9
	bx lr
