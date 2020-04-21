	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2CEA00, 0x1220
	.balign 512, 255
