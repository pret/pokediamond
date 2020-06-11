	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global PMi_LEDStatus
PMi_LEDStatus:
	.word	0x00000001

	.global PMi_BlinkPatternData
PMi_BlinkPatternData:
	.word	0x00000000
	.word	0xAA000000
	.word	0x00010008
	.word	0x00000000
	.word	0xCC000000
	.word	0x00010008
	.word	0x00000000
	.word	0xE3800000
	.word	0x0001000C
	.word	0x00000000
	.word	0xF0F00000
	.word	0x00010010
	.word	0x00000000
	.word	0xF83E0000
	.word	0x00010014
	.word	0x00000000
	.word	0xFC000000
	.word	0x0001000C
	.word	0x00000000
	.word	0xFF000000
	.word	0x00010010
	.word	0x00000000
	.word	0xFFC00000
	.word	0x00010014
	.word	0x00000000
	.word	0xFF000000
	.word	0x00010020
	.word	0x00000000
	.word	0xFF00FF00
	.word	0x00010020
	.word	0x00000000
	.word	0xFFFFFF00
	.word	0x00010020
	.word	0x00000000
	.word	0xC3000000
	.word	0x00020028

	.global _03807704
_03807704:
	.word	0x00000001

	.global _03807708
_03807708:
	.word	0xFFFFFFFF
	.balign 2, 0 ; Don't pad with nop
