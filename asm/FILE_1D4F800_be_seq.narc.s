	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1D4F800, 0x41FC
	.balign 512, 255
