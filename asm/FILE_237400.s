	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x237400, 0x4680
	.balign 512, 255
