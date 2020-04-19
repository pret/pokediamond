	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x37ACA00, 0x5818
	.balign 512, 255
