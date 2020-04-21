	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2CFE00, 0x5DE0
	.balign 512, 255
