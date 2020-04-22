	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00014F10 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x000000FC ; chunk size
	.short 30 ; number of files
	.balign 4
	.word 0x00000000, 0x0000007C
	.word 0x0000007C, 0x0000015E
	.word 0x00000160, 0x00000396
	.word 0x00000398, 0x000003F2
	.word 0x000003F4, 0x00001C24
	.word 0x00001C24, 0x00001CBB
	.word 0x00001CBC, 0x00001D3F
	.word 0x00001D40, 0x00001E70
	.word 0x00001E70, 0x00001EF0
	.word 0x00001EF0, 0x00001F68
	.word 0x00001F68, 0x00002098
	.word 0x00002098, 0x0000211A
	.word 0x0000211C, 0x00002196
	.word 0x00002198, 0x000021E8
	.word 0x000021E8, 0x00002254
	.word 0x00002254, 0x000022C4
	.word 0x000022C4, 0x00002674
	.word 0x00002674, 0x00002760
	.word 0x00002760, 0x00002808
	.word 0x00002808, 0x00007848
	.word 0x00007848, 0x0000D888
	.word 0x0000D888, 0x0000F688
	.word 0x0000F688, 0x0000FCAC
	.word 0x0000FCAC, 0x0000FD78
	.word 0x0000FD78, 0x0001039C
	.word 0x0001039C, 0x000123C0
	.word 0x000123C0, 0x000143E4
	.word 0x000143E4, 0x0001454C
	.word 0x0001454C, 0x00014B70
	.word 0x00014B70, 0x00014DEC

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00014DF4 ; chunk size
	.incbin "baserom.nds", 0x1FB2B24, 0x14DEC
	.balign 512, 255
