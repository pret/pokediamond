	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3FAA00, 0x124
	.balign 512, 255
