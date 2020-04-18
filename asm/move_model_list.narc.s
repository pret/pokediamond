	; There are two NARCs with the same name
	; TODO: actual file structure
	.section .narc.1DE7E00
NARC_1DE7E00:
	.incbin "baserom.nds", 0x1DE7E00, 0x61C

	.section .narc.1E73400
NARC_1E73400:
	.incbin "baserom.nds", 0x1E73400, 0x364

