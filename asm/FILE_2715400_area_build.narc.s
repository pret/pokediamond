	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2715400, 0x1274
	.balign 512, 255
