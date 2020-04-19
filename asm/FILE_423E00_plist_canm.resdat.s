	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x423E00, 0xC4
	.balign 512, 255
