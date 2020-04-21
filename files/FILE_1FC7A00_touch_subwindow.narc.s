	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00000998 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000005C ; chunk size
	.short 10 ; number of files
	.balign 4
	.word 0x00000000, 0x00000228
	.word 0x00000228, 0x0000061E
	.word 0x00000620, 0x0000067A
	.word 0x0000067C, 0x000006D9
	.word 0x000006DC, 0x00000739
	.word 0x0000073C, 0x00000799
	.word 0x0000079C, 0x000007F9
	.word 0x000007FC, 0x00000859
	.word 0x0000085C, 0x000008B5
	.word 0x000008B8, 0x00000914

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x0000091C ; chunk size
	.incbin "baserom.nds", 0x1FC7A84, 0x914
	.balign 512, 255
