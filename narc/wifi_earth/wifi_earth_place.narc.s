	.text
	; NARC header
	.ascii "NARC"
	.short 0xFFFE ; byte order
	.short 0x0100 ; version
	.word 0x00000CC8 ; size
	.short 0x0010 ; chunk size
	.short 3 ; number following chunks

	; BTAF header
	.ascii "BTAF"
	.word 0x000000A4 ; chunk size
	.short 19 ; number of files
	.balign 4
	.word 0x00000000, 0x00000064
	.word 0x00000064, 0x00000084
	.word 0x00000084, 0x000000F4
	.word 0x000000F4, 0x0000012C
	.word 0x0000012C, 0x000001AC
	.word 0x000001AC, 0x000001F0
	.word 0x000001F0, 0x00000238
	.word 0x00000238, 0x00000254
	.word 0x00000254, 0x000002B0
	.word 0x000002B0, 0x000002E4
	.word 0x000002E4, 0x00000374
	.word 0x00000374, 0x000003C8
	.word 0x000003C8, 0x00000494
	.word 0x00000494, 0x000004E8
	.word 0x000004E8, 0x0000052C
	.word 0x0000052C, 0x0000054C
	.word 0x0000054C, 0x000005B0
	.word 0x000005B0, 0x00000680
	.word 0x00000680, 0x00000BFC

	; BTNF header
	.ascii "BTNF"
	.word 0x00000010 ; chunk size
	.word 0x00000004 ; offset to first dir
	.short 0 ; first file
	.short 1 ; number of directories

	; GMIF header
	.ascii "GMIF"
	.word 0x00000C04 ; chunk size
	.incbin "baserom.nds", 0x37D78CC, 0x64
	.incbin "baserom.nds", 0x37D7930, 0x20
	.incbin "baserom.nds", 0x37D7950, 0x70
	.incbin "baserom.nds", 0x37D79C0, 0x38
	.incbin "baserom.nds", 0x37D79F8, 0x80
	.incbin "baserom.nds", 0x37D7A78, 0x44
	.incbin "baserom.nds", 0x37D7ABC, 0x48
	.incbin "baserom.nds", 0x37D7B04, 0x1C
	.incbin "baserom.nds", 0x37D7B20, 0x5C
	.incbin "baserom.nds", 0x37D7B7C, 0x34
	.incbin "baserom.nds", 0x37D7BB0, 0x90
	.incbin "baserom.nds", 0x37D7C40, 0x54
	.incbin "baserom.nds", 0x37D7C94, 0xCC
	.incbin "baserom.nds", 0x37D7D60, 0x54
	.incbin "baserom.nds", 0x37D7DB4, 0x44
	.incbin "baserom.nds", 0x37D7DF8, 0x20
	.incbin "baserom.nds", 0x37D7E18, 0x64
	.incbin "baserom.nds", 0x37D7E7C, 0xD0
	.incbin "baserom.nds", 0x37D7F4C, 0x57C
