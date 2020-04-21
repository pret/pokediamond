	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x295400, 0x4A0
	.balign 512, 255
