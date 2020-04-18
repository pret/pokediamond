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
	.incbin "baserom.nds", 0x33F8D4, 0x118D8
	.incbin "baserom.nds", 0x3511AC, 0x91C
	.incbin "baserom.nds", 0x351AC8, 0x2E60
	.incbin "baserom.nds", 0x354928, 0x628
	.incbin "baserom.nds", 0x354F50, 0x5A4
	.incbin "baserom.nds", 0x3554F4, 0x5A4
	.incbin "baserom.nds", 0x355A98, 0x5A4
	.incbin "baserom.nds", 0x35603C, 0x4878
	.incbin "baserom.nds", 0x35A8B4, 0x2B9F4
	.incbin "baserom.nds", 0x3862A8, 0x7E0
	.incbin "baserom.nds", 0x386A88, 0x2B7C
	.incbin "baserom.nds", 0x389604, 0xCA4
	.incbin "baserom.nds", 0x38A2A8, 0x114E4
	.incbin "baserom.nds", 0x39B78C, 0x7BA0
	.incbin "baserom.nds", 0x3A332C, 0x23D4
	.incbin "baserom.nds", 0x3A5700, 0xBF44
	.incbin "baserom.nds", 0x3B1644, 0x84C
	.incbin "baserom.nds", 0x3B1E90, 0x9B4
	.incbin "baserom.nds", 0x3B2844, 0x494
	.incbin "baserom.nds", 0x3B2CD8, 0x154
