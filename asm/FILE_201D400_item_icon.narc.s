	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x201D400, 0x608B0
	.balign 512, 255
