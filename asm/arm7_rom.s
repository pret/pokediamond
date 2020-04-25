/* arm7_rom.s TODO: Disassemble */
	.include "asm/macros.inc"
	.global ARM7AutoLoad

	.section .text
	arm_func_start Entry_ARM7

Entry_ARM7:
	mov	ip, #67108864	; 0x4000000
	str	ip, [ip, #520]	; 0x208
	ldr	r1, _23800cc
	mov	r0, #58720256	; 0x3800000
	cmp	r0, r1
	movpl	r1, r0
	ldr	r2, _23800d0
	mov	r0, #0
_02380020:
	cmp	r1, r2
	stmltia	r1!, {r0}
	blt	_02380020
	mov	r0, #19
	msr	CPSR_c, r0
	ldr	sp, _23800d4
	mov	r0, #18
	msr	CPSR_c, r0
	ldr	r0, _23800d8
	mov	sp, r0
	ldr	r1, _23800dc
	sub	r1, r0, r1
	mov	r0, #31
	msr	CPSR_fsxc, r0
	sub	sp, r1, #4
	ldr	r0, _23800e0
	ldr	r1, _23800e4
	add	r2, r1, #352	; 0x160
_02380068:
	ldr	r3, [r0], #4
	str	r3, [r1], #4
	cmp	r1, r2
	bmi	_02380068
	ldr	r0, _23800e8
	add	r2, r1, #32
_02380080:
	ldr	r3, [r0], #4
	str	r3, [r1], #4
	cmp	r1, r2
	bmi	_02380080
	bl	FUN_2380100
	ldr	r0, _23800ec
	ldr	r1, [r0, #12]
	ldr	r2, [r0, #16]
	mov	r0, #0
_023800a4:
	cmp	r1, r2
	strcc	r0, [r1], #4
	bcc	_023800a4
	bl	FUN_238015C
	ldr	r1, _23800f0
	ldr	r0, _23800f4
	str	r0, [r1]
	ldr	r1, _23800f8
	ldr	lr, _23800fc
	bx	r1
_23800cc:	.word FUN_023801B0
_23800d0:	.word 0x0380ff00
_23800d4:	.word 0x0380ffc0
_23800d8:	.word 0x0380ff80
_23800dc:	.word 0x00000400
_23800e0:	.word 0x023fe940
_23800e4:	.word 0x027ffa80
_23800e8:	.word 0x023fe904
_23800ec:	.word _2380198
_23800f0:	.word 0x0380fffc
_23800f4:	.word 0x037f853c
_23800f8:	.word 0x037f8468
_23800fc:	.word 0xffff0000
	arm_func_end Entry_ARM7

	arm_func_start FUN_2380100
FUN_2380100:
	ldr	r0, _2380154
	ldr	r1, [r0]
	ldr	r2, [r0, #4]
	ldr	r3, [r0, #8]
_02380110:
	cmp	r1, r2
	beq	_02380150
	ldr	r4, [r1], #4
	ldr	r5, [r1], #4
	add	r6, r4, r5
_02380124:
	cmp	r4, r6
	ldrmi	r7, [r3], #4
	strmi	r7, [r4], #4
	bmi	_02380124
	ldr	r5, [r1], #4
	add	r6, r4, r5
	mov	r7, #0
_02380140:
	cmp	r4, r6
	strcc	r7, [r4], #4
	bcc	_02380140
	beq	_02380110
_02380150:
	b	ARM7AutoLoad
_2380154:	.word _2380198
ARM7AutoLoad:
	bx	lr
	arm_func_end FUN_2380100

	arm_func_start FUN_238015C
FUN_238015C:
	mov	r0, #1
	mov	r1, #0
	ldr	r2, _2380194
	sub	r3, r2, #4194304	; 0x400000
_0238016c:
	strh	r1, [r2]
	ldrh	ip, [r3]
	cmp	r1, ip
	movne	r0, #2
	bne	_0238018c
	add	r1, r1, #1
	cmp	r1, #2
	bne	_0238016c
_0238018c:
	strh	r0, [r2]
	bx	lr
_2380194:	.word 0x027ffffa
_2380198:
	.word UNK_23A92F8
	.word UNK_23A931C
	.word FUN_023801B0
	.word FUN_023801B0
	.word FUN_023801B0
	.word 0x00000000
	arm_func_end FUN_238015C

	arm_func_start FUN_023801B0
FUN_023801B0:
	.incbin "baserom.nds", 0x30D1B0, 0x91B0

	thumb_func_start ROM7_SVC_SoftReset
ROM7_SVC_SoftReset: ; 0x02389360
	swi 0
	bx lr

	thumb_func_start ROM7_SVC_WaitByLoop
ROM7_SVC_WaitByLoop: ; 0x02389364
	swi 3
	bx lr

	thumb_func_start ROM7_SVC_WaitIntr
ROM7_SVC_WaitIntr: ; 0x02389368
	ldr r2, =0x04000000
	mov ip, r2
	mov r2, #0x0
	swi 4
	bx lr
	.pool

	thumb_func_start ROM7_SVC_WaitVBlankIntr
ROM7_SVC_WaitVBlankIntr:
	mov r2, #0x0
	swi 5
	bx lr

	non_word_aligned_thumb_func_start ROM7_SVC_Halt
ROM7_SVC_Halt:
	swi 6
	bx lr

	non_word_aligned_thumb_func_start ROM7_SVC_Stop
ROM7_SVC_Stop:
	swi 7
	bx lr

	non_word_aligned_thumb_func_start ROM7_SVC_SoundBias
ROM7_SVC_SoundBias:
	swi 8
	bx lr

	non_word_aligned_thumb_func_start ROM7_SVC_SoundBiasSet
ROM7_SVC_SoundBiasSet:
	add r1, r0, #0x0
	mov r0, #0x1
	swi 8
	bx lr

	non_word_aligned_thumb_func_start ROM7_SVC_SoundBiasReset
ROM7_SVC_SoundBiasReset:
	add r1, r0, #0x0
	mov r0, #0x0
	swi 8
	bx lr

	non_word_aligned_thumb_func_start ROM7_SVC_Div
ROM7_SVC_Div:
	swi 9
	bx lr

	non_word_aligned_thumb_func_start ROM7_SVC_DivRem
ROM7_SVC_DivRem:
	swi 9
	add r0, r1, #0x0
	bx lr
	.incbin "baserom.nds", 0x3163a4, 0x1ff54

UNK_23A92F8:
	.incbin "baserom.nds", 0x3362F8, 0x24

UNK_23A931C:
