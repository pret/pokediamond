	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2AEC00, 0x3DE0
	.balign 512, 255
