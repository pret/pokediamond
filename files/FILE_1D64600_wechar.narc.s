	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00008134 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000134 ; chunk size
	.short 37 ; number of files
	.balign 4
	.word 0x00000000, 0x00000BE0
	.word 0x00000BE0, 0x00000DB4
	.word 0x00000DB4, 0x0000154C
	.word 0x0000154C, 0x00001750
	.word 0x00001750, 0x000019C8
	.word 0x000019C8, 0x00001D00
	.word 0x00001D00, 0x000021B4
	.word 0x000021B4, 0x00002714
	.word 0x00002714, 0x0000315C
	.word 0x0000315C, 0x00003288
	.word 0x00003288, 0x000036A8
	.word 0x000036A8, 0x0000375C
	.word 0x0000375C, 0x00003DB4
	.word 0x00003DB4, 0x00003FC4
	.word 0x00003FC4, 0x00004188
	.word 0x00004188, 0x00004320
	.word 0x00004320, 0x000044EC
	.word 0x000044EC, 0x00004C54
	.word 0x00004C54, 0x00004F28
	.word 0x00004F28, 0x00005264
	.word 0x00005264, 0x0000553C
	.word 0x0000553C, 0x00005740
	.word 0x00005740, 0x00005C3C
	.word 0x00005C3C, 0x000061B8
	.word 0x000061B8, 0x000064F0
	.word 0x000064F0, 0x00006600
	.word 0x00006600, 0x00006D80
	.word 0x00006D80, 0x00007040
	.word 0x00007040, 0x000072BC
	.word 0x000072BC, 0x000073F0
	.word 0x000073F0, 0x000074DC
	.word 0x000074DC, 0x000077B4
	.word 0x000077B4, 0x0000788C
	.word 0x0000788C, 0x00007A4C
	.word 0x00007A4C, 0x00007D88
	.word 0x00007D88, 0x00007EB8
	.word 0x00007EB8, 0x00007FD8

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00007FE0 ; chunk size
	.incbin "baserom.nds", 0x1D6475C, 0x7FD8
	.balign 512, 255
