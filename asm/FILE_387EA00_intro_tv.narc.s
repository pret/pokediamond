	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x387EA00, 0xDFE0
	.balign 512, 255
