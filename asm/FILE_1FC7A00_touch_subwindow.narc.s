	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1FC7A00, 0x998
	.balign 512, 255
