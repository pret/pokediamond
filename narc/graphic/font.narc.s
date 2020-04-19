	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00020E58 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000004C ; chunk size
	.short 8 ; number of files
	.balign 4
	.word 0x00000000, 0x0000814D
	.word 0x00008150, 0x0001029D
	.word 0x000102A0, 0x000183ED
	.word 0x000183F0, 0x0002053D
	.word 0x00020540, 0x000206EC
	.word 0x000206EC, 0x00020D2C
	.word 0x00020D2C, 0x00020D86
	.word 0x00020D88, 0x00020DE2

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00020DEC ; chunk size
	.incbin "baserom.nds", 0x0, 0x814D
	.incbin "baserom.nds", 0x8150, 0x814D
	.incbin "baserom.nds", 0x102A0, 0x814D
	.incbin "baserom.nds", 0x183F0, 0x814D
	.incbin "baserom.nds", 0x20540, 0x1AC
	.incbin "baserom.nds", 0x206EC, 0x640
	.incbin "baserom.nds", 0x20D2C, 0x5A
	.incbin "baserom.nds", 0x20D88, 0x5A
	.balign 4, 255
