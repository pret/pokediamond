	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1C1B000, 0x65F8
	.balign 512, 255
