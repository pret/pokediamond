	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1F86600, 0x14AC
	.balign 512, 255
