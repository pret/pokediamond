	.text

	.global ARM9Overlay
ARM9Overlay:
	.incbin "baserom.nds", 0x10B800, 0xAE0
