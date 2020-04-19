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
	.incbin "baserom.nds", 0x0, 0x9A
	.incbin "baserom.nds", 0x9C, 0x8E
	.incbin "baserom.nds", 0x12C, 0x430
	.incbin "baserom.nds", 0x55C, 0xA40
	.incbin "baserom.nds", 0xF9C, 0x228
	.incbin "baserom.nds", 0x11C4, 0xF0
	.incbin "baserom.nds", 0x12B4, 0x150
	.incbin "baserom.nds", 0x1404, 0x2430
	.incbin "baserom.nds", 0x3834, 0x228
	.incbin "baserom.nds", 0x3A5C, 0xF0
	.incbin "baserom.nds", 0x3B4C, 0x120
	.incbin "baserom.nds", 0x3C6C, 0x7B0
	.incbin "baserom.nds", 0x441C, 0x2040
	.incbin "baserom.nds", 0x645C, 0x228
	.incbin "baserom.nds", 0x6684, 0x824
	.incbin "baserom.nds", 0x6EA8, 0x1440
	.incbin "baserom.nds", 0x82E8, 0x228
	.incbin "baserom.nds", 0x8510, 0x824
	.incbin "baserom.nds", 0x8D34, 0xC5
	.incbin "baserom.nds", 0x8DFC, 0xB5
	.incbin "baserom.nds", 0x8EB4, 0x90
	.incbin "baserom.nds", 0x8F44, 0x228
	.incbin "baserom.nds", 0x916C, 0x824
	.incbin "baserom.nds", 0x9990, 0x228
	.balign 4, 255
