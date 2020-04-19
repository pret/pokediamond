	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1F6E400, 0x3164
	.balign 512, 255
