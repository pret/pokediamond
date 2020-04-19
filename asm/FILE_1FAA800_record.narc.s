	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1FAA800, 0x59C4
	.balign 512, 255
