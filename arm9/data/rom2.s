
		.include "asm/macros.inc"
		.include "global.inc"

	.section .rodata

	; 0x020EC710
	.global UNK_020EC710
UNK_020EC710: ; 0x020EC710
	.incbin "baserom.nds", 0xf0710, 0x8

	.global UNK_020EC718
UNK_020EC718: ; 0x020EC718
	.incbin "baserom.nds", 0xf0718, 0x8

	.global UNK_020EC720
UNK_020EC720: ; 0x020EC720
	.incbin "baserom.nds", 0xf0720, 0x8

	.global UNK_020EC728
UNK_020EC728: ; 0x020EC728
	.incbin "baserom.nds", 0xf0728, 0x8

	.global UNK_020EC730
UNK_020EC730: ; 0x020EC730
	.incbin "baserom.nds", 0xf0730, 0x8

	.global UNK_020EC738
UNK_020EC738: ; 0x020EC738
	.incbin "baserom.nds", 0xf0738, 0x8

	.global UNK_020EC740
UNK_020EC740: ; 0x020EC740
	.incbin "baserom.nds", 0xf0740, 0x380

	.global UNK_020ECAC0
UNK_020ECAC0: ; 0x020ECAC0
	.incbin "baserom.nds", 0xf0ac0, 0x4

	.global UNK_020ECAC4
UNK_020ECAC4: ; 0x020ECAC4
	.incbin "baserom.nds", 0xf0ac4, 0x4

	.global UNK_020ECAC8
UNK_020ECAC8: ; 0x020ECAC8
	.incbin "baserom.nds", 0xf0ac8, 0x40

