	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1C3A400, 0x122A8
	.balign 512, 255
