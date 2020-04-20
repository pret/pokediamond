	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x0007362C ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x000000AC ; chunk size
	.short 20 ; number of files
	.balign 4
	.word 0x00000000, 0x000118D8
	.word 0x000118D8, 0x000121F4
	.word 0x000121F4, 0x00015054
	.word 0x00015054, 0x0001567C
	.word 0x0001567C, 0x00015C20
	.word 0x00015C20, 0x000161C4
	.word 0x000161C4, 0x00016768
	.word 0x00016768, 0x0001AFE0
	.word 0x0001AFE0, 0x000469D4
	.word 0x000469D4, 0x000471B4
	.word 0x000471B4, 0x00049D30
	.word 0x00049D30, 0x0004A9D4
	.word 0x0004A9D4, 0x0005BEB8
	.word 0x0005BEB8, 0x00063A58
	.word 0x00063A58, 0x00065E2C
	.word 0x00065E2C, 0x00071D70
	.word 0x00071D70, 0x000725BC
	.word 0x000725BC, 0x00072F70
	.word 0x00072F70, 0x00073404
	.word 0x00073404, 0x00073558

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00073560 ; chunk size
	.incbin "baserom.nds", 0x33F8D4, 0x73558
	.balign 512, 255
