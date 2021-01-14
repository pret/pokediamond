	.include "asm/macros.inc"
	.include "global.inc"

	.extern CTRDGi_EraseFlashChipAsyncMX
	.extern CTRDGi_EraseFlashChipMX
	.extern CTRDGi_EraseFlashSectorAsyncMX
	.extern CTRDGi_EraseFlashSectorMX
	.extern CTRDGi_PollingSR1MCOMMON
	.extern CTRDGi_WriteFlashSectorAsyncMX
	.extern CTRDGi_WriteFlashSectorMX

	.section .rodata

	.global LeMaxTime
LeMaxTime: ; 0x02104084
	.short 10, 10, 2000, 5000

	.global LE26FV10N1TS_10
LE26FV10N1TS_10: ; 0x0210408C
	.word CTRDGi_WriteFlashSectorMX
	.word CTRDGi_EraseFlashChipMX
	.word CTRDGi_EraseFlashSectorMX
	.word CTRDGi_WriteFlashSectorAsyncMX
	.word CTRDGi_EraseFlashChipAsyncMX
	.word CTRDGi_EraseFlashSectorAsyncMX
	.word CTRDGi_PollingSR1MCOMMON
	.word LeMaxTime
	.byte 0x00, 0x00, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00, 0x0C, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x62, 0x00, 0x13, 0x00
