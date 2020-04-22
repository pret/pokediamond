	.include "asm/macros.inc"
	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00002AFC ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x00000064 ; chunk size
	.short 11 ; number of files
	.balign 4
	.word 0x00000000, 0x00001978
	.word 0x00001978, 0x00001ED8
	.word 0x00001ED8, 0x00001F4C
	.word 0x00001F4C, 0x00001FD0
	.word 0x00001FD0, 0x00002374
	.word 0x00002374, 0x000023D0
	.word 0x000023D0, 0x00002464
	.word 0x00002464, 0x00002770
	.word 0x00002770, 0x000027EC
	.word 0x000027EC, 0x00002846
	.word 0x00002848, 0x00002A70

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00002A78 ; chunk size
	.incbin "baserom.nds", 0x381F08C, 0x2A70
	.balign 512, 255
