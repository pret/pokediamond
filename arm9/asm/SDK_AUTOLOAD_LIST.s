	.include "asm/macros.inc"
	.include "global.inc"
	.section .data

	.global SDK_AUTOLOAD_LIST
SDK_AUTOLOAD_LIST: ; 0x02107700
	.word SDK_AUTOLOAD_ITCM_START
	.word 0x00000700
	.word 0x00000000

	.word SDK_AUTOLOAD_DTCM_START
	.word 0x00000060
	.word 0x00000020

	.word 0x02400000
	.word 0x00000000
	.word 0x00000000

	.global SDK_AUTOLOAD_LIST_END
SDK_AUTOLOAD_LIST_END:

