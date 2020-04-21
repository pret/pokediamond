	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x451A00, 0xF9
	.balign 512, 255
