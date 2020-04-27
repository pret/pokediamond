	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x283200, 0x2400
	.balign 512, 255
