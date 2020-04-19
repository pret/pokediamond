	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x24F2600, 0xBC8
	.balign 512, 255
