/* secure.s TODO: Disassemble */
	.include "asm/macros.inc"

.section .text

.incbin "baserom.nds", 0x4000, 0x19E

	non_word_aligned_thumb_func_start SVC_Sqrt
SVC_Sqrt: ; 0x0200019E
	swi 13
	bx lr
	thumb_func_end SVC_Sqrt

.incbin "baserom.nds", 0x41A2, 0x15C

	non_word_aligned_thumb_func_start FUN_020002FE
FUN_020002FE: ; 0x020002FE
	swi 11
	bx lr

.incbin "baserom.nds", 0x4302, 0x2F0

	non_word_aligned_thumb_func_start SVC_WaitByLoop
SVC_WaitByLoop:
	swi 3
	bx lr

.incbin "baserom.nds", 0x45F6, 0x20A
