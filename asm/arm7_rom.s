/* arm7_rom.s TODO: Disassemble */

	.section .text
	.global Entry_ARM7
Entry_ARM7: @ 0x02380000
	.incbin "baserom.nds", 0x30D000, 0x158

	.global ARM7AutoLoad
ARM7AutoLoad: @ 0x02380158
	.incbin "baserom.nds", 0x30D158, 0x291C4
