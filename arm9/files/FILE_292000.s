	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x292000, 0xC60
	.balign 512, 255
