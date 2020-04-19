	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1E69C00, 0x9708
	.balign 512, 255
