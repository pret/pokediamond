	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x426400, 0x64
	.balign 512, 255
