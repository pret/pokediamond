	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global sPrepareThread
sPrepareThread: ; 0x021D2900
	.space 0x4

	.global sFreeCommandList
sFreeCommandList: ; 0x021D2904
	.space 0xC
	; sStrmThread
	.global sStrmThread
sStrmThread: ; 0x021D2910
	.space 0x4EC

	.global sStrmPlayer
sStrmPlayer: ; 0x021D2DFC
	.space 0x5c0

	.section .text

	arm_func_start FreeCommandBuffer
FreeCommandBuffer: ; 0x020C3A6C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	mov r4, r0
	ldr r0, _020C3A9C ; =sFreeCommandList
	mov r1, r5
	bl NNS_FndAppendListObject
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C3A9C: .word sFreeCommandList

	arm_func_start RemoveCommandByPlayer
RemoveCommandByPlayer: ; 0x020C3AA0
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	bl OS_DisableInterrupts
	mov r6, r0
	mov r0, r8
	mov r1, #0x0
	bl NNS_FndGetNextListObject
	movs r5, r0
	beq _020C3B04
_020C3AC8:
	mov r0, r8
	mov r1, r5
	bl NNS_FndGetNextListObject
	ldr r1, [r5, #0x8]
	mov r4, r0
	cmp r1, r7
	bne _020C3AF8
	mov r0, r8
	mov r1, r5
	bl NNS_FndRemoveListObject
	mov r0, r5
	bl FreeCommandBuffer
_020C3AF8:
	mov r5, r4
	cmp r4, #0x0
	bne _020C3AC8
_020C3B04:
	mov r0, r6
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,pc}

	arm_func_start FreeChannel
FreeChannel: ; 0x020C3B10
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, [r0, #0x120]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {pc}
	sub r1, r1, #0x1
	str r1, [r0, #0x120]
	ldr r1, [r0, #0x120]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {pc}
	bl NNS_SndStrmFreeChannel
	add sp, sp, #0x4
	ldmia sp!, {pc}

	local_arm_func_start ShutdownPlayer
ShutdownPlayer: ; 0x020C3B4C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0x110]
	mov r1, r1, lsl #0x1f
	movs r1, r1, asr #0x1f
	ldmeqia sp!, {r4,pc}
	bl FreeChannel
	ldr r1, [r4, #0x164]
	mov r0, r4
	blx r1
	ldr r0, _020C3BA8 ; =sStrmThread + 0x4E0
	mov r1, r4
	bl RemoveCommandByPlayer
	ldr r0, _020C3BAC ; =sPrepareThread
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020C3B9C
	mov r1, r4
	add r0, r0, #0x4e0
	bl RemoveCommandByPlayer
_020C3B9C:
	mov r0, r4
	bl FreePlayer
	ldmia sp!, {r4,pc}
	.balign 4
_020C3BA8: .word sStrmThread + 0x4E0
_020C3BAC: .word sPrepareThread

	local_arm_func_start ForceStopStrm
ForceStopStrm: ; 0x020C3BB0
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, _020C3C40 ; =sStrmThread + 0x4C8
	bl OS_LockMutex
	ldr r0, _020C3C44 ; =sPrepareThread
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _020C3BDC
	ldr r0, _020C3C48 ; =0x000004C8
	add r0, r1, r0
	bl OS_LockMutex
_020C3BDC:
	ldr r0, [r4, #0x110]
	mov r0, r0, lsl #0x1e
	movs r0, r0, asr #0x1f
	beq _020C3BF4
	mov r0, r4
	bl NNS_SndStrmStop
_020C3BF4:
	ldr r0, [r4, #0x110]
	mov r0, r0, lsl #0x1f
	movs r0, r0, asr #0x1f
	beq _020C3C10
	ldr r1, [r4, #0x16c]
	mov r0, r4
	blx r1
_020C3C10:
	mov r0, r4
	bl ShutdownPlayer
	ldr r0, _020C3C40 ; =sStrmThread + 0x4C8
	bl OS_UnlockMutex
	ldr r0, _020C3C44 ; =sPrepareThread
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r0, _020C3C48 ; =0x000004C8
	add r0, r1, r0
	bl OS_UnlockMutex
	ldmia sp!, {r4,pc}
	.balign 4
_020C3C40: .word sStrmThread + 0x4C8
_020C3C44: .word sPrepareThread
_020C3C48: .word 0x000004C8

	arm_func_start FreePlayer
FreePlayer: ; 0x020C3C4C
	ldr r2, [r0, #0x14c]
	cmp r2, #0x0
	movne r1, #0x0
	strne r1, [r2, #0x0]
	strne r1, [r0, #0x14c]
	ldr r1, [r0, #0x110]
	bic r1, r1, #0x1
	str r1, [r0, #0x110]
	ldr r1, [r0, #0x110]
	bic r1, r1, #0x4
	str r1, [r0, #0x110]
	ldr r1, [r0, #0x110]
	bic r1, r1, #0x2
	str r1, [r0, #0x110]
	bx lr

	arm_func_start NNSi_SndArcStrmMain
NNSi_SndArcStrmMain: ; 0x020C3C88
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r5, _020C3D94 ; =sStrmPlayer
	mov r7, #0x0
	ldr r4, _020C3D98 ; =SNDi_DecibelTable
_020C3C9C:
	ldr r1, [r5, #0x110]
	mov r0, r1, lsl #0x1f
	movs r0, r0, asr #0x1f
	beq _020C3D7C
	ldr r0, [r5, #0x114]
	cmp r0, #0x0
	bne _020C3CC4
	mov r0, r5
	bl ForceStopStrm
	b _020C3D7C
_020C3CC4:
	mov r0, r1, lsl #0x1d
	movs r0, r0, asr #0x1f
	beq _020C3CFC
	ldr r0, [r5, #0x118]
	cmp r0, #0x0
	beq _020C3CFC
	mov r0, r5
	bl NNS_SndStrmStart
	ldr r0, [r5, #0x110]
	orr r0, r0, #0x2
	str r0, [r5, #0x110]
	ldr r0, [r5, #0x110]
	bic r0, r0, #0x4
	str r0, [r5, #0x110]
_020C3CFC:
	ldr r0, [r5, #0x110]
	mov r0, r0, lsl #0x1e
	movs r0, r0, asr #0x1f
	beq _020C3D7C
	add r0, r5, #0xe8
	bl NNSi_SndFaderUpdate
	ldr r1, [r5, #0x154]
	add r0, r5, #0xe8
	mov r1, r1, lsl #0x1
	ldrsh r6, [r4, r1]
	bl NNSi_SndFaderGet
	mov r0, r0, asr #0x8
	mov r0, r0, lsl #0x1
	ldrsh r1, [r4, r0]
	ldr r0, [r5, #0x158]
	add r6, r1, r6
	cmp r6, r0
	beq _020C3D54
	mov r0, r5
	mov r1, r6
	bl NNS_SndStrmSetVolume
	str r6, [r5, #0x158]
_020C3D54:
	ldr r0, [r5, #0x110]
	mov r0, r0, lsl #0x1c
	movs r0, r0, asr #0x1f
	beq _020C3D7C
	add r0, r5, #0xe8
	bl NNSi_SndFaderIsFinished
	cmp r0, #0x0
	beq _020C3D7C
	mov r0, r5
	bl ForceStopStrm
_020C3D7C:
	add r7, r7, #0x1
	cmp r7, #0x4
	add r5, r5, #0x170
	blt _020C3C9C
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C3D94: .word sStrmPlayer
_020C3D98: .word SNDi_DecibelTable
