	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00009CAC ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x000000CC ; chunk size
	.short 24 ; number of files
	.balign 4
	.word 0x00000000, 0x0000009A
	.word 0x0000009C, 0x0000012A
	.word 0x0000012C, 0x0000055C
	.word 0x0000055C, 0x00000F9C
	.word 0x00000F9C, 0x000011C4
	.word 0x000011C4, 0x000012B4
	.word 0x000012B4, 0x00001404
	.word 0x00001404, 0x00003834
	.word 0x00003834, 0x00003A5C
	.word 0x00003A5C, 0x00003B4C
	.word 0x00003B4C, 0x00003C6C
	.word 0x00003C6C, 0x0000441C
	.word 0x0000441C, 0x0000645C
	.word 0x0000645C, 0x00006684
	.word 0x00006684, 0x00006EA8
	.word 0x00006EA8, 0x000082E8
	.word 0x000082E8, 0x00008510
	.word 0x00008510, 0x00008D34
	.word 0x00008D34, 0x00008DF9
	.word 0x00008DFC, 0x00008EB1
	.word 0x00008EB4, 0x00008F44
	.word 0x00008F44, 0x0000916C
	.word 0x0000916C, 0x00009990
	.word 0x00009990, 0x00009BB8

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00009BC0 ; chunk size
	.incbin "baserom.nds", 0x1F646F4, 0x9BB8
	.balign 512, 255
