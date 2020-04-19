	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00037B10 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x000000AC ; chunk size
	.short 20 ; number of files
	.balign 4
	.word 0x00000000, 0x00000824
	.word 0x00000824, 0x00008864
	.word 0x00008864, 0x00008A8C
	.word 0x00008A8C, 0x00010ACC
	.word 0x00010ACC, 0x00010CF4
	.word 0x00010CF4, 0x00020D24
	.word 0x00020D24, 0x0002D698
	.word 0x0002D698, 0x0002D7D8
	.word 0x0002D7D8, 0x0002DDFC
	.word 0x0002DDFC, 0x0002E024
	.word 0x0002E024, 0x0002E24C
	.word 0x0002E24C, 0x0002E38C
	.word 0x0002E38C, 0x0002E9B0
	.word 0x0002E9B0, 0x0002EBD8
	.word 0x0002EBD8, 0x0002EE00
	.word 0x0002EE00, 0x00036E40
	.word 0x00036E40, 0x00037068
	.word 0x00037068, 0x0003768C
	.word 0x0003768C, 0x00037864
	.word 0x00037864, 0x00037A3C

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00037A44 ; chunk size
	.incbin "baserom.nds", 0x0, 0x824
	.incbin "baserom.nds", 0x824, 0x8040
	.incbin "baserom.nds", 0x8864, 0x228
	.incbin "baserom.nds", 0x8A8C, 0x8040
	.incbin "baserom.nds", 0x10ACC, 0x228
	.incbin "baserom.nds", 0x10CF4, 0x10030
	.incbin "baserom.nds", 0x20D24, 0xC974
	.incbin "baserom.nds", 0x2D698, 0x140
	.incbin "baserom.nds", 0x2D7D8, 0x624
	.incbin "baserom.nds", 0x2DDFC, 0x228
	.incbin "baserom.nds", 0x2E024, 0x228
	.incbin "baserom.nds", 0x2E24C, 0x140
	.incbin "baserom.nds", 0x2E38C, 0x624
	.incbin "baserom.nds", 0x2E9B0, 0x228
	.incbin "baserom.nds", 0x2EBD8, 0x228
	.incbin "baserom.nds", 0x2EE00, 0x8040
	.incbin "baserom.nds", 0x36E40, 0x228
	.incbin "baserom.nds", 0x37068, 0x624
	.incbin "baserom.nds", 0x3768C, 0x1D8
	.incbin "baserom.nds", 0x37864, 0x1D8
	.balign 4, 255
