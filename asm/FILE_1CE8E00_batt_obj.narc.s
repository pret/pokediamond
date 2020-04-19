	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1CE8E00, 0x2025C
	.balign 512, 255
