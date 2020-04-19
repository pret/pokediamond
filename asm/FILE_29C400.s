	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x29C400, 0x2380
	.balign 512, 255
