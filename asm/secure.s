/* secure.s TODO: Disassemble */
	.include "asm/macros.inc"

.section .text

.incbin "baserom.nds", 0x4000, 0x5F2

	thumb_func_start
FUN_020005F2:
	swi 3
	bx lr

.incbin "baserom.nds", 0x45F6, 0x20A
