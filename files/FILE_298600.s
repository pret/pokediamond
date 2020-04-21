	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x298600, 0x320
	.balign 512, 255
