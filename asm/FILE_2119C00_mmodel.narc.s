	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2119C00, 0x12845C
	.balign 512, 255
