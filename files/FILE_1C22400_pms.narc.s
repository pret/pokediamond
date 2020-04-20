	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1C22400, 0x3EA
	.balign 512, 255
