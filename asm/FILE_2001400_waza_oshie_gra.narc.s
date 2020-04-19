	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2001400, 0x2F34
	.balign 512, 255
