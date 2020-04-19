	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x33A400, 0x842
	.balign 512, 255
