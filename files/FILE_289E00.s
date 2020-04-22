	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x289E00, 0xBA0
	.balign 512, 255
