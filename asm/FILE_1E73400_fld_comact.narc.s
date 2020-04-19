	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1E73400, 0x364
	.balign 512, 255
