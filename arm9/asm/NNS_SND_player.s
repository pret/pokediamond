	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global sFreeList
sFreeList: ; 0x021D1DFC
	.space 0xc

	.global sPrioList
sPrioList: ; 0x021D1E08
	.space 0xc

	.global sSeqPlayer
sSeqPlayer: ; 0x021D1E14
	.space 0x440

	.global sPlayer
sPlayer: ; 0x021D2254
	.space 0x480

	.section .text

	arm_func_start SetPlayerPriority
SetPlayerPriority: ; 0x020C06CC
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldr r4, [r6, #0x4]
	mov r5, r1
	cmp r4, #0x0
	beq _020C06F8
	mov r0, r4
	mov r1, r6
	bl NNS_FndRemoveListObject
	mov r0, #0x0
	str r0, [r6, #0x4]
_020C06F8:
	ldr r0, _020C0728 ; =sPrioList
	mov r1, r6
	bl NNS_FndRemoveListObject
	strb r5, [r6, #0x3d]
	cmp r4, #0x0
	beq _020C071C
	mov r0, r4
	mov r1, r6
	bl InsertPlayerList
_020C071C:
	mov r0, r6
	bl InsertPrioList
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C0728: .word sPrioList

	arm_func_start PlayerHeapDisposeCallback
PlayerHeapDisposeCallback: ; 0x020C072C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	ldmeqia sp!, {r4,pc}
	bl NNS_SndHeapDestroy
	ldr r1, [r4, #0xc]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x8]
	ldmneia sp!, {r4,pc}
	ldr r1, [r4, #0x10]
	ldr r2, _020C0778 ; =sPlayer
	mov r0, #0x24
	mla r0, r1, r0, r2
	mov r1, r4
	add r0, r0, #0xc
	bl NNS_FndRemoveListObject
	ldmia sp!, {r4,pc}
	.balign 4
_020C0778: .word sPlayer

	local_arm_func_start ShutdownPlayer
ShutdownPlayer: ; 0x020C077C
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
	bl NNS_FndRemoveListObject
	mov r0, #0x0
	str r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	cmp r1, #0x0
	beq _020C07D8
	add r0, r5, #0xc
	bl NNS_FndAppendListObject
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	str r1, [r0, #0xc]
	str r1, [r4, #0x8]
_020C07D8:
	ldr r0, _020C0800 ; =sPrioList
	mov r1, r4
	bl NNS_FndRemoveListObject
	ldr r0, _020C0804 ; =sFreeList
	mov r1, r4
	bl NNS_FndAppendListObject
	mov r0, #0x0
	strb r0, [r4, #0x2c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C0800: .word sPrioList
_020C0804: .word sFreeList

	arm_func_start AllocSeqPlayer
AllocSeqPlayer: ; 0x020C0808
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, _020C0874 ; =sFreeList
	mov r1, #0x0
	bl NNS_FndGetNextListObject
	movs r4, r0
	bne _020C0850
	ldr r0, _020C0878 ; =sPrioList
	mov r1, #0x0
	bl NNS_FndGetNextListObject
	mov r4, r0
	ldrb r1, [r4, #0x3d]
	cmp r5, r1
	addlt sp, sp, #0x4
	movlt r0, #0x0
	ldmltia sp!, {r4-r5,pc}
	bl ForceStopSeq
_020C0850:
	ldr r0, _020C0874 ; =sFreeList
	mov r1, r4
	bl NNS_FndRemoveListObject
	mov r0, r4
	strb r5, [r4, #0x3d]
	bl InsertPrioList
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C0874: .word sFreeList
_020C0878: .word sPrioList

	arm_func_start ForceStopSeq
ForceStopSeq: ; 0x020C087C
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
	bl ShutdownPlayer
	ldmia sp!, {r4,pc}
	.balign 4
_020C08B0: .word 0xFFFFFD2D

	arm_func_start InsertPrioList
InsertPrioList: ; 0x020C08B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, _020C090C ; =sPrioList
	mov r1, #0x0
	bl NNS_FndGetNextListObject
	movs r1, r0
	beq _020C08F8
	ldr r4, _020C090C ; =sPrioList
_020C08D8:
	ldrb r2, [r5, #0x3d]
	ldrb r0, [r1, #0x3d]
	cmp r2, r0
	blo _020C08F8
	mov r0, r4
	bl NNS_FndGetNextListObject
	movs r1, r0
	bne _020C08D8
_020C08F8:
	ldr r0, _020C090C ; =sPrioList
	mov r2, r5
	bl NNS_FndInsertListObject
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C090C: .word sPrioList

	arm_func_start InsertPlayerList
InsertPlayerList: ; 0x020C0910
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r1
	mov r1, #0x0
	mov r5, r0
	bl NNS_FndGetNextListObject
	movs r1, r0
	beq _020C0950
_020C0930:
	ldrb r2, [r4, #0x3d]
	ldrb r0, [r1, #0x3d]
	cmp r2, r0
	blo _020C0950
	mov r0, r5
	bl NNS_FndGetNextListObject
	movs r1, r0
	bne _020C0930
_020C0950:
	mov r0, r5
	mov r2, r4
	bl NNS_FndInsertListObject
	str r5, [r4, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start InitPlayer
InitPlayer: ; 0x020C0968
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
	bl NNSi_SndFaderInit
	add r0, r4, #0x1c
	mov r1, #0x7f00
	mov r2, #0x1
	bl NNSi_SndFaderSet
	ldmia sp!, {r4,pc}

	arm_func_start NNSi_SndPlayerAllocHeap
NNSi_SndPlayerAllocHeap: ; 0x020C09B0
	stmdb sp!, {r4-r6,lr}
	ldr r3, _020C0A00 ; =sPlayer
	mov r2, #0x24
	mla r5, r0, r2, r3
	mov r6, r1
	add r0, r5, #0xc
	mov r1, #0x0
	bl NNS_FndGetNextListObject
	movs r4, r0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	mov r1, r4
	add r0, r5, #0xc
	bl NNS_FndRemoveListObject
	str r6, [r4, #0xc]
	str r4, [r6, #0x8]
	ldr r0, [r4, #0x8]
	bl NNS_SndHeapClear
	ldr r0, [r4, #0x8]
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C0A00: .word sPlayer

	arm_func_start NNSi_SndPlayerPause
NNSi_SndPlayerPause: ; 0x020C0A04
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

	arm_func_start NNSi_SndPlayerStopSeq
NNSi_SndPlayerStopSeq: ; 0x020C0A40
	stmdb sp!, {r4,lr}
	movs r4, r0
	mov r2, r1
	ldmeqia sp!, {r4,pc}
	ldrb r1, [r4, #0x2c]
	cmp r1, #0x0
	ldmeqia sp!, {r4,pc}
	cmp r2, #0x0
	bne _020C0A6C
	bl ForceStopSeq
	ldmia sp!, {r4,pc}
_020C0A6C:
	add r0, r4, #0x1c
	mov r1, #0x0
	bl NNSi_SndFaderSet
	mov r0, r4
	mov r1, #0x0
	bl SetPlayerPriority
	mov r0, #0x2
	strb r0, [r4, #0x2c]
	ldmia sp!, {r4,pc}

	arm_func_start NNSi_SndPlayerStartSeq
NNSi_SndPlayerStartSeq: ; 0x020C0A90
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
	bl InitPlayer
	bl SND_GetCurrentCommandTag
	str r0, [r5, #0x30]
	mov r0, #0x1
	strb r0, [r5, #0x2f]
	strb r0, [r5, #0x2c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C0AE4: .word 0x0000FFFF

	arm_func_start NNSi_SndPlayerFreeSeqPlayer
NNSi_SndPlayerFreeSeqPlayer: ; 0x020C0AE8
	ldr ip, _020C0AF0 ; =ShutdownPlayer
	bx r12
	.balign 4
_020C0AF0: .word ShutdownPlayer

	arm_func_start NNSi_SndPlayerAllocSeqPlayer
NNSi_SndPlayerAllocSeqPlayer: ; 0x020C0AF4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr ip, _020C0B9C ; =sPlayer
	mov r3, #0x24
	mov r4, r0
	ldr r5, [r4, #0x0]
	mla r6, r1, r3, r12
	mov r7, r2
	cmp r5, #0x0
	beq _020C0B20
	bl NNS_SndHandleReleaseSeq
_020C0B20:
	ldrh r1, [r6, #0x8]
	ldr r0, [r6, #0x18]
	cmp r1, r0
	blo _020C0B64
	mov r0, r6
	mov r1, #0x0
	bl NNS_FndGetNextListObject
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	ldrb r1, [r0, #0x3d]
	cmp r7, r1
	addlt sp, sp, #0x4
	movlt r0, #0x0
	ldmltia sp!, {r4-r7,pc}
	bl ForceStopSeq
_020C0B64:
	mov r0, r7
	bl AllocSeqPlayer
	movs r5, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7,pc}
	mov r0, r6
	mov r1, r5
	bl InsertPlayerList
	str r4, [r5, #0x0]
	mov r0, r5
	str r5, [r4, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C0B9C: .word sPlayer

	arm_func_start NNSi_SndPlayerMain
NNSi_SndPlayerMain: ; 0x020C0BA0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	bl SND_GetPlayerStatus
	str r0, [sp, #0x0]
	ldr r0, _020C0D14 ; =sPrioList
	mov r1, #0x0
	bl NNS_FndGetNextListObject
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
	ldr r0, _020C0D14 ; =sPrioList
	mov r1, r10
	bl NNS_FndGetNextListObject
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
	bl ShutdownPlayer
	b _020C0D00
_020C0C38:
	add r0, r10, #0x1c
	bl NNSi_SndFaderUpdate
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
	bl NNSi_SndFaderGet
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
	bl NNSi_SndFaderIsFinished
	cmp r0, #0x0
	beq _020C0CE8
	mov r0, r10
	bl ForceStopSeq
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
_020C0D14: .word sPrioList
_020C0D18: .word SNDi_DecibelTable
_020C0D1C: .word 0x00007FFF

	arm_func_start NNSi_SndPlayerInit
NNSi_SndPlayerInit: ; 0x020C0D20
	stmdb sp!, {r4-r10,lr}
	ldr r0, _020C0DC4 ; =sPrioList
	mov r1, #0x14
	bl NNS_FndInitList
	ldr r0, _020C0DC8 ; =sFreeList
	mov r1, #0x14
	bl NNS_FndInitList
	ldr r6, _020C0DCC ; =sSeqPlayer
	mov r7, #0x0
	ldr r4, _020C0DC8 ; =sFreeList
	mov r5, r7
_020C0D4C:
	strb r5, [r6, #0x2c]
	mov r0, r4
	mov r1, r6
	strb r7, [r6, #0x3c]
	bl NNS_FndAppendListObject
	add r7, r7, #0x1
	cmp r7, #0x10
	add r6, r6, #0x44
	blt _020C0D4C
	ldr sl, _020C0DD0 ; =sPlayer
	mov r9, #0x0
	mov r7, r9
	mov r4, r9
	mov r8, #0xc
	mov r6, #0x7f
	mov r5, #0x1
_020C0D8C:
	mov r0, r10
	mov r1, r8
	bl NNS_FndInitList
	mov r1, r7
	add r0, r10, #0xc
	bl NNS_FndInitList
	strb r6, [r10, #0x20]
	str r5, [r10, #0x18]
	add r9, r9, #0x1
	str r4, [r10, #0x1c]
	cmp r9, #0x20
	add r10, r10, #0x24
	blt _020C0D8C
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020C0DC4: .word sPrioList
_020C0DC8: .word sFreeList
_020C0DCC: .word sSeqPlayer
_020C0DD0: .word sPlayer

	arm_func_start NNS_SndPlayerGetTick
NNS_SndPlayerGetTick: ; 0x020C0DD4
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

	arm_func_start NNS_SndPlayerGetSeqNo
NNS_SndPlayerGetSeqNo: ; 0x020C0E14
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	mvneq r0, #0x0
	bxeq lr
	ldrh r0, [r1, #0x34]
	cmp r0, #0x1
	mvnne r0, #0x0
	ldreqh r0, [r1, #0x38]
	bx lr

	arm_func_start NNS_SndPlayerSetSeqArcNo
NNS_SndPlayerSetSeqArcNo: ; 0x020C0E38
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

	arm_func_start NNS_SndPlayerSetSeqNo
NNS_SndPlayerSetSeqNo: ; 0x020C0E60
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	movne r2, #0x1
	strneh r2, [r3, #0x34]
	ldrne r0, [r0, #0x0]
	strneh r1, [r0, #0x38]
	bx lr

	arm_func_start NNS_SndPlayerSetTrackPan
NNS_SndPlayerSetTrackPan: ; 0x020C0E7C
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

	arm_func_start NNS_SndPlayerSetTrackPitch
NNS_SndPlayerSetTrackPitch: ; 0x020C0EA4
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

	arm_func_start NNS_SndPlayerSetChannelPriority
NNS_SndPlayerSetChannelPriority: ; 0x020C0ECC
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

	arm_func_start NNS_SndPlayerMoveVolume
NNS_SndPlayerMoveVolume: ; 0x020C0EF4
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
	bl NNSi_SndFaderSet
	add sp, sp, #0x4
	ldmia sp!, {pc}

	arm_func_start NNS_SndPlayerSetInitialVolume
NNS_SndPlayerSetInitialVolume: ; 0x020C0F30
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	strneb r1, [r0, #0x40]
	bx lr

	arm_func_start NNS_SndPlayerSetVolume
NNS_SndPlayerSetVolume: ; 0x020C0F40
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	strneb r1, [r0, #0x41]
	bx lr

	arm_func_start NNS_SndPlayerCountPlayingSeqByPlayerNo
NNS_SndPlayerCountPlayingSeqByPlayerNo: ; 0x020C0F50
	mov r1, #0x24
	mul r1, r0, r1
	ldr r0, _020C0F64 ; =sPlayer + 0x8
	ldrh r0, [r0, r1]
	bx lr
	.balign 4
_020C0F64: .word sPlayer + 0x8

	arm_func_start NNS_SndHandleReleaseSeq
NNS_SndHandleReleaseSeq: ; 0x020C0F68
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	movne r1, #0x0
	strne r1, [r2, #0x0]
	strne r1, [r0, #0x0]
	bx lr

	arm_func_start NNS_SndHandleInit
NNS_SndHandleInit: ; 0x020C0F80
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr

	arm_func_start NNS_SndPlayerPause
NNS_SndPlayerPause: ; 0x020C0F8C
	ldr ip, _020C0F98 ; =NNSi_SndPlayerPause
	ldr r0, [r0, #0x0]
	bx r12
	.balign 4
_020C0F98: .word NNSi_SndPlayerPause

	arm_func_start NNS_SndPlayerStopSeqAll
NNS_SndPlayerStopSeqAll: ; 0x020C0F9C
	stmdb sp!, {r4-r6,lr}
	ldr r4, _020C0FD8 ; =sSeqPlayer
	mov r6, r0
	mov r5, #0x0
_020C0FAC:
	ldrb r0, [r4, #0x2c]
	cmp r0, #0x0
	beq _020C0FC4
	mov r0, r4
	mov r1, r6
	bl NNSi_SndPlayerStopSeq
_020C0FC4:
	add r5, r5, #0x1
	cmp r5, #0x10
	add r4, r4, #0x44
	blt _020C0FAC
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C0FD8: .word sSeqPlayer

	arm_func_start NNS_SndPlayerStopSeqBySeqNo
NNS_SndPlayerStopSeqBySeqNo: ; 0x020C0FDC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r4, _020C103C ; =sSeqPlayer
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
	bl NNSi_SndPlayerStopSeq
_020C1024:
	add r5, r5, #0x1
	cmp r5, #0x10
	add r4, r4, #0x44
	blt _020C0FF4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C103C: .word sSeqPlayer

	arm_func_start NNS_SndPlayerStopSeqByPlayerNo
NNS_SndPlayerStopSeqByPlayerNo: ; 0x020C1040
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r3, _020C109C ; =sPlayer
	mov r2, #0x24
	mla r4, r0, r2, r3
	ldr r5, _020C10A0 ; =sSeqPlayer
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
	bl NNSi_SndPlayerStopSeq
_020C1084:
	add r6, r6, #0x1
	cmp r6, #0x10
	add r5, r5, #0x44
	blt _020C1060
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C109C: .word sPlayer
_020C10A0: .word sSeqPlayer

	arm_func_start NNS_SndPlayerStopSeq
NNS_SndPlayerStopSeq: ; 0x020C10A4
	ldr ip, _020C10B0 ; =NNSi_SndPlayerStopSeq
	ldr r0, [r0, #0x0]
	bx r12
	.balign 4
_020C10B0: .word NNSi_SndPlayerStopSeq

	arm_func_start NNS_SndPlayerCreateHeap
NNS_SndPlayerCreateHeap: ; 0x020C10B4
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r5, r2
	mov r6, r0
	mov r0, r1
	mov r3, #0x0
	ldr r2, _020C1140 ; =PlayerHeapDisposeCallback
	add r1, r5, #0x14
	str r3, [sp, #0x0]
	bl NNS_SndHeapAlloc
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
	bl NNS_SndHeapCreate
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	ldr r2, _020C1144 ; =sPlayer
	mov r1, #0x24
	mla r2, r6, r1, r2
	str r0, [r4, #0x8]
	mov r1, r4
	add r0, r2, #0xc
	bl NNS_FndAppendListObject
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,pc}
	.balign 4
_020C1140: .word PlayerHeapDisposeCallback
_020C1144: .word sPlayer

	arm_func_start NNS_SndPlayerSetAllocatableChannel
NNS_SndPlayerSetAllocatableChannel: ; 0x020C1148
	mov r2, #0x24
	mul r2, r0, r2
	ldr r0, _020C115C ; =sPlayer + 0x1C
	str r1, [r0, r2]
	bx lr
	.balign 4
_020C115C: .word sPlayer + 0x1C

	arm_func_start NNS_SndPlayerSetPlayableSeqCount
NNS_SndPlayerSetPlayableSeqCount: ; 0x020C1160
	mov r2, #0x24
	mul r2, r0, r2
	mov r0, r1, lsl #0x10
	ldr r1, _020C117C ; =sPlayer + 0x18
	mov r0, r0, lsr #0x10
	str r0, [r1, r2]
	bx lr
	.balign 4
_020C117C: .word sPlayer + 0x18

	arm_func_start NNS_SndPlayerSetPlayerVolume
NNS_SndPlayerSetPlayerVolume: ; 0x020C1180
	mov r2, #0x24
	mul r2, r0, r2
	ldr r0, _020C1194 ; =sPlayer + 0x20
	strb r1, [r0, r2]
	bx lr
	.balign 4
_020C1194: .word sPlayer + 0x20
