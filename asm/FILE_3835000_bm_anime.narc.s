	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3835000, 0x9200
	.balign 512, 255
