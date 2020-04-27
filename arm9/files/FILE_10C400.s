	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x10C400, 0x20
	.balign 512, 255
