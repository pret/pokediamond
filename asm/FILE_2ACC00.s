	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x2ACC00, 0xD00
	.balign 512, 255
