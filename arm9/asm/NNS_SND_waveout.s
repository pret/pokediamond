	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	; sWaveOut
	.global UNK_021D1CBC
UNK_021D1CBC: ; 0x021D1CBC
	.space 0x140

	.section .text

	; _end
	arm_func_start FUN_020C03B8
FUN_020C03B8: ; 0x020C03B8
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r0, [r4, #0xc]
	cmp r0, #0x0
	bne _020C03F8
	ldr r0, [r4, #0x10]
	bl SND_IsFinishedCommandTag
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4,pc}
	mov r0, #0x1
	str r0, [r4, #0xc]
_020C03F8:
	bl SND_GetChannelStatus
	ldr r1, [r4, #0x0]
	mov r2, #0x1
	mov r1, r2, lsl r1
	ands r0, r1, r0
	movne r0, r2
	moveq r0, #0x0
	streq r0, [r4, #0x8]
	ldmia sp!, {r4,pc}

	; _end
	arm_func_start FUN_020C041C
FUN_020C041C: ; 0x020C041C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r0, [r0, #0x0]
	mov r2, #0x1
	mov r0, r2, lsl r0
	bl SND_SetChannelPan
	add sp, sp, #0x4
	ldmia sp!, {pc}

	; NNS_SndWaveOutSetSpeed
	arm_func_start FUN_020C044C
FUN_020C044C: ; 0x020C044C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, [r5, #0x8]
	mov r4, r1
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	ldr r2, [r5, #0x4]
	ldr r0, _020C04D4 ; =0xD87F8000
	mov r3, r2, asr #0x1f
	mov r1, #0x7f
	bl _ll_udiv
	mov r2, r4
	mov r3, r4, asr #0x1f
	bl _ll_udiv
	mov r2, #0x0
	mov r3, r0
	mov r0, #0x10
	cmp r1, r2
	cmpeq r3, r0
	movcc r3, r0
	blo _020C04B8
	ldr r0, _020C04D8 ; =0x0000FFFF
	cmp r1, r2
	cmpeq r3, r0
	movhi r3, r0
_020C04B8:
	ldr r0, [r5, #0x0]
	mov r1, #0x1
	mov r0, r1, lsl r0
	mov r1, r3
	bl SND_SetChannelTimer
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C04D4: .word 0xD87F8000
_020C04D8: .word 0x0000FFFF

	; _end
	arm_func_start FUN_020C04DC
FUN_020C04DC: ; 0x020C04DC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldr r0, [r0, #0x0]
	mov r2, #0x1
	mov r0, r2, lsl r0
	mov r2, #0x0
	bl SND_SetChannelVolume
	add sp, sp, #0x4
	ldmia sp!, {pc}

	; _end
	arm_func_start FUN_020C0510
FUN_020C0510: ; 0x020C0510
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r0, [r4, #0x0]
	mov r2, #0x1
	mov r1, #0x0
	mov r0, r2, lsl r0
	mov r2, r1
	mov r3, r1
	bl SND_StopTimer
	mov r0, #0x0
	str r0, [r4, #0x8]
	ldmia sp!, {r4,pc}

	; NNS_SndWaveOutStart
	arm_func_start FUN_020C054C
FUN_020C054C: ; 0x020C054C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x1c
	movs r8, r1
	mov r9, r0
	mov r7, r2
	mov r6, r3
	beq _020C0584
	cmp r8, #0x1
	ldreq r0, [sp, #0x3c]
	ldreq r1, [sp, #0x38]
	moveq r0, r0, asr #0x1
	moveq r5, r1, asr #0x1
	subeq r4, r0, r1, asr #0x1
	b _020C0598
_020C0584:
	ldr r0, [sp, #0x3c]
	ldr r1, [sp, #0x38]
	mov r0, r0, asr #0x2
	mov r5, r1, asr #0x2
	sub r4, r0, r1, asr #0x2
_020C0598:
	ldr r2, [sp, #0x40]
	ldr r0, _020C0668 ; =0xD87F8000
	mov r3, r2, asr #0x1f
	mov r1, #0x7f
	bl _ll_udiv
	ldr r2, [sp, #0x48]
	mov r3, r2, asr #0x1f
	bl _ll_udiv
	mov r3, #0x0
	mov r2, #0x10
	cmp r1, r3
	cmpeq r0, r2
	movcc r0, r2
	blo _020C05E0
	ldr r2, _020C066C ; =0x0000FFFF
	cmp r1, r3
	cmpeq r0, r2
	movhi r0, r2
_020C05E0:
	str r5, [sp, #0x0]
	ldr r1, [sp, #0x44]
	str r4, [sp, #0x4]
	str r1, [sp, #0x8]
	mov r1, #0x0
	str r1, [sp, #0xc]
	cmp r6, #0x0
	movne r3, #0x1
	ldr r1, [sp, #0x4c]
	str r0, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r0, [r9, #0x0]
	moveq r3, #0x2
	mov r1, r8
	mov r2, r7
	bl SND_SetupChannelPcm
	mov r1, #0x0
	ldr r0, [r9, #0x0]
	mov r2, #0x1
	mov r0, r2, lsl r0
	mov r2, r1
	mov r3, r1
	bl SND_StartTimer
	mov r0, #0x1
	str r0, [r9, #0x8]
	mov r0, #0x0
	str r0, [r9, #0xc]
	bl SND_GetCurrentCommandTag
	str r0, [r9, #0x10]
	ldr r1, [sp, #0x40]
	mov r0, #0x1
	str r1, [r9, #0x4]
	add sp, sp, #0x1c
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020C0668: .word 0xD87F8000
_020C066C: .word 0x0000FFFF

	; NNS_SndWaveOutFreeChannel
	arm_func_start FUN_020C0670
FUN_020C0670: ; 0x020C0670
	ldr r0, [r0, #0x0]
	mov r1, #0x1
	ldr ip, _020C0684 ; =FUN_020C0340
	mov r0, r1, lsl r0
	bx r12
	.balign 4
_020C0684: .word FUN_020C0340

	; NNS_SndWaveOutAllocChannel
	arm_func_start FUN_020C0688
FUN_020C0688: ; 0x020C0688
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x1
	mov r0, r0, lsl r4
	bl FUN_020C0370
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	mov r0, #0x14
	mul r0, r4, r0
	ldr r2, _020C06C8 ; =UNK_021D1CBC
	mov r1, #0x0
	str r4, [r2, r0]
	add r0, r2, r0
	str r1, [r0, #0x8]
	ldmia sp!, {r4,pc}
	.balign 4
_020C06C8: .word UNK_021D1CBC

