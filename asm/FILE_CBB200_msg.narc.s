	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0xCBB200, 0x292010
	.balign 512, 255
