	.include "asm/macros.inc"
	.text
	.incbin "baserom.nds", 0x1B78200, 0x9C644
	.balign 512, 255
