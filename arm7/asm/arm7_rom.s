/* arm7_rom.s TODO: Disassemble */
	.include "asm/macros.inc"
	.include "global.inc"

	.section .itcm
	arm_func_start FUNC_027E0000
FUNC_027E0000: ; 0x027E0000 load at 0x023801B0
	stmdb	sp!, {r4, r5, r6, lr}
	ldr	r6, [pc, #180]	; 0x270
	ldr	r3, [pc, #180]	; 0x274
	ldr	r0, [pc, #180]	; 0x278
	b	_027E00B0
_027E0014:
	mov	r2, r3
	ldr	r5, [r3, #4]
	add	r1, r3, #8
	add	r3, r3, #12
	ldr	r4, [r1]
	ldr	r1, [r2]
	cmp	r1, #100663296	; 0x6000000
	bne	_027E00AC
	ldr	r3, [pc, #144]	; 0x27c
	ldr	r0, [pc, #144]	; 0x280
	str	r3, [r0]
	add	r2, r5, r4
	ldr	r0, [pc, #136]	; 0x284
	str	r2, [r0]
	ldr	r1, [pc, #132]	; 0x288
	add	r0, r3, r2
	cmp	r1, r0
	beq	_027E0060
	bl	FUN_037FB1F0
_027E0060:
	ldr	r0, [pc, #104]	; 0x280
	ldr	r3, [r0]
	mov	r2, #0
	mov	r1, r5, lsr #2
	b	_027E0080
_027E0074:
	ldr	r0, [r6], #4
	str	r0, [r3], #4
	add	r2, r2, #1
_027E0080:
	cmp	r2, r1
	bcc	_027E0074
	mov	r1, #0
	mov	r2, r4, lsr #2
	mov	r0, r1
	b	_027E00A0
_027E0098:
	str	r0, [r3], #4
	add	r1, r1, #1
_027E00A0:
	cmp	r1, r2
	bcc	_027E0098
	b	_027E00B8
_027E00AC:
	add	r6, r6, r5
_027E00B0:
	cmp	r3, r0
	bne	_027E0014
_027E00B8:
	ldmia	sp!, {r4, r5, r6, lr}
	bx	lr
_027E00C0: .word 0x023801B0
_027E00C4: .word 0x023A92F8
_027E00C8: .word 0x023A931C
_027E00CC: .word 0x027E00DC
_027E00D0: .word 0x0380A3F4
_027E00D4: .word 0x0380A3FC
_027E00D8: .word 0x027FAFCC

	.section .dtcm
	.incbin "baserom.nds", 0x30D28C, 0x31F0

	arm_func_start FUN_037FB1F0
FUN_037FB1F0: ; 0x037FB1F0
	.incbin "baserom.nds", 0x31047C, 0x5EE4

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
