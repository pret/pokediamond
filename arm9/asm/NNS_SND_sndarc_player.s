	.include "asm/macros.inc"
	.include "global.inc"

	.section .text

	arm_func_start StartSeqArc
StartSeqArc: ; 0x020C36C8
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r7, r2
	mov r2, r3
	ldr r6, [sp, #0x20]
	mov r4, r0
	mov r8, r1
	bl NNSi_SndPlayerAllocSeqPlayer
	movs r5, r0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	mov r0, r8
	mov r1, r5
	bl NNSi_SndPlayerAllocHeap
	add r12, sp, #0x4
	mov r2, r0
	mov r0, r7
	mov r1, #0x6
	mov r3, #0x0
	str r12, [sp, #0x0]
	bl NNSi_SndArcLoadBank
	cmp r0, #0x0
	beq _020C373C
	mov r0, r5
	bl NNSi_SndPlayerFreeSeqPlayer
	add sp, sp, #0x8
	mov r0, #0x0
	ldmia sp!, {r4-r8,pc}
_020C373C:
	ldr r12, [sp, #0x24]
	ldr r2, [r6, #0x0]
	ldr r1, [r12, #0x18]
	ldr r3, [sp, #0x4]
	mov r0, r5
	add r1, r12, r1
	bl NNSi_SndPlayerStartSeq
	ldrb r1, [r6, #0x6]
	mov r0, r4
	bl NNS_SndPlayerSetInitialVolume
	ldrb r1, [r6, #0x7]
	mov r0, r4
	bl NNS_SndPlayerSetChannelPriority
	ldr r1, [sp, #0x28]
	ldr r2, [sp, #0x2c]
	mov r0, r4
	bl NNS_SndPlayerSetSeqArcNo
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,pc}

	arm_func_start StartSeq
StartSeq: ; 0x020C378C
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	mov r8, r2
	mov r2, r3
	ldr r5, [sp, #0x28]
	mov r6, r0
	mov r7, r1
	bl NNSi_SndPlayerAllocSeqPlayer
	movs r4, r0
	addeq sp, sp, #0x10
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	mov r0, r7
	mov r1, r4
	bl NNSi_SndPlayerAllocHeap
	mov r7, r0
	add r12, sp, #0x8
	mov r0, r8
	mov r2, r7
	mov r1, #0x6
	mov r3, #0x0
	str r12, [sp, #0x0]
	bl NNSi_SndArcLoadBank
	cmp r0, #0x0
	beq _020C3804
	mov r0, r4
	bl NNSi_SndPlayerFreeSeqPlayer
	add sp, sp, #0x10
	mov r0, #0x0
	ldmia sp!, {r4-r8,pc}
_020C3804:
	ldr r0, [sp, #0x2c]
	add r12, sp, #0x4
	mov r2, r7
	mov r1, #0x1
	mov r3, #0x0
	str r12, [sp, #0x0]
	bl NNSi_SndArcLoadSeq
	cmp r0, #0x0
	beq _020C383C
	mov r0, r4
	bl NNSi_SndPlayerFreeSeqPlayer
	add sp, sp, #0x10
	mov r0, #0x0
	ldmia sp!, {r4-r8,pc}
_020C383C:
	ldr r2, [sp, #0x4]
	ldr r3, [sp, #0x8]
	ldr r1, [r2, #0x18]
	mov r0, r4
	add r1, r2, r1
	mov r2, #0x0
	bl NNSi_SndPlayerStartSeq
	ldrb r1, [r5, #0x6]
	mov r0, r6
	bl NNS_SndPlayerSetInitialVolume
	ldrb r1, [r5, #0x7]
	mov r0, r6
	bl NNS_SndPlayerSetChannelPriority
	ldr r1, [sp, #0x2c]
	mov r0, r6
	bl NNS_SndPlayerSetSeqNo
	mov r0, #0x1
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}

	arm_func_start NNS_SndArcPlayerStartSeqArc
NNS_SndArcPlayerStartSeqArc: ; 0x020C3888
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov r6, r1
	mov r7, r0
	mov r0, r6
	mov r5, r2
	bl NNS_SndArcGetSeqArcInfo
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	ldr r0, [r0, #0x0]
	bl NNS_SndArcGetFileAddress
	movs r4, r0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	mov r1, r5
	bl NNSi_SndSeqArcGetSeqInfo
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	str r6, [sp, #0x8]
	str r5, [sp, #0xc]
	ldrb r1, [r0, #0x9]
	ldrh r2, [r0, #0x4]
	ldrb r3, [r0, #0x8]
	mov r0, r7
	bl StartSeqArc
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,pc}

	arm_func_start NNS_SndArcPlayerStartSeqEx
NNS_SndArcPlayerStartSeqEx: ; 0x020C3910
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	mov r7, r0
	ldr r0, [sp, #0x20]
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl NNS_SndArcGetSeqInfo
	cmp r0, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	cmp r4, #0x0
	ldrltb r4, [r0, #0x8]
	cmp r5, #0x0
	ldrlth r5, [r0, #0x4]
	cmp r6, #0x0
	ldrltb r6, [r0, #0x9]
	ldr r12, [sp, #0x20]
	mov r2, r5
	str r0, [sp, #0x0]
	mov r0, r7
	mov r1, r6
	mov r3, r4
	str r12, [sp, #0x4]
	bl StartSeq
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,pc}

	arm_func_start NNS_SndArcPlayerStartSeq
NNS_SndArcPlayerStartSeq: ; 0x020C3980
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r4, r1
	mov r5, r0
	mov r0, r4
	bl NNS_SndArcGetSeqInfo
	cmp r0, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	ldrb r1, [r0, #0x9]
	ldrh r2, [r0, #0x4]
	ldrb r3, [r0, #0x8]
	mov r0, r5
	bl StartSeq
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}

	arm_func_start NNS_SndArcPlayerSetup
NNS_SndArcPlayerSetup: ; 0x020C39CC
	stmdb sp!, {r4-r8,lr}
	mov r6, r0
	bl NNS_SndArcGetCurrent
	mov r5, #0x0
	mov r7, r5
_020C39E0:
	mov r0, r5
	bl NNS_SndArcGetPlayerInfo
	movs r4, r0
	beq _020C3A58
	ldrb r1, [r4, #0x0]
	mov r0, r5
	bl NNS_SndPlayerSetPlayableSeqCount
	ldrh r1, [r4, #0x2]
	mov r0, r5
	bl NNS_SndPlayerSetAllocatableChannel
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _020C3A58
	cmp r6, #0x0
	beq _020C3A58
	ldrb r0, [r4, #0x0]
	mov r8, r7
	cmp r0, #0x0
	ble _020C3A58
_020C3A2C:
	ldr r2, [r4, #0x4]
	mov r0, r5
	mov r1, r6
	bl NNS_SndPlayerCreateHeap
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,pc}
	ldrb r0, [r4, #0x0]
	add r8, r8, #0x1
	cmp r8, r0
	blt _020C3A2C
_020C3A58:
	add r5, r5, #0x1
	cmp r5, #0x20
	blt _020C39E0
	mov r0, #0x1
	ldmia sp!, {r4-r8,pc}
