/* secure.s TODO: Disassemble */

.section .text

.incbin "baserom.nds", 0x4000, 0x5F2

	.global FUN_020005F2
	.thumb
FUN_020005F2:
	swi 3
	bx lr

.incbin "baserom.nds", 0x45F6, 0x20A
