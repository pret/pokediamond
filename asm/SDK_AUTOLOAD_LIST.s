	.include "asm/macros.inc"
	.section .data

	.global SDK_AUTOLOAD_LIST
SDK_AUTOLOAD_LIST: ; 0x02107700
	.word 0x01FF8000
	.word 0x00000700
	.word 0x00000000

	.word 0x027e0000
	.word 0x00000060
	.word 0x00000020

	.word 0x02400000
	.word 0x00000000
	.word 0x00000000

	.global SDK_AUTOLOAD_LIST_END
SDK_AUTOLOAD_LIST_END:

