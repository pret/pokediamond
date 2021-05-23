	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	; sPrepareThread
	.global UNK_021D2900
UNK_021D2900: ; 0x021D2900
	.space 0x4

	; sFreeCommandList
	.global UNK_021D2904
UNK_021D2904: ; 0x021D2904
	.space 0x4d4

	; sFreeCommandList + 0x4D4
	.global UNK_021D2DD8
UNK_021D2DD8: ; 0x021D2DD8
	.space 0x18

	; sFreeCommandList + 0x4EC
	.global UNK_021D2DF0
UNK_021D2DF0: ; 0x021D2DF0
	.space 0xc

	; sStrmPlayer
	.global UNK_021D2DFC
UNK_021D2DFC: ; 0x021D2DFC
	.space 0x5c0

	.section .text

	; FreeCommandBuffer
	arm_func_start FUN_020C3A6C
FUN_020C3A6C: ; 0x020C3A6C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	mov r4, r0
	ldr r0, _020C3A9C ; =UNK_021D2904
	mov r1, r5
	bl FUN_020ADBE8
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020C3A9C: .word UNK_021D2904

	; _end
	arm_func_start FUN_020C3AA0
FUN_020C3AA0: ; 0x020C3AA0
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	bl OS_DisableInterrupts
	mov r6, r0
	mov r0, r8
	mov r1, #0x0
	bl FUN_020ADA98
	movs r5, r0
	beq _020C3B04
_020C3AC8:
	mov r0, r8
	mov r1, r5
	bl FUN_020ADA98
	ldr r1, [r5, #0x8]
	mov r4, r0
	cmp r1, r7
	bne _020C3AF8
	mov r0, r8
	mov r1, r5
	bl FUN_020ADAB0
	mov r0, r5
	bl FUN_020C3A6C
_020C3AF8:
	mov r5, r4
	cmp r4, #0x0
	bne _020C3AC8
_020C3B04:
	mov r0, r6
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,pc}

	; _end
	arm_func_start FUN_020C3B10
FUN_020C3B10: ; 0x020C3B10
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
	bl FUN_020C1674
	add sp, sp, #0x4
	ldmia sp!, {pc}

	; ShutdownPlayer
	arm_func_start FUN_020C3B4C
FUN_020C3B4C: ; 0x020C3B4C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0x110]
	mov r1, r1, lsl #0x1f
	movs r1, r1, asr #0x1f
	ldmeqia sp!, {r4,pc}
	bl FUN_020C3B10
	ldr r1, [r4, #0x164]
	mov r0, r4
	blx r1
	ldr r0, _020C3BA8 ; =UNK_021D2DF0
	mov r1, r4
	bl FUN_020C3AA0
	ldr r0, _020C3BAC ; =UNK_021D2900
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020C3B9C
	mov r1, r4
	add r0, r0, #0x4e0
	bl FUN_020C3AA0
_020C3B9C:
	mov r0, r4
	bl FUN_020C3C4C
	ldmia sp!, {r4,pc}
	.balign 4
_020C3BA8: .word UNK_021D2DF0
_020C3BAC: .word UNK_021D2900

	; ForceStopStrm
	arm_func_start FUN_020C3BB0
FUN_020C3BB0: ; 0x020C3BB0
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, _020C3C40 ; =UNK_021D2DD8
	bl OS_LockMutex
	ldr r0, _020C3C44 ; =UNK_021D2900
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
	bl FUN_020C1430
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
	bl FUN_020C3B4C
	ldr r0, _020C3C40 ; =UNK_021D2DD8
	bl OS_UnlockMutex
	ldr r0, _020C3C44 ; =UNK_021D2900
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r0, _020C3C48 ; =0x000004C8
	add r0, r1, r0
	bl OS_UnlockMutex
	ldmia sp!, {r4,pc}
	.balign 4
_020C3C40: .word UNK_021D2DD8
_020C3C44: .word UNK_021D2900
_020C3C48: .word 0x000004C8

	; _end
	arm_func_start FUN_020C3C4C
FUN_020C3C4C: ; 0x020C3C4C
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

	; NNSi_SndArcStrmMain
	arm_func_start FUN_020C3C88
FUN_020C3C88: ; 0x020C3C88
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r5, _020C3D94 ; =UNK_021D2DFC
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
	bl FUN_020C3BB0
	b _020C3D7C
_020C3CC4:
	mov r0, r1, lsl #0x1d
	movs r0, r0, asr #0x1f
	beq _020C3CFC
	ldr r0, [r5, #0x118]
	cmp r0, #0x0
	beq _020C3CFC
	mov r0, r5
	bl FUN_020C1458
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
	bl FUN_020C3DF4
	ldr r1, [r5, #0x154]
	add r0, r5, #0xe8
	mov r1, r1, lsl #0x1
	ldrsh r6, [r4, r1]
	bl FUN_020C3E0C
	mov r0, r0, asr #0x8
	mov r0, r0, lsl #0x1
	ldrsh r1, [r4, r0]
	ldr r0, [r5, #0x158]
	add r6, r1, r6
	cmp r6, r0
	beq _020C3D54
	mov r0, r5
	mov r1, r6
	bl FUN_020C13C4
	str r6, [r5, #0x158]
_020C3D54:
	ldr r0, [r5, #0x110]
	mov r0, r0, lsl #0x1c
	movs r0, r0, asr #0x1f
	beq _020C3D7C
	add r0, r5, #0xe8
	bl FUN_020C3DDC
	cmp r0, #0x0
	beq _020C3D7C
	mov r0, r5
	bl FUN_020C3BB0
_020C3D7C:
	add r7, r7, #0x1
	cmp r7, #0x4
	add r5, r5, #0x170
	blt _020C3C9C
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,pc}
	.balign 4
_020C3D94: .word UNK_021D2DFC
_020C3D98: .word SNDi_DecibelTable

