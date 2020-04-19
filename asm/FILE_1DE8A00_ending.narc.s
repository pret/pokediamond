	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1DE8A00, 0x5169C
	.balign 512, 255
