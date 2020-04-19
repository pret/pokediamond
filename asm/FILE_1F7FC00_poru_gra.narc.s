	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1F7FC00, 0x69E4
	.balign 512, 255
