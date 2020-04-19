	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x423800, 0x228
	.balign 512, 255
