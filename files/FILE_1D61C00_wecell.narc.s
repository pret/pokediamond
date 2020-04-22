	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x000014F4 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000134 ; chunk size
	.short 37 ; number of files
	.balign 4
	.word 0x00000000, 0x00000080
	.word 0x00000080, 0x000000DC
	.word 0x000000DC, 0x00000198
	.word 0x00000198, 0x00000208
	.word 0x00000208, 0x00000264
	.word 0x00000264, 0x000002DC
	.word 0x000002DC, 0x00000364
	.word 0x00000364, 0x000003E8
	.word 0x000003E8, 0x0000047C
	.word 0x0000047C, 0x000004D8
	.word 0x000004D8, 0x000005C8
	.word 0x000005C8, 0x00000624
	.word 0x00000624, 0x000006A0
	.word 0x000006A0, 0x00000718
	.word 0x00000718, 0x00000774
	.word 0x00000774, 0x000007D0
	.word 0x000007D0, 0x00000844
	.word 0x00000844, 0x000008CC
	.word 0x000008CC, 0x000009B0
	.word 0x000009B0, 0x00000A9C
	.word 0x00000A9C, 0x00000B60
	.word 0x00000B60, 0x00000BD0
	.word 0x00000BD0, 0x00000C74
	.word 0x00000C74, 0x00000D34
	.word 0x00000D34, 0x00000DF0
	.word 0x00000DF0, 0x00000E4C
	.word 0x00000E4C, 0x00000EE0
	.word 0x00000EE0, 0x00000F50
	.word 0x00000F50, 0x00000FCC
	.word 0x00000FCC, 0x00001048
	.word 0x00001048, 0x000010A4
	.word 0x000010A4, 0x0000111C
	.word 0x0000111C, 0x00001178
	.word 0x00001178, 0x00001200
	.word 0x00001200, 0x0000128C
	.word 0x0000128C, 0x00001320
	.word 0x00001320, 0x00001398

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x000013A0 ; chunk size
	.incbin "baserom.nds", 0x1D61D5C, 0x1398
	.balign 512, 255
