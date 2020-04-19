	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1C35400, 0x4F04
	.balign 512, 255
