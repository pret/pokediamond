	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global _03807704
_03807704:
	.word	0x00000001

	.global _03807708
_03807708:
	.word	0xFFFFFFFF
	.balign 2, 0 ; Don't pad with nop
