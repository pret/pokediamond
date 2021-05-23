	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	; sFreeList
	.global UNK_021D1DFC
UNK_021D1DFC: ; 0x021D1DFC
	.space 0xc

	; sPrioList
	.global UNK_021D1E08
UNK_021D1E08: ; 0x021D1E08
	.space 0xc

	; sSeqPlayer
	.global UNK_021D1E14
UNK_021D1E14: ; 0x021D1E14
	.space 0x440

	; sPlayer
	.global UNK_021D2254
UNK_021D2254: ; 0x021D2254
	.space 0x8

	; sPlayer + 0x8
	.global UNK_021D225C
UNK_021D225C: ; 0x021D225C
	.space 0x10

	; sPlayer + 0x18
	.global UNK_021D226C
UNK_021D226C: ; 0x021D226C
	.space 0x4

	; sPlayer + 0x1C
	.global UNK_021D2270
UNK_021D2270: ; 0x021D2270
	.space 0x4

	; sPlayer + 0x20
	.global UNK_021D2274
UNK_021D2274: ; 0x021D2274
	.space 0x460

	.section .text

	; SetPlayerPriority
	arm_func_start FUN_020C06CC
FUN_020C06CC: ; 0x020C06CC
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldr r4, [r6, #0x4]
	mov r5, r1
	cmp r4, #0x0
	beq _020C06F8
	mov r0, r4
	mov r1, r6
	bl FUN_020ADAB0
	mov r0, #0x0
	str r0, [r6, #0x4]
_020C06F8:
	ldr r0, _020C0728 ; =UNK_021D1E08
	mov r1, r6
	bl FUN_020ADAB0
	strb r5, [r6, #0x3d]
	cmp r4, #0x0
	beq _020C071C
	mov r0, r4
	mov r1, r6
	bl FUN_020C0910
_020C071C:
	mov r0, r6
	bl FUN_020C08B4
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C0728: .word UNK_021D1E08

	; PlayerHeapDisposeCallback
	arm_func_start FUN_020C072C
FUN_020C072C: ; 0x020C072C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
	bl FUN_020C2A7C
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x8]
	ldmneia sp!, {r4,pc}
	ldr r1, [r4, #0x10]
	ldr r2, _020C0778 ; =UNK_021D2254
	mov r0, #0x24
	mla r0, r1, r0, r2
	mov r1, r4
	add r0, r0, #0xc
	bl FUN_020ADAB0
	ldmia sp!, {r4,pc}
	.balign 4
_020C0778: .word UNK_021D2254

	; ShutdownPlayer
	arm_func_start FUN_020C077C
FUN_020C077C: ; 0x020C077C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x0]
	strne r0, [r4, #0x0]
	ldr r5, [r4, #0x4]
	mov r1, r4
	mov r0, r5
	bl FUN_020ADAB0
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	cmp r1, #0x0
	beq _020C07D8
	add r0, r5, #0xc
	bl FUN_020ADBE8
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	str r1, [r0, #0xc]
	str r1, [r4, #0x8]
_020C07D8:
	ldr r0, _020C0800 ; =UNK_021D1E08
	mov r1, r4
	bl FUN_020ADAB0
	ldr r0, _020C0804 ; =UNK_021D1DFC
	mov r1, r4
	bl FUN_020ADBE8
	mov r0, #0x0
	strb r0, [r4, #0x2c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C0800: .word UNK_021D1E08
_020C0804: .word UNK_021D1DFC

	; AllocSeqPlayer
	arm_func_start FUN_020C0808
FUN_020C0808: ; 0x020C0808
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, _020C0874 ; =UNK_021D1DFC
	mov r1, #0x0
	bl FUN_020ADA98
	movs r4, r0
	bne _020C0850
	ldr r0, _020C0878 ; =UNK_021D1E08
	mov r1, #0x0
	bl FUN_020ADA98
	mov r4, r0
	ldrb r1, [r4, #0x3d]
	cmp r5, r1
	addlt sp, sp, #0x4
	movlt r0, #0x0
	ldmltia sp!, {r4-r5,pc}
	bl FUN_020C087C
_020C0850:
	ldr r0, _020C0874 ; =UNK_021D1DFC
	mov r1, r4
	bl FUN_020ADAB0
	mov r0, r4
	strb r5, [r4, #0x3d]
	bl FUN_020C08B4
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C0874: .word UNK_021D1DFC
_020C0878: .word UNK_021D1E08

	; ForceStopSeq
	arm_func_start FUN_020C087C
FUN_020C087C: ; 0x020C087C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrb r0, [r4, #0x2c]
	cmp r0, #0x2
	bne _020C089C
	ldrb r0, [r4, #0x3c]
	ldr r1, _020C08B0 ; =0xFFFFFD2D
	bl SND_SetPlayerVolume
_020C089C:
	ldrb r0, [r4, #0x3c]
	bl SND_StopSeq
	mov r0, r4
	bl FUN_020C077C
	ldmia sp!, {r4,pc}
	.balign 4
_020C08B0: .word 0xFFFFFD2D

	; InsertPrioList
	arm_func_start FUN_020C08B4
FUN_020C08B4: ; 0x020C08B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, _020C090C ; =UNK_021D1E08
	mov r1, #0x0
	bl FUN_020ADA98
	movs r1, r0
	beq _020C08F8
	ldr r4, _020C090C ; =UNK_021D1E08
_020C08D8:
	ldrb r2, [r5, #0x3d]
	ldrb r0, [r1, #0x3d]
	cmp r2, r0
	blo _020C08F8
	mov r0, r4
	bl FUN_020ADA98
	movs r1, r0
	bne _020C08D8
_020C08F8:
	ldr r0, _020C090C ; =UNK_021D1E08
	mov r2, r5
	bl FUN_020ADB18
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C090C: .word UNK_021D1E08

	; _end
	arm_func_start FUN_020C0910
FUN_020C0910: ; 0x020C0910
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r1, #0x0
	mov r5, r0
	bl FUN_020ADA98
	movs r1, r0
	beq _020C0950
_020C0930:
	ldrb r2, [r4, #0x3d]
	ldrb r0, [r1, #0x3d]
	cmp r2, r0
	blo _020C0950
	mov r0, r5
	bl FUN_020ADA98
	movs r1, r0
	bne _020C0930
_020C0950:
	mov r0, r5
	mov r2, r4
	bl FUN_020ADB18
	str r5, [r4, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	; _end
	arm_func_start FUN_020C0968
FUN_020C0968: ; 0x020C0968
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x0
	strb r0, [r4, #0x2e]
	strb r0, [r4, #0x2d]
	strb r0, [r4, #0x2f]
	strh r0, [r4, #0x34]
	strh r0, [r4, #0x3e]
	mov r1, #0x7f
	strb r1, [r4, #0x40]
	add r0, r4, #0x1c
	strb r1, [r4, #0x41]
	bl FUN_020C3E6C
	add r0, r4, #0x1c
	mov r1, #0x7f00
	mov r2, #0x1
	bl FUN_020C3E40
	ldmia sp!, {r4,pc}

	; NNSi_SndPlayerAllocHeap
	arm_func_start FUN_020C09B0
FUN_020C09B0: ; 0x020C09B0
	stmdb sp!, {r4-r6,lr}
	ldr r3, _020C0A00 ; =UNK_021D2254
	mov r2, #0x24
	mla r5, r0, r2, r3
	mov r6, r1
	add r0, r5, #0xc
	mov r1, #0x0
	bl FUN_020ADA98
	movs r4, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	mov r1, r4
	add r0, r5, #0xc
	bl FUN_020ADAB0
	str r6, [r4, #0xc]
	str r4, [r6, #0x8]
	ldr r0, [r4, #0x8]
	bl FUN_020C29C0
	ldr r0, [r4, #0x8]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C0A00: .word UNK_021D2254

	; _end
	arm_func_start FUN_020C0A04
FUN_020C0A04: ; 0x020C0A04
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r5, r0
	mov r4, r1
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	ldrb r0, [r5, #0x2e]
	cmp r4, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,pc}
	ldrb r0, [r5, #0x3c]
	bl SND_PauseSeq
	strb r4, [r5, #0x2e]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	; _end
	arm_func_start FUN_020C0A40
FUN_020C0A40: ; 0x020C0A40
	stmdb sp!, {r4,lr}
	movs r4, r0
	mov r2, r1
	ldmeqia sp!, {r4,pc}
	ldrb r1, [r4, #0x2c]
	cmp r1, #0x0
	ldmeqia sp!, {r4,pc}
	cmp r2, #0x0
	bne _020C0A6C
	bl FUN_020C087C
	ldmia sp!, {r4,pc}
_020C0A6C:
	add r0, r4, #0x1c
	mov r1, #0x0
	bl FUN_020C3E40
	mov r0, r4
	mov r1, #0x0
	bl FUN_020C06CC
	mov r0, #0x2
	strb r0, [r4, #0x2c]
	ldmia sp!, {r4,pc}

	; NNSi_SndPlayerStartSeq
	arm_func_start FUN_020C0A90
FUN_020C0A90: ; 0x020C0A90
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldrb r0, [r5, #0x3c]
	ldr r4, [r5, #0x4]
	bl SND_PrepareSeq
	ldr r2, [r4, #0x1c]
	cmp r2, #0x0
	beq _020C0AC0
	ldrb r0, [r5, #0x3c]
	ldr r1, _020C0AE4 ; =0x0000FFFF
	bl SND_SetTrackAllocatableChannel
_020C0AC0:
	mov r0, r5
	bl FUN_020C0968
	bl SND_GetCurrentCommandTag
	str r0, [r5, #0x30]
	mov r0, #0x1
	strb r0, [r5, #0x2f]
	strb r0, [r5, #0x2c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C0AE4: .word 0x0000FFFF

	; NNSi_SndPlayerFreeSeqPlayer
	arm_func_start thunk_FUN_020c077c
thunk_FUN_020c077c: ; 0x020C0AE8
	ldr ip, _020C0AF0 ; =FUN_020C077C
	bx r12
	.balign 4
_020C0AF0: .word FUN_020C077C

	; NNSi_SndPlayerAllocSeqPlayer
	arm_func_start FUN_020C0AF4
FUN_020C0AF4: ; 0x020C0AF4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr ip, _020C0B9C ; =UNK_021D2254
	mov r3, #0x24
	mov r4, r0
	ldr r5, [r4, #0x0]
	mla r6, r1, r3, r12
	mov r7, r2
	cmp r5, #0x0
	beq _020C0B20
	bl FUN_020C0F68
_020C0B20:
	ldrh r1, [r6, #0x8]
	ldr r0, [r6, #0x18]
	cmp r1, r0
	blo _020C0B64
	mov r0, r6
	mov r1, #0x0
	bl FUN_020ADA98
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	ldrb r1, [r0, #0x3d]
	cmp r7, r1
	addlt sp, sp, #0x4
	movlt r0, #0x0
	ldmltia sp!, {r4-r7,pc}
	bl FUN_020C087C
_020C0B64:
	mov r0, r7
	bl FUN_020C0808
	movs r5, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	mov r0, r6
	mov r1, r5
	bl FUN_020C0910
	str r4, [r5, #0x0]
	mov r0, r5
	str r5, [r4, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C0B9C: .word UNK_021D2254

	; NNSi_SndPlayerMain
	arm_func_start FUN_020C0BA0
FUN_020C0BA0: ; 0x020C0BA0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	bl SND_GetPlayerStatus
	str r0, [sp, #0x0]
	ldr r0, _020C0D14 ; =UNK_021D1E08
	mov r1, #0x0
	bl FUN_020ADA98
	movs r10, r0
	addeq sp, sp, #0xc
	ldmeqia sp!, {r4-r11,pc}
	mov r0, #0x8000
	rsb r0, r0, #0x0
	ldr r4, _020C0D18 ; =SNDi_DecibelTable
	str r0, [sp, #0x4]
	mov r5, #0x1
	mov r11, #0x0
_020C0BE0:
	ldr r0, _020C0D14 ; =UNK_021D1E08
	mov r1, r10
	bl FUN_020ADA98
	ldrb r1, [r10, #0x2d]
	mov r9, r0
	cmp r1, #0x0
	bne _020C0C0C
	ldr r0, [r10, #0x30]
	bl SND_IsFinishedCommandTag
	cmp r0, #0x0
	strneb r5, [r10, #0x2d]
_020C0C0C:
	ldrb r0, [r10, #0x2d]
	cmp r0, #0x0
	beq _020C0C38
	ldrb r0, [r10, #0x3c]
	mov r1, r5, lsl r0
	ldr r0, [sp, #0x0]
	ands r0, r0, r1
	bne _020C0C38
	mov r0, r10
	bl FUN_020C077C
	b _020C0D00
_020C0C38:
	add r0, r10, #0x1c
	bl FUN_020C3DF4
	ldr r0, [r10, #0x4]
	ldrb r2, [r10, #0x41]
	ldrb r1, [r10, #0x40]
	ldrb r0, [r0, #0x20]
	mov r3, r2, lsl #0x1
	mov r2, r1, lsl #0x1
	mov r1, r0, lsl #0x1
	add r0, r10, #0x1c
	ldrsh r8, [r4, r3]
	ldrsh r7, [r4, r2]
	ldrsh r6, [r4, r1]
	bl FUN_020C3E0C
	mov r0, r0, asr #0x8
	mov r2, r0, lsl #0x1
	add r1, r7, r8
	mov r0, #0x8000
	ldrsh r2, [r4, r2]
	add r1, r6, r1
	rsb r0, r0, #0x0
	add r6, r2, r1
	cmp r6, r0
	ldrlt r6, [sp, #0x4]
	blt _020C0CA8
	ldr r0, _020C0D1C ; =0x00007FFF
	cmp r6, r0
	movgt r6, r0
_020C0CA8:
	ldrsh r0, [r10, #0x3e]
	cmp r6, r0
	beq _020C0CC4
	ldrb r0, [r10, #0x3c]
	mov r1, r6
	bl SND_SetPlayerVolume
	strh r6, [r10, #0x3e]
_020C0CC4:
	ldrb r0, [r10, #0x2c]
	cmp r0, #0x2
	bne _020C0CE8
	add r0, r10, #0x1c
	bl FUN_020C3DDC
	cmp r0, #0x0
	beq _020C0CE8
	mov r0, r10
	bl FUN_020C087C
_020C0CE8:
	ldrb r0, [r10, #0x2f]
	cmp r0, #0x0
	beq _020C0D00
	ldrb r0, [r10, #0x3c]
	bl SND_StartPreparedSeq
	strb r11, [r10, #0x2f]
_020C0D00:
	mov r10, r9
	cmp r9, #0x0
	bne _020C0BE0
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020C0D14: .word UNK_021D1E08
_020C0D18: .word SNDi_DecibelTable
_020C0D1C: .word 0x00007FFF

	; NNSi_SndPlayerInit
	arm_func_start FUN_020C0D20
FUN_020C0D20: ; 0x020C0D20
	stmdb sp!, {r4-r10,lr}
	ldr r0, _020C0DC4 ; =UNK_021D1E08
	mov r1, #0x14
	bl FUN_020ADC74
	ldr r0, _020C0DC8 ; =UNK_021D1DFC
	mov r1, #0x14
	bl FUN_020ADC74
	ldr r6, _020C0DCC ; =UNK_021D1E14
	mov r7, #0x0
	ldr r4, _020C0DC8 ; =UNK_021D1DFC
	mov r5, r7
_020C0D4C:
	strb r5, [r6, #0x2c]
	mov r0, r4
	mov r1, r6
	strb r7, [r6, #0x3c]
	bl FUN_020ADBE8
	add r7, r7, #0x1
	cmp r7, #0x10
	add r6, r6, #0x44
	blt _020C0D4C
	ldr sl, _020C0DD0 ; =UNK_021D2254
	mov r9, #0x0
	mov r7, r9
	mov r4, r9
	mov r8, #0xc
	mov r6, #0x7f
	mov r5, #0x1
_020C0D8C:
	mov r0, r10
	mov r1, r8
	bl FUN_020ADC74
	mov r1, r7
	add r0, r10, #0xc
	bl FUN_020ADC74
	strb r6, [r10, #0x20]
	str r5, [r10, #0x18]
	add r9, r9, #0x1
	str r4, [r10, #0x1c]
	cmp r9, #0x20
	add r10, r10, #0x24
	blt _020C0D8C
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020C0DC4: .word UNK_021D1E08
_020C0DC8: .word UNK_021D1DFC
_020C0DCC: .word UNK_021D1E14
_020C0DD0: .word UNK_021D2254

	; _end
	arm_func_start FUN_020C0DD4
FUN_020C0DD4: ; 0x020C0DD4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {pc}
	ldrb r0, [r1, #0x2d]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {pc}
	ldrb r0, [r1, #0x3c]
	bl SND_GetPlayerTickCounter
	add sp, sp, #0x4
	ldmia sp!, {pc}

	; _end
	arm_func_start FUN_020C0E14
FUN_020C0E14: ; 0x020C0E14
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	mvneq r0, #0x0
	bxeq lr
	ldrh r0, [r1, #0x34]
	cmp r0, #0x1
	mvnne r0, #0x0
	ldreqh r0, [r1, #0x38]
	bx lr

	; _end
	arm_func_start FUN_020C0E38
FUN_020C0E38: ; 0x020C0E38
	ldr r12, [r0, #0x0]
	cmp r12, #0x0
	bxeq lr
	mov r3, #0x2
	strh r3, [r12, #0x34]
	ldr r3, [r0, #0x0]
	strh r1, [r3, #0x38]
	ldr r0, [r0, #0x0]
	strh r2, [r0, #0x3a]
	bx lr

	; _end
	arm_func_start FUN_020C0E60
FUN_020C0E60: ; 0x020C0E60
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	movne r2, #0x1
	strneh r2, [r3, #0x34]
	ldrne r0, [r0, #0x0]
	strneh r1, [r0, #0x38]
	bx lr

	; _end
	arm_func_start FUN_020C0E7C
FUN_020C0E7C: ; 0x020C0E7C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldrb r0, [r0, #0x3c]
	bl SND_SetTrackPan
	add sp, sp, #0x4
	ldmia sp!, {pc}

	; _end
	arm_func_start FUN_020C0EA4
FUN_020C0EA4: ; 0x020C0EA4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldrb r0, [r0, #0x3c]
	bl SND_SetTrackPitch
	add sp, sp, #0x4
	ldmia sp!, {pc}

	; _end
	arm_func_start FUN_020C0ECC
FUN_020C0ECC: ; 0x020C0ECC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldrb r0, [r0, #0x3c]
	bl SND_SetPlayerChannelPriority
	add sp, sp, #0x4
	ldmia sp!, {pc}

	; _end
	arm_func_start FUN_020C0EF4
FUN_020C0EF4: ; 0x020C0EF4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	ldrb r0, [r3, #0x2c]
	cmp r0, #0x2
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	add r0, r3, #0x1c
	mov r1, r1, lsl #0x8
	bl FUN_020C3E40
	add sp, sp, #0x4
	ldmia sp!, {pc}

	; _end
	arm_func_start FUN_020C0F30
FUN_020C0F30: ; 0x020C0F30
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	strneb r1, [r0, #0x40]
	bx lr

	; _end
	arm_func_start FUN_020C0F40
FUN_020C0F40: ; 0x020C0F40
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	strneb r1, [r0, #0x41]
	bx lr

	; NNS_SndPlayerCountPlayingSeqByPlayerNo
	arm_func_start FUN_020C0F50
FUN_020C0F50: ; 0x020C0F50
	mov r1, #0x24
	mul r1, r0, r1
	ldr r0, _020C0F64 ; =UNK_021D225C
	ldrh r0, [r0, r1]
	bx lr
	.balign 4
_020C0F64: .word UNK_021D225C

	; _end
	arm_func_start FUN_020C0F68
FUN_020C0F68: ; 0x020C0F68
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	movne r1, #0x0
	strne r1, [r2, #0x0]
	strne r1, [r0, #0x0]
	bx lr

	; _end
	arm_func_start FUN_020C0F80
FUN_020C0F80: ; 0x020C0F80
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr

	; NNS_SndPlayerPause
	arm_func_start FUN_020C0F8C
FUN_020C0F8C: ; 0x020C0F8C
	ldr ip, _020C0F98 ; =FUN_020C0A04
	ldr r0, [r0, #0x0]
	bx r12
	.balign 4
_020C0F98: .word FUN_020C0A04

	; NNS_SndPlayerStopSeqAll
	arm_func_start FUN_020C0F9C
FUN_020C0F9C: ; 0x020C0F9C
	stmdb sp!, {r4-r6,lr}
	ldr r4, _020C0FD8 ; =UNK_021D1E14
	mov r6, r0
	mov r5, #0x0
_020C0FAC:
	ldrb r0, [r4, #0x2c]
	cmp r0, #0x0
	beq _020C0FC4
	mov r0, r4
	mov r1, r6
	bl FUN_020C0A40
_020C0FC4:
	add r5, r5, #0x1
	cmp r5, #0x10
	add r4, r4, #0x44
	blt _020C0FAC
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C0FD8: .word UNK_021D1E14

	; NNS_SndPlayerStopSeqBySeqNo
	arm_func_start FUN_020C0FDC
FUN_020C0FDC: ; 0x020C0FDC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r4, _020C103C ; =UNK_021D1E14
	mov r7, r0
	mov r6, r1
	mov r5, #0x0
_020C0FF4:
	ldrb r0, [r4, #0x2c]
	cmp r0, #0x0
	beq _020C1024
	ldrh r0, [r4, #0x34]
	cmp r0, #0x1
	bne _020C1024
	ldrh r0, [r4, #0x38]
	cmp r0, r7
	bne _020C1024
	mov r0, r4
	mov r1, r6
	bl FUN_020C0A40
_020C1024:
	add r5, r5, #0x1
	cmp r5, #0x10
	add r4, r4, #0x44
	blt _020C0FF4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C103C: .word UNK_021D1E14

	; NNS_SndPlayerStopSeqByPlayerNo
	arm_func_start FUN_020C1040
FUN_020C1040: ; 0x020C1040
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r3, _020C109C ; =UNK_021D2254
	mov r2, #0x24
	mla r4, r0, r2, r3
	ldr r5, _020C10A0 ; =UNK_021D1E14
	mov r7, r1
	mov r6, #0x0
_020C1060:
	ldrb r0, [r5, #0x2c]
	cmp r0, #0x0
	beq _020C1084
	ldr r0, [r5, #0x4]
	cmp r0, r4
	bne _020C1084
	mov r0, r5
	mov r1, r7
	bl FUN_020C0A40
_020C1084:
	add r6, r6, #0x1
	cmp r6, #0x10
	add r5, r5, #0x44
	blt _020C1060
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C109C: .word UNK_021D2254
_020C10A0: .word UNK_021D1E14

	; NNS_SndPlayerStopSeq
	arm_func_start FUN_020C10A4
FUN_020C10A4: ; 0x020C10A4
	ldr ip, _020C10B0 ; =FUN_020C0A40
	ldr r0, [r0, #0x0]
	bx r12
	.balign 4
_020C10B0: .word FUN_020C0A40

	; NNS_SndPlayerCreateHeap
	arm_func_start FUN_020C10B4
FUN_020C10B4: ; 0x020C10B4
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r5, r2
	mov r6, r0
	mov r0, r1
	mov r3, #0x0
	ldr r2, _020C1140 ; =FUN_020C072C
	add r1, r5, #0x14
	str r3, [sp, #0x0]
	bl SDATi_AllocAndInitChunk
	movs r4, r0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	mov r2, #0x0
	str r2, [r4, #0xc]
	str r6, [r4, #0x10]
	mov r1, r5
	add r0, r4, #0x14
	str r2, [r4, #0x8]
	bl FUN_020C2A94
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r2, _020C1144 ; =UNK_021D2254
	mov r1, #0x24
	mla r2, r6, r1, r2
	str r0, [r4, #0x8]
	mov r1, r4
	add r0, r2, #0xc
	bl FUN_020ADBE8
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C1140: .word FUN_020C072C
_020C1144: .word UNK_021D2254

	; NNS_SndPlayerSetAllocatableChannel
	arm_func_start FUN_020C1148
FUN_020C1148: ; 0x020C1148
	mov r2, #0x24
	mul r2, r0, r2
	ldr r0, _020C115C ; =UNK_021D2270
	str r1, [r0, r2]
	bx lr
	.balign 4
_020C115C: .word UNK_021D2270

	; NNS_SndPlayerSetPlayableSeqCount
	arm_func_start FUN_020C1160
FUN_020C1160: ; 0x020C1160
	mov r2, #0x24
	mul r2, r0, r2
	mov r0, r1, lsl #0x10
	ldr r1, _020C117C ; =UNK_021D226C
	mov r0, r0, lsr #0x10
	str r0, [r1, r2]
	bx lr
	.balign 4
_020C117C: .word UNK_021D226C

	; NNS_SndPlayerSetPlayerVolume
	arm_func_start FUN_020C1180
FUN_020C1180: ; 0x020C1180
	mov r2, #0x24
	mul r2, r0, r2
	ldr r0, _020C1194 ; =UNK_021D2274
	strb r1, [r0, r2]
	bx lr
	.balign 4
_020C1194: .word UNK_021D2274

