	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1F9200, 0x2EBE0
	.balign 512, 255
