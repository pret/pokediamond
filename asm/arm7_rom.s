/* arm7_rom.s TODO: Disassemble */

	.section .text
	.global Entry_ARM7
Entry_ARM7:
	.incbin "baserom.nds", 0x30D000, 0x2931C
