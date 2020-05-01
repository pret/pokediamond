    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start SND_GetWaveDataAddress
SND_GetWaveDataAddress: ; 0x020CF768
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl SNDi_LockMutex
	add r0, r5, r4, lsl #0x2
	ldr r4, [r0, #0x3c]
	cmp r4, #0x0
	beq _020CF798
	cmp r4, #0x2000000
	addcc r4, r5, r4
	b _020CF79C
_020CF798:
	mov r4, #0x0
_020CF79C:
	bl SNDi_UnlockMutex
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SND_SetWaveDataAddress
SND_SetWaveDataAddress: ; 0x020CF7B0
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl SNDi_LockMutex
	add r0, r6, #0x3c
	add r2, r6, r5, lsl #0x2
	add r0, r0, r5, lsl #0x2
	mov r1, #0x4
	str r4, [r2, #0x3c]
	bl DC_StoreRange
	bl SNDi_UnlockMutex
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start SND_GetWaveDataCount
SND_GetWaveDataCount: ; 0x020CF7E8
	ldr r0, [r0, #0x38]
	bx lr

	arm_func_start SND_GetNextInstData
SND_GetNextInstData: ; 0x020CF7F0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r4, [r2, #0x0]
	ldr r3, [r0, #0x38]
	cmp r4, r3
	bhs _020CF9B8
	mov r12, #0x0
_020CF80C:
	add r3, r0, r4, lsl #0x2
	ldr r4, [r3, #0x3c]
	strb r4, [r1, #0x0]
	ldrb r3, [r1, #0x0]
	cmp r3, #0x10
	bgt _020CF850
	cmp r3, #0x10
	bge _020CF8A8
	cmp r3, #0x5
	addls pc, pc, r3, lsl #0x2
	b _020CF998
_020CF838:
	b _020CF998
	b _020CF85C
	b _020CF85C
	b _020CF85C
	b _020CF85C
	b _020CF85C
_020CF850:
	cmp r3, #0x11
	beq _020CF924
	b _020CF998
_020CF85C:
	mov r3, r4, lsr #0x8
	add r5, r0, r4, lsr #0x8
	ldrh r4, [r0, r3]
	ldrh r3, [r5, #0x2]
	add sp, sp, #0x4
	mov r0, #0x1
	strh r4, [r1, #0x2]
	strh r3, [r1, #0x4]
	ldrh r4, [r5, #0x4]
	ldrh r3, [r5, #0x6]
	strh r4, [r1, #0x6]
	strh r3, [r1, #0x8]
	ldrh r3, [r5, #0x8]
	strh r3, [r1, #0xA]
	ldr r1, [r2]
	add r1, r1, #0x1
	str r1, [r2]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CF8A8:
	add r5, r0, r4, lsr #0x8
	b _020CF904
_020CF8B0:
	mov r0, #0xc
	mla r12, lr, r0, r5
	ldrh r4, [r12, #0x2]
	ldrh r3, [r12, #0x4]
	add sp, sp, #0x4
	mov r0, #0x1
	strh r4, [r1, #0x0]
	strh r3, [r1, #0x2]
	ldrh r4, [r12, #0x6]
	ldrh r3, [r12, #0x8]
	strh r4, [r1, #0x4]
	strh r3, [r1, #0x6]
	ldrh r4, [r12, #0xa]
	ldrh r3, [r12, #0xc]
	strh r4, [r1, #0x8]
	strh r3, [r1, #0xa]
	ldr r1, [r2, #0x4]
	add r1, r1, #0x1
	str r1, [r2, #0x4]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CF904:
	ldrb r4, [r5, #0x1]
	ldrb r3, [r5, #0x0]
	ldr lr, [r2, #0x4]
	sub r3, r4, r3
	add r3, r3, #0x1
	cmp lr, r3
	blo _020CF8B0
	b _020CF998
_020CF924:
	add r4, r0, r4, lsr #0x8
	b _020CF98C
_020CF92C:
	ldrb lr, [r4, r3]
	cmp lr, #0x0
	beq _020CF998
	mov r0, #0xc
	mla lr, r3, r0, r4
	ldrh r12, [lr, #0x8]
	ldrh r3, [lr, #0xa]
	add sp, sp, #0x4
	mov r0, #0x1
	strh r12, [r1, #0x0]
	strh r3, [r1, #0x2]
	ldrh r12, [lr, #0xc]
	ldrh r3, [lr, #0xe]
	strh r12, [r1, #0x4]
	strh r3, [r1, #0x6]
	ldrh r12, [lr, #0x10]
	ldrh r3, [lr, #0x12]
	strh r12, [r1, #0x8]
	strh r3, [r1, #0xa]
	ldr r1, [r2, #0x4]
	add r1, r1, #0x1
	str r1, [r2, #0x4]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CF98C:
	ldr r3, [r2, #0x4]
	cmp r3, #0x8
	blo _020CF92C
_020CF998:
	ldr r3, [r2, #0x0]
	add r3, r3, #0x1
	str r3, [r2, #0x0]
	str r12, [r2, #0x4]
	ldr r4, [r2, #0x0]
	ldr r3, [r0, #0x38]
	cmp r4, r3
	blo _020CF80C
_020CF9B8:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SND_GetFirstInstDataPos
SND_GetFirstInstDataPos: ; 0x020CF9C8
	sub sp, sp, #0x8
	mov r1, #0x0
	str r1, [sp, #0x0]
	str r1, [sp, #0x4]
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	add sp, sp, #0x8
	bx lr

	arm_func_start SND_DestroyWaveArc
SND_DestroyWaveArc: ; 0x020CF9E8
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	bl SNDi_LockMutex
	ldr r0, [r4, #0x18]
	cmp r0, #0x0
	beq _020CFA28
	mov r5, #0x0
	mov r4, #0x8
_020CFA08:
	ldr r6, [r0, #0x4]
	mov r1, r4
	str r5, [r0, #0x0]
	str r5, [r0, #0x4]
	bl DC_StoreRange
	mov r0, r6
	cmp r6, #0x0
	bne _020CFA08
_020CFA28:
	bl SNDi_UnlockMutex
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start SND_DestroyBank
SND_DestroyBank: ; 0x020CFA34
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	bl SNDi_LockMutex
	add r5, r7, #0x18
	mov r6, #0x0
	mov r8, #0x8
	mov r4, #0x3c
_020CFA50:
	add r1, r7, r6, lsl #0x3
	ldr r0, [r1, #0x18]
	cmp r0, #0x0
	beq _020CFAB8
	ldr r3, [r0, #0x18]
	cmp r5, r3
	bne _020CFA80
	ldr r2, [r1, #0x1c]
	mov r1, r4
	str r2, [r0, #0x18]
	bl DC_StoreRange
	b _020CFAB8
_020CFA80:
	cmp r3, #0x0
	beq _020CFAA0
_020CFA88:
	ldr r0, [r3, #0x4]
	cmp r5, r0
	beq _020CFAA0
	mov r3, r0
	cmp r0, #0x0
	bne _020CFA88
_020CFAA0:
	add r0, r7, r6, lsl #0x3
	ldr r2, [r0, #0x1c]
	mov r0, r3
	mov r1, r8
	str r2, [r3, #0x4]
	bl DC_StoreRange
_020CFAB8:
	add r6, r6, #0x1
	cmp r6, #0x4
	add r5, r5, #0x8
	blt _020CFA50
	bl SNDi_UnlockMutex
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start SND_AssignWaveArc
SND_AssignWaveArc: ; 0x020CFAD4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl SNDi_LockMutex
	add r3, r6, r5, lsl #0x3
	ldr r2, [r3, #0x18]
	mov r12, r5, lsl #0x3
	cmp r2, #0x0
	beq _020CFB70
	cmp r4, r2
	bne _020CFB10
	bl SNDi_UnlockMutex
	ldmia sp!, {r4-r6,lr}
	bx lr
_020CFB10:
	add r1, r6, #0x18
	ldr r0, [r2, #0x18]
	add r12, r1, r12
	cmp r12, r0
	bne _020CFB3C
	ldr r0, [r3, #0x1c]
	mov r1, #0x3c
	str r0, [r2, #0x18]
	ldr r0, [r3, #0x18]
	bl DC_StoreRange
	b _020CFB70
_020CFB3C:
	cmp r0, #0x0
	beq _020CFB5C
_020CFB44:
	ldr r1, [r0, #0x4]
	cmp r12, r1
	beq _020CFB5C
	mov r0, r1
	cmp r1, #0x0
	bne _020CFB44
_020CFB5C:
	add r1, r6, r5, lsl #0x3
	ldr r2, [r1, #0x1c]
	mov r1, #0x8
	str r2, [r0, #0x4]
	bl DC_StoreRange
_020CFB70:
	add r0, r6, #0x18
	ldr r1, [r4, #0x18]
	add r0, r0, r5, lsl #0x3
	str r0, [r4, #0x18]
	add r0, r6, r5, lsl #0x3
	str r1, [r0, #0x1c]
	str r4, [r0, #0x18]
	bl SNDi_UnlockMutex
	mov r0, r6
	mov r1, #0x3c
	bl DC_StoreRange
	mov r0, r4
	mov r1, #0x3c
	bl DC_StoreRange
	ldmia sp!, {r4-r6,lr}
	bx lr
