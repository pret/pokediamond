	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1F5DA00, 0x6BBC
	.balign 512, 255
