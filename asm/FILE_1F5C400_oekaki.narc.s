	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1F5C400, 0x1524
	.balign 512, 255
