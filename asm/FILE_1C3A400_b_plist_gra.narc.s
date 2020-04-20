	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x000122A8 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x000000EC ; chunk size
	.short 28 ; number of files
	.balign 4
	.word 0x00000000, 0x00000624
	.word 0x00000624, 0x00000C48
	.word 0x00000C48, 0x0000126C
	.word 0x0000126C, 0x00001890
	.word 0x00001890, 0x00001EB4
	.word 0x00001EB4, 0x000024D8
	.word 0x000024D8, 0x00002AFC
	.word 0x00002AFC, 0x00003120
	.word 0x00003120, 0x00003744
	.word 0x00003744, 0x00003D68
	.word 0x00003D68, 0x0000438C
	.word 0x0000438C, 0x000049B0
	.word 0x000049B0, 0x00004FD4
	.word 0x00004FD4, 0x000055F8
	.word 0x000055F8, 0x00005C1C
	.word 0x00005C1C, 0x00006240
	.word 0x00006240, 0x00006864
	.word 0x00006864, 0x00006E88
	.word 0x00006E88, 0x000074AC
	.word 0x000074AC, 0x00007AD0
	.word 0x00007AD0, 0x00008A34
	.word 0x00008A34, 0x00009A18
	.word 0x00009A18, 0x00011A58
	.word 0x00011A58, 0x00011C80
	.word 0x00011C80, 0x00011D9B
	.word 0x00011D9C, 0x00011E9B
	.word 0x00011E9C, 0x00011F6C
	.word 0x00011F6C, 0x00012194

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x0001219C ; chunk size
	.incbin "baserom.nds", 0x1C3A514, 0x12194
	.balign 512, 255
