	.text
	.global ROMTitles
ROMTitles:
	; UTF16LE has a leading short that should be skipped
	.incbin "data/title/title.txt", 2
	.space 0x100-(.-ROMTitles)
	.incbin "data/title/title.txt", 2
	.space 0x200-(.-ROMTitles)
	.incbin "data/title/title.txt", 2
	.space 0x300-(.-ROMTitles)
	.incbin "data/title/title.txt", 2
	.space 0x400-(.-ROMTitles)
	.incbin "data/title/title.txt", 2
	.space 0x500-(.-ROMTitles)
	.incbin "data/title/title.txt", 2
	.space 0x600-(.-ROMTitles)
