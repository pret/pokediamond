	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1FA9200, 0x14C8
	.balign 512, 255
