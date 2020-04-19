	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1B6B400, 0xCC74
	.balign 512, 255
