	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1F8A000, 0x1F0B0
	.balign 512, 255
