	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global _038075E4
_038075E4:
	.word	0x00090008
	.word	0x000B000A
	.word	0x00040003
	.word	0x00060005
	.word	0x00000000

	.global OS_IRQTable
OS_IRQTable:
	.word	OSi_IrqVBlank
	.word	OS_IrqDummy
	.word	OS_IrqDummy
	.word	OSi_IrqTimer0
	.word	OSi_IrqTimer1
	.word	OSi_IrqTimer2
	.word	OSi_IrqTimer3
	.word	OS_IrqDummy
	.word	OSi_IrqDma0
	.word	OSi_IrqDma1
	.word	OSi_IrqDma2
	.word	OSi_IrqDma3
	.word	OS_IrqDummy
	.word	OS_IrqDummy
	.word	OS_IrqDummy
	.word	OS_IrqDummy
	.word	OS_IrqDummy
	.word	OS_IrqDummy
	.word	OS_IrqDummy
	.word	OS_IrqDummy
	.word	OS_IrqDummy
	.word	OS_IrqDummy
	.word	OS_IrqDummy
	.word	OS_IrqDummy
	.word	OS_IrqDummy

	.global sMasterPan
sMasterPan:
	.word	0xFFFFFFFF

	.global _03807660
_03807660:
	.word	0x12345678

	.global cardi_rom_header_addr
cardi_rom_header_addr:
	.word	0x027FFE00

	.global _03807668
_03807668:
	.word	0xFFFFFFFF

	.global _0380766C
_0380766C:
	.word	0x00000001

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
