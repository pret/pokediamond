	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x000064C4 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x0000006C ; chunk size
	.short 12 ; number of files
	.balign 4
	.word 0x00000000, 0x000011C0
	.word 0x000011C0, 0x00002A00
	.word 0x00002A00, 0x00002A80
	.word 0x00002A80, 0x00002B00
	.word 0x00002B00, 0x00002D28
	.word 0x00002D28, 0x00002F50
	.word 0x00002F50, 0x00003178
	.word 0x00003178, 0x000033A0
	.word 0x000033A0, 0x000043C4
	.word 0x000043C4, 0x000053E8
	.word 0x000053E8, 0x00005C0C
	.word 0x00005C0C, 0x00006430

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00006438 ; chunk size
	.incbin "baserom.nds", 0x0, 0x11C0
	.incbin "baserom.nds", 0x11C0, 0x1840
	.incbin "baserom.nds", 0x2A00, 0x80
	.incbin "baserom.nds", 0x2A80, 0x80
	.incbin "baserom.nds", 0x2B00, 0x228
	.incbin "baserom.nds", 0x2D28, 0x228
	.incbin "baserom.nds", 0x2F50, 0x228
	.incbin "baserom.nds", 0x3178, 0x228
	.incbin "baserom.nds", 0x33A0, 0x1024
	.incbin "baserom.nds", 0x43C4, 0x1024
	.incbin "baserom.nds", 0x53E8, 0x824
	.incbin "baserom.nds", 0x5C0C, 0x824
	.balign 4, 255
