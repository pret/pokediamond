	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x3FAC00, 0xD220
	.balign 512, 255
