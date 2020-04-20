	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x0000B6D8 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000013C ; chunk size
	.short 38 ; number of files
	.balign 4
	.word 0x00000000, 0x00000228
	.word 0x00000228, 0x00000450
	.word 0x00000450, 0x00000678
	.word 0x00000678, 0x000008A0
	.word 0x000008A0, 0x00000AC8
	.word 0x00000AC8, 0x00000CF0
	.word 0x00000CF0, 0x00000F18
	.word 0x00000F18, 0x00001140
	.word 0x00001140, 0x00001368
	.word 0x00001368, 0x00001590
	.word 0x00001590, 0x00001995
	.word 0x00001998, 0x00001BA1
	.word 0x00001BA4, 0x00001DB8
	.word 0x00001DB8, 0x00001FA0
	.word 0x00001FA0, 0x000021BC
	.word 0x000021BC, 0x00002F05
	.word 0x00002F08, 0x000076D1
	.word 0x000076D4, 0x00007907
	.word 0x00007908, 0x000088EF
	.word 0x000088F0, 0x00008BDD
	.word 0x00008BE0, 0x00008F25
	.word 0x00008F28, 0x000091C0
	.word 0x000091C0, 0x000092CD
	.word 0x000092D0, 0x00009415
	.word 0x00009418, 0x00009545
	.word 0x00009548, 0x00009698
	.word 0x00009698, 0x000097DE
	.word 0x000097E0, 0x0000993D
	.word 0x00009940, 0x00009A9C
	.word 0x00009A9C, 0x00009B82
	.word 0x00009B84, 0x00009C82
	.word 0x00009C84, 0x00009F32
	.word 0x00009F34, 0x0000ACCC
	.word 0x0000ACCC, 0x0000B011
	.word 0x0000B014, 0x0000B40E
	.word 0x0000B410, 0x0000B472
	.word 0x0000B474, 0x0000B4F4
	.word 0x0000B4F4, 0x0000B571

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x0000B57C ; chunk size
	.incbin "baserom.nds", 0x200CF64, 0xB574
	.balign 512, 255
