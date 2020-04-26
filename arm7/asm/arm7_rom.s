/* arm7_rom.s TODO: Disassemble */
	.include "asm/macros.inc"
	.include "global.inc"

	.section .itcm
	.incbin "baserom.nds", 0x30D1B0, 0xDC

	.section .dtcm
	.incbin "baserom.nds", 0x30D28C, 0x90D4

	thumb_func_start SVC_SoftReset
SVC_SoftReset: ; 0x02389360
	swi 0
	bx lr

	thumb_func_start SVC_WaitByLoop
SVC_WaitByLoop: ; 0x02389364
	swi 3
	bx lr

	thumb_func_start SVC_WaitIntr
SVC_WaitIntr: ; 0x02389368
	ldr r2, =0x04000000
	mov ip, r2
	mov r2, #0x0
	swi 4
	bx lr
	.pool

	thumb_func_start SVC_WaitVBlankIntr
SVC_WaitVBlankIntr:
	mov r2, #0x0
	swi 5
	bx lr

	non_word_aligned_thumb_func_start SVC_Halt
SVC_Halt:
	swi 6
	bx lr

	non_word_aligned_thumb_func_start SVC_Stop
SVC_Stop:
	swi 7
	bx lr

	non_word_aligned_thumb_func_start SVC_SoundBias
SVC_SoundBias:
	swi 8
	bx lr

	non_word_aligned_thumb_func_start SVC_SoundBiasSet
SVC_SoundBiasSet:
	add r1, r0, #0x0
	mov r0, #0x1
	swi 8
	bx lr

	non_word_aligned_thumb_func_start SVC_SoundBiasReset
SVC_SoundBiasReset:
	add r1, r0, #0x0
	mov r0, #0x0
	swi 8
	bx lr

	non_word_aligned_thumb_func_start SVC_Div
SVC_Div:
	swi 9
	bx lr

	non_word_aligned_thumb_func_start SVC_DivRem
SVC_DivRem:
	swi 9
	add r0, r1, #0x0
	bx lr
	.incbin "baserom.nds", 0x3163a4, 0x65F4

	.section .ewram
	.incbin "baserom.nds", 0x31C998, 0x19960
