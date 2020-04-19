	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x299A00, 0x400
	.balign 512, 255
