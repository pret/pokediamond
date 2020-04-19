	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1E9CE00, 0x3E630
	.balign 512, 255
