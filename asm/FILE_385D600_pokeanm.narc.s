	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x385D600, 0x3644
	.balign 512, 255
