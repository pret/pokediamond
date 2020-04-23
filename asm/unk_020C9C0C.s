	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start OS_WaitIrq
OS_WaitIrq:
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	mov r4, r1
	bl OS_DisableInterrupts
	cmp r5, #0x0
	beq _020C9C3C
	ldr r1, _020C9C80 ; =0x027E0000
	mvn r2, r4
	add r1, r1, #0x3000
	ldr r3, [r1, #0xff8]
	and r2, r3, r2
	str r2, [r1, #0xff8]
_020C9C3C:
	bl OS_RestoreInterrupts
	ldr r1, _020C9C80 ; =0x027E0000
	add r0, r1, #0x3000
	ldr r0, [r0, #0xff8]
	ands r0, r4, r0
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldr r0, _020C9C84 ; =0x00003FF8
	add r6, r1, r0
	ldr r5, _020C9C88 ; =0x027E0060
_020C9C64:
	mov r0, r5
	bl OS_SleepThread
	ldr r0, [r6, #0x0]
	ands r0, r4, r0
	beq _020C9C64
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C9C80: .word 0x027E0000
_020C9C84: .word 0x00003FF8
_020C9C88: .word 0x027E0060

	arm_func_start OSi_IrqTimer3
OSi_IrqTimer3: ; 0x020C9C8C
	ldr ip, _020C9C98 ; =OSi_IrqCallback
	mov r0, #0x7
	bx r12
	.balign 4
_020C9C98: .word OSi_IrqCallback

	arm_func_start OSi_IrqTimer2
OSi_IrqTimer2: ; 0x020C9C9C
	ldr ip, _020C9CA8 ; =OSi_IrqCallback
	mov r0, #0x6
	bx r12
	.balign 4
_020C9CA8: .word OSi_IrqCallback

	arm_func_start OSi_IrqTimer1
OSi_IrqTimer1: ; 0x020C9CAC
	ldr ip, _020C9CB8 ; =OSi_IrqCallback
	mov r0, #0x5
	bx r12
	.balign 4
_020C9CB8: .word OSi_IrqCallback

	arm_func_start OSi_IrqTimer0
OSi_IrqTimer0: ; 0x020C9CBC
	ldr ip, _020C9CC8 ; =OSi_IrqCallback
	mov r0, #0x4
	bx r12
	.balign 4
_020C9CC8: .word OSi_IrqCallback

	arm_func_start OSi_IrqDma3
OSi_IrqDma3: ; 0x020C9CCC
	ldr ip, _020C9CD8 ; =OSi_IrqCallback
	mov r0, #0x3
	bx r12
	.balign 4
_020C9CD8: .word OSi_IrqCallback

	arm_func_start OSi_IrqDma2
OSi_IrqDma2: ; 0x020C9CDC
	ldr ip, _020C9CE8 ; =OSi_IrqCallback
	mov r0, #0x2
	bx r12
	.balign 4
_020C9CE8: .word OSi_IrqCallback

	arm_func_start OSi_IrqDma1
OSi_IrqDma1: ; 0x020C9CEC
	ldr ip, _020C9CF8 ; =OSi_IrqCallback
	mov r0, #0x1
	bx r12
	.balign 4
_020C9CF8: .word OSi_IrqCallback

	arm_func_start OSi_IrqDma0
OSi_IrqDma0: ; 0x020C9CFC
	ldr ip, _020C9D08 ; =OSi_IrqCallback
	mov r0, #0x0
	bx r12
	.balign 4
_020C9D08: .word OSi_IrqCallback

	arm_func_start OSi_IrqCallback
OSi_IrqCallback: ; 0x020C9D0C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r1, #0xc
	mul r4, r0, r1
	ldr r2, _020C9D94 ; =0x021D341C
	ldr r3, _020C9D98 ; =0x02106818
	mov r0, r0, lsl #0x1
	ldr r1, [r2, r4]
	ldrh r3, [r3, r0]
	mov r5, #0x1
	mov r0, #0x0
	str r0, [r2, r4]
	cmp r1, #0x0
	mov r5, r5, lsl r3
	beq _020C9D54
	ldr r0, _020C9D9C ; =0x021D3424
	ldr r0, [r0, r4]
	blx r1
_020C9D54:
	ldr r0, _020C9DA0 ; =0x027E0000
	ldr r1, _020C9DA4 ; =0x021D3420
	add r0, r0, #0x3000
	ldr r2, [r0, #0xff8]
	orr r2, r2, r5
	str r2, [r0, #0xff8]
	ldr r0, [r1, r4]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r0, r5
	bl OS_DisableIrqMask
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C9D94: .word 0x021D341C
_020C9D98: .word 0x02106818
_020C9D9C: .word 0x021D3424
_020C9DA0: .word 0x027E0000
_020C9DA4: .word 0x021D3420

	arm_func_start OS_IrqDummy
OS_IrqDummy: ; 0x020C9DA8
	bx lr

	arm_func_start OS_SetIrqStackChecker
OS_SetIrqStackChecker: ; 0x020C9DAC
	ldr ip, _020C9DD0 ; =0x027E0000
	ldr r3, _020C9DD4 ; =0xFDDB597D
	add r0, r12, #0x3000
	ldr r2, _020C9DD8 ; =0x7BF9DD5B
	ldr r1, _020C9DDC ; =0x00000400
	str r3, [r0, #0xf7c]
	add r0, r12, #0x3f80
	str r2, [r0, -r1]
	bx lr
	.balign 4
_020C9DD0: .word 0x027E0000
_020C9DD4: .word 0xFDDB597D
_020C9DD8: .word 0x7BF9DD5B
_020C9DDC: .word 0x00000400

	arm_func_start OS_ResetRequestIrqMask
OS_ResetRequestIrqMask: ; 0x020C9DE0
	ldr ip, _020C9E0C ; =0x04000208
	mov r1, #0x0
	ldrh r3, [r12, #0x0]
	ldr r2, _020C9E10 ; =0x04000214
	strh r1, [r12, #0x0]
	ldr r1, [r2, #0x0]
	str r0, [r2, #0x0]
	ldrh r0, [r12, #0x0]
	mov r0, r1
	strh r3, [r12, #0x0]
	bx lr
	.balign 4
_020C9E0C: .word 0x04000208
_020C9E10: .word 0x04000214

	arm_func_start OS_DisableIrqMask
OS_DisableIrqMask: ; 0x020C9E14
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr lr, _020C9E54 ; =0x04000208
	mov r3, #0x0
	ldrh r12, [lr, #0x0]
	ldr r2, _020C9E58 ; =0x04000210
	mvn r1, r0
	strh r3, [lr, #0x0]
	ldr r0, [r2, #0x0]
	and r1, r0, r1
	str r1, [r2, #0x0]
	ldrh r1, [lr, #0x0]
	strh r12, [lr, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C9E54: .word 0x04000208
_020C9E58: .word 0x04000210

	arm_func_start OS_EnableIrqMask
OS_EnableIrqMask: ; 0x020C9E5C
	ldr ip, _020C9E8C ; =0x04000208
	mov r1, #0x0
	ldrh r3, [r12, #0x0]
	ldr r2, _020C9E90 ; =0x04000210
	strh r1, [r12, #0x0]
	ldr r1, [r2, #0x0]
	orr r0, r1, r0
	str r0, [r2, #0x0]
	ldrh r0, [r12, #0x0]
	mov r0, r1
	strh r3, [r12, #0x0]
	bx lr
	.balign 4
_020C9E8C: .word 0x04000208
_020C9E90: .word 0x04000210

	arm_func_start OS_SetIrqMask
OS_SetIrqMask: ; 0x020C9E94
	ldr ip, _020C9EC0 ; =0x04000208
	mov r1, #0x0
	ldrh r3, [r12, #0x0]
	ldr r2, _020C9EC4 ; =0x04000210
	strh r1, [r12, #0x0]
	ldr r1, [r2, #0x0]
	str r0, [r2, #0x0]
	ldrh r0, [r12, #0x0]
	mov r0, r1
	strh r3, [r12, #0x0]
	bx lr
	.balign 4
_020C9EC0: .word 0x04000208
_020C9EC4: .word 0x04000210

	arm_func_start OSi_EnterTimerCallback
OSi_EnterTimerCallback: ; 0x020C9EC8
	stmdb sp!, {r4,lr}
	mov r3, #0xc
	mul r4, r0, r3
	ldr ip, _020C9F08 ; =0x021D344C
	add r0, r0, #0x3
	mov r3, #0x1
	mov r0, r3, lsl r0
	ldr r3, _020C9F0C ; =0x021D3454
	str r1, [r12, r4]
	str r2, [r3, r4]
	bl OS_EnableIrqMask
	ldr r0, _020C9F10 ; =0x021D3450
	mov r1, #0x1
	str r1, [r0, r4]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C9F08: .word 0x021D344C
_020C9F0C: .word 0x021D3454
_020C9F10: .word 0x021D3450

	arm_func_start OSi_EnterDmaCallback
OSi_EnterDmaCallback: ; 0x020C9F14
	stmdb sp!, {r4-r6,lr}
	mov r3, #0xc
	mul r6, r0, r3
	ldr ip, _020C9F54 ; =0x021D341C
	add r4, r0, #0x8
	mov r5, #0x1
	mov r0, r5, lsl r4
	ldr r3, _020C9F58 ; =0x021D3424
	str r1, [r12, r6]
	str r2, [r3, r6]
	bl OS_EnableIrqMask
	and r1, r0, r5, lsl r4
	ldr r0, _020C9F5C ; =0x021D3420
	str r1, [r0, r6]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020C9F54: .word 0x021D341C
_020C9F58: .word 0x021D3424
_020C9F5C: .word 0x021D3420

	arm_func_start OS_GetIrqFunction
OS_GetIrqFunction: ; 0x020C9F60
	ldr r2, _020C9FE4 ; =0x027E0000
	mov r3, #0x0
_020C9F68:
	ands r1, r0, #0x1
	beq _020C9FC8
	cmp r3, #0x8
	blt _020C9F98
	cmp r3, #0xb
	bgt _020C9F98
	sub r1, r3, #0x8
	mov r0, #0xc
	mul r2, r1, r0
	ldr r0, _020C9FE8 ; =0x021D341C
	ldr r0, [r0, r2]
	bx lr
_020C9F98:
	cmp r3, #0x3
	blt _020C9FC0
	cmp r3, #0x6
	bgt _020C9FC0
	add r1, r3, #0x1
	mov r0, #0xc
	mul r2, r1, r0
	ldr r0, _020C9FE8 ; =0x021D341C
	ldr r0, [r0, r2]
	bx lr
_020C9FC0:
	ldr r0, [r2, #0x0]
	bx lr
_020C9FC8:
	add r3, r3, #0x1
	cmp r3, #0x16
	mov r0, r0, lsr #0x1
	add r2, r2, #0x4
	blt _020C9F68
	mov r0, #0x0
	bx lr
	.balign 4
_020C9FE4: .word 0x027E0000
_020C9FE8: .word 0x021D341C

	arm_func_start OS_SetIrqFunction
OS_SetIrqFunction: ; 0x020C9FEC
	stmdb sp!, {r4-r8,lr}
	mov r8, #0x0
	ldr lr, _020CA074 ; =0x027E0000
	ldr r5, _020CA078 ; =0x021D341C
	mov r6, r8
	mov r12, r8
	mov r3, #0x1
	mov r2, #0xc
_020CA00C:
	ands r4, r0, #0x1
	beq _020CA05C
	mov r7, r6
	cmp r8, #0x8
	blt _020CA030
	cmp r8, #0xb
	suble r4, r8, #0x8
	mlale r7, r4, r2, r5
	ble _020CA04C
_020CA030:
	cmp r8, #0x3
	blt _020CA048
	cmp r8, #0x6
	addle r4, r8, #0x1
	mlale r7, r4, r2, r5
	ble _020CA04C
_020CA048:
	str r1, [lr, r8, lsl #0x2]
_020CA04C:
	cmp r7, #0x0
	strne r1, [r7, #0x0]
	strne r12, [r7, #0x8]
	strne r3, [r7, #0x4]
_020CA05C:
	add r8, r8, #0x1
	cmp r8, #0x16
	mov r0, r0, lsr #0x1
	blt _020CA00C
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020CA074: .word 0x027E0000
_020CA078: .word 0x021D341C

	arm_func_start OS_InitIrqTable
OS_InitIrqTable: ; 0x020CA07C
	ldr r0, _020CA090 ; =0x027E0060
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020CA090: .word 0x027E0060

	arm_func_start OS_UnlockCartridge
OS_UnlockCartridge: ; 0x020CA094
	ldr r1, _020CA09C ; =OS_UnlockCartridge2
	bx r1
	.balign 4
_020CA09C: .word OS_UnlockCartridge2

	arm_func_start OS_GetLockID
OS_GetLockID: ; 0x020CA0A0
	ldr r3, _020CA0F0 ; =0x027FFFB0
	ldr r1, [r3, #0x0]
	clz r2, r1
	cmp r2, #0x20
	movne r0, #0x40
	bne _020CA0D4
	add r3, r3, #0x4
	ldr r1, [r3, #0x0]
	clz r2, r1
	cmp r2, #0x20
	ldr r0, _020CA0F4 ; =0xFFFFFFFD
	bxeq lr
	mov r0, #0x60
_020CA0D4:
	add r0, r0, r2
	mov r1, #0x80000000
	mov r1, r1, lsr r2
	ldr r2, [r3, #0x0]
	bic r2, r2, r1
	str r2, [r3, #0x0]
	bx lr
	.balign 4
_020CA0F0: .word 0x027FFFB0
_020CA0F4: .word 0xFFFFFFFD

	arm_func_start OS_ReleaseLockID
OS_ReleaseLockID: ; 0x020CA0F8
	ldr r3, _020CA124 ; =0x027FFFB0
	cmp r0, #0x60
	addpl r3, r3, #0x4
	subpl r0, r0, #0x60
	submi r0, r0, #0x40
	mov r1, #0x80000000
	mov r1, r1, lsr r0
	ldr r2, [r3, #0x0]
	orr r2, r2, r1
	str r2, [r3, #0x0]
	bx lr
	.balign 4
_020CA124: .word 0x027FFFB0

	arm_func_start OS_ReadOwnerOfLockWord
OS_ReadOwnerOfLockWord: ; 0x020CA128
	ldrh r0, [r0, #0x4]
	bx lr

	arm_func_start OSi_FreeCardBus
OSi_FreeCardBus: ; 0x020CA130
	ldr r1, _020CA144 ; =0x04000204
	ldrh r0, [r1, #0x0]
	orr r0, r0, #0x800
	strh r0, [r1, #0x0]
	bx lr
	.balign 4
_020CA144: .word 0x04000204

	arm_func_start OSi_AllocateCardBus
OSi_AllocateCardBus: ; 0x020CA148
	ldr r1, _020CA15C ; =0x04000204
	ldrh r0, [r1, #0x0]
	bic r0, r0, #0x800
	strh r0, [r1, #0x0]
	bx lr
	.balign 4
_020CA15C: .word 0x04000204

	arm_func_start OS_UnlockCard
OS_UnlockCard: ; 0x020CA160
	ldr ip, _020CA170 ; =OS_UnlockByWord
	ldr r1, _020CA174 ; =0x027FFFE0
	ldr r2, _020CA178 ; =OSi_FreeCardBus
	bx r12
	.balign 4
_020CA170: .word OS_UnlockByWord
_020CA174: .word 0x027FFFE0
_020CA178: .word OSi_FreeCardBus

	arm_func_start OS_TryLockCard
OS_TryLockCard: ; 0x020CA17C
	ldr ip, _020CA18C ; =OS_TryLockByWord
	ldr r1, _020CA190 ; =0x027FFFE0
	ldr r2, _020CA194 ; =OSi_AllocateCardBus
	bx r12
	.balign 4
_020CA18C: .word OS_TryLockByWord
_020CA190: .word 0x027FFFE0
_020CA194: .word OSi_AllocateCardBus

	arm_func_start OSi_FreeCartridgeBus
OSi_FreeCartridgeBus: ; 0x020CA198
	ldr r1, _020CA1AC ; =0x04000204
	ldrh r0, [r1, #0x0]
	orr r0, r0, #0x80
	strh r0, [r1, #0x0]
	bx lr
	.balign 4
_020CA1AC: .word 0x04000204

	arm_func_start OSi_AllocateCartridgeBus
OSi_AllocateCartridgeBus: ; 0x020CA1B0
	ldr r1, _020CA1C4 ; =0x04000204
	ldrh r0, [r1, #0x0]
	bic r0, r0, #0x80
	strh r0, [r1, #0x0]
	bx lr
	.balign 4
_020CA1C4: .word 0x04000204

	arm_func_start OS_TryLockCartridge
OS_TryLockCartridge: ; 0x020CA1C8
	ldr ip, _020CA1DC ; =OSi_DoTryLockByWord
	ldr r1, _020CA1E0 ; =0x027FFFE8
	ldr r2, _020CA1E4 ; =OSi_AllocateCartridgeBus
	mov r3, #0x1
	bx r12
	.balign 4
_020CA1DC: .word OSi_DoTryLockByWord
_020CA1E0: .word 0x027FFFE8
_020CA1E4: .word OSi_AllocateCartridgeBus

	arm_func_start OS_UnlockCartridge2
OS_UnlockCartridge2: ; 0x020CA1E8
	ldr ip, _020CA1FC ; =FUN_020CA2B8
	ldr r1, _020CA200 ; =0x027FFFE8
	ldr r2, _020CA204 ; =OSi_FreeCartridgeBus
	mov r3, #0x1
	bx r12
	.balign 4
_020CA1FC: .word FUN_020CA2B8
_020CA200: .word 0x027FFFE8
_020CA204: .word OSi_FreeCartridgeBus

	arm_func_start OS_LockCartridge
OS_LockCartridge: ; 0x020CA208
	ldr ip, _020CA21C ; =FUN_020CA358
	ldr r1, _020CA220 ; =0x027FFFE8
	ldr r2, _020CA224 ; =OSi_AllocateCartridgeBus
	mov r3, #0x1
	bx r12
	.balign 4
_020CA21C: .word FUN_020CA358
_020CA220: .word 0x027FFFE8
_020CA224: .word OSi_AllocateCartridgeBus

	arm_func_start OSi_DoTryLockByWord
OSi_DoTryLockByWord:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	movs r6, r3
	mov r9, r0
	mov r8, r1
	mov r7, r2
	beq _020CA250
	bl OS_DisableInterrupts_IrqAndFiq
	mov r5, r0
	b _020CA258
_020CA250:
	bl OS_DisableInterrupts
	mov r5, r0
_020CA258:
	mov r0, r9
	mov r1, r8
	bl MI_SwapWord
	movs r4, r0
	bne _020CA27C
	cmp r7, #0x0
	beq _020CA278
	blx r7
_020CA278:
	strh r9, [r8, #0x4]
_020CA27C:
	cmp r6, #0x0
	beq _020CA290
	mov r0, r5
	bl OS_RestoreInterrupts_IrqAndFiq
	b _020CA298
_020CA290:
	mov r0, r5
	bl OS_RestoreInterrupts
_020CA298:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start OS_UnlockByWord
OS_UnlockByWord: ; 0x020CA2A8
	ldr ip, _020CA2B4 ; =FUN_020CA2B8
	mov r3, #0x0
	bx r12
	.balign 4
_020CA2B4: .word FUN_020CA2B8

	arm_func_start FUN_020CA2B8
FUN_020CA2B8: ; 0x020CA2B8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r1
	ldrh r1, [r7, #0x4]
	mov r6, r2
	mov r5, r3
	cmp r0, r1
	addne sp, sp, #0x4
	mvnne r0, #0x1
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	cmp r5, #0x0
	beq _020CA2F8
	bl OS_DisableInterrupts_IrqAndFiq
	mov r4, r0
	b _020CA300
_020CA2F8:
	bl OS_DisableInterrupts
	mov r4, r0
_020CA300:
	mov r0, #0x0
	strh r0, [r7, #0x4]
	cmp r6, #0x0
	beq _020CA314
	blx r6
_020CA314:
	mov r0, #0x0
	str r0, [r7, #0x0]
	cmp r5, #0x0
	beq _020CA330
	mov r0, r4
	bl OS_RestoreInterrupts_IrqAndFiq
	b _020CA338
_020CA330:
	mov r0, r4
	bl OS_RestoreInterrupts
_020CA338:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start OS_TryLockByWord
OS_TryLockByWord: ; 0x020CA348
	ldr ip, _020CA354 ; =FUN_020CA358
	mov r3, #0x0
	bx r12
	.balign 4
_020CA354: .word FUN_020CA358

	arm_func_start FUN_020CA358
FUN_020CA358: ; 0x020CA358
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, r3
	bl OSi_DoTryLockByWord
	cmp r0, #0x0
	ldmleia sp!, {r4-r8,lr}
	bxle lr
	mov r4, #0x400
_020CA380:
	mov r0, r4
	blx FUN_020005F2
	mov r0, r8
	mov r1, r7
	mov r2, r6
	mov r3, r5
	bl OSi_DoTryLockByWord
	cmp r0, #0x0
	bgt _020CA380
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start OS_InitLock
OS_InitLock: ; 0x020CA3AC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020CA484 ; =0x021D347C
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r2, #0x1
	ldr r1, _020CA488 ; =0x027FFFF0
	str r2, [r0, #0x0]
	mov r2, #0x0
	mov r0, #0x7e
	str r2, [r1, #0x0]
	bl OS_TryLockByWord
	ldr r5, _020CA488 ; =0x027FFFF0
	ldrh r0, [r5, #0x6]
	cmp r0, #0x0
	beq _020CA410
	mov r4, #0x400
_020CA3FC:
	mov r0, r4
	blx FUN_020005F2
	ldrh r0, [r5, #0x6]
	cmp r0, #0x0
	bne _020CA3FC
_020CA410:
	ldr r2, _020CA48C ; =0x027FFFB0
	mvn r12, #0x0
	mov r0, #0x10000
	ldr r3, _020CA490 ; =0x027FFFB4
	ldr r1, _020CA494 ; =0x027FFFC0
	str r12, [r2, #0x0]
	rsb r12, r0, #0x0
	mov r0, #0x0
	mov r2, #0x28
	str r12, [r3, #0x0]
	bl MIi_CpuClear32
	ldr ip, _020CA498 ; =0x04000204
	ldr r1, _020CA488 ; =0x027FFFF0
	ldrh r3, [r12, #0x0]
	mov r0, #0x7e
	mov r2, #0x0
	orr r3, r3, #0x800
	strh r3, [r12, #0x0]
	ldrh r3, [r12, #0x0]
	orr r3, r3, #0x80
	strh r3, [r12, #0x0]
	bl OS_UnlockByWord
	ldr r1, _020CA488 ; =0x027FFFF0
	mov r0, #0x7f
	mov r2, #0x0
	bl OS_TryLockByWord
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CA484: .word 0x021D347C
_020CA488: .word 0x027FFFF0
_020CA48C: .word 0x027FFFB0
_020CA490: .word 0x027FFFB4
_020CA494: .word 0x027FFFC0
_020CA498: .word 0x04000204

	arm_func_start OS_VSNPrintf
OS_VSNPrintf: ; 0x020CA49C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x64
	mov r9, r2
	str r1, [sp, #0x54]
	str r0, [sp, #0x5c]
	str r0, [sp, #0x58]
	ldrsb r0, [r9, #0x0]
	str r1, [sp, #0x0]
	mov r11, r3
	cmp r0, #0x0
	beq _020CAD18
	mov r0, #0xa
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x4]
	mov r0, #0x20
	str r0, [sp, #0x1c]
	mov r0, #0x30
	str r0, [sp, #0x20]
	mvn r0, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x57
	str r0, [sp, #0x10]
	mov r0, #0x8
	str r0, [sp, #0x14]
	mov r0, #0x37
	str r0, [sp, #0x18]
	mov r0, #0x10
	str r0, [sp, #0x24]
	mov r0, #0x1
	str r0, [sp, #0x28]
	mov r0, #0x2b
	str r0, [sp, #0x34]
	mov r0, #0x2d
	str r0, [sp, #0x30]
	mov r0, #0x2
	str r0, [sp, #0x2c]
_020CA530:
	ldrsb r1, [r9, #0x0]
	and r0, r1, #0xff
	eor r0, r0, #0x20
	sub r0, r0, #0xa1
	cmp r0, #0x3c
	bhs _020CA56C
	add r0, sp, #0x54
	bl string_put_char
	ldrsb r1, [r9, #0x1]!
	cmp r1, #0x0
	beq _020CAD0C
	add r0, sp, #0x54
	add r9, r9, #0x1
	bl string_put_char
	b _020CAD0C
_020CA56C:
	cmp r1, #0x25
	beq _020CA584
	add r0, sp, #0x54
	add r9, r9, #0x1
	bl string_put_char
	b _020CAD0C
_020CA584:
	ldr r6, [sp, #0x4]
	ldr r5, [sp, #0x8]
	ldr r2, [sp, #0xc]
	ldr r0, [sp, #0x10]
	mov r10, r6
	mov r3, r9
_020CA59C:
	ldrsb r4, [r9, #0x1]!
	cmp r4, #0x20
	bgt _020CA5B4
	cmp r4, #0x20
	beq _020CA5F4
	b _020CA60C
_020CA5B4:
	cmp r4, #0x30
	bgt _020CA60C
	cmp r4, #0x2b
	blt _020CA60C
	cmp r4, #0x2b
	beq _020CA5E0
	cmp r4, #0x2d
	beq _020CA5FC
	cmp r4, #0x30
	beq _020CA604
	b _020CA60C
_020CA5E0:
	ldrsb r1, [r9, #-0x1]
	cmp r1, #0x20
	bne _020CA60C
	orr r6, r6, #0x2
	b _020CA59C
_020CA5F4:
	orr r6, r6, #0x1
	b _020CA59C
_020CA5FC:
	orr r6, r6, #0x8
	b _020CA59C
_020CA604:
	orr r6, r6, #0x10
	b _020CA59C
_020CA60C:
	cmp r4, #0x2a
	bne _020CA640
	add r11, r11, #0x4
	ldr r10, [r11, #-0x4]
	add r9, r9, #0x1
	cmp r10, #0x0
	rsblt r10, r10, #0x0
	orrlt r6, r6, #0x8
	b _020CA654
_020CA630:
	ldrsb r4, [r9], #0x1
	mov r1, #0xa
	mla r1, r10, r1, r4
	sub r10, r1, #0x30
_020CA640:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x30
	blt _020CA654
	cmp r1, #0x39
	ble _020CA630
_020CA654:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x2e
	bne _020CA6AC
	ldrsb r1, [r9, #0x1]!
	ldr r5, [sp, #0x4]
	cmp r1, #0x2a
	bne _020CA698
	add r11, r11, #0x4
	ldr r5, [r11, #-0x4]
	add r9, r9, #0x1
	cmp r5, #0x0
	ldrlt r5, [sp, #0x8]
	b _020CA6AC
_020CA688:
	ldrsb r4, [r9], #0x1
	mov r1, #0xa
	mla r1, r5, r1, r4
	sub r5, r1, #0x30
_020CA698:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x30
	blt _020CA6AC
	cmp r1, #0x39
	ble _020CA688
_020CA6AC:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x68
	beq _020CA6C4
	cmp r1, #0x6c
	beq _020CA6DC
	b _020CA6F0
_020CA6C4:
	ldrsb r1, [r9, #0x1]!
	cmp r1, #0x68
	orrne r6, r6, #0x40
	addeq r9, r9, #0x1
	orreq r6, r6, #0x100
	b _020CA6F0
_020CA6DC:
	ldrsb r1, [r9, #0x1]!
	cmp r1, #0x6c
	orrne r6, r6, #0x20
	addeq r9, r9, #0x1
	orreq r6, r6, #0x80
_020CA6F0:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x69
	bgt _020CA740
	cmp r1, #0x63
	blt _020CA720
	cmp r1, #0x63
	beq _020CA7B4
	cmp r1, #0x64
	beq _020CA96C
	cmp r1, #0x69
	beq _020CA96C
	b _020CA950
_020CA720:
	cmp r1, #0x25
	bgt _020CA734
	cmp r1, #0x25
	beq _020CA934
	b _020CA950
_020CA734:
	cmp r1, #0x58
	beq _020CA7A0
	b _020CA950
_020CA740:
	cmp r1, #0x6e
	bgt _020CA754
	cmp r1, #0x6e
	beq _020CA8DC
	b _020CA950
_020CA754:
	sub r1, r1, #0x6f
	cmp r1, #0x9
	addls pc, pc, r1, lsl #0x2
	b _020CA950
_020CA764:
	b _020CA78C
	b _020CA7A8
	b _020CA950
	b _020CA950
	b _020CA828
	b _020CA950
	b _020CA798
	b _020CA950
	b _020CA950
	b _020CA964
_020CA78C:
	ldr r2, [sp, #0x14]
	orr r6, r6, #0x1000
	b _020CA96C
_020CA798:
	orr r6, r6, #0x1000
	b _020CA96C
_020CA7A0:
	ldr r0, [sp, #0x18]
	b _020CA964
_020CA7A8:
	orr r6, r6, #0x4
	ldr r5, [sp, #0x14]
	b _020CA964
_020CA7B4:
	cmp r5, #0x0
	bge _020CA950
	ands r0, r6, #0x8
	add r11, r11, #0x4
	ldr r4, [r11, #-0x4]
	beq _020CA7F0
	mov r0, r4, lsl #0x18
	mov r1, r0, asr #0x18
	add r0, sp, #0x54
	bl string_put_char
	ldr r1, [sp, #0x1c]
	sub r2, r10, #0x1
	add r0, sp, #0x54
	bl string_fill_char
	b _020CA820
_020CA7F0:
	ands r0, r6, #0x10
	ldrne r0, [sp, #0x20]
	sub r2, r10, #0x1
	ldreq r0, [sp, #0x1c]
	mov r0, r0, lsl #0x18
	mov r1, r0, asr #0x18
	add r0, sp, #0x54
	bl string_fill_char
	mov r0, r4, lsl #0x18
	mov r1, r0, asr #0x18
	add r0, sp, #0x54
	bl string_put_char
_020CA820:
	add r9, r9, #0x1
	b _020CAD0C
_020CA828:
	add fp, fp, #0x4
	cmp r5, #0x0
	ldr r7, [sp, #0x4]
	ldr r4, [fp, #-0x4]
	bge _020CA860
	ldrsb r0, [r4]
	cmp r0, #0x0
	beq _020CA874
_020CA848:
	add r7, r7, #0x1
	ldrsb r0, [r4, r7]
	cmp r0, #0x0
	bne _020CA848
	b _020CA874
_020CA85C:
	add r7, r7, #0x1
_020CA860:
	cmp r7, r5
	bge _020CA874
	ldrsb r0, [r4, r7]
	cmp r0, #0x0
	bne _020CA85C
_020CA874:
	ands r0, r6, #0x8
	sub sl, sl, r7
	beq _020CA8A4
	mov r1, r4
	mov r2, r7
	add r0, sp, #0x54
	bl string_put_string
	ldr r1, [sp, #0x1C]
	mov r2, sl
	add r0, sp, #0x54
	bl string_fill_char
	b _020CA8D4
_020CA8A4:
	ands r0, r6, #0x10
	ldrne r0, [sp, #0x20]
	mov r2, sl
	ldreq r0, [sp, #0x1C]
	mov r0, r0, lsl #0x18
	mov r1, r0, asr #0x18
	add r0, sp, #0x54
	bl string_fill_char
	mov r1, r4
	mov r2, r7
	add r0, sp, #0x54
	bl string_put_string
_020CA8D4:
	add r9, r9, #0x1
	b _020CAD0C
_020CA8DC:
	ands r0, r6, #0x100
	ldr r1, [sp, #0x58]
	ldr r0, [sp, #0x5c]
	sub r2, r1, r0
	bne _020CA92C
	ands r0, r6, #0x40
	addne r11, r11, #0x4
	ldrne r0, [r11, #-0x4]
	strneh r2, [r0, #0x0]
	bne _020CA92C
	ands r0, r6, #0x80
	addeq r11, r11, #0x4
	ldreq r0, [r11, #-0x4]
	streq r2, [r0, #0x0]
	beq _020CA92C
	add r11, r11, #0x4
	ldr r0, [r11, #-0x4]
	mov r1, r2, asr #0x1f
	str r2, [r0, #0x0]
	str r1, [r0, #0x4]
_020CA92C:
	add r9, r9, #0x1
	b _020CAD0C
_020CA934:
	add r0, r3, #0x1
	cmp r0, r9
	bne _020CA950
	add r0, sp, #0x54
	add r9, r9, #0x1
	bl string_put_char
	b _020CAD0C
_020CA950:
	add r0, sp, #0x54
	mov r1, r3
	sub r2, r9, r3
	bl string_put_string
	b _020CAD0C
_020CA964:
	ldr r2, [sp, #0x24]
	orr r6, r6, #0x1000
_020CA96C:
	ands r1, r6, #0x8
	bicne r6, r6, #0x10
	cmp r5, #0x0
	bicge r6, r6, #0x10
	ldrlt r5, [sp, #0x28]
	ldr r7, [sp, #0x4]
	ands r1, r6, #0x1000
	beq _020CAA20
	ands r1, r6, #0x100
	addne r11, r11, #0x4
	ldrneb r4, [r11, #-0x4]
	movne r1, #0x0
	bne _020CA9D0
	ands r1, r6, #0x40
	addne r11, r11, #0x4
	ldrneh r4, [r11, #-0x4]
	movne r1, #0x0
	bne _020CA9D0
	ands r1, r6, #0x80
	addne r11, r11, #0x8
	ldrne r1, [r11, #-0x4]
	ldrne r4, [r11, #-0x8]
	addeq r11, r11, #0x4
	ldreq r4, [r11, #-0x4]
	moveq r1, #0x0
_020CA9D0:
	bic r6, r6, #0x3
	ands r3, r6, #0x4
	beq _020CAAD8
	cmp r2, #0x10
	bne _020CAA0C
	mov r3, #0x0
	cmp r1, r3
	cmpeq r4, r3
	beq _020CAAD8
	ldr r3, [sp, #0x20]
	ldr r7, [sp, #0x2c]
	strb r3, [sp, #0x39]
	add r3, r0, #0x21
	strb r3, [sp, #0x38]
	b _020CAAD8
_020CAA0C:
	cmp r2, #0x8
	ldreq r3, [sp, #0x20]
	ldreq r7, [sp, #0x28]
	streqb r3, [sp, #0x38]
	b _020CAAD8
_020CAA20:
	ands r1, r6, #0x100
	addne r11, r11, #0x4
	ldrnesb r4, [r11, #-0x4]
	movne r1, r4, asr #0x1f
	bne _020CAA64
	ands r1, r6, #0x40
	addne r11, r11, #0x4
	ldrnesh r4, [r11, #-0x4]
	movne r1, r4, asr #0x1f
	bne _020CAA64
	ands r1, r6, #0x80
	addne r11, r11, #0x8
	ldrne r4, [r11, #-0x8]
	ldrne r1, [r11, #-0x4]
	addeq r11, r11, #0x4
	ldreq r4, [r11, #-0x4]
	moveq r1, r4, asr #0x1f
_020CAA64:
	mov r3, #0x0
	and r8, r3, #0x0
	cmp r8, r3
	and r8, r1, #0x80000000
	cmpeq r8, r3
	beq _020CAAA0
	ldr r7, [sp, #0x30]
	mvn r4, r4
	strb r7, [sp, #0x38]
	mvn r7, r1
	mov r1, #0x1
	adds r4, r4, r1
	adc r1, r7, r3
	ldr r7, [sp, #0x28]
	b _020CAAD8
_020CAAA0:
	cmp r1, r3
	cmpeq r4, r3
	bne _020CAAB4
	cmp r5, #0x0
	beq _020CAAD8
_020CAAB4:
	ands r3, r6, #0x2
	ldrne r3, [sp, #0x34]
	ldrne r7, [sp, #0x28]
	strneb r3, [sp, #0x38]
	bne _020CAAD8
	ands r3, r6, #0x1
	ldrne r3, [sp, #0x1c]
	ldrne r7, [sp, #0x28]
	strneb r3, [sp, #0x38]
_020CAAD8:
	cmp r2, #0x8
	ldr r8, [sp, #0x4]
	beq _020CAAF8
	cmp r2, #0xa
	beq _020CAB40
	cmp r2, #0x10
	beq _020CABDC
	b _020CAC28
_020CAAF8:
	mov r0, #0x0
	cmp r1, r0
	cmpeq r4, r0
	beq _020CAC28
_020CAB08:
	and r0, r4, #0x7
	add r3, r0, #0x30
	add r0, sp, #0x3a
	strb r3, [r0, r8]
	mov r4, r4, lsr #0x3
	mov r2, #0x0
	mov r0, r1, lsr #0x3
	orr r4, r4, r1, lsl #0x1d
	cmp r0, r2
	cmpeq r4, r2
	mov r1, r0
	add r8, r8, #0x1
	bne _020CAB08
	b _020CAC28
_020CAB40:
	mov r0, #0x0
	cmp r0, r0
	cmpeq r1, r0
	bne _020CAB8C
	cmp r4, #0x0
	beq _020CAC28
_020CAB58:
	ldr r0, _020CAD60 ; =0xCCCCCCCD
	umull r1, r0, r4, r0
	movs r0, r0, lsr #0x3
	mov r1, #0xa
	mul r1, r0, r1
	sub r1, r4, r1
	mov r4, r0
	add r1, r1, #0x30
	add r0, sp, #0x3a
	strb r1, [r0, r8]
	add r8, r8, #0x1
	bne _020CAB58
	b _020CAC28
_020CAB8C:
	cmp r1, r0
	cmpeq r4, r0
	beq _020CAC28
_020CAB98:
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x4]
	mov r0, r4
	bl _ll_udiv
	mov r3, #0xa
	umull r3, r12, r0, r3
	subs r3, r4, r3
	mov r2, #0x0
	add r4, r3, #0x30
	add r3, sp, #0x3a
	strb r4, [r3, r8]
	cmp r1, r2
	cmpeq r0, r2
	mov r4, r0
	add r8, r8, #0x1
	bne _020CAB98
	b _020CAC28
_020CABDC:
	mov r2, #0x0
	cmp r1, r2
	cmpeq r4, r2
	beq _020CAC28
_020CABEC:
	and r3, r4, #0xf
	cmp r3, #0xa
	mov r4, r4, lsr #0x4
	addlt r3, r3, #0x30
	mov r2, r1, lsr #0x4
	orr r4, r4, r1, lsl #0x1c
	mov r1, r2
	addge r3, r3, r0
	add r2, sp, #0x3a
	strb r3, [r2, r8]
	mov r2, #0x0
	cmp r1, r2
	add r8, r8, #0x1
	cmpeq r4, r2
	bne _020CABEC
_020CAC28:
	cmp r7, #0x0
	ble _020CAC4C
	ldrsb r0, [sp, #0x38]
	cmp r0, #0x30
	ldreq r1, [sp, #0x20]
	addeq r0, sp, #0x3a
	streqb r1, [r0, r8]
	ldreq r7, [sp, #0x4]
	addeq r8, r8, #0x1
_020CAC4C:
	sub r5, r5, r8
	ands r0, r6, #0x10
	beq _020CAC68
	sub r0, r10, r8
	sub r0, r0, r7
	cmp r5, r0
	movlt r5, r0
_020CAC68:
	cmp r5, #0x0
	subgt r10, r10, r5
	add r0, r7, r8
	ands r6, r6, #0x8
	sub r10, r10, r0
	bne _020CAC90
	ldr r1, [sp, #0x1c]
	add r0, sp, #0x54
	mov r2, r10
	bl string_fill_char
_020CAC90:
	cmp r7, #0x0
	ble _020CACB8
	add r0, sp, #0x38
	add r4, r0, r7
_020CACA0:
	ldrsb r1, [r4, #-0x1]!
	sub r7, r7, #0x1
	add r0, sp, #0x54
	bl string_put_char
_020CACB0:
	cmp r7, #0x0
	bgt _020CACA0
_020CACB8:
	ldr r1, [sp, #0x20]
	mov r2, r5
	add r0, sp, #0x54
	bl string_fill_char
_020CACC8:
	cmp r8, #0x0
	ble _020CACF0
	add r0, sp, #0x3A
	add r4, r0, r8
_020CACD8:
	ldrsb r1, [r4, #-0x1]!
	sub r8, r8, #0x1
	add r0, sp, #0x54
	bl string_put_char
	cmp r8, #0x0
	bgt _020CACD8
_020CACF0:
	cmp r6, #0x0
	beq _020CAD08
	ldr r1, [sp, #0x1C]
	mov r2, sl
	add r0, sp, #0x54
	bl string_fill_char
_020CAD08:
	add r9, r9, #0x1
_020CAD0C:
	ldrsb r0, [r9, #0x0]
	cmp r0, #0x0
	bne _020CA530
_020CAD18:
	ldr r0, [sp, #0x54]
	cmp r0, #0x0
	ldrne r0, [sp, #0x58]
	movne r1, #0x0
	strneb r1, [r0, #0x0]
	bne _020CAD48
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	ldrne r1, [sp, #0x5c]
	movne r2, #0x0
	addne r0, r1, r0
	strneb r2, [r0, #-0x1]
_020CAD48:
	ldr r1, [sp, #0x58]
	ldr r0, [sp, #0x5c]
	sub r0, r1, r0
	add sp, sp, #0x64
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020CAD60: .word 0xCCCCCCCD

	arm_func_start OS_SNPrintf
OS_SNPrintf: ; 0x020CAD64
	stmdb sp!, {r0-r3}
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	add r3, sp, #0x10
	bic r3, r3, #0x3
	ldr r2, [sp, #0x10]
	add r3, r3, #0x4
	bl OS_VSNPrintf
	add sp, sp, #0x4
	ldmia sp!, {lr}
	add sp, sp, #0x10
	bx lr

	arm_func_start OS_VSPrintf
OS_VSPrintf: ; 0x020CAD94
	ldr ip, _020CADA8 ; =OS_VSNPrintf
	mov r3, r2
	mov r2, r1
	mvn r1, #0x80000000
	bx r12
	.balign 4
_020CADA8: .word OS_VSNPrintf

	arm_func_start OS_SPrintf
OS_SPrintf: ; 0x020CADAC
	stmdb sp!, {r0-r3}
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	add r2, sp, #0xc
	bic r2, r2, #0x3
	ldr r1, [sp, #0xc]
	add r2, r2, #0x4
	bl OS_VSPrintf
	add sp, sp, #0x4
	ldmia sp!, {lr}
	add sp, sp, #0x10
	bx lr

	arm_func_start string_put_string
string_put_string: ; 0x020CADDC
	stmdb sp!, {r4,lr}
	cmp r2, #0x0
	ldmleia sp!, {r4,lr}
	bxle lr
	ldr lr, [r0, #0x0]
	mov r4, #0x0
	cmp lr, r2
	movhi lr, r2
	cmp lr, #0x0
	bls _020CAE1C
_020CAE04:
	ldrsb r12, [r1, r4]
	ldr r3, [r0, #0x4]
	strb r12, [r3, r4]
	add r4, r4, #0x1
	cmp r4, lr
	blo _020CAE04
_020CAE1C:
	ldr r1, [r0, #0x0]
	sub r1, r1, lr
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, r2
	str r1, [r0, #0x4]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start string_fill_char
string_fill_char:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	addle sp, sp, #0x4
	ldmleia sp!, {lr}
	bxle lr
	ldr r12, [r0, #0x0]
	mov lr, #0x0
	cmp r12, r2
	movhi r12, r2
	cmp r12, #0x0
	bls _020CAE80
_020CAE6C:
	ldr r3, [r0, #0x4]
	strb r1, [r3, lr]
	add lr, lr, #0x1
	cmp lr, r12
	blo _020CAE6C
_020CAE80:
	ldr r1, [r0, #0x0]
	sub r1, r1, r12
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, r2
	str r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start string_put_char
string_put_char:
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	ldrne r2, [r0, #0x4]
	strneb r1, [r2, #0x0]
	ldrne r1, [r0, #0x0]
	subne r1, r1, #0x1
	strne r1, [r0, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, #0x1
	str r1, [r0, #0x4]
	bx lr

	arm_func_start FUN_020CAED0
FUN_020CAED0: ; 0x020CAED0
	ldr r0, _020CAEDC ; =0x021D3494
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020CAEDC: .word 0x021D3494

	arm_func_start OS_SetThreadDestructor
OS_SetThreadDestructor:
	str r1, [r0, #0xb4]
	bx lr

	arm_func_start OS_EnableScheduler
OS_EnableScheduler: ; 0x020CAEE8
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020CAF1C ; =0x021D3484
	mov r4, #0x0
	ldr r3, [r1, #0x0]
	cmp r3, #0x0
	subne r2, r3, #0x1
	movne r4, r3
	strne r2, [r1, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CAF1C: .word 0x021D3484

	arm_func_start OS_DisableScheduler
OS_DisableScheduler: ; 0x020CAF20
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r2, _020CAF54 ; =0x021D3484
	mvn r1, #0x0
	ldr r3, [r2, #0x0]
	cmp r3, r1
	addcc r1, r3, #0x1
	movcc r4, r3
	strcc r1, [r2, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CAF54: .word 0x021D3484

	arm_func_start OSi_IdleThreadProc
OSi_IdleThreadProc: ; 0x020CAF58
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_EnableInterrupts
_020CAF64:
	bl OS_Halt
	b _020CAF64

	arm_func_start OS_SetSwitchThreadCallback
OS_SetSwitchThreadCallback: ; 0x020CAF6C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020CAF9C ; =0x021D3498
	ldr r4, [r1, #0xc]
	str r5, [r1, #0xc]
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CAF9C: .word 0x021D3498

	arm_func_start OSi_SleepAlarmCallback
OSi_SleepAlarmCallback: ; 0x020CAFA0
	ldr r2, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	ldr ip, _020CAFBC ; =OS_WakeupThreadDirect
	mov r0, r2
	str r1, [r2, #0xb0]
	bx r12
	.balign 4
_020CAFBC: .word OS_WakeupThreadDirect

	arm_func_start OS_Sleep
OS_Sleep: ; 0x020CAFC0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x34
	mov r4, r0
	add r0, sp, #0x8
	bl OS_CreateAlarm
	ldr r0, _020CB060 ; =0x021D3490
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	str r0, [sp, #0x4]
	bl OS_DisableInterrupts
	ldr r1, _020CB064 ; =0x000082EA
	mov r2, #0x0
	umull r5, r3, r4, r1
	mla r3, r4, r2, r3
	mla r3, r2, r1, r3
	mov r1, r5, lsr #0x6
	mov r4, r0
	ldr r5, [sp, #0x4]
	add r0, sp, #0x8
	add r2, sp, #0x4
	str r0, [r5, #0xb0]
	str r2, [sp, #0x0]
	mov r2, r3, lsr #0x6
	orr r1, r1, r3, lsl #0x1a
	ldr r3, _020CB068 ; =OSi_SleepAlarmCallback
	bl OS_SetAlarm
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020CB04C
	mov r5, #0x0
_020CB038:
	mov r0, r5
	bl OS_SleepThread
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _020CB038
_020CB04C:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x34
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CB060: .word 0x021D3490
_020CB064: .word 0x000082EA
_020CB068: .word OSi_SleepAlarmCallback

	arm_func_start OS_GetThreadPriority
OS_GetThreadPriority: ; 0x020CB06C
	ldr r0, [r0, #0x70]
	bx lr

	arm_func_start OS_SetThreadPriority
OS_SetThreadPriority: ; 0x020CB074
	stmdb sp!, {r4-r8,lr}
	ldr r2, _020CB120 ; =0x021D3498
	mov r6, r0
	mov r5, r1
	ldr r8, [r2, #0x8]
	mov r7, #0x0
	bl OS_DisableInterrupts
	mov r4, r0
	b _020CB0A0
_020CB098:
	mov r7, r8
	ldr r8, [r8, #0x68]
_020CB0A0:
	cmp r8, #0x0
	beq _020CB0B0
	cmp r8, r6
	bne _020CB098
_020CB0B0:
	cmp r8, #0x0
	beq _020CB0C4
	ldr r0, _020CB124 ; =0x021D34A8
	cmp r8, r0
	bne _020CB0D8
_020CB0C4:
	mov r0, r4
	bl OS_RestoreInterrupts
_020CB0CC:
	mov r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CB0D8:
	ldr r0, [r8, #0x70]
	cmp r0, r5
	beq _020CB10C
	cmp r7, #0x0
	ldreq r1, [r6, #0x68]
	ldreq r0, _020CB120 ; =0x021D3498
	streq r1, [r0, #0x8]
	ldrne r0, [r6, #0x68]
	strne r0, [r7, #0x68]
	mov r0, r6
	str r5, [r6, #0x70]
	bl OSi_InsertThreadToList
	bl OSi_RescheduleThread
_020CB10C:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020CB120: .word 0x021D3498
_020CB124: .word 0x021D34A8

	arm_func_start OS_YieldThread
OS_YieldThread: ; 0x020CB128
	stmdb sp!, {r4-r8,lr}
	ldr r0, _020CB1E0 ; =0x021D3498
	mov r7, #0x0
	mov r6, r7
	mov r5, r7
	ldr r8, [r0, #0x4]
	bl OS_DisableInterrupts
	ldr r1, _020CB1E0 ; =0x021D3498
	mov r4, r0
	ldr r2, [r1, #0x8]
	mov r0, r7
	cmp r2, #0x0
	beq _020CB188
	ldr r1, [r8, #0x70]
_020CB160:
	cmp r2, r8
	moveq r7, r0
	ldr r0, [r2, #0x70]
	cmp r1, r0
	moveq r6, r2
	mov r0, r2
	ldr r2, [r2, #0x68]
	addeq r5, r5, #0x1
	cmp r2, #0x0
	bne _020CB160
_020CB188:
	cmp r5, #0x1
	ble _020CB198
	cmp r6, r8
	bne _020CB1A8
_020CB198:
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CB1A8:
	cmp r7, #0x0
	ldreq r1, [r8, #0x68]
	ldreq r0, _020CB1E0 ; =0x021D3498
	streq r1, [r0, #0x8]
	ldrne r0, [r8, #0x68]
	strne r0, [r7, #0x68]
	ldr r0, [r6, #0x68]
	str r0, [r8, #0x68]
	str r8, [r6, #0x68]
	bl OSi_RescheduleThread
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020CB1E0: .word 0x021D3498

	arm_func_start OS_RescheduleThread
OS_RescheduleThread: ; 0x020CB1E4
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	mov r4, r0
	bl OSi_RescheduleThread
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start OS_SelectThread
OS_SelectThread: ; 0x020CB204
	ldr r0, _020CB22C ; =0x021D3498
	ldr r0, [r0, #0x8]
	b _020CB214
_020CB210:
	ldr r0, [r0, #0x68]
_020CB214:
	cmp r0, #0x0
	bxeq lr
	ldr r1, [r0, #0x64]
	cmp r1, #0x1
	bne _020CB210
	bx lr
	.balign 4
_020CB22C: .word 0x021D3498

	arm_func_start OS_WakeupThreadDirect
OS_WakeupThreadDirect: ; 0x020CB230
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	mov r1, #0x1
	mov r4, r0
	str r1, [r5, #0x64]
	bl OSi_RescheduleThread
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start OS_WakeupThread
OS_WakeupThread: ; 0x020CB264
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x0]
	mov r4, r0
	cmp r1, #0x0
	beq _020CB2D0
	cmp r1, #0x0
	beq _020CB2BC
	mov r7, #0x1
	mov r6, #0x0
_020CB294:
	mov r0, r5
	bl OSi_RemoveLinkFromQueue
	str r7, [r0, #0x64]
	str r6, [r0, #0x78]
	str r6, [r0, #0x80]
	ldr r1, [r0, #0x80]
	str r1, [r0, #0x7c]
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	bne _020CB294
_020CB2BC:
	mov r0, #0x0
	str r0, [r5, #0x4]
	ldr r0, [r5, #0x4]
	str r0, [r5, #0x0]
	bl OSi_RescheduleThread
_020CB2D0:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start OS_SleepThread
OS_SleepThread:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	bl OS_DisableInterrupts
	ldr r1, _020CB334 ; =0x021D3490
	mov r5, r0
	ldr r0, [r1, #0x0]
	cmp r6, #0x0
	ldr r4, [r0, #0x0]
	beq _020CB318
	mov r0, r6
	mov r1, r4
	str r6, [r4, #0x78]
	bl OSi_InsertLinkToQueue
_020CB318:
	mov r0, #0x0
	str r0, [r4, #0x64]
	bl OSi_RescheduleThread
	mov r0, r5
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020CB334: .word 0x021D3490

	arm_func_start OS_IsThreadTerminated
OS_IsThreadTerminated: ; 0x020CB338
	ldr r0, [r0, #0x64]
	cmp r0, #0x2
	moveq r0, #0x1
	movne r0, #0x0
	bx lr

	arm_func_start OS_JoinThread
OS_JoinThread: ; 0x020CB34C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x64]
	mov r4, r0
	cmp r1, #0x2
	beq _020CB374
	add r0, r5, #0x9c
	bl OS_SleepThread
_020CB374:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start OSi_CancelThreadAlarmForSleep
OSi_CancelThreadAlarmForSleep: ; 0x020CB388
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0xb0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	bl OS_CancelAlarm
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start OS_DestroyThread
OS_DestroyThread: ; 0x020CB3B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020CB438 ; =0x021D3498
	mov r4, r0
	ldr r0, [r1, #0x4]
	cmp r0, r5
	bne _020CB3DC
	bl OSi_ExitThread_Destroy
_020CB3DC:
	bl OS_DisableScheduler
	mov r0, r5
	bl OSi_UnlockAllMutex
	mov r0, r5
	bl OSi_CancelThreadAlarmForSleep
	ldr r0, [r5, #0x78]
	cmp r0, #0x0
	beq _020CB404
	mov r1, r5
	bl OSi_RemoveSpecifiedLinkFromQueue
_020CB404:
	mov r0, r5
	bl OSi_RemoveThreadFromList
	mov r1, #0x2
	add r0, r5, #0x9c
	str r1, [r5, #0x64]
	bl OS_WakeupThread
	bl OS_EnableScheduler
	mov r0, r4
	bl OS_RestoreInterrupts
	bl OS_RescheduleThread
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CB438: .word 0x021D3498

	arm_func_start OSi_ExitThread_Destroy
OSi_ExitThread_Destroy: ; 0x020CB43C
	stmdb sp!, {r4,lr}
	ldr r0, _020CB498 ; =0x021D3490
	ldr r0, [r0, #0x0]
	ldr r4, [r0, #0x0]
	bl OS_DisableScheduler
	mov r0, r4
	bl OSi_UnlockAllMutex
	ldr r0, [r4, #0x78]
	cmp r0, #0x0
	beq _020CB46C
	mov r1, r4
	bl OSi_RemoveSpecifiedLinkFromQueue
_020CB46C:
	mov r0, r4
	bl OSi_RemoveThreadFromList
	mov r1, #0x2
	add r0, r4, #0x9c
	str r1, [r4, #0x64]
	bl OS_WakeupThread
	bl OS_EnableScheduler
	bl OS_RescheduleThread
	bl OS_Terminate
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CB498: .word 0x021D3490

	arm_func_start OSi_ExitThread_Destroy2
OSi_ExitThread_Destroy2: ; 0x020CB49C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020CB4DC ; =0x021D3490
	ldr r1, [r1, #0x0]
	ldr r3, [r1, #0x0]
	ldr r2, [r3, #0xb4]
	cmp r2, #0x0
	beq _020CB4CC
	mov r1, #0x0
	str r1, [r3, #0xb4]
	blx r2
	bl OS_DisableInterrupts
_020CB4CC:
	bl OSi_ExitThread_Destroy
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CB4DC: .word 0x021D3490

	arm_func_start OSi_ExitThread_ArgSpecified
OSi_ExitThread_ArgSpecified: ; 0x020CB4E0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r2, _020CB548 ; =0x021D3480
	mov r5, r0
	ldr r2, [r2, #0x0]
	mov r4, r1
	cmp r2, #0x0
	beq _020CB534
	ldr r1, _020CB54C ; =OSi_ExitThread_Destroy2
	bl OS_InitContext
	str r4, [r5, #0x4]
	ldr r1, [r5, #0x0]
	mov r0, r5
	orr r1, r1, #0x80
	str r1, [r5, #0x0]
	mov r1, #0x1
	str r1, [r5, #0x64]
	bl OS_LoadContext
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CB534:
	mov r0, r4
	bl OSi_ExitThread_Destroy2
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CB548: .word 0x021D3480
_020CB54C: .word OSi_ExitThread_Destroy2

	arm_func_start OS_ExitThread
OS_ExitThread: ; 0x020CB550
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r0, _020CB578 ; =0x021D3498
	mov r1, #0x0
	ldr r0, [r0, #0x4]
	bl OSi_ExitThread_ArgSpecified
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CB578: .word 0x021D3498

	arm_func_start OS_CreateThread
OS_CreateThread: ; 0x020CB57C
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r5, r1
	mov r7, r2
	mov r6, r3
	bl OS_DisableInterrupts
	mov r4, r0
	bl OSi_GetUnusedThreadId
	ldr r2, [sp, #0x1c]
	mov r1, #0x0
	str r2, [r8, #0x70]
	str r0, [r8, #0x6c]
	str r1, [r8, #0x64]
	str r1, [r8, #0x74]
	mov r0, r8
	bl OSi_InsertThreadToList
	mov r1, r5
	str r6, [r8, #0x94]
	ldr r0, [sp, #0x18]
	mov r12, #0x0
	sub r5, r6, r0
	sub r2, r6, #0x4
	str r5, [r8, #0x90]
	str r12, [r8, #0x98]
	ldr r3, _020CB678 ; =0xFDDB597D
	ldr r0, [r8, #0x94]
	ldr r6, _020CB67C ; =0x7BF9DD5B
	str r3, [r0, #-0x4]
	ldr r3, [r8, #0x90]
	mov r0, r8
	str r6, [r3, #0x0]
	str r12, [r8, #0xa0]
	ldr r3, [r8, #0xa0]
	str r3, [r8, #0x9c]
	bl OS_InitContext
	str r7, [r8, #0x4]
	add r1, r5, #0x4
	ldr r2, _020CB680 ; =OS_ExitThread
	mov r0, #0x0
	str r2, [r8, #0x3c]
	ldr r2, [sp, #0x18]
	sub r2, r2, #0x8
	bl MIi_CpuClear32
	mov r1, #0x0
	str r1, [r8, #0x84]
	str r1, [r8, #0x88]
	str r1, [r8, #0x8c]
	mov r0, r8
	bl OS_SetThreadDestructor
_020CB640:
	mov r0, #0x0
	str r0, [r8, #0x78]
	str r0, [r8, #0x80]
	ldr r2, [r8, #0x80]
	add r1, r8, #0xA4
	str r2, [r8, #0x7C]
	mov r2, #0xC
	bl MIi_CpuClear32
	mov r0, r4
	mov r1, #0x0
	str r1, [r8, #0xB0]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8, lr}
	bx lr
_020CB678: .word 0xFDDB597D
_020CB67C: .word 0x7BF9DD5B
_020CB680: .word OS_ExitThread

	arm_func_start OS_InitThread
OS_InitThread: ; 0x020CB684
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	ldr r3, _020CB7A4 ; =0x021D3494
	ldr r0, [r3, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x8
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldr ip, _020CB7A8 ; =0x00000000
	ldr r1, _020CB7AC ; =0x021D3568
	mov lr, #0x0
	ldr r0, _020CB7B0 ; =0x021D3498
	mov r6, #0x1
	mov r4, #0x10
	str r1, [r0, #0x8]
	str r1, [r0, #0x4]
	cmp r12, #0x0
	ldrle r0, _020CB7B4 ; =0x027E0080
	str r4, [r1, #0x70]
	suble r4, r0, r12
	str lr, [r1, #0x6c]
	str r6, [r1, #0x64]
	str lr, [r1, #0x68]
	str lr, [r1, #0x74]
	ldrgt r1, _020CB7B8 ; =0x027E0000
	ldrgt r0, _020CB7BC ; =0x00000400
	addgt r1, r1, #0x3f80
	subgt r0, r1, r0
	subgt r4, r0, r12
	ldr r1, _020CB7B8 ; =0x027E0000
	ldr r5, _020CB7C0 ; =0x021D349C
	ldr r2, _020CB7C4 ; =0x021D3490
	ldr r0, _020CB7BC ; =0x00000400
	str r5, [r2, #0x0]
	ldr r2, _020CB7AC ; =0x021D3568
	add r1, r1, #0x3f80
	str r6, [r3, #0x0]
	sub r3, r1, r0
	mov r0, #0x0
	ldr r1, _020CB7C8 ; =0xFDDB597D
	str r3, [r2, #0x94]
	str r4, [r2, #0x90]
	str r0, [r2, #0x98]
	str r1, [r3, #-0x4]
	ldr r3, [r2, #0x90]
	ldr ip, _020CB7CC ; =0x7BF9DD5B
	ldr r1, _020CB7B0 ; =0x021D3498
	str r12, [r3, #0x0]
	ldr r3, _020CB7D0 ; =0x027FFFA0
	str r0, [r2, #0xa0]
	str r0, [r2, #0x9c]
	strh r0, [r1, #0x0]
	strh r0, [r1, #0x2]
	str r1, [r3, #0x0]
	bl OS_SetSwitchThreadCallback
	mov r2, #0xc8
	str r2, [sp, #0x0]
	mov r12, #0x1f
	ldr r0, _020CB7D4 ; =0x021D34A8
	ldr r1, _020CB7D8 ; =OSi_IdleThreadProc
	ldr r3, _020CB7DC ; =0x021D36F0
	mov r2, #0x0
	str r12, [sp, #0x4]
	bl OS_CreateThread
	ldr r0, _020CB7D4 ; =0x021D34A8
	mov r2, #0x20
	mov r1, #0x1
	str r2, [r0, #0x70]
	str r1, [r0, #0x64]
	add sp, sp, #0x8
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020CB7A4: .word 0x021D3494
_020CB7A8: .word 0x00000000
_020CB7AC: .word 0x021D3568
_020CB7B0: .word 0x021D3498
_020CB7B4: .word 0x027E0080
_020CB7B8: .word 0x027E0000
_020CB7BC: .word 0x00000400
_020CB7C0: .word 0x021D349C
_020CB7C4: .word 0x021D3490
_020CB7C8: .word 0xFDDB597D
_020CB7CC: .word 0x7BF9DD5B
_020CB7D0: .word 0x027FFFA0
_020CB7D4: .word 0x021D34A8
_020CB7D8: .word OSi_IdleThreadProc
_020CB7DC: .word 0x021D36F0

	arm_func_start OSi_RescheduleThread
OSi_RescheduleThread: ; 0x020CB7E0
	stmdb sp!, {r4-r6,lr}
	ldr r0, _020CB8BC ; =0x021D3484
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldmneia sp!, {r4-r6,lr}
	bxne lr
	ldr r4, _020CB8C0 ; =0x021D3498
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	bne _020CB814
	bl OS_GetProcMode
	cmp r0, #0x12
	bne _020CB824
_020CB814:
	mov r0, #0x1
	strh r0, [r4, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
_020CB824:
	ldr r0, _020CB8C4 ; =0x021D3490
	ldr r0, [r0, #0x0]
	ldr r6, [r0, #0x0]
	bl OS_SelectThread
	mov r5, r0
	cmp r6, r5
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	cmp r5, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, [r6, #0x64]
	cmp r0, #0x2
	beq _020CB870
	mov r0, r6
	bl OS_SaveContext
_020CB864:
	cmp r0, #0x0
	ldmneia sp!, {r4-r6,lr}
	bxne lr
_020CB870:
	ldr r0, _020CB8C8 ; =0x021D348C
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _020CB88C
	mov r0, r6
	mov r1, r5
	blx r2
_020CB88C:
	ldr r2, [r4, #0xc]
	cmp r2, #0x0
	beq _020CB8A4
	mov r0, r6
	mov r1, r5
	blx r2
_020CB8A4:
	ldr r1, _020CB8C0 ; =0x021D3498
	mov r0, r5
	str r5, [r1, #0x4]
	bl OS_LoadContext
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020CB8BC: .word 0x021D3484
_020CB8C0: .word 0x021D3498
_020CB8C4: .word 0x021D3490
_020CB8C8: .word 0x021D348C

	arm_func_start OSi_RemoveThreadFromList
OSi_RemoveThreadFromList: ; 0x020CB8CC
	ldr r1, _020CB910 ; =0x021D3498
	mov r2, #0x0
	ldr r1, [r1, #0x8]
	b _020CB8E4
_020CB8DC:
	mov r2, r1
	ldr r1, [r1, #0x68]
_020CB8E4:
	cmp r1, #0x0
	beq _020CB8F4
	cmp r1, r0
	bne _020CB8DC
_020CB8F4:
	cmp r2, #0x0
	ldreq r1, [r0, #0x68]
	ldreq r0, _020CB910 ; =0x021D3498
	streq r1, [r0, #0x8]
	ldrne r0, [r0, #0x68]
	strne r0, [r2, #0x68]
	bx lr
	.balign 4
_020CB910: .word 0x021D3498

	arm_func_start OSi_InsertThreadToList
OSi_InsertThreadToList: ; 0x020CB914
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020CB978 ; =0x021D3498
	mov r12, #0x0
	ldr r3, [r1, #0x8]
	mov lr, r3
	b _020CB938
_020CB930:
	mov r12, lr
	ldr lr, [lr, #0x68]
_020CB938:
	cmp lr, #0x0
	beq _020CB950
	ldr r2, [lr, #0x70]
	ldr r1, [r0, #0x70]
	cmp r2, r1
	blo _020CB930
_020CB950:
	cmp r12, #0x0
	ldreq r1, _020CB978 ; =0x021D3498
	streq r3, [r0, #0x68]
	streq r0, [r1, #0x8]
	ldrne r1, [r12, #0x68]
	strne r1, [r0, #0x68]
	strne r0, [r12, #0x68]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CB978: .word 0x021D3498

	arm_func_start OSi_RemoveMutexLinkFromQueue
OSi_RemoveMutexLinkFromQueue: ; 0x020CB97C
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _020CB9A4
	ldr r1, [r2, #0x10]
	str r1, [r0, #0x0]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x14]
	moveq r1, #0x0
	streq r1, [r0, #0x4]
_020CB9A4:
	mov r0, r2
	bx lr

	arm_func_start OSi_RemoveSpecifiedLinkFromQueue
OSi_RemoveSpecifiedLinkFromQueue: ; 0x020CB9AC
	ldr r2, [r0, #0x0]
	mov r12, r2
	cmp r2, #0x0
	beq _020CB9F8
_020CB9BC:
	cmp r12, r1
	ldr r3, [r12, #0x80]
	bne _020CB9EC
	cmp r2, r12
	ldr r2, [r12, #0x7c]
	streq r3, [r0, #0x0]
	strne r3, [r2, #0x80]
	ldr r1, [r0, #0x4]
	cmp r1, r12
	streq r2, [r0, #0x4]
	strne r2, [r3, #0x7c]
	b _020CB9F8
_020CB9EC:
	mov r12, r3
	cmp r3, #0x0
	bne _020CB9BC
_020CB9F8:
	mov r0, r12
	bx lr

	arm_func_start OSi_RemoveLinkFromQueue
OSi_RemoveLinkFromQueue: ; 0x020CBA00
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	beq _020CBA2C
	ldr r1, [r2, #0x80]
	str r1, [r0, #0x0]
	cmp r1, #0x0
	movne r0, #0x0
	strne r0, [r1, #0x7c]
	moveq r1, #0x0
	streq r1, [r0, #0x4]
	streq r1, [r2, #0x78]
_020CBA2C:
	mov r0, r2
	bx lr

	arm_func_start OSi_InsertLinkToQueue
OSi_InsertLinkToQueue:
	ldr r12, [r0, #0x0]
	b _020CBA48
_020CBA3C:
	cmp r12, r1
	bxeq lr
	ldr r12, [r12, #0x80]
_020CBA48:
	cmp r12, #0x0
	beq _020CBA60
	ldr r3, [r12, #0x70]
	ldr r2, [r1, #0x70]
	cmp r3, r2
	bls _020CBA3C
_020CBA60:
	cmp r12, #0x0
	bne _020CBA8C
	ldr r2, [r0, #0x4]
	cmp r2, #0x0
	streq r1, [r0, #0x0]
	strne r1, [r2, #0x80]
	str r2, [r1, #0x7c]
	mov r2, #0x0
	str r2, [r1, #0x80]
	str r1, [r0, #0x4]
	bx lr
_020CBA8C:
	ldr r2, [r12, #0x7c]
	cmp r2, #0x0
	streq r1, [r0, #0x0]
	strne r1, [r2, #0x80]
	str r2, [r1, #0x7c]
	str r12, [r1, #0x80]
	str r1, [r12, #0x7c]
	bx lr

	arm_func_start OSi_GetUnusedThreadId
OSi_GetUnusedThreadId: ; 0x020CBAAC
	ldr r1, _020CBAC0 ; =0x021D3488
	ldr r0, [r1, #0x0]
	add r0, r0, #0x1
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020CBAC0: .word 0x021D3488

	arm_func_start OS_InitContext
OS_InitContext: ; 0x020CBAC4
	add r1, r1, #0x4
	str r1, [r0, #0x40]
	str r2, [r0, #0x44]
	sub r2, r2, #0x40
	tst r2, #0x4
	subne r2, r2, #0x4
	str r2, [r0, #0x38]
	ands r1, r1, #0x1
	movne r1, #0x3f
	moveq r1, #0x1f
	str r1, [r0, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [r0, #0x8]
	str r1, [r0, #0xc]
	str r1, [r0, #0x10]
	str r1, [r0, #0x14]
	str r1, [r0, #0x18]
	str r1, [r0, #0x1c]
	str r1, [r0, #0x20]
	str r1, [r0, #0x24]
	str r1, [r0, #0x28]
	str r1, [r0, #0x2c]
	str r1, [r0, #0x30]
	str r1, [r0, #0x34]
	str r1, [r0, #0x3c]
	bx lr

	arm_func_start OS_SaveContext
OS_SaveContext:
	stmdb sp!, {r0,lr}
	add r0, r0, #0x48
	ldr r1, _020CBB78 ; =CP_SaveContext
	blx r1
	ldmia sp!, {r0,lr}
	add r1, r0, #0x0
	mrs r2, cpsr
	str r2, [r1], #0x4
	mov r0, #0xd3
	msr cpsr_c, r0
	str sp, [r1, #0x40]
	msr cpsr_c, r2
	mov r0, #0x1
	stmia r1, {r0-lr}
	add r0, pc, #0x8 ; =_020CBB78
	str r0, [r1, #0x3c]
	mov r0, #0x0
	bx lr
	.balign 4
_020CBB78: .word CP_SaveContext

	arm_func_start OS_LoadContext
OS_LoadContext: ; 0x020CBB7C
	stmdb sp!, {r0,lr}
	add r0, r0, #0x48
	ldr r1, _020CBBBC ; =CP_RestoreContext
	blx r1
	ldmia sp!, {r0,lr}
	mrs r1, cpsr
	bic r1, r1, #0x1f
	orr r1, r1, #0xd3
	msr cpsr_c, r1
	ldr r1, [r0], #0x4
	msr spsr_fsxc, r1
	ldr sp, [r0, #0x40]
	ldr lr, [r0, #0x3c]
	ldmia r0, {r0-lr}^
	mov r0, r0
	subs pc, lr, #0x4
	.balign 4
_020CBBBC: .word CP_RestoreContext

	arm_func_start OS_GetConsoleType
OS_GetConsoleType: ; 0x020CBBC0
	ldr r0, _020CBBD0 ; =0x82000001
	ldr r1, _020CBBD4 ; =0x02106828
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020CBBD0: .word 0x82000001
_020CBBD4: .word 0x02106828

	arm_func_start OS_IsRunOnEmulator
OS_IsRunOnEmulator:
	mov r0, #0x0
	bx lr

	arm_func_start OS_ReadMessage
OS_ReadMessage: ; 0x020CBBE0
	stmdb sp!, {r4-r8,lr}
	mov r6, r0
	mov r5, r1
	mov r7, r2
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x1c]
	mov r4, r0
	cmp r1, #0x0
	bne _020CBC3C
	and r8, r7, #0x1
	add r7, r6, #0x8
_020CBC0C:
	cmp r8, #0x0
	bne _020CBC28
	mov r0, r4
	bl OS_RestoreInterrupts
_020CBC1C:
	mov r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CBC28:
	mov r0, r7
	bl OS_SleepThread
	ldr r0, [r6, #0x1c]
	cmp r0, #0x0
	beq _020CBC0C
_020CBC3C:
	cmp r5, #0x0
	ldrne r1, [r6, #0x10]
	ldrne r0, [r6, #0x18]
	ldrne r0, [r1, r0, lsl #0x2]
	strne r0, [r5, #0x0]
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start OS_JamMessage
OS_JamMessage: ; 0x020CBC64
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, r1
	mov r7, r2
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x14]
	ldr r2, [r6, #0x1c]
	mov r4, r0
	cmp r1, r2
	bgt _020CBCCC
	and r7, r7, #0x1
_020CBC94:
	cmp r7, #0x0
	bne _020CBCB4
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020CBCB4:
	mov r0, r6
	bl OS_SleepThread
	ldr r1, [r6, #0x14]
	ldr r0, [r6, #0x1c]
	cmp r1, r0
	ble _020CBC94
_020CBCCC:
	ldr r0, [r6, #0x18]
	add r0, r0, r1
	sub r0, r0, #0x1
	bl _s32_div_f
	str r1, [r6, #0x18]
	ldr r2, [r6, #0x10]
	ldr r1, [r6, #0x18]
	add r0, r6, #0x8
	str r5, [r2, r1, lsl #0x2]
	ldr r1, [r6, #0x1c]
	add r1, r1, #0x1
	str r1, [r6, #0x1c]
	bl OS_WakeupThread
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start OS_ReceiveMessage
OS_ReceiveMessage: ; 0x020CBD18
	stmdb sp!, {r4-r8,lr}
	mov r6, r0
	mov r5, r1
	mov r7, r2
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x1c]
	mov r4, r0
	cmp r1, #0x0
	bne _020CBD74
	and r8, r7, #0x1
	add r7, r6, #0x8
_020CBD44:
	cmp r8, #0x0
	bne _020CBD60
	mov r0, r4
	bl OS_RestoreInterrupts
_020CBD54:
	mov r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CBD60:
	mov r0, r7
	bl OS_SleepThread
	ldr r0, [r6, #0x1c]
	cmp r0, #0x0
	beq _020CBD44
_020CBD74:
	cmp r5, #0x0
	ldrne r1, [r6, #0x10]
	ldrne r0, [r6, #0x18]
	ldrne r0, [r1, r0, lsl #0x2]
	strne r0, [r5, #0x0]
	ldr r0, [r6, #0x18]
	ldr r1, [r6, #0x14]
	add r0, r0, #0x1
	bl _s32_div_f
	str r1, [r6, #0x18]
	ldr r1, [r6, #0x1c]
	mov r0, r6
	sub r1, r1, #0x1
	str r1, [r6, #0x1c]
	bl OS_WakeupThread
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start OS_SendMessage
OS_SendMessage: ; 0x020CBDC4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, r1
	mov r7, r2
	bl OS_DisableInterrupts
	ldr r2, [r6, #0x1c]
	ldr r1, [r6, #0x14]
	mov r4, r0
	cmp r1, r2
	bgt _020CBE2C
	and r7, r7, #0x1
_020CBDF4:
	cmp r7, #0x0
	bne _020CBE14
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020CBE14:
	mov r0, r6
	bl OS_SleepThread
	ldr r2, [r6, #0x1c]
	ldr r1, [r6, #0x14]
	cmp r1, r2
	ble _020CBDF4
_020CBE2C:
	ldr r0, [r6, #0x18]
	add r0, r0, r2
	bl _s32_div_f
	ldr r2, [r6, #0x10]
	add r0, r6, #0x8
	str r5, [r2, r1, lsl #0x2]
	ldr r1, [r6, #0x1c]
	add r1, r1, #0x1
	str r1, [r6, #0x1c]
	bl OS_WakeupThread
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start OS_InitMessageQueue
OS_InitMessageQueue: ; 0x020CBE6C
	mov r12, #0x0
	str r12, [r0, #0x4]
	ldr r3, [r0, #0x4]
	str r3, [r0, #0x0]
	str r12, [r0, #0xc]
	ldr r3, [r0, #0xc]
	str r3, [r0, #0x8]
	str r1, [r0, #0x10]
	str r2, [r0, #0x14]
	str r12, [r0, #0x18]
	str r12, [r0, #0x1c]
	bx lr

	arm_func_start OSi_DequeueItem
OSi_DequeueItem: ; 0x020CBE9C
	ldr r2, [r1, #0x10]
	ldr r1, [r1, #0x14]
	cmp r2, #0x0
	streq r1, [r0, #0x8c]
	strne r1, [r2, #0x14]
	cmp r1, #0x0
	streq r2, [r0, #0x88]
	strne r2, [r1, #0x10]
	bx lr

	arm_func_start OSi_EnqueueTail
OSi_EnqueueTail: ; 0x020CBEC0
	ldr r2, [r0, #0x8c]
	cmp r2, #0x0
	streq r1, [r0, #0x88]
	strne r1, [r2, #0x10]
	str r2, [r1, #0x14]
	mov r2, #0x0
	str r2, [r1, #0x10]
	str r1, [r0, #0x8c]
	bx lr

	arm_func_start OS_TryLockMutex
OS_TryLockMutex: ; 0x020CBEE4
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r2, [r5, #0x8]
	ldr r1, _020CBF54 ; =0x021D3498
	mov r4, r0
	cmp r2, #0x0
	ldr r0, [r1, #0x4]
	bne _020CBF28
	str r0, [r5, #0x8]
	ldr r2, [r5, #0xc]
	mov r1, r5
	add r2, r2, #0x1
	str r2, [r5, #0xc]
	bl OSi_EnqueueTail
	mov r6, #0x1
	b _020CBF40
_020CBF28:
	cmp r2, r0
	ldreq r0, [r5, #0xc]
	moveq r6, #0x1
	addeq r0, r0, #0x1
	streq r0, [r5, #0xc]
	movne r6, #0x0
_020CBF40:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r6
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020CBF54: .word 0x021D3498

	arm_func_start OSi_UnlockAllMutex
OSi_UnlockAllMutex: ; 0x020CBF58
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldr r0, [r6, #0x88]
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	add r5, r6, #0x88
	mov r4, #0x0
_020CBF78:
	mov r0, r5
	bl OSi_RemoveMutexLinkFromQueue
	str r4, [r0, #0xc]
	str r4, [r0, #0x8]
	bl OS_WakeupThread
	ldr r0, [r6, #0x88]
	cmp r0, #0x0
	bne _020CBF78
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start OS_UnlockMutex
OS_UnlockMutex: ; 0x020CBFA0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020CC00C ; =0x021D3498
	mov r4, r0
	ldr r0, [r1, #0x4]
	ldr r1, [r5, #0x8]
	cmp r1, r0
	bne _020CBFF8
	ldr r1, [r5, #0xc]
	sub r1, r1, #0x1
	str r1, [r5, #0xc]
	ldr r1, [r5, #0xc]
	cmp r1, #0x0
	bne _020CBFF8
	mov r1, r5
	bl OSi_DequeueItem
	mov r1, #0x0
	mov r0, r5
	str r1, [r5, #0x8]
	bl OS_WakeupThread
_020CBFF8:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CC00C: .word 0x021D3498

	arm_func_start OS_LockMutex
OS_LockMutex: ; 0x020CC010
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020CC098 ; =0x021D3498
	mov r4, r0
	ldr r7, [r1, #0x4]
	mov r6, #0x0
_020CC030:
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	bne _020CC05C
	str r7, [r5, #0x8]
	ldr r1, [r5, #0xc]
	mov r0, r7
	add r2, r1, #0x1
	mov r1, r5
	str r2, [r5, #0xc]
	bl OSi_EnqueueTail
	b _020CC084
_020CC05C:
	cmp r0, r7
	ldreq r0, [r5, #0xc]
	addeq r0, r0, #0x1
	streq r0, [r5, #0xc]
	beq _020CC084
	mov r0, r5
	str r5, [r7, #0x84]
	bl OS_SleepThread
	str r6, [r7, #0x84]
	b _020CC030
_020CC084:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020CC098: .word 0x021D3498

	arm_func_start OS_InitMutex
OS_InitMutex: ; 0x020CC09C
	mov r2, #0x0
	str r2, [r0, #0x4]
	ldr r1, [r0, #0x4]
	str r1, [r0, #0x0]
	str r2, [r0, #0x8]
	str r2, [r0, #0xc]
	bx lr

	arm_func_start DC_InvalidateAll
DC_InvalidateAll: ; 0x020CC0B8
	mov r0, #0x0
	mcr p15, 0x0, r0, c7, c6, 0x0
	bx lr

	arm_func_start DC_StoreAll
DC_StoreAll: ; 0x020CC0C4
	mov r1, #0x0
_020CC0C8:
	mov r0, #0x0
_020CC0CC:
	orr r2, r1, r0
	mcr p15, 0x0, r2, c7, c10, 0x2
	add r0, r0, #0x20
	cmp r0, #0x400
	blt _020CC0CC
	add r1, r1, #0x40000000
	cmp r1, #0x0
	bne _020CC0C8
	bx lr

	arm_func_start DC_FlushAll
DC_FlushAll: ; 0x020CC0F0
	mov r12, #0x0
	mov r1, #0x0
_020CC0F8:
	mov r0, #0x0
_020CC0FC:
	orr r2, r1, r0
	mcr p15, 0x0, r12, c7, c10, 0x4
	mcr p15, 0x0, r2, c7, c14, 0x2
	add r0, r0, #0x20
	cmp r0, #0x400
	blt _020CC0FC
	add r1, r1, #0x40000000
	cmp r1, #0x0
	bne _020CC0F8
	bx lr

	arm_func_start DC_InvalidateRange
DC_InvalidateRange: ; 0x020CC124
	add r1, r1, r0
	bic r0, r0, #0x1f
_020CC12C:
	mcr p15, 0x0, r0, c7, c6, 0x1
	add r0, r0, #0x20
	cmp r0, r1
	blt _020CC12C
	bx lr

	arm_func_start DC_StoreRange
DC_StoreRange: ; 0x020CC140
	add r1, r1, r0
	bic r0, r0, #0x1f
_020CC148:
	mcr p15, 0x0, r0, c7, c10, 0x1
	add r0, r0, #0x20
	cmp r0, r1
	blt _020CC148
	bx lr

	arm_func_start DC_FlushRange
DC_FlushRange: ; 0x020CC15C
	mov r12, #0x0
	add r1, r1, r0
	bic r0, r0, #0x1f
_020CC168:
	mcr p15, 0x0, r12, c7, c10, 0x4
	mcr p15, 0x0, r0, c7, c14, 0x1
	add r0, r0, #0x20
	cmp r0, r1
	blt _020CC168
	bx lr

	arm_func_start DC_WaitWriteBufferEmpty
DC_WaitWriteBufferEmpty: ; 0x020CC180
	mov r0, #0x0
	mcr p15, 0x0, r0, c7, c10, 0x4
	bx lr

	arm_func_start IC_InvalidateAll
IC_InvalidateAll: ; 0x020CC18C
	mov r0, #0x0
	mcr p15, 0x0, r0, c7, c5, 0x0
	bx lr

	arm_func_start IC_InvalidateRange
IC_InvalidateRange:
	add r1, r1, r0
	bic r0, r0, #0x1f
_020CC1A0:
	mcr p15, 0x0, r0, c7, c5, 0x1
	add r0, r0, #0x20
	cmp r0, r1
	blt _020CC1A0
	bx lr

	arm_func_start OS_Init
OS_Init: ; 0x020CC1B4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_InitArena
	bl PXI_Init
	bl OS_InitLock
	bl OS_InitArenaEx
	bl OS_InitIrqTable
	bl OS_SetIrqStackChecker
	bl OS_InitException
	bl MI_Init
	bl OS_InitVAlarm
	bl OSi_InitVramExclusive
	bl OS_InitThread
	bl OS_InitReset
	bl CTRDG_Init
	bl CARD_Init
	bl PM_Init
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start OS_AllocFromArenaHi
OS_AllocFromArenaHi: ; 0x020CC204
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	mov r6, r1
	mov r5, r2
	bl OS_GetArenaHi
_020CC218:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	sub r1, r5, #0x1
	mvn r2, r1
	and r0, r0, r2
	sub r1, r0, r6
	mov r0, r4
	and r5, r1, r2
	bl OS_GetArenaLo
	cmp r5, r0
	movcc r0, #0x0
	ldmccia sp!, {r4-r6, lr}
	bxcc lr
	mov r0, r4
	mov r1, r5
	bl OS_SetArenaHi
	mov r0, r5
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start OS_AllocFromArenaLo
OS_AllocFromArenaLo: ; 0x020CC26C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl OS_GetArenaLo
_020CC284:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r7, lr}
	bxeq lr
	add r0, r0, r5
	sub r1, r5, #0x1
	mvn r2, r1
	sub r0, r0, #0x1
	and r4, r2, r0
	add r0, r4, r6
	add r0, r0, r5
	sub r1, r0, #0x1
	mov r0, r7
	and r5, r2, r1
	bl OS_GetArenaHi
	cmp r5, r0
	addhi sp, sp, #0x4
	movhi r0, #0x0
	ldmhiia sp!, {r4-r7, lr}
	bxhi lr
	mov r0, r7
	mov r1, r5
	bl OS_SetArenaLo
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7, lr}
	bx lr

	arm_func_start OS_SetArenaLo
OS_SetArenaLo: ; 0x020CC2F4
	mov r0, r0, lsl #0x2
	add r0, r0, #0x2700000
	add r0, r0, #0xff000
	str r1, [r0, #0xda0]
	bx lr

	arm_func_start OS_SetArenaHi
OS_SetArenaHi:
	mov r0, r0, lsl #0x2
	add r0, r0, #0x2700000
	add r0, r0, #0xff000
	str r1, [r0, #0xdc4]
	bx lr

	arm_func_start OS_GetInitArenaLo
OS_GetInitArenaLo: ; 0x020CC31C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x6
	addls pc, pc, r0, lsl #0x2
	b _020CC3DC
_020CC330:
	b _020CC34C
	b _020CC3DC
	b _020CC35C
	b _020CC39C
	b _020CC3AC
	b _020CC3BC
	b _020CC3CC
_020CC34C:
	add sp, sp, #0x4
	ldr r0, _020CC3EC ; =0x0225FFA0
	ldmfd sp!, {lr}
	bx lr
_020CC35C:
	ldr r0, _020CC3F0 ; =0x021D36F4
	ldr r0, [r0]
	cmp r0, #0x0
	beq _020CC37C
	bl OS_GetConsoleType
	and r0, r0, #0x3
	cmp r0, #0x1
	bne _020CC38C
_020CC37C:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmfd sp!, {lr}
	bx lr
_020CC38C:
	add sp, sp, #0x4
	ldr r0, _020CC3F4 ; =0x023E0000
	ldmfd sp!, {lr}
	bx lr
_020CC39C:
	add sp, sp, #0x4
	ldr r0, _020CC3F8 ; =0x01FF8720
	ldmfd sp!, {lr}
	bx lr
_020CC3AC:
	add sp, sp, #0x4
	ldr r0, _020CC3FC ; =0x027E0080
	ldmfd sp!, {lr}
	bx lr
_020CC3BC:
	add sp, sp, #0x4
	ldr r0, _020CC400 ; =0x027FF000
	ldmfd sp!, {lr}
	bx lr
_020CC3CC:
	add sp, sp, #0x4
	ldr r0, _020CC404 ; =0x037F8000
	ldmfd sp!, {lr}
	bx lr
_020CC3DC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020CC3EC: .word 0x0225FFA0
_020CC3F0: .word 0x021D36F4
_020CC3F4: .word 0x023E0000
_020CC3F8: .word 0x01FF8720
_020CC3FC: .word 0x027E0080
_020CC400: .word 0x027FF000
_020CC404: .word 0x037F8000

	arm_func_start OS_GetInitArenaHi
OS_GetInitArenaHi: ; 0x020CC408
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x6
	addls pc, pc, r0, lsl #0x2
	b _020CC508
_020CC41C:
	b _020CC438
	b _020CC508
	b _020CC448
	b _020CC488
	b _020CC498
	b _020CC4E8
	b _020CC4F8
_020CC438:
	add sp, sp, #0x4
	ldr r0, _020CC518 ; =0x023E0000
	ldmfd sp!, {lr}
	bx lr
_020CC448:
	ldr r0, _020CC51C ; =0x021D36F4
	ldr r0, [r0]
	cmp r0, #0x0
	beq _020CC468
	bl OS_GetConsoleType
	and r0, r0, #0x3
	cmp r0, #0x1
	bne _020CC478
_020CC468:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmfd sp!, {lr}
	bx lr
_020CC478:
	add sp, sp, #0x4
	mov r0, #0x2700000
	ldmfd sp!, {lr}
	bx lr
_020CC488:
	add sp, sp, #0x4
	mov r0, #0x2000000
	ldmfd sp!, {lr}
	bx lr
_020CC498:
	ldr r0, _020CC520 ; =0x027E0000
	ldr r1, _020CC524 ; =0x00000000
	ldr r2, _020CC528 ; =0x00000400
	add r3, r0, #0x3f80
	cmp r1, #0x0
	sub r2, r3, r2
	bne _020CC4CC
	ldr r1, _020CC52C ; =0x027E0080
	add sp, sp, #0x4
	cmp r0, r1
	movcc r0, r1
	ldmfd sp!, {lr}
	bx lr
_020CC4CC:
	cmp r1, #0x0
	ldrlt r0, _020CC52C ; =0x027E0080
	add sp, sp, #0x4
	sublt r0, r0, r1
	subge r0, r2, r1
	ldmfd sp!, {lr}
	bx lr
_020CC4E8:
	add sp, sp, #0x4
	ldr r0, _020CC530 ; =0x027FF680
	ldmfd sp!, {lr}
	bx lr
_020CC4F8:
	add sp, sp, #0x4
	ldr r0, _020CC534 ; =0x037F8000
	ldmfd sp!, {lr}
	bx lr
_020CC508:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020CC518: .word 0x023E0000
_020CC51C: .word 0x021D36F4
_020CC520: .word 0x027E0000
_020CC524: .word 0x00000000
_020CC528: .word 0x00000400
_020CC52C: .word 0x027E0080
_020CC530: .word 0x027FF680
_020CC534: .word 0x037F8000

	arm_func_start OS_GetArenaLo
OS_GetArenaLo:
	mov r0, r0, lsl #0x2
	add r0, r0, #0x2700000
	add r0, r0, #0xff000
	ldr r0, [r0, #0xda0]
	bx lr

	arm_func_start OS_GetArenaHi
OS_GetArenaHi:
	mov r0, r0, lsl #0x2
	add r0, r0, #0x2700000
	add r0, r0, #0xff000
	ldr r0, [r0, #0xdc4]
	bx lr

	arm_func_start OS_InitArenaEx
OS_InitArenaEx: ; 0x020CC560
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0x2
	bl OS_GetInitArenaHi
	mov r1, r0
	mov r0, #0x2
	bl OS_SetArenaHi
	mov r0, #0x2
	bl OS_GetInitArenaLo
	mov r1, r0
	mov r0, #0x2
	bl OS_SetArenaLo
	ldr r0, _020CC5D4 ; =0x021D36F4
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _020CC5B8
	bl OS_GetConsoleType
	and r0, r0, #0x3
	cmp r0, #0x1
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
_020CC5B8:
	ldr r0, _020CC5D8 ; =0x0200002B
	bl OS_SetProtectionRegion1
	ldr r0, _020CC5DC ; =0x023E0021
	bl OS_SetProtectionRegion2
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CC5D4: .word 0x021D36F4
_020CC5D8: .word 0x0200002B
_020CC5DC: .word 0x023E0021

	arm_func_start OS_InitArena
OS_InitArena: ; 0x020CC5E0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020CC6F4 ; =0x021D36F0
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	mov r2, #0x1
	mov r0, #0x0
	str r2, [r1, #0x0]
	bl OS_GetInitArenaHi
	mov r1, r0
	mov r0, #0x0
	bl OS_SetArenaHi
_020CC61C:
	mov r0, #0x0
	bl OS_GetInitArenaLo
	mov r1, r0
	mov r0, #0x0
	bl OS_SetArenaLo
	mov r0, #0x2
	mov r1, #0x0
	bl OS_SetArenaLo
	mov r0, #0x2
	mov r1, #0x0
	bl OS_SetArenaHi
	mov r0, #0x3
	bl OS_GetInitArenaHi
	mov r1, r0
	mov r0, #0x3
	bl OS_SetArenaHi
	mov r0, #0x3
	bl OS_GetInitArenaLo
	mov r1, r0
	mov r0, #0x3
	bl OS_SetArenaLo
	mov r0, #0x4
	bl OS_GetInitArenaHi
	mov r1, r0
	mov r0, #0x4
	bl OS_SetArenaHi
	mov r0, #0x4
	bl OS_GetInitArenaLo
	mov r1, r0
	mov r0, #0x4
	bl OS_SetArenaLo
	mov r0, #0x5
	bl OS_GetInitArenaHi
	mov r1, r0
	mov r0, #0x5
	bl OS_SetArenaHi
	mov r0, #0x5
	bl OS_GetInitArenaLo
	mov r1, r0
	mov r0, #0x5
	bl OS_SetArenaLo
	mov r0, #0x6
	bl OS_GetInitArenaHi
	mov r1, r0
	mov r0, #0x6
	bl OS_SetArenaHi
	mov r0, #0x6
	bl OS_GetInitArenaLo
	mov r1, r0
	mov r0, #0x6
	bl OS_SetArenaLo
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr
_020CC6F4: .word 0x021D36F0

	arm_func_start OS_FreeToHeap
OS_FreeToHeap: ; 0x020CC6F8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r5, r1
	mov r4, r2
	bl OS_DisableInterrupts
	ldr r1, _020CC768 ; =0x021D36F8
	mov r6, r0
	ldr r0, [r1, r7, lsl #0x2]
	cmp r5, #0x0
	ldrlt r5, [r0, #0x0]
	ldr r1, [r0, #0x10]
	mov r0, #0xc
	mla r7, r5, r0, r1
	sub r4, r4, #0x20
	ldr r0, [r7, #0x8]
	mov r1, r4
	bl DLExtract
	str r0, [r7, #0x8]
	ldr r0, [r7, #0x4]
	mov r1, r4
	bl DLInsert
	str r0, [r7, #0x4]
	mov r0, r6
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020CC768: .word 0x021D36F8

	arm_func_start OS_AllocFromHeap
OS_AllocFromHeap: ; 0x020CC76C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, r1
	mov r7, r2
	bl OS_DisableInterrupts
	ldr r1, _020CC894 ; =0x021D36F8
	mov r4, r0
	ldr r1, [r1, r6, lsl #0x2]
	cmp r1, #0x0
	bne _020CC7AC
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020CC7AC:
	cmp r5, #0x0
	ldrlt r5, [r1, #0x0]
	ldr r1, [r1, #0x10]
	mov r0, #0xc
	mla r6, r5, r0, r1
	ldr r0, [r6, #0x4]
	add r1, r7, #0x20
	add r1, r1, #0x1f
	mov r5, r0
	cmp r0, #0x0
	bic r7, r1, #0x1f
	beq _020CC7F4
_020CC7DC:
	ldr r1, [r5, #0x8]
	cmp r7, r1
	ble _020CC7F4
	ldr r5, [r5, #0x4]
	cmp r5, #0x0
	bne _020CC7DC
_020CC7F4:
	cmp r5, #0x0
	bne _020CC814
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020CC814:
	ldr r1, [r5, #0x8]
	sub r1, r1, r7
	cmp r1, #0x40
	bhs _020CC834
	mov r1, r5
	bl DLExtract
	str r0, [r6, #0x4]
	b _020CC86C
_020CC834:
	str r7, [r5, #0x8]
	add r2, r5, r7
	str r1, [r2, #0x8]
	ldr r0, [r5, #0x0]
	str r0, [r5, r7]
	ldr r0, [r5, #0x4]
	str r0, [r2, #0x4]
	ldr r0, [r2, #0x4]
	cmp r0, #0x0
	strne r2, [r0, #0x0]
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	strne r2, [r0, #0x4]
	streq r2, [r6, #0x4]
_020CC86C:
	ldr r0, [r6, #0x8]
	mov r1, r5
	bl DLAddFront
	str r0, [r6, #0x8]
	mov r0, r4
	bl OS_RestoreInterrupts
	add r0, r5, #0x20
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020CC894: .word 0x021D36F8

	arm_func_start DLInsert
DLInsert: ; 0x020CC898
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r12, r0
	cmp r0, #0x0
	mov lr, #0x0
	beq _020CC8C8
_020CC8B0:
	cmp r1, r12
	bls _020CC8C8
	mov lr, r12
	ldr r12, [r12, #0x4]
	cmp r12, #0x0
	bne _020CC8B0
_020CC8C8:
	str r12, [r1, #0x4]
	str lr, [r1, #0x0]
	cmp r12, #0x0
	beq _020CC908
	str r1, [r12, #0x0]
	ldr r3, [r1, #0x8]
	add r2, r1, r3
	cmp r2, r12
	bne _020CC908
	ldr r2, [r12, #0x8]
	add r2, r3, r2
	str r2, [r1, #0x8]
	ldr r12, [r12, #0x4]
	str r12, [r1, #0x4]
	cmp r12, #0x0
	strne r1, [r12, #0x0]
_020CC908:
	cmp lr, #0x0
	beq _020CC950
	str r1, [lr, #0x4]
	ldr r2, [lr, #0x8]
	add r3, lr, r2
	cmp r3, r1
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r1, [r1, #0x8]
	add sp, sp, #0x4
	add r1, r2, r1
	str r1, [lr, #0x8]
	str r12, [lr, #0x4]
	cmp r12, #0x0
	strne lr, [r12, #0x0]
	ldmia sp!, {lr}
	bx lr
_020CC950:
	mov r0, r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start DLExtract
DLExtract: ; 0x020CC960
	ldr r3, [r1, #0x4]
	cmp r3, #0x0
	ldrne r2, [r1, #0x0]
	strne r2, [r3, #0x0]
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	ldreq r0, [r1, #0x4]
	ldrne r1, [r1, #0x4]
	strne r1, [r2, #0x4]
	bx lr

	arm_func_start DLAddFront
DLAddFront: ; 0x020CC988
	str r0, [r1, #0x4]
	mov r2, #0x0
	str r2, [r1, #0x0]
	cmp r0, #0x0
	strne r1, [r0, #0x0]
	mov r0, r1
	bx lr

	arm_func_start OS_GetDTCMAddress
OS_GetDTCMAddress: ; 0x020CC9A4
	mrc p15, 0x0, r0, c9, c1, 0x0
	ldr r1, _020CC9B4 ; =0xFFFFF000
	and r0, r0, r1
	bx lr
	.balign 4
_020CC9B4: .word 0xFFFFF000

	arm_func_start OS_EnableProtectionUnit
OS_EnableProtectionUnit: ; 0x020CC9B8
	mrc p15, 0x0, r0, c1, c0, 0x0
	orr r0, r0, #0x1
	mcr p15, 0x0, r0, c1, c0, 0x0
	bx lr

	arm_func_start OS_DisableProtectionUnit
OS_DisableProtectionUnit: ; 0x020CC9C8
	mrc p15, 0x0, r0, c1, c0, 0x0
	bic r0, r0, #0x1
	mcr p15, 0x0, r0, c1, c0, 0x0
	bx lr

	arm_func_start OS_SetDPermissionsForProtectionRegion
OS_SetDPermissionsForProtectionRegion: ; 0x020CC9D8
	mrc p15, 0x0, r2, c5, c0, 0x2
	bic r2, r2, r0
	orr r2, r2, r1
	mcr p15, 0x0, r2, c5, c0, 0x2
	bx lr

	arm_func_start OS_SetProtectionRegion1
OS_SetProtectionRegion1: ; 0x020CC9EC
	mcr p15, 0x0, r0, c6, c1, 0x0
	bx lr

	arm_func_start OS_SetProtectionRegion2
OS_SetProtectionRegion2: ; 0x020CC9F4
	mcr p15, 0x0, r0, c6, c2, 0x0
	bx lr

	arm_func_start OSi_ExceptionHandler
OSi_ExceptionHandler: ; 0x020CC9FC
	ldr ip, _020CCA68 ; =0x021D3724
	ldr r12, [r12, #0x0]
	cmp r12, #0x0
	movne lr, pc
	bxne r12
	ldr ip, _020CCA6C ; =0x02000000
	stmdb r12!, {r0-r3,sp-lr}
	and r0, sp, #0x1
	mov sp, r12
	mrs r1, cpsr
	and r1, r1, #0x1f
	teq r1, #0x17
	bne _020CCA38
	bl OSi_GetAndDisplayContext
	b _020CCA44
_020CCA38:
	teq r1, #0x1b
	bne _020CCA44
	bl OSi_GetAndDisplayContext
_020CCA44:
	ldr ip, _020CCA68 ; =0x021D3724
	ldr r12, [r12, #0x0]
	cmp r12, #0x0
_020CCA50:
	beq _020CCA50
_020CCA54:
	mov r0, r0
	b _020CCA54
_020CCA5C:
	ldmia sp!, {r0-r3,ip,lr}
	mov sp, ip
	bx lr
_020CCA68: .word 0x021D3724
_020CCA6C: .word 0x02000000

	arm_func_start OSi_GetAndDisplayContext
OSi_GetAndDisplayContext: ; 0x020CCA70
	stmdb sp!, {r0,lr}
	bl OSi_SetExContext
	bl OSi_DisplayExContext
	ldmia sp!, {r0,lr}
	bx lr

	arm_func_start OSi_SetExContext
OSi_SetExContext: ; 0x020CCA84
	ldr r1, _020CCB10 ; =0x021D3728
	mrs r2, cpsr
	str r2, [r1, #0x74]
	str r0, [r1, #0x6c]
	ldr r0, [r12, #0x0]
	str r0, [r1, #0x4]
	ldr r0, [r12, #0x4]
	str r0, [r1, #0x8]
	ldr r0, [r12, #0x8]
	str r0, [r1, #0xc]
	ldr r0, [r12, #0xc]
	str r0, [r1, #0x10]
	ldr r2, [r12, #0x10]
	bic r2, r2, #0x1
	add r0, r1, #0x14
	stmia r0, {r4-r11}
	str r12, [r1, #0x70]
	ldr r0, [r2, #0x0]
	str r0, [r1, #0x64]
	ldr r3, [r2, #0x4]
	str r3, [r1, #0x0]
	ldr r0, [r2, #0x8]
	str r0, [r1, #0x34]
	ldr r0, [r2, #0xc]
	str r0, [r1, #0x40]
	mrs r0, cpsr
	orr r3, r3, #0x80
	bic r3, r3, #0x20
	msr cpsr_fsxc, r3
	str sp, [r1, #0x38]
	str lr, [r1, #0x3c]
	mrs r2, spsr
	str r2, [r1, #0x7c]
	msr cpsr_fsxc, r0
	bx lr
	.balign 4
_020CCB10: .word 0x021D3728

	arm_func_start OSi_DisplayExContext
OSi_DisplayExContext: ; 0x020CCB14
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020CCB70 ; =0x021D371C
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	mov r0, sp
	ldr r1, _020CCB74 ; =0x0000009F
	msr cpsr_fsxc, r1
	mov sp, r0
	bl OS_EnableProtectionUnit
	ldr r1, _020CCB78 ; =0x021D3720
	ldr r0, _020CCB70 ; =0x021D371C
	ldr r1, [r1, #0x0]
	ldr r2, [r0, #0x0]
	ldr r0, _020CCB7C ; =0x021D3728
	blx r2
	bl OS_DisableProtectionUnit
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CCB70: .word 0x021D371C
_020CCB74: .word 0x0000009F
_020CCB78: .word 0x021D3720
_020CCB7C: .word 0x021D3728

	arm_func_start OS_InitException
OS_InitException: ; 0x020CCB80
	ldr r0, _020CCBDC ; =0x027FFD9C
	ldr r1, [r0, #0x0]
	cmp r1, #0x2600000
	blo _020CCBA0
	cmp r1, #0x2800000
	ldrlo r0, _020CCBE0 ; =0x021D3724
	strcc r1, [r0, #0x0]
	blo _020CCBAC
_020CCBA0:
	ldr r0, _020CCBE0 ; =0x021D3724
	mov r1, #0x0
	str r1, [r0, #0x0]
_020CCBAC:
	ldr r0, _020CCBE0 ; =0x021D3724
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	ldreq r2, _020CCBE4 ; =OSi_ExceptionHandler
	ldreq r1, _020CCBDC ; =0x027FFD9C
	ldreq r0, _020CCBE8 ; =0x027E3000
	streq r2, [r1, #0x0]
	streq r2, [r0, #0xfdc]
	ldr r0, _020CCBEC ; =0x021D371C
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_020CCBDC: .word 0x027FFD9C
_020CCBE0: .word 0x021D3724
_020CCBE4: .word OSi_ExceptionHandler
_020CCBE8: .word 0x027E3000
_020CCBEC: .word 0x021D371C

	arm_func_start OSi_SetTimerReserved
OSi_SetTimerReserved: ; 0x020CCBF0
	ldr r1, _020CCC08 ; =0x021D37A8
	mov r2, #0x1
	ldrh r3, [r1, #0x0]
	orr r0, r3, r2, lsl r0
	strh r0, [r1, #0x0]
	bx lr
	.balign 4
_020CCC08: .word 0x021D37A8

	arm_func_start OS_GetTickLo
OS_GetTickLo: ; 0x020CCC0C
	ldr r0, _020CCC18 ; =0x04000100
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4
_020CCC18: .word 0x04000100

	arm_func_start OS_GetTick
OS_GetTick: ; 0x020CCC1C
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	bl OS_DisableInterrupts
	ldr r1, _020CCCBC ; =0x04000100
	ldr r3, _020CCCC0 ; =0x021D37B4
	ldrh r12, [r1, #0x0]
	ldr r2, _020CCCC4 ; =0x0000FFFF
	mvn r1, #0x0
	strh r12, [sp, #0x0]
	ldr r12, [r3, #0x0]
	ldr r3, [r3, #0x4]
	and r1, r12, r1
	and r2, r3, r2
	str r1, [sp, #0x4]
	ldr r1, _020CCCC8 ; =0x04000214
	str r2, [sp, #0x8]
	ldr r1, [r1, #0x0]
	ands r1, r1, #0x8
	beq _020CCC90
	ldrh r1, [sp, #0x0]
	ands r1, r1, #0x8000
	bne _020CCC90
	ldr r3, [sp, #0x4]
	mov r1, #0x1
	ldr r2, [sp, #0x8]
	adds r3, r3, r1
	adc r1, r2, #0x0
	str r3, [sp, #0x4]
	str r1, [sp, #0x8]
_020CCC90:
	bl OS_RestoreInterrupts
	ldr r2, [sp, #0x4]
	ldr r1, [sp, #0x8]
	ldrh r0, [sp, #0x0]
	mov r1, r1, lsl #0x10
	orr r1, r1, r2, lsr #0x10
	orr r1, r1, r0, asr #0x1f
	orr r0, r0, r2, lsl #0x10
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CCCBC: .word 0x04000100
_020CCCC0: .word 0x021D37B4
_020CCCC4: .word 0x0000FFFF
_020CCCC8: .word 0x04000214

	arm_func_start OSi_CountUpTick
OSi_CountUpTick: ; 0x020CCCCC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020CCD40 ; =0x021D37B4
	ldr r1, _020CCD44 ; =0x021D37B0
	ldr r12, [r2, #0x0]
	mov r0, #0x1
	ldr r3, [r2, #0x4]
	adds r12, r12, r0
	ldr r0, [r1, #0x0]
	adc r3, r3, #0x0
	str r12, [r2, #0x0]
	str r3, [r2, #0x4]
	cmp r0, #0x0
	mov r3, #0x0
	beq _020CCD24
	ldr r2, _020CCD48 ; =0x04000102
	ldr r0, _020CCD4C ; =0x04000100
	strh r3, [r2, #0x0]
	strh r3, [r0, #0x0]
	mov r0, #0xc1
	strh r0, [r2, #0x0]
	str r3, [r1, #0x0]
_020CCD24:
	mov r0, #0x0
	ldr r1, _020CCD50 ; =OSi_CountUpTick
	mov r2, r0
	bl OSi_EnterTimerCallback
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CCD40: .word 0x021D37B4
_020CCD44: .word 0x021D37B0
_020CCD48: .word 0x04000102
_020CCD4C: .word 0x04000100
_020CCD50: .word OSi_CountUpTick

	arm_func_start OS_IsTickAvailable
OS_IsTickAvailable: ; 0x020CCD54
	ldr r0, _020CCD60 ; =0x021D37AC
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4
_020CCD60: .word 0x021D37AC

	arm_func_start OS_InitTick
OS_InitTick: ; 0x020CCD64
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020CCDE8 ; =0x021D37AC
	ldrh r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	mov r2, #0x1
	mov r0, #0x0
	strh r2, [r1, #0x0]
	bl OSi_SetTimerReserved
	ldr r0, _020CCDEC ; =0x021D37B4
	mov r2, #0x0
	str r2, [r0, #0x0]
	ldr r3, _020CCDF0 ; =0x04000102
	str r2, [r0, #0x4]
	ldr r0, _020CCDF4 ; =0x04000100
	strh r2, [r3, #0x0]
	ldr r1, _020CCDF8 ; =OSi_CountUpTick
	strh r2, [r0, #0x0]
	mov r2, #0xc1
	mov r0, #0x8
	strh r2, [r3, #0x0]
	bl OS_SetIrqFunction
	mov r0, #0x8
	bl OS_EnableIrqMask
	ldr r0, _020CCDFC ; =0x021D37B0
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CCDE8: .word 0x021D37AC
_020CCDEC: .word 0x021D37B4
_020CCDF0: .word 0x04000102
_020CCDF4: .word 0x04000100
_020CCDF8: .word OSi_CountUpTick
_020CCDFC: .word 0x021D37B0

	arm_func_start OSi_AlarmHandler
OSi_AlarmHandler: ; 0x020CCE00
	stmdb sp!, {r0,lr}
	bl OSi_ArrangeTimer
	ldmia sp!, {r0,lr}
	bx lr

	arm_func_start OSi_ArrangeTimer
OSi_ArrangeTimer: ; 0x020CCE10
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _020CCF1C ; =0x04000106
	mov r2, #0x0
	mov r0, #0x10
	strh r2, [r1, #0x0]
	bl OS_DisableIrqMask
	ldr r0, _020CCF20 ; =0x027E0000
	add r0, r0, #0x3000
	ldr r1, [r0, #0xff8]
	orr r1, r1, #0x10
	str r1, [r0, #0xff8]
	bl OS_GetTick
	ldr r2, _020CCF24 ; =0x021D37C0
	ldr r4, [r2, #0x0]
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r3, [r4, #0x10]
	ldr r12, [r4, #0xc]
	cmp r1, r3
	cmpeq r0, r12
	bhs _020CCE84
	mov r0, r4
	bl OSi_SetTimer
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CCE84:
	ldr r1, [r4, #0x18]
	cmp r1, #0x0
	moveq r0, #0x0
	streq r0, [r2, #0x4]
	str r1, [r2, #0x0]
	movne r0, #0x0
	strne r0, [r1, #0x14]
	ldr r2, [r4, #0x1c]
	ldr r1, [r4, #0x20]
	mov r0, #0x0
	cmp r1, r0
	ldr r5, [r4, #0x0]
	cmpeq r2, r0
	streq r0, [r4, #0x0]
	cmp r5, #0x0
	beq _020CCECC
	ldr r0, [r4, #0x4]
	blx r5
_020CCECC:
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0x20]
	mov r1, #0x0
	cmp r0, r1
	cmpeq r2, r1
	beq _020CCEF4
	mov r0, r4
	mov r2, r1
	str r5, [r4, #0x0]
	bl OSi_InsertAlarm
_020CCEF4:
	ldr r0, _020CCF24 ; =0x021D37C0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	bl OSi_SetTimer
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CCF1C: .word 0x04000106
_020CCF20: .word 0x027E0000
_020CCF24: .word 0x021D37C0

	arm_func_start OS_CancelAlarm
OS_CancelAlarm: ; 0x020CCF28
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x0]
	mov r4, r0
	cmp r1, #0x0
	bne _020CCF58
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CCF58:
	ldr r0, [r5, #0x18]
	cmp r0, #0x0
	ldreq r2, [r5, #0x14]
	ldreq r1, _020CCFBC ; =0x021D37C0
	streq r2, [r1, #0x4]
	ldrne r1, [r5, #0x14]
	strne r1, [r0, #0x14]
	ldr r1, [r5, #0x14]
	cmp r1, #0x0
	strne r0, [r1, #0x18]
	bne _020CCF98
	ldr r1, _020CCFBC ; =0x021D37C0
	cmp r0, #0x0
	str r0, [r1, #0x0]
	beq _020CCF98
	bl OSi_SetTimer
_020CCF98:
	mov r1, #0x0
	str r1, [r5, #0x0]
	str r1, [r5, #0x1c]
	mov r0, r4
	str r1, [r5, #0x20]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CCFBC: .word 0x021D37C0

	arm_func_start OS_SetAlarm
OS_SetAlarm: ; 0x020CCFC0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	movs r6, r0
	mov r5, r1
	mov r4, r2
	mov r7, r3
	beq _020CCFE8
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	beq _020CCFEC
_020CCFE8:
	bl OS_Terminate
_020CCFEC:
	bl OS_DisableInterrupts
	mov r1, #0x0
	str r1, [r6, #0x1c]
	str r1, [r6, #0x20]
	str r7, [r6, #0x0]
	ldr r1, [sp, #0x18]
	mov r7, r0
	str r1, [r6, #0x4]
	bl OS_GetTick
	adds r3, r5, r0
	adc r2, r4, r1
	mov r0, r6
	mov r1, r3
	bl OSi_InsertAlarm
	mov r0, r7
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start OSi_InsertAlarm
OSi_InsertAlarm: ; 0x020CD038
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	ldr r4, [r8, #0x1c]
	ldr r3, [r8, #0x20]
	mov r0, #0x0
	cmp r3, r0
	mov r7, r1
	mov r6, r2
	cmpeq r4, r0
	beq _020CD0B4
	bl OS_GetTick
	ldr r6, [r8, #0x28]
	ldr r7, [r8, #0x24]
	cmp r6, r1
	cmpeq r7, r0
	bhs _020CD0B4
	ldr r5, [r8, #0x1c]
	ldr r4, [r8, #0x20]
	subs r0, r0, r7
	mov r2, r5
	mov r3, r4
	sbc r1, r1, r6
	bl _ll_udiv
	mov r2, #0x1
	adds r2, r0, r2
	adc r0, r1, #0x0
	umull r3, r1, r5, r2
	mla r1, r5, r0, r1
	mla r1, r4, r2, r1
	adds r7, r7, r3
	adc r6, r6, r1
_020CD0B4:
	str r7, [r8, #0xc]
	ldr r0, _020CD174 ; =0x021D37C0
	str r6, [r8, #0x10]
	ldr r4, [r0, #0x0]
	cmp r4, #0x0
	beq _020CD134
	mov r1, #0x0
_020CD0D0:
	ldr r2, [r4, #0xc]
	ldr r0, [r4, #0x10]
	subs r3, r7, r2
	sbc r2, r6, r0
	subs r0, r3, r1
	sbcs r0, r2, r1
	bge _020CD128
	ldr r0, [r4, #0x14]
	str r0, [r8, #0x14]
	str r8, [r4, #0x14]
	str r4, [r8, #0x18]
	ldr r0, [r8, #0x14]
	cmp r0, #0x0
	strne r8, [r0, #0x18]
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	ldr r1, _020CD174 ; =0x021D37C0
	mov r0, r8
	str r8, [r1, #0x0]
	bl OSi_SetTimer
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CD128:
	ldr r4, [r4, #0x18]
	cmp r4, #0x0
	bne _020CD0D0
_020CD134:
	ldr r1, _020CD174 ; =0x021D37C0
	mov r0, #0x0
	str r0, [r8, #0x18]
	ldr r0, [r1, #0x4]
	str r8, [r1, #0x4]
	str r0, [r8, #0x14]
	cmp r0, #0x0
	strne r8, [r0, #0x18]
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	mov r0, r8
	str r8, [r1, #0x4]
	str r8, [r1, #0x0]
	bl OSi_SetTimer
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020CD174: .word 0x021D37C0

	arm_func_start OS_CreateAlarm
OS_CreateAlarm: ; 0x020CD178
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x8]
	bx lr

	arm_func_start OS_IsAlarmAvailable
OS_IsAlarmAvailable: ; 0x020CD188
	ldr r0, _020CD194 ; =0x021D37BC
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4
_020CD194: .word 0x021D37BC

	arm_func_start OS_InitAlarm
OS_InitAlarm: ; 0x020CD198
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020CD1E8 ; =0x021D37BC
	ldrh r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	mov r0, #0x1
	strh r0, [r1, #0x0]
	bl OSi_SetTimerReserved
	ldr r1, _020CD1EC ; =0x021D37C0
	mov r2, #0x0
	mov r0, #0x10
	str r2, [r1, #0x0]
	str r2, [r1, #0x4]
	bl OS_DisableIrqMask
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CD1E8: .word 0x021D37BC
_020CD1EC: .word 0x021D37C0

	arm_func_start OSi_SetTimer
OSi_SetTimer: ; 0x020CD1F0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	bl OS_GetTick
	ldr r3, _020CD27C ; =0x04000106
	mov r2, #0x0
	strh r2, [r3, #0x0]
	ldr r12, [r4, #0xc]
	ldr r3, [r4, #0x10]
	subs r5, r12, r0
	sbc r4, r3, r1
	ldr r1, _020CD280 ; =OSi_AlarmHandler
	mov r0, #0x1
	bl OSi_EnterTimerCallback
	mov r2, #0x0
	subs r0, r5, r2
	sbcs r0, r4, r2
	ldrlt r2, _020CD284 ; =0x0000FFFE
	blt _020CD254
	mov r0, #0x10000
	subs r0, r5, r0
	sbcs r0, r4, r2
	mvnlt r0, r5
	movlt r0, r0, lsl #0x10
	movlt r2, r0, lsr #0x10
_020CD254:
	ldr r0, _020CD288 ; =0x04000104
	ldr r1, _020CD27C ; =0x04000106
	strh r2, [r0, #0x0]
	mov r2, #0xc1
	mov r0, #0x10
	strh r2, [r1, #0x0]
	bl OS_EnableIrqMask
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CD27C: .word 0x04000106
_020CD280: .word OSi_AlarmHandler
_020CD284: .word 0x0000FFFE
_020CD288: .word 0x04000104

	arm_func_start OS_InitVAlarm
OS_InitVAlarm: ; 0x020CD28C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020CD2EC ; =0x021D37C8
	ldrh r0, [r2, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r1, _020CD2F0 ; =0x021D37D4
	mov r3, #0x0
	mov r12, #0x1
	mov r0, #0x4
	strh r12, [r2, #0x0]
	str r3, [r1, #0x0]
	str r3, [r1, #0x4]
	bl OS_DisableIrqMask
	ldr r1, _020CD2F4 ; =0x021D37D0
	mov r2, #0x0
	ldr r0, _020CD2F8 ; =0x021D37CC
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CD2EC: .word 0x021D37C8
_020CD2F0: .word 0x021D37D4
_020CD2F4: .word 0x021D37D0
_020CD2F8: .word 0x021D37CC

	arm_func_start OS_EnableInterrupts
OS_EnableInterrupts: ; 0x020CD2FC
	mrs r0, cpsr
	bic r1, r0, #0x80
	msr cpsr_c, r1
	and r0, r0, #0x80
	bx lr

	arm_func_start OS_DisableInterrupts
OS_DisableInterrupts:
	mrs r0, cpsr
	orr r1, r0, #0x80
	msr cpsr_c, r1
	and r0, r0, #0x80
	bx lr

	arm_func_start OS_RestoreInterrupts
OS_RestoreInterrupts:
	mrs r1, cpsr
	bic r2, r1, #0x80
	orr r2, r2, r0
	msr cpsr_c, r2
	and r0, r1, #0x80
	bx lr

	arm_func_start OS_DisableInterrupts_IrqAndFiq
OS_DisableInterrupts_IrqAndFiq: ; 0x020CD33C
	mrs r0, cpsr
	orr r1, r0, #0xc0
	msr cpsr_c, r1
	and r0, r0, #0xc0
	bx lr

	arm_func_start OS_RestoreInterrupts_IrqAndFiq
OS_RestoreInterrupts_IrqAndFiq: ; 0x020CD350
	mrs r1, cpsr
	bic r2, r1, #0xc0
	orr r2, r2, r0
	msr cpsr_c, r2
	and r0, r1, #0xc0
	bx lr

	arm_func_start OS_GetCpsrIrq
OS_GetCpsrIrq: ; 0x020CD368
	mrs r0, cpsr
	and r0, r0, #0x80
	bx lr

	arm_func_start OS_GetProcMode
OS_GetProcMode: ; 0x020CD374
	mrs r0, cpsr
	and r0, r0, #0x1f
	bx lr

	arm_func_start OS_SpinWait
OS_SpinWait:
	subs r0, r0, #0x4
	bhs OS_SpinWait
	bx lr

	arm_func_start OS_WaitVBlankIntr
OS_WaitVBlankIntr: ; 0x020CD38C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0x1
	blx FUN_020005F2
	mov r0, #0x1
	mov r1, r0
	bl OS_WaitIrq
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start OS_ResetSystem
OS_ResetSystem: ; 0x020CD3B4
	stmdb sp!, {r4,lr}
	ldr r1, _020CD42C ; =0x027FFC40
	mov r4, r0
	ldrh r0, [r1, #0x0]
	cmp r0, #0x2
	bne _020CD3D0
	bl OS_Terminate
_020CD3D0:
	bl OS_GetLockID
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl CARD_LockRom
_020CD3E0:
	mov r0, #0x0
	bl MI_StopDma
	mov r0, #0x1
	bl MI_StopDma
	mov r0, #0x2
	bl MI_StopDma
	mov r0, #0x3
	bl MI_StopDma
	mov r0, #0x40000
	bl OS_SetIrqMask
	mvn r0, #0x0
	bl OS_ResetRequestIrqMask
	ldr r1, _020CD430
	mov r0, #0x10
	str r4, [r1]
	bl OSi_SendToPxi
	bl FUN_01FF84A4
	ldmia sp!, {r4, lr}
	bx lr
_020CD42C: .word 0x027FFC40
_020CD430: .word 0x027FFC20

	arm_func_start OSi_SendToPxi
OSi_SendToPxi: ; 0x020CD434
	stmdb sp!, {r4-r6,lr}
	mov r6, r0, lsl #0x8
	mov r5, #0xc
	mov r4, #0x0
_020CD444:
	mov r0, r5
	mov r1, r6
	mov r2, r4
	bl PXI_SendWordByFifo
_020CD454:
	cmp r0, #0x0
	bne _020CD444
	ldmia sp!, {r4-r6, lr}
	bx lr

	arm_func_start OSi_CommonCallback
OSi_CommonCallback: ; 0x020CD464
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	and r0, r1, #0x7f00
	mov r0, r0, lsl #0x8
	mov r0, r0, lsr #0x10
	cmp r0, #0x10
	ldreq r0, _020CD4A4 ; =0x021D37E0
	moveq r1, #0x1
	streqh r1, [r0, #0x0]
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	bl OS_Terminate
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CD4A4: .word 0x021D37E0

	arm_func_start OS_InitReset
OS_InitReset: ; 0x020CD4A8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020CD508 ; =0x021D37DC
	ldrh r1, [r0, #0x0]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r1, #0x1
	strh r1, [r0, #0x0]
	bl PXI_Init
	mov r5, #0xc
	mov r4, #0x1
_020CD4DC:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
_020CD4E8:
	cmp r0, #0x0
	beq _020CD4DC
	ldr r1, _020CD50C
	mov r0, #0xC
	bl PXI_SetFifoRecvCallback
	add sp, sp, #0x4
	ldmia sp!, {r4-r5, lr}
	bx lr
_020CD508: .word 0x021D37DC
_020CD50C: .word 0x020CD464

	arm_func_start OS_GetOwnerRtcOffset
OS_GetOwnerRtcOffset: ; 0x020CD510
	ldr r1, _020CD520 ; =0x027FFC80
	ldr r0, [r1, #0x68]
	ldr r1, [r1, #0x6c]
	bx lr
	.balign 4
_020CD520: .word 0x027FFC80

	arm_func_start OS_GetOwnerInfo
OS_GetOwnerInfo: ; 0x020CD524
	stmdb sp!, {r4,lr}
	ldr ip, _020CD59C ; =0x027FFC80
	mov r4, r0
	ldrh r2, [r12, #0x64]
	add r0, r12, #0x6
	add r1, r4, #0x4
	mov r2, r2, lsl #0x1d
	mov r2, r2, lsr #0x1d
	strb r2, [r4, #0x0]
	ldrb r3, [r12, #0x2]
	mov r2, #0x14
	mov r3, r3, lsl #0x1c
	mov r3, r3, lsr #0x1c
	strb r3, [r4, #0x1]
	ldrb r3, [r12, #0x3]
	strb r3, [r4, #0x2]
	ldrb r3, [r12, #0x4]
	strb r3, [r4, #0x3]
	ldrb r3, [r12, #0x1a]
	strh r3, [r4, #0x18]
	ldrb r3, [r12, #0x50]
	strh r3, [r4, #0x4e]
	bl MIi_CpuCopy16
	ldr r0, _020CD59C ; =0x027FFC80
	add r1, r4, #0x1a
	add r0, r0, #0x1c
	mov r2, #0x34
	bl MIi_CpuCopy16
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CD59C: .word 0x027FFC80

	arm_func_start OS_GetMacAddress
OS_GetMacAddress: ; 0x020CD5A0
	ldr ip, _020CD5B4 ; =MI_CpuCopy8
	mov r1, r0
	ldr r0, _020CD5B8 ; =0x027FFCF4
	mov r2, #0x6
	bx r12
	.balign 4
_020CD5B4: .word MI_CpuCopy8
_020CD5B8: .word 0x027FFCF4

	arm_func_start OsCountZeroBits
OsCountZeroBits: ; 0x020CD5BC
	clz r0, r0
	bx lr

	arm_func_start OSi_UnlockVram
OSi_UnlockVram: ; 0x020CD5C4
	stmdb sp!, {r4-r10,lr}
	mov r5, r0
	mov r10, r1
	bl OS_DisableInterrupts
	ldr r4, _020CD640 ; =0x021D37E4
	ldr r1, _020CD644 ; =0x000001FF
	ldr r2, [r4, #0x0]
	mov r8, r0
	and r0, r5, r2
	and r9, r0, r1
	ldr r6, _020CD648 ; =0x021D37E8
	mov r7, #0x1
	mov r5, #0x0
_020CD5F8:
	mov r0, r9
	bl OsCountZeroBits
	rsbs r2, r0, #0x1f
	bmi _020CD630
	mov r1, r2, lsl #0x1
	ldrh r0, [r6, r1]
	mvn r2, r7, lsl r2
	cmp r10, r0
	ldreq r0, [r4, #0x0]
	and r9, r9, r2
	andeq r0, r0, r2
	streqh r5, [r6, r1]
	streq r0, [r4, #0x0]
	b _020CD5F8
_020CD630:
	mov r0, r8
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_020CD640: .word 0x021D37E4
_020CD644: .word 0x000001FF
_020CD648: .word 0x021D37E8

	arm_func_start OSi_TryLockVram
OSi_TryLockVram: ; 0x020CD64C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r8, r1
	bl OS_DisableInterrupts
	ldr r1, _020CD714 ; =0x021D37E4
	mov r7, r0
	ldr r0, [r1, #0x0]
	and r5, r6, r0
	ldr sb, _020CD718 ; =0x021D37E8
	mov r4, #0x1
_020CD678:
	mov r0, r5
	bl OsCountZeroBits
	rsbs r1, r0, #0x1f
	bmi _020CD6B8
	mov r0, r1, lsl #0x1
	ldrh r0, [r9, r0]
	mvn r1, r4, lsl r1
	cmp r8, r0
	and r5, r5, r1
	beq _020CD678
	mov r0, r7
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r9,lr}
	bx lr
_020CD6B8:
	ldr r0, _020CD71C ; =0x000001FF
	and r6, r6, r0
	ldr r4, _020CD718 ; =0x021D37E8
	ldr sb, _020CD714 ; =0x021D37E4
	mov r5, #0x1
_020CD6CC:
	mov r0, r6
	bl OsCountZeroBits
	rsbs r1, r0, #0x1f
	bmi _020CD6FC
	ldr r0, [r9, #0x0]
	mvn r2, r5, lsl r1
	orr r0, r0, r5, lsl r1
	mov r1, r1, lsl #0x1
	strh r8, [r4, r1]
	str r0, [r9, #0x0]
	and r6, r6, r2
	b _020CD6CC
_020CD6FC:
	mov r0, r7
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020CD714: .word 0x021D37E4
_020CD718: .word 0x021D37E8
_020CD71C: .word 0x000001FF

	arm_func_start OSi_InitVramExclusive
OSi_InitVramExclusive: ; 0x020CD720
	ldr r0, _020CD74C ; =0x021D37E4
	mov r3, #0x0
	str r3, [r0, #0x0]
	ldr r0, _020CD750 ; =0x021D37E8
	mov r2, r3
_020CD734:
	mov r1, r3, lsl #0x1
	add r3, r3, #0x1
	strh r2, [r0, r1]
	cmp r3, #0x9
	blt _020CD734
	bx lr
	.balign 4
_020CD74C: .word 0x021D37E4
_020CD750: .word 0x021D37E8

	arm_func_start OS_GetLowEntropyData
OS_GetLowEntropyData: ; 0x020CD754
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r1, _020CD82C ; =0x04000006
	ldr r2, _020CD830 ; =0x027FFC00
	ldrh r7, [r1, #0x0]
	add r4, r2, #0x80
	mov r6, r0
	add r5, r4, #0x74
	bl OS_GetTickLo
	orr r0, r0, r7, lsl #0x10
	str r0, [r6, #0x0]
	ldr r1, _020CD834 ; =0x021D37B4
	ldr r0, _020CD830 ; =0x027FFC00
	ldr r3, [r1, #0x0]
	ldrh r5, [r5, #0x4]
	ldr r2, [r1, #0x4]
	ldr r2, _020CD838 ; =0x04000600
	eor r3, r3, r5, lsl #0x10
	str r3, [r6, #0x4]
	ldr r3, [r1, #0x0]
	ldr r3, [r1, #0x4]
	ldr r1, [r4, #0x74]
	ldr r4, [r0, #0x3c]
	eor r1, r3, r1
	eor r1, r4, r1
	str r1, [r6, #0x8]
	ldr r3, [r6, #0x8]
	ldr r2, [r2, #0x0]
	add r1, r0, #0x300
	eor r2, r3, r2
	str r2, [r6, #0x8]
	ldr r2, [r0, #0x1e8]
	ldr r3, _020CD83C ; =0x04000130
	str r2, [r6, #0xc]
	ldr r4, [r0, #0x1ec]
	ldr r2, _020CD840 ; =0x027FFFA8
	str r4, [r6, #0x10]
	ldrh r4, [r1, #0x94]
	ldr r0, [r0, #0x390]
	eor r0, r0, r4, lsl #0x10
	str r0, [r6, #0x14]
	ldrh r4, [r1, #0xaa]
	ldrh r0, [r1, #0xac]
	orr r0, r0, r4, lsl #0x10
	str r0, [r6, #0x18]
	ldrh r3, [r3, #0x0]
	ldrh r0, [r2, #0x0]
	ldrh r1, [r1, #0x98]
	orr r0, r3, r0
	orr r0, r0, r1, lsl #0x10
	str r0, [r6, #0x1c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020CD82C: .word 0x04000006
_020CD830: .word 0x027FFC00
_020CD834: .word 0x021D37B4
_020CD838: .word 0x04000600
_020CD83C: .word 0x04000130
_020CD840: .word 0x027FFFA8

	arm_func_start OS_Halt
OS_Halt: ; 0x020CD844
	mov r0, #0x0
	mcr p15, 0x0, r0, c7, c0, 0x4
	bx lr

	arm_func_start OS_Terminate
OS_Terminate: ; 0x020CD850
	stmdb sp!, {lr}
	sub sp, sp, #0x4
_020CD858:
	bl OS_DisableInterrupts
	bl OS_Halt
	b _020CD858

	arm_func_start MI_SetWramBank
MI_SetWramBank:
	ldr r1, _020CD870 ; =0x04000247
	strb r0, [r1, #0x0]
	bx lr
	.balign 4
_020CD870: .word 0x04000247

	arm_func_start MIi_CheckDma0SourceAddress
MIi_CheckDma0SourceAddress:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	cmp r3, #0x0
	and r0, r1, #0xff000000
	beq _020CD8A4
	cmp r3, #0x800000
	subeq r1, r1, r2
	b _020CD8A8
_020CD8A4:
	add r1, r1, r2
_020CD8A8:
	cmp r0, #0x4000000
	beq _020CD8D4
	cmp r0, #0x8000000
	bhs _020CD8D4
	and r0, r1, #0xff000000
	cmp r0, #0x4000000
	beq _020CD8D4
	cmp r0, #0x8000000
	addcc sp, sp, #0x4
	ldmccia sp!, {lr}
	bxcc lr
_020CD8D4:
	bl OS_Terminate
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start MIi_CheckAnotherAutoDMA
MIi_CheckAnotherAutoDMA: ; 0x020CD8E4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	ldr r4, _020CD994 ; =0x040000B8
	mov r7, r0
	mov r6, r1
	mov r5, #0x0
_020CD8FC:
	cmp r5, r7
	beq _020CD978
	ldr r1, [r4, #0x0]
	ands r0, r1, #0x80000000
	beq _020CD978
	and r0, r1, #0x38000000
	cmp r0, r6
	beq _020CD978
	cmp r0, #0x8000000
	bne _020CD92C
	cmp r6, #0x10000000
	beq _020CD978
_020CD92C:
	cmp r0, #0x10000000
	bne _020CD93C
	cmp r6, #0x8000000
	beq _020CD978
_020CD93C:
	cmp r0, #0x18000000
	beq _020CD974
	cmp r0, #0x20000000
	beq _020CD974
	cmp r0, #0x28000000
	beq _020CD974
	cmp r0, #0x30000000
	beq _020CD974
	cmp r0, #0x38000000
	beq _020CD974
	cmp r0, #0x8000000
	beq _020CD974
	cmp r0, #0x10000000
	bne _020CD978
_020CD974:
	bl OS_Terminate
_020CD978:
	add r5, r5, #0x1
	cmp r5, #0x3
	add r4, r4, #0xc
	blt _020CD8FC
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020CD994: .word 0x040000B8

	arm_func_start MI_StopDma
MI_StopDma: ; 0x020CD998
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	mov r1, #0x6
	mul r1, r4, r1
	add r1, r1, #0x5
	mov r1, r1, lsl #0x1
	add r1, r1, #0x4000000
	ldrh r2, [r1, #0xb0]
	cmp r4, #0x0
	bic r2, r2, #0x3a00
	strh r2, [r1, #0xb0]
	ldrh r2, [r1, #0xb0]
	bic r2, r2, #0x8000
	strh r2, [r1, #0xb0]
	ldrh r2, [r1, #0xb0]
	ldrh r1, [r1, #0xb0]
	bne _020CDA08
	mov r1, #0xc
	mul r12, r4, r1
	ldr r1, _020CDA14 ; =0x040000B0
	add r2, r12, #0x4000000
	mov r3, #0x0
	str r3, [r2, #0xb0]
	add r2, r12, r1
	ldr r1, _020CDA18 ; =0x81400001
	str r3, [r2, #0x4]
	str r1, [r2, #0x8]
_020CDA08:
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CDA14: .word 0x040000B0
_020CDA18: .word 0x81400001

	arm_func_start MI_WaitDma
MI_WaitDma:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	mov r1, #0x3
	mul r2, r4, r1
	ldr r1, _020CDA84 ; =0x040000B0
	add r2, r2, #0x2
	add r2, r1, r2, lsl #0x2
_020CDA3C:
	ldr r1, [r2, #0x0]
	ands r1, r1, #0x80000000
	bne _020CDA3C
	cmp r4, #0x0
	bne _020CDA78
	mov r1, #0xc
	mul r12, r4, r1
	ldr r1, _020CDA84 ; =0x040000B0
	add r2, r12, #0x4000000
	mov r3, #0x0
	str r3, [r2, #0xb0]
	add r2, r12, r1
	ldr r1, _020CDA88 ; =0x81400001
	str r3, [r2, #0x4]
	str r1, [r2, #0x8]
_020CDA78:
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CDA84: .word 0x040000B0
_020CDA88: .word 0x81400001

	arm_func_start MI_DmaCopy32Async
MI_DmaCopy32Async: ; 0x020CDA8C
	stmdb sp!, {r4-r8,lr}
	mov r5, r3
	mov r6, r2
	mov r2, r5
	mov r3, #0x0
	mov r8, r0
	mov r7, r1
	ldr r4, [sp, #0x18]
	bl MIi_CheckDma0SourceAddress
_020CDAB0:
	cmp r5, #0x0
	bne _020CDAD4
	cmp r4, #0x0
	ldmeqia sp!, {r4-r8, lr}
	bxeq lr
	ldr r0, [sp, #0x1C]
	blx r4
	ldmia sp!, {r4-r8, lr}
	bx lr
_020CDAD4:
	mov r0, r8
	bl MI_WaitDma
	cmp r4, #0x0
	beq _020CDB14
	ldr r2, [sp, #0x1C]
	mov r0, r8
	mov r1, r4
	bl OSi_EnterDmaCallback
	mov r3, r5, lsr #0x2
	mov r0, r8
	mov r1, r7
	mov r2, r6
	orr r3, r3, #0xc4000000
	bl FUN_01FF85F0
	ldmia sp!, {r4-r8, lr}
	bx lr
_020CDB14:
	mov r3, r5, lsr #0x2
	mov r0, r8
	mov r1, r7
	mov r2, r6
	orr r3, r3, #0x84000000
	bl FUN_01FF85F0
	ldmia sp!, {r4-r8, lr}
	bx lr

	arm_func_start MI_DmaFill32Async
MI_DmaFill32Async: ; 0x020CDB34
	stmdb sp!, {r4-r8,lr}
	movs r4, r3
	mov r7, r0
	mov r6, r1
	mov r5, r2
	ldr r8, [sp, #0x18]
	bne _020CDB6C
	cmp r8, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r0, [sp, #0x1c]
	blx r8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CDB6C:
	bl MI_WaitDma
_020CDB70:
	cmp r8, #0x0
	beq _020CDBC8
	ldr r2, [sp, #0x1C]
	mov r0, r7
	mov r1, r8
	bl OSi_EnterDmaCallback
	bl OS_DisableInterrupts
	mov r3, r4, lsr #2
	ldr r1, _20CDC08
	mov r2, r7, lsl #2
	add r2, r2, #0x4000000
	str r5, [r2, #0xE0]
	mov r4, r0
	add r1, r1, r7, lsl #0x2
	mov r0, r7
	mov r2, r6
	orr r3, r3, #0xc5000000
	bl FUN_01FF8544
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CDBC8:
	bl OS_DisableInterrupts
	ldr r1, _20CDC08
	mov r2, r7, lsl #0x2
	mov r3, r4, lsr #0x2
	mov r4, r0
	add ip, r2, #0x4000000
	mov r0, r7
	mov r2, r6
	add r1, r1, r7, lsl #0x2
	orr r3, r3, #0x85000000
	str r5, [ip, #0xE0] 
	bl FUN_01FF8544
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
_20CDC08: .word 0x040000E0

	arm_func_start MI_DmaCopy16
MI_DmaCopy16: ; 0x020CDC0C
	stmdb sp!, {r4-r8,lr}
	movs r5, r3
	mov r8, r0
	mov r7, r1
	mov r6, r2
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r2, r5
	mov r3, #0x0
	bl MIi_CheckDma0SourceAddress
	mov r0, #0x3
	mul r1, r8, r0
	ldr r0, _020CDC80 ; =0x040000B0
	add r1, r1, #0x2
	add r4, r0, r1, lsl #0x2
_020CDC48:
	ldr r0, [r4, #0x0]
	ands r0, r0, #0x80000000
	bne _020CDC48
	mov r3, r5, lsr #0x1
	mov r0, r8
	mov r1, r7
	mov r2, r6
	orr r3, r3, #0x80000000
	bl FUN_01FF857C
_020CDC6C:
	ldr r0, [r4]
	ands r0, r0, #0x80000000
	bne _020CDC6C
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CDC80: .word 0x040000B0

	arm_func_start MI_DmaCopy32
MI_DmaCopy32: ; 0x020CDC84
	stmdb sp!, {r4-r8,lr}
	mov r5, r3
	mov r6, r2
	mov r2, r5
	mov r3, #0x0
	mov r8, r0
	mov r7, r1
	bl MIi_CheckDma0SourceAddress
_020CDCA4:
	cmp r5, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r0, #0x3
	mul r1, r8, r0
	ldr r0, _020CDCFC
	add r1, r1, #0x2
	add r4, r0, r1, lsl #0x2
_020CDCC4:
	ldr r0, [r4]
	ands r0, r0, #0x80000000
	bne _020CDCC4
	mov r3, r5, lsr #0x2
	mov r0, r8
	mov r1, r7
	mov r2, r6
	orr r3, r3, #0x84000000
	bl FUN_01FF857C
_020CDCE8:
	ldr r0, [r4]
	ands r0, r0, #0x80000000
	bne _020CDCE8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CDCFC: .word 0x040000B0

	arm_func_start MI_DmaFill32
MI_DmaFill32: ; 0x020CDD00
	stmdb sp!, {r4-r8,lr}
	movs r4, r3
	mov r8, r0
	mov r7, r1
	mov r6, r2
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r0, #0x3
	mul r1, r8, r0
	ldr r0, _020CDD88 ; =0x040000B0
	add r1, r1, #0x2
	add r5, r0, r1, lsl #0x2
_020CDD30:
	ldr r0, [r5, #0x0]
	ands r0, r0, #0x80000000
	bne _020CDD30
	bl OS_DisableInterrupts
	ldr r1, _020CDD8C ; =0x040000E0
	mov r2, r8, lsl #0x2
	mov r3, r4, lsr #0x2
	mov r4, r0
	add r12, r2, #0x4000000
	mov r0, r8
	mov r2, r7
	add r1, r1, r8, lsl #0x2
	orr r3, r3, #0x85000000
	str r6, [r12, #0xe0]
	bl FUN_01FF84E4
	mov r0, r4
	bl OS_RestoreInterrupts
_020CDD74:
	ldr r0, [r5]
	ands r0, r0, #0x80000000
	bne _020CDD74
	ldmia sp!, {r4-r8,lr}
	bx lr
_020CDD88: .word 0x040000B0
_020CDD8C: .word 0x040000E0

	arm_func_start MI_HBlankDmaCopy16
MI_HBlankDmaCopy16: ; 0x020CDD90
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	mov r7, r0
	mov r4, r3
	mov r1, #0x10000000
	mov r5, r2
	bl MIi_CheckAnotherAutoDMA
	mov r0, r7
	mov r1, r6
	mov r2, r4
	mov r3, #0x0
	bl MIi_CheckDma0SourceAddress
_020CDDC4:
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7, lr}
	bxeq lr
	mov r0, r7
	bl MI_WaitDma
	ldr r3, _020CDE00
	mov r0, r7
	mov r1, r6
	mov r2, r5
	orr r3, r3, r4, lsr #0x1
	bl FUN_01FF85F0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020CDE00: .word 0x92600000

	arm_func_start MI_HBlankDmaCopy32
MI_HBlankDmaCopy32: ; 0x020CDE04
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	mov r7, r0
	mov r4, r3
	mov r1, #0x10000000
	mov r5, r2
	bl MIi_CheckAnotherAutoDMA
	mov r0, r7
	mov r1, r6
	mov r2, r4
	mov r3, #0x0
	bl MIi_CheckDma0SourceAddress
_020CDE38:
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r7
	bl MI_WaitDma
	ldr r3, _020CDE74
	mov r0, r7
	mov r1, r6
	mov r2, r5
	orr r3, r3, r4, lsr #0x2
	bl FUN_01FF85F0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020CDE74: .word 0x96600000

	arm_func_start MIi_DMAFastCallback
MIi_DMAFastCallback: ; 0x020CDE78
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020CDEB4 ; =0x021D37FC
	mov r2, #0x0
	ldr r1, [r0, #0x10]
	str r2, [r0, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldr r0, [r0, #0x14]
	ldmeqia sp!, {lr}
	bxeq lr
	blx r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CDEB4: .word 0x021D37FC

	arm_func_start MI_SendGXCommandAsyncFast
MI_SendGXCommandAsyncFast: ; 0x020CDEB8
	stmdb sp!, {r4-r6,lr}
	movs r4, r2
	mov r6, r0
	mov r5, r1
	bne _020CDEE8
	cmp r3, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldr r0, [sp, #0x10]
	blx r3
	ldmia sp!, {r4-r6,lr}
	bx lr
_020CDEE8:
	ldr r2, _020CDF6C ; =0x021D37FC
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	bne _020CDEE8
	ldr r12, [sp, #0x10]
	mov lr, #0x1
	mov r0, r6
	mov r1, #0x38000000
	str lr, [r2, #0x0]
	str r6, [r2, #0x4]
	str r3, [r2, #0x10]
	str r12, [r2, #0x14]
	bl MIi_CheckAnotherAutoDMA
	mov r0, r6
	mov r1, r5
	mov r2, r4
	mov r3, #0x0
	bl MIi_CheckDma0SourceAddress
	mov r0, r6
	bl MI_WaitDma
	mov r0, r6
	ldr r1, _020CDF70 ; =MIi_DMAFastCallback
	mov r2, #0x0
	bl OSi_EnterDmaCallback
	mov r0, r6
	mov r1, r5
	ldr r2, _020CDF74 ; =0x04000400
	mov r3, #0x3c00000
	rsb r3, r3, #0x0
	orr r3, r3, r4, lsr #0x2
	bl FUN_01FF85F0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020CDF6C: .word 0x021D37FC
_020CDF70: .word MIi_DMAFastCallback
_020CDF74: .word 0x04000400

	arm_func_start MIi_DMACallback
MIi_DMACallback: ; 0x020CDF78
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0x200000
	bl OS_DisableIrqMask
	ldr r2, _020CDFE4 ; =0x04000600
	ldr r0, _020CDFE8 ; =0x021D37FC
	ldr r1, [r2, #0x0]
	ldr r3, [r0, #0x18]
	bic r1, r1, #0xc0000000
	orr r1, r1, r3, lsl #0x1e
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x1c]
	mov r0, #0x200000
	bl OS_SetIrqFunction
	ldr r0, _020CDFE8 ; =0x021D37FC
	mov r2, #0x0
	ldr r1, [r0, #0x10]
	str r2, [r0, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldr r0, [r0, #0x14]
	ldmeqia sp!, {lr}
	bxeq lr
	blx r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CDFE4: .word 0x04000600
_020CDFE8: .word 0x021D37FC

	arm_func_start MIi_FIFOCallback
MIi_FIFOCallback: ; 0x020CDFEC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020CE0A4 ; =0x021D37FC
	ldr r4, [r0, #0xc]
	cmp r4, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, _020CE0A4 ; =0x021D37FC
	cmp r4, #0x1d8
	ldr r5, [r0, #0x8]
	movcs r4, #0x1d8
	ldr r2, [r0, #0xc]
	add r1, r5, r4
	subs r2, r2, r4
	str r2, [r0, #0xc]
	str r1, [r0, #0x8]
	bne _020CE078
	ldr r0, [r0, #0x4]
	ldr r1, _020CE0A8 ; =MIi_DMACallback
	mov r2, #0x0
	bl OSi_EnterDmaCallback
	mov r0, #0x3bc00000
	rsb r3, r0, #0x0
	ldr r1, _020CE0A4 ; =0x021D37FC
	ldr r2, _020CE0AC ; =0x04000400
	ldr r0, [r1, #0x4]
	mov r1, r5
	orr r3, r3, r4, lsr #0x2
	bl FUN_01FF85F0
	mov r0, #0x200000
	bl OS_ResetRequestIrqMask
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CE078:
	ldr r3, _020CE0B0 ; =0x84400000
	ldr r0, [r0, #0x4]
	ldr r2, _020CE0AC ; =0x04000400
	mov r1, r5
	orr r3, r3, r4, lsr #0x2
	bl FUN_01FF85F0
	mov r0, #0x200000
	bl OS_ResetRequestIrqMask
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CE0A4: .word 0x021D37FC
_020CE0A8: .word MIi_DMACallback
_020CE0AC: .word 0x04000400
_020CE0B0: .word 0x84400000

	arm_func_start MI_SendGXCommandAsync
MI_SendGXCommandAsync: ; 0x020CE0B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	cmp r2, #0x0
	bne _020CE0EC
	cmp r3, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, [sp, #0x10]
	blx r3
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020CE0EC:
	ldr r0, _020CE1BC ; =0x021D37FC
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _020CE0EC
	ldr r5, _020CE1C0 ; =0x04000600
_020CE100:
	ldr r0, [r5, #0x0]
	and r0, r0, #0x7000000
	mov r0, r0, lsr #0x18
	ands r0, r0, #0x2
	beq _020CE100
	ldr ip, _020CE1BC ; =0x021D37FC
	ldr lr, [sp, #0x10]
	str r3, [r12, #0x10]
	mov r5, #0x1
	mov r0, r4
	mov r3, #0x0
	str r5, [r12, #0x0]
	str r4, [r12, #0x4]
	str r1, [r12, #0x8]
	str r2, [r12, #0xc]
	str lr, [r12, #0x14]
	bl MIi_CheckDma0SourceAddress
	mov r0, r4
	bl MI_WaitDma
	bl OS_DisableInterrupts
	ldr r1, _020CE1C0 ; =0x04000600
	mov r4, r0
	ldr r0, [r1, #0x0]
	ldr r1, _020CE1BC ; =0x021D37FC
	and r0, r0, #0xc0000000
	mov r2, r0, lsr #0x1e
	mov r0, #0x200000
	str r2, [r1, #0x18]
	bl OS_GetIrqFunction
	ldr r1, _020CE1BC ; =0x021D37FC
	ldr r2, _020CE1C0 ; =0x04000600
	str r0, [r1, #0x1c]
	ldr r0, [r2, #0x0]
	ldr r1, _020CE1C4 ; =MIi_FIFOCallback
	bic r0, r0, #0xc0000000
	orr r3, r0, #0x40000000
	mov r0, #0x200000
	str r3, [r2, #0x0]
	bl OS_SetIrqFunction
	mov r0, #0x200000
	bl OS_EnableIrqMask
	bl MIi_FIFOCallback
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CE1BC: .word 0x021D37FC
_020CE1C0: .word 0x04000600
_020CE1C4: .word MIi_FIFOCallback

	arm_func_start MIi_CpuClear16
MIi_CpuClear16: ; 0x020CE1C8
	mov r3, #0x0
_020CE1CC:
	cmp r3, r2
	strlth r0, [r1, r3]
	addlt r3, r3, #0x2
	blt _020CE1CC
	bx lr

	arm_func_start MIi_CpuCopy16
MIi_CpuCopy16: ; 0x020CE1E0
	mov r12, #0x0
_020CE1E4:
	cmp r12, r2
	ldrlth r3, [r0, r12]
	strlth r3, [r1, r12]
	addlt r12, r12, #0x2
	blt _020CE1E4
	bx lr

	arm_func_start MIi_CpuClear32
MIi_CpuClear32: ; 0x020CE1FC
	add r12, r1, r2
_020CE200:
	cmp r1, r12
	stmltia r1!, {r0}
	blt _020CE200
	bx lr

	arm_func_start MIi_CpuCopy32
MIi_CpuCopy32: ; 0x020CE210
	add r12, r1, r2
_020CE214:
	cmp r1, r12
	ldmltia r0!, {r2}
	stmltia r1!, {r2}
	blt _020CE214
	bx lr

	arm_func_start MIi_CpuSend32
MIi_CpuSend32: ; 0x020CE228
	add r12, r0, r2
_020CE22C:
	cmp r0, r12
	ldmltia r0!, {r2}
	strlt r2, [r1, #0x0]
	blt _020CE22C
	bx lr

	arm_func_start MIi_CpuClearFast
MIi_CpuClearFast: ; 0x020CE240
	stmdb sp!, {r4-r9}
	add r9, r1, r2
	mov r12, r2, lsr #0x5
	add r12, r1, r12, lsl #0x5
	mov r2, r0
	mov r3, r2
	mov r4, r2
	mov r5, r2
	mov r6, r2
	mov r7, r2
	mov r8, r2
_020CE26C:
	cmp r1, r12
	stmltia r1!, {r0,r2-r8}
	blt _020CE26C
_020CE278:
	cmp r1, r9
	stmltia r1!, {r0}
	blt _020CE278
	ldmia sp!, {r4-r9}
	bx lr

	arm_func_start MIi_CpuCopyFast
MIi_CpuCopyFast: ; 0x020CE28C
	stmdb sp!, {r4-r10}
	add r10, r1, r2
	mov r12, r2, lsr #0x5
	add r12, r1, r12, lsl #0x5
_020CE29C:
	cmp r1, r12
	ldmltia r0!, {r2-r9}
	stmltia r1!, {r2-r9}
	blt _020CE29C
_020CE2AC:
	cmp r1, r10
	ldmltia r0!, {r2}
	stmltia r1!, {r2}
	blt _020CE2AC
	ldmia sp!, {r4-r10}
	bx lr

	arm_func_start FUN_020CE2C4
FUN_020CE2C4:
	ldmia r0!, {r2, r3, ip}
	stmia r1!, {r2, r3, ip}
	ldmia r0!, {r2, r3, ip}
	stmia r1!, {r2, r3, ip}
	ldmia r0!, {r2, r3}
	stmia r1!, {r2, r3}
	bx lr

	arm_func_start MI_Copy36B
MI_Copy36B: ; 0x020CE2E0
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	bx lr

	arm_func_start MI_Copy48B
MI_Copy48B: ; 0x020CE2FC
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	bx lr

	arm_func_start MI_Copy64B
MI_Copy64B: ; 0x020CE320
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0!, {r2-r3,r12}
	stmia r1!, {r2-r3,r12}
	ldmia r0, {r0,r2-r3,r12}
	stmia r1!, {r0,r2-r3,r12}
	bx lr

	arm_func_start MI_CpuFill8
MI_CpuFill8: ; 0x020CE34C
	cmp r2, #0x0
	bxeq lr
	tst r0, #0x1
	beq _020CE378
	ldrh r12, [r0, #-0x1]
	and r12, r12, #0xff
	orr r3, r12, r1, lsl #0x8
	strh r3, [r0, #-0x1]
	add r0, r0, #0x1
	subs r2, r2, #0x1
	bxeq lr
_020CE378:
	cmp r2, #0x2
	blo _020CE3C0
	orr r1, r1, r1, lsl #0x8
	tst r0, #0x2
	beq _020CE398
	strh r1, [r0], #0x2
	subs r2, r2, #0x2
	bxeq lr
_020CE398:
	orr r1, r1, r1, lsl #0x10
	bics r3, r2, #0x3
	beq _020CE3B8
	sub r2, r2, r3
	add r12, r3, r0
_020CE3AC:
	str r1, [r0], #0x4
	cmp r0, r12
	blo _020CE3AC
_020CE3B8:
	tst r2, #0x2
	strneh r1, [r0], #0x2
_020CE3C0:
	tst r2, #0x1
	bxeq lr
	ldrh r3, [r0, #0x0]
	and r3, r3, #0xff00
	and r1, r1, #0xff
	orr r1, r1, r3
	strh r1, [r0, #0x0]
	bx lr

	arm_func_start MI_CpuCopy8
MI_CpuCopy8:
	cmp r2, #0x0
	bxeq lr
	tst r1, #0x1
	beq _020CE420
	ldrh r12, [r1, #-0x1]
	and r12, r12, #0xff
	tst r0, #0x1
	ldrneh r3, [r0, #-0x1]
	movne r3, r3, lsr #0x8
	ldreqh r3, [r0, #0x0]
	orr r3, r12, r3, lsl #0x8
	strh r3, [r1, #-0x1]
	add r0, r0, #0x1
	add r1, r1, #0x1
	subs r2, r2, #0x1
	bxeq lr
_020CE420:
	eor r12, r1, r0
	tst r12, #0x1
	beq _020CE474
	bic r0, r0, #0x1
	ldrh r12, [r0], #0x2
	mov r3, r12, lsr #0x8
	subs r2, r2, #0x2
	blo _020CE458
_020CE440:
	ldrh r12, [r0], #0x2
	orr r12, r3, r12, lsl #0x8
	strh r12, [r1], #0x2
	mov r3, r12, lsr #0x10
	subs r2, r2, #0x2
	bhs _020CE440
_020CE458:
	tst r2, #0x1
	bxeq lr
	ldrh r12, [r1, #0x0]
	and r12, r12, #0xff00
	orr r12, r12, r3
	strh r12, [r1, #0x0]
	bx lr
_020CE474:
	tst r12, #0x2
	beq _020CE4A0
	bics r3, r2, #0x1
	beq _020CE4EC
	sub r2, r2, r3
	add r12, r3, r1
_020CE48C:
	ldrh r3, [r0], #0x2
	strh r3, [r1], #0x2
	cmp r1, r12
	blo _020CE48C
	b _020CE4EC
_020CE4A0:
	cmp r2, #0x2
	blo _020CE4EC
	tst r1, #0x2
	beq _020CE4C0
	ldrh r3, [r0], #0x2
	strh r3, [r1], #0x2
	subs r2, r2, #0x2
	bxeq lr
_020CE4C0:
	bics r3, r2, #0x3
	beq _020CE4E0
	sub r2, r2, r3
	add r12, r3, r1
_020CE4D0:
	ldr r3, [r0], #0x4
	str r3, [r1], #0x4
	cmp r1, r12
	blo _020CE4D0
_020CE4E0:
	tst r2, #0x2
	ldrneh r3, [r0], #0x2
	strneh r3, [r1], #0x2
_020CE4EC:
	tst r2, #0x1
	bxeq lr
	ldrh r2, [r1, #0x0]
	ldrh r0, [r0, #0x0]
	and r2, r2, #0xff00
	and r0, r0, #0xff
	orr r0, r2, r0
	strh r0, [r1, #0x0]
	bx lr

	thumb_func_start MI_Zero36B
MI_Zero36B: ; 0x020CE510
	mov r1, #0x0
	mov r2, #0x0
	mov r3, #0x0
	stmia r0!, {r1-r3}
	stmia r0!, {r1-r3}
	stmia r0!, {r1-r3}
	bx lr

	arm_func_start MI_SwapWord
MI_SwapWord: ; 0x020CE520
	swp r0, r0, [r1]
	bx lr

	arm_func_start MI_UncompressLZ8
MI_UncompressLZ8: ; 0x020CE528
	stmdb sp!, {r4-r6,lr}
	ldr r5, [r0], #0x4
	mov r2, r5, lsr #0x8
_020CE534:
	cmp r2, #0x0
	ble _020CE5B4
	ldrb lr, [r0], #0x1
	mov r4, #0x8
_020CE544:
	subs r4, r4, #0x1
	blt _020CE534
	tst lr, #0x80
	bne _020CE568
	ldrb r6, [r0], #0x1
	.word 0xE1416096
	add r1, r1, #0x1
	sub r2, r2, #0x1
	b _020CE5A4
_020CE568:
	ldrb r5, [r0, #0x0]
	mov r6, #0x3
	add r3, r6, r5, asr #0x4
	ldrb r6, [r0], #0x1
	and r5, r6, #0xf
	mov r12, r5, lsl #0x8
	ldrb r6, [r0], #0x1
	orr r5, r6, r12
	add r12, r5, #0x1
	sub r2, r2, r3
_020CE590:
	ldrb r5, [r1, -r12]
	.word 0xE1415095
	add r1, r1, #0x1
	subs r3, r3, #0x1
	bgt _020CE590
_020CE5A4:
	cmp r2, #0x0
	movgt lr, lr, lsl #0x1
	bgt _020CE544
	b _020CE534
_020CE5B4:
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start MIi_CardDmaCopy32
MIi_CardDmaCopy32: ; 0x020CE5BC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	mov r6, r0
	mov r7, r3
	mvn r1, #0x0
	mov r4, r2
	bl MIi_CheckAnotherAutoDMA
	mov r0, r6
	mov r1, r5
	mov r2, r7
	mov r3, #0x1000000
	bl MIi_CheckDma0SourceAddress
_020CE5F0:
	cmp r7, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7, lr}
	bxeq lr
	mov r0, #0x3
	mul r1, r6, r0
	ldr r0, _020CE640
	add r1, r1, #0x2
	add r1, r0, r1, lsl #0x2
_020CE614:
	ldr r0, [r1]
	ands r0, r0, #0x80000000
	bne _020CE614
	ldr r3, _020CE644
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl FUN_01FF85F0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7, lr}
	bx lr
_020CE640: .word 0x040000B0
_020CE644: .word 0xAf000001

	arm_func_start MI_Init
MI_Init: ; 0x020CE648
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, #0x3
	bl MI_SetWramBank
	mov r0, #0x0
	bl MI_StopDma
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr

	arm_func_start PushCommand_impl
PushCommand_impl: ; 0x020CE66C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r0, #0x1
	mov r6, r1
	mov r5, r2
	mov r4, r3
	bl SND_AllocCommand
_020CE68C:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7, lr}
	bxeq lr
	str r7, [r0, #0x4]
	str r6, [r0, #0x8]
	str r5, [r0, #0xc]
	ldr r1, [sp, #0x18]
	str r4, [r0, #0x10]
	str r1, [r0, #0x14]
	bl SND_PushCommand
	add sp, sp, #0x4
	ldmia sp!, {r4-r7, lr}
	bx lr

	arm_func_start SNDi_SetTrackParam
SNDi_SetTrackParam: ; 0x020CE6C4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r12, [sp, #0x8]
	mov lr, r2
	str r3, [sp, #0x0]
	mov r2, r1
	orr r1, r0, r12, lsl #0x18
	mov r3, lr
	mov r0, #0x7
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020CE6F8
FUN_020CE6F8: ; 0x020CE6F8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r12, r2
	str r3, [sp, #0x0]
	mov r1, r0
	mov r2, lr
	mov r3, r12
	mov r0, #0x6
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_ResetMasterPan
SND_ResetMasterPan: ; 0x020CE72C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0x0
	mov r3, r2
	mov r0, #0x18
	mvn r1, #0x0
	str r2, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetMasterPan
SND_SetMasterPan: ; 0x020CE758
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0x0
	mov r1, r0
	mov r3, r2
	mov r0, #0x18
	str r2, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetOutputSelector
SND_SetOutputSelector: ; 0x020CE784
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r12, r2
	str r3, [sp, #0x0]
	mov r1, r0
	mov r2, lr
	mov r3, r12
	mov r0, #0x19
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_InvalidateWaveData
SND_InvalidateWaveData: ; 0x020CE7B8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x20
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_InvalidateBankData
SND_InvalidateBankData: ; 0x020CE7E4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x1f
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_InvalidateSeqData
SND_InvalidateSeqData: ; 0x020CE810
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x1e
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetupChannelPcm
SND_SetupChannelPcm: ; 0x020CE83C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r12, [sp, #0x18]
	mov r3, r3, lsl #0x1a
	orr r4, r3, r1, lsl #0x18
	ldr r5, [sp, #0x24]
	mov r3, r12, lsl #0x18
	ldr r1, [sp, #0x1c]
	ldr r12, [sp, #0x10]
	orr r4, r4, r5, lsl #0x10
	orr r4, r12, r4
	ldr lr, [sp, #0x20]
	orr r3, r3, r1, lsl #0x16
	ldr r12, [sp, #0x14]
	orr r1, r0, lr, lsl #0x10
	orr r3, r12, r3
	mov r0, #0xe
	str r4, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SND_SetChannelPan
SND_SetChannelPan: ; 0x020CE894
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x15
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetChannelVolume
SND_SetChannelVolume: ; 0x020CE8C0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r3, r2
	mov r12, #0x0
	mov r1, r0
	mov r2, lr
	mov r0, #0x14
	str r12, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetChannelTimer
SND_SetChannelTimer: ; 0x020CE8F4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x13
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_UnlockChannel
SND_UnlockChannel: ; 0x020CE920
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x1b
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_LockChannel
SND_LockChannel: ; 0x020CE94C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x1a
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetupAlarm
SND_SetupAlarm: ; 0x020CE978
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r4, r2
	mov r5, r1
	ldr r2, [sp, #0x18]
	mov r6, r0
	mov r1, r3
	bl SNDi_SetAlarmHandler
_020CE998:
	str r0, [sp]
	mov r1, r6
	mov r2, r5
	mov r3, r4
	mov r0, #0x12
	bl PushCommand_impl
	add sp, sp, #0x8
	ldmia sp!, {r4-r6, lr}
	bx lr

	arm_func_start SND_SetupCapture
SND_SetupCapture: ; 0x020CE9BC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, r0, lsl #0x1f
	orr r0, r0, r1, lsl #0x1e
	ldr r12, [sp, #0x8]
	mov r1, r2
	orr r0, r0, r12, lsl #0x1d
	ldr r2, [sp, #0xc]
	mov lr, #0x0
	orr r0, r0, r2, lsl #0x1c
	ldr r12, [sp, #0x10]
	mov r2, r3
	orr r3, r0, r12, lsl #0x1b
	mov r0, #0x11
	str lr, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_StopTimer
SND_StopTimer: ; 0x020CEA08
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r7, r2
	mov r9, r0
	mov r8, r1
	mov r6, r3
	mov r4, r7
	mov r5, #0x0
	b _020CEA44
_020CEA2C:
	ands r0, r4, #0x1
	beq _020CEA3C
	mov r0, r5
	bl SNDi_IncAlarmId
_020CEA3C:
	add r5, r5, #0x1
	mov r4, r4, lsr #0x1
_020CEA44:
	cmp r5, #0x8
	bge _020CEA54
	cmp r4, #0x0
	bne _020CEA2C
_020CEA54:
	mov r1, r9
	mov r2, r8
	mov r3, r7
	mov r0, #0xd
	str r6, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start SND_StartTimer
SND_StartTimer: ; 0x020CEA78
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r12, r2
	str r3, [sp, #0x0]
	mov r1, r0
	mov r2, lr
	mov r3, r12
	mov r0, #0xc
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetTrackAllocatableChannel
SND_SetTrackAllocatableChannel: ; 0x020CEAAC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r3, r2
	mov r12, #0x0
	mov r1, r0
	mov r2, lr
	mov r0, #0x9
	str r12, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetTrackPan
SND_SetTrackPan: ; 0x020CEAE0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r3, r2
	mov r12, #0x1
	mov r2, #0x9
	str r12, [sp, #0x0]
	bl SNDi_SetTrackParam
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetTrackPitch
SND_SetTrackPitch: ; 0x020CEB08
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r3, r2
	mov r12, #0x2
	mov r2, #0xc
	str r12, [sp, #0x0]
	bl SNDi_SetTrackParam
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_SetPlayerChannelPriority
SND_SetPlayerChannelPriority: ; 0x020CEB30
	ldr ip, _020CEB44 ; =FUN_020CE6F8
	mov r2, r1
	mov r1, #0x4
	mov r3, #0x1
	bx r12
	.balign 4
_020CEB44: .word FUN_020CE6F8

	arm_func_start SND_SetPlayerVolume
SND_SetPlayerVolume: ; 0x020CEB48
	ldr ip, _020CEB5C ; =FUN_020CE6F8
	mov r2, r1
	mov r1, #0x6
	mov r3, #0x2
	bx r12
	.balign 4
_020CEB5C: .word FUN_020CE6F8

	arm_func_start SND_PauseSeq
SND_PauseSeq: ; 0x020CEB60
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, r1
	mov r3, #0x0
	mov r1, r0
	mov r0, #0x4
	str r3, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_StartPreparedSeq
SND_StartPreparedSeq: ; 0x020CEB8C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0x0
	mov r1, r0
	mov r3, r2
	mov r0, #0x3
	str r2, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_PrepareSeq
SND_PrepareSeq: ; 0x020CEBB8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov lr, r1
	mov r12, r2
	str r3, [sp, #0x0]
	mov r1, r0
	mov r2, lr
	mov r3, r12
	mov r0, #0x2
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SND_StopSeq
SND_StopSeq: ; 0x020CEBEC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r2, #0x0
	mov r1, r0
	mov r3, r2
	mov r0, #0x1
	str r2, [sp, #0x0]
	bl PushCommand_impl
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SNDi_UnlockMutex
SNDi_UnlockMutex: ; 0x020CEC18
	ldr ip, _020CEC24 ; =OS_UnlockMutex
	ldr r0, _020CEC28 ; =0x021D3820
	bx r12
	.balign 4
_020CEC24: .word OS_UnlockMutex
_020CEC28: .word 0x021D3820

	arm_func_start SNDi_LockMutex
SNDi_LockMutex: ; 0x020CEC2C
	ldr ip, _020CEC38 ; =OS_LockMutex
	ldr r0, _020CEC3C ; =0x021D3820
	bx r12
	.balign 4
_020CEC38: .word OS_LockMutex
_020CEC3C: .word 0x021D3820

	arm_func_start SND_Init
SND_Init: ; 0x020CEC40
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020CEC84 ; =0x021D381C
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020CEC88 ; =0x021D3820
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl OS_InitMutex
	bl SND_CommandInit
	bl SND_AlarmInit
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CEC84: .word 0x021D381C
_020CEC88: .word 0x021D3820

	arm_func_start IsCommandAvailable
IsCommandAvailable:
	stmdb sp!, {r4,lr}
	bl OS_IsRunOnEmulator
_020CEC94:
	cmp r0, #0x0
	moveq r0, #0x1
	ldmeqia sp!, {r4, lr}
	bxeq lr
	bl OS_DisableInterrupts
	ldr r1, _020CECD0
	mov r2, #0x10
	str r2, [r1]
	ldr r4, [r1]
	bl OS_RestoreInterrupts
	cmp r4, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	ldmia sp!, {r4, lr}
	bx lr
_020CECD0: .word 0x04FFF200

	arm_func_start AllocCommand
AllocCommand: ; 0x020CECD4
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020CED24 ; =0x021D3838
	ldr r4, [r1, #0x0]
	cmp r4, #0x0
	bne _020CECFC
	bl OS_RestoreInterrupts
_020CECF0:
	mov r0, #0x0
	ldmia sp!, {r4, lr}
	bx lr
_020CECFC:
	ldr r2, [r4, #0x0]
	str r2, [r1, #0x0]
	cmp r2, #0x0
	ldreq r1, _020CED28 ; =0x021D3848
	moveq r2, #0x0
	streq r2, [r1, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CED24: .word 0x021D3838
_020CED28: .word 0x021D3848

	arm_func_start RequestCommandProc
RequestCommandProc: ; 0x020CED2C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, #0x7
	mov r4, #0x0
_020CED3C:
	mov r0, r5
	mov r1, r4
	mov r2, r4
	bl PXI_SendWordByFifo
_020CED4C:
	cmp r0, #0
	blt _020CED3C
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start InitPXI
InitPXI: ; 0x020CED60
	stmdb sp!, {r4-r6,lr}
	ldr r1, _020CEDC8 ; =PxiFifoCallback
	mov r0, #0x7
	bl PXI_SetFifoRecvCallback
	bl IsCommandAvailable
_020CED74:
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6, lr}
	bxeq lr
	mov r0, #0x7
	mov r1, #0x1
	bl PXI_IsCallbackReady
	cmp r0, #0x0
	ldmneia sp!, {r4-r6, lr}
	bxne lr
	mov r6, #0x64
	mov r5, #0x7
	mov r4, #0x1
_020CEDA4:
	mov r0, r6
	bl OS_SpinWait
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
	cmp r0, #0x0
	beq _020CEDA4
	ldmia sp!, {r4-r6, lr}
	bx lr
_020CEDC8: .word PxiFifoCallback

	arm_func_start PxiFifoCallback
PxiFifoCallback: ; 0x020CEDCC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r1
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, r5
	bl SNDi_CallAlarmHandler
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SND_CountWaitingCommand
SND_CountWaitingCommand: ; 0x020CEDFC
	stmdb sp!, {r4,lr}
	bl SND_CountFreeCommand
	mov r4, r0
	bl SND_CountReservedCommand
	rsb r1, r4, #0x100
	sub r0, r1, r0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SND_CountReservedCommand
SND_CountReservedCommand: ; 0x020CEE1C
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020CEE58 ; =0x021D3840
	mov r4, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020CEE48
_020CEE38:
	ldr r1, [r1, #0x0]
	add r4, r4, #0x1
	cmp r1, #0x0
	bne _020CEE38
_020CEE48:
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CEE58: .word 0x021D3840

	arm_func_start SND_CountFreeCommand
SND_CountFreeCommand: ; 0x020CEE5C
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020CEE98 ; =0x021D3838
	mov r4, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	beq _020CEE88
_020CEE78:
	ldr r1, [r1, #0x0]
	add r4, r4, #0x1
	cmp r1, #0x0
	bne _020CEE78
_020CEE88:
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CEE98: .word 0x021D3838

	arm_func_start SND_IsFinishedCommandTag
SND_IsFinishedCommandTag:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _020CEEEC ; =0x021D383C
	ldr r1, [r1, #0x0]
	cmp r4, r1
	bls _020CEECC
	sub r1, r4, r1
	cmp r1, #0x80000000
	movcc r4, #0x0
	movcs r4, #0x1
	b _020CEEDC
_020CEECC:
	sub r1, r1, r4
	cmp r1, #0x80000000
	movcc r4, #0x1
	movcs r4, #0x0
_020CEEDC:
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CEEEC: .word 0x021D383C

	arm_func_start SND_GetCurrentCommandTag
SND_GetCurrentCommandTag: ; 0x020CEEF0
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020CEF24 ; =0x021D3840
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	ldreq r1, _020CEF28 ; =0x021D383C
	ldreq r4, [r1, #0x0]
	ldrne r1, _020CEF2C ; =0x021D3858
	ldrne r4, [r1, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CEF24: .word 0x021D3840
_020CEF28: .word 0x021D383C
_020CEF2C: .word 0x021D3858

	arm_func_start SND_WaitForCommandProc
SND_WaitForCommandProc: ; 0x020CEF30
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl SND_IsFinishedCommandTag
_020CEF40:
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5, lr}
	bxne lr
	mov r4, #0x0
_020CEF54:
	mov r0, r4
	bl SND_RecvCommandReply
	cmp r0, #0x0
	bne _020CEF54
	mov r0, r5
	bl SND_IsFinishedCommandTag
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5, lr}
	bxne lr
	bl RequestCommandProc
	mov r0, r5
	bl SND_IsFinishedCommandTag
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5, lr}
	bxne lr
	mov r4, #0x1
_020CEF9C:
	mov r0, r4
	bl SND_RecvCommandReply
	mov r0, r5
	bl SND_IsFinishedCommandTag
	cmp r0, #0x0
	beq _020CEF9C
	add sp, sp, #0x4
	ldmia sp!, {r4-r5, lr}
	bx lr

	arm_func_start SND_FlushCommand
SND_FlushCommand: ; 0x020CEFC0
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020CF164 ; =0x021D3840
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020CEFF8
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r9,lr}
	bx lr
_020CEFF8:
	ldr r1, _020CF168 ; =0x021D3854
	ldr r1, [r1, #0x0]
	cmp r1, #0x8
	blt _020CF03C
	ands r1, r5, #0x1
	bne _020CF024
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r9,lr}
	bx lr
_020CF024:
	mov r0, #0x1
	bl SND_RecvCommandReply
	ldr r0, _020CF168 ; =0x021D3854
	ldr r0, [r0, #0x0]
	cmp r0, #0x8
	bge _020CF024
_020CF03C:
	ldr r0, _020CF16C ; =0x021D3B00
	mov r1, #0x1800
	bl DC_FlushRange
	ldr r1, _020CF164 ; =0x021D3840
	mov r0, #0x7
	ldr r1, [r1, #0x0]
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020CF05C:
	cmp r0, #0x0
	bge _020CF0E0
	ands r0, r5, #0x1
	bne _020CF084
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r9, lr}
	bx lr
_020CF084:
	ldr r1, _020CF164
	mov r0, #0x7
	ldr r1, [r1]
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	bge _020CF0E0
	ldr r6, _020CF164
	mov r9, #0x64
	mov r8, #0x7
	mov r7, #0x0
_020CF0B0:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r9
	bl OS_SpinWait
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, r8
	ldr r1, [r6]
	mov r2, r7
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	blt _020CF0B0
_020CF0E0:
	ands r0, r5, #0x2
	beq _020CF0EC
	bl RequestCommandProc
_020CF0EC:
	ldr r0, _020CF170
	ldr r1, _020CF164
	ldr r3, [r0]
	ldr r5, [r1]
	add r1, r3, #0x1
	ldr r2, _020CF174
	str r1, [r0]
	str r5, [r2, r3, lsl #2]
	cmp r1, #0x8
	movgt r1, #0x0
	ldr r2, _020CF168
	strgt r1, [r0]
	ldr r1, _020CF178
	ldr r3, [r2]
	ldr r0, [r1]
	add ip, r3, #0x1
	add r6, r0, #0x1
	ldr r5, _020CF164
	mov lr, #0x0
	ldr r3, _020CF17C
	mov r0, r4
	str lr, [r5]
	str lr, [r3]
	str ip, [r2]
	str r6, [r1]
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9, lr}
	bx lr
_020CF164: .word 0x021D3840
_020CF168: .word 0x021D3854
_020CF16C: .word 0x021D3B00
_020CF170: .word 0x021D3850
_020CF174: .word 0x021D385C
_020CF178: .word 0x021D3858
_020CF17C: .word 0x021D3844

	arm_func_start SND_PushCommand
SND_PushCommand: ; 0x020CF180
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r2, _020CF1C0 ; =0x021D3844
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	ldreq r1, _020CF1C4 ; =0x021D3840
	streq r4, [r2, #0x0]
	streq r4, [r1, #0x0]
	strne r4, [r1, #0x0]
	strne r4, [r2, #0x0]
	mov r1, #0x0
	str r1, [r4, #0x0]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CF1C0: .word 0x021D3844
_020CF1C4: .word 0x021D3840

	arm_func_start SND_AllocCommand
SND_AllocCommand:
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl IsCommandAvailable
_020CF1D4:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl AllocCommand
	cmp r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	ands r0, r4, #0x1
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl SND_CountWaitingCommand
	cmp r0, #0x0
	ble _020CF238
	mov r4, #0x0
_020CF214:
	mov r0, r4
	bl SND_RecvCommandReply
	cmp r0, #0x0
	bne _020CF214
	bl AllocCommand
	cmp r0, #0x0
	beq _020CF240
	ldmia sp!, {r4,lr}
	bx lr
_020CF238:
	mov r0, #0x1
	bl SND_FlushCommand
_020CF240:
	bl RequestCommandProc
	mov r4, #0x1
_020CF248:
	mov r0, r4
	bl SND_RecvCommandReply
	bl AllocCommand
	cmp r0, #0x0
	beq _020CF248
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SND_RecvCommandReply
SND_RecvCommandReply: ; 0x020CF264
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	mov r5, r0
	ands r0, r4, #0x1
	beq _020CF2C0
	bl SNDi_GetFinishedCommandTag
	ldr r4, _020CF380 ; =0x021D383C
	ldr r1, [r4, #0x0]
	cmp r1, r0
	bne _020CF2E8
	mov r6, #0x64
_020CF294:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r6
	bl OS_SpinWait
	bl OS_DisableInterrupts
	mov r5, r0
	bl SNDi_GetFinishedCommandTag
	ldr r1, [r4, #0x0]
	cmp r1, r0
	beq _020CF294
	b _020CF2E8
_020CF2C0:
	bl SNDi_GetFinishedCommandTag
	ldr r1, _020CF380 ; =0x021D383C
	ldr r1, [r1, #0x0]
	cmp r1, r0
	bne _020CF2E8
	mov r0, r5
	bl OS_RestoreInterrupts
_020CF2DC:
	mov r0, #0x0
	ldmia sp!, {r4-r6, lr}
	bx lr
_020CF2E8:
	ldr r0, _020CF384 ; =0x021D384C
	ldr r2, _020CF388 ; =0x021D385C
	ldr r3, [r0, #0x0]
	add r1, r3, #0x1
	ldr r4, [r2, r3, lsl #0x2]
	str r1, [r0, #0x0]
	cmp r1, #0x8
	movgt r1, #0x0
	strgt r1, [r0, #0x0]
	ldr r0, [r4, #0x0]
	mov r1, r4
	cmp r0, #0x0
	beq _020CF32C
_020CF31C:
	ldr r1, [r1, #0x0]
	ldr r0, [r1, #0x0]
	cmp r0, #0x0
	bne _020CF31C
_020CF32C:
	ldr r0, _020CF38C ; =0x021D3848
	ldr r3, _020CF390 ; =0x021D3854
	ldr r0, [r0, #0x0]
	ldr r2, _020CF380 ; =0x021D383C
	cmp r0, #0x0
	strne r4, [r0, #0x0]
	ldreq r0, _020CF394 ; =0x021D3838
	ldr lr, [r3, #0x0]
	streq r4, [r0, #0x0]
	ldr ip, _020CF38C ; =0x021D3848
	sub r6, lr, #0x1
	ldr r0, [r2, #0x0]
	str r1, [r12, #0x0]
	add lr, r0, #0x1
	mov r0, r5
	str r6, [r3, #0x0]
	str lr, [r2, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020CF380: .word 0x021D383C
_020CF384: .word 0x021D384C
_020CF388: .word 0x021D385C
_020CF38C: .word 0x021D3848
_020CF390: .word 0x021D3854
_020CF394: .word 0x021D3838

	arm_func_start SND_CommandInit
SND_CommandInit: ; 0x020CF398
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	bl InitPXI
	ldr r3, _020CF478 ; =0x021D3B00
	ldr r0, _020CF47C ; =0x021D3838
	mov r4, #0x0
	str r3, [r0, #0x0]
	mov r1, r3
	mov r0, #0x18
_020CF3BC:
	add r4, r4, #0x1
	mla r2, r4, r0, r1
	cmp r4, #0xff
	str r2, [r3], #0x18
	blt _020CF3BC
	ldr r7, _020CF480 ; =0x021D4B00
	mov r10, #0x0
	ldr r5, _020CF484 ; =0x021D3840
	ldr r4, _020CF488 ; =0x021D3844
	ldr lr, _020CF48C ; =0x021D3854
	ldr ip, _020CF490 ; =0x021D384C
	ldr r3, _020CF494 ; =0x021D3850
	ldr r1, _020CF498 ; =0x021D383C
	ldr sb, _020CF49C ; =0x021D52E8
	ldr r6, _020CF4A0 ; =0x021D3848
	ldr r2, _020CF4A4 ; =0x021D3858
	mov r8, #0x1
	ldr r0, _020CF4A8 ; =0x021D3880
	ldr fp, _020CF4AC ; =0x021D5360
	str r9, [r6, #0x0]
	str r10, [r7, #0x7e8]
	str r10, [r5, #0x0]
	str r10, [r4, #0x0]
	str r10, [lr, #0x0]
	str r10, [r12, #0x0]
	str r10, [r3, #0x0]
	str r8, [r2, #0x0]
	str r10, [r1, #0x0]
	str r0, [r11, #0x0]
	bl SNDi_InitSharedWork
	mov r0, r8
	bl SND_AllocCommand
_020CF43C:
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r11, lr}
	bxeq lr
	mov r2, #0x1D
	mov r1, fp
	str r2, [r0, #0x4]
	ldr r1, [r1]
	str r1, [r0, #0x8]
	bl SND_PushCommand
	mov r0, r8
	bl SND_FlushCommand
	add sp, sp, #0x4
	ldmia sp!, {r4-r11, lr}
	bx lr
_020CF478: .word 0x021D3B00
_020CF47C: .word 0x021D3838
_020CF480: .word 0x021D4B00
_020CF484: .word 0x021D3840
_020CF488: .word 0x021D3844
_020CF48C: .word 0x021D3854
_020CF490: .word 0x021D384C
_020CF494: .word 0x021D3850
_020CF498: .word 0x021D383C
_020CF49C: .word 0x021D52E8
_020CF4A0: .word 0x021D3848
_020CF4A4: .word 0x021D3858
_020CF4A8: .word 0x021D3880
_020CF4AC: .word 0x021D5360

	arm_func_start SNDi_CallAlarmHandler
SNDi_CallAlarmHandler: ; 0x020CF4B0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, _020CF50C ; =0x021D5300
	and r2, r0, #0xff
	mov r1, #0xc
	mla r3, r2, r1, r3
	mov r1, r0, asr #0x8
	ldrb r0, [r3, #0x8]
	and r1, r1, #0xff
	cmp r1, r0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r1, [r3, #0x0]
	cmp r1, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r0, [r3, #0x4]
	blx r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CF50C: .word 0x021D5300

	arm_func_start SNDi_SetAlarmHandler
SNDi_SetAlarmHandler:
	mov r3, #0xc
	mul r3, r0, r3
	ldr r0, _020CF53C ; =0x021D5300
	str r1, [r0, r3]
	add r1, r0, r3
	str r2, [r1, #0x4]
	ldrb r0, [r1, #0x8]
	add r0, r0, #0x1
	strb r0, [r1, #0x8]
	ldrb r0, [r1, #0x8]
	bx lr
	.balign 4
_020CF53C: .word 0x021D5300

	arm_func_start SNDi_IncAlarmId
SNDi_IncAlarmId: ; 0x020CF540
	ldr r2, _020CF55C ; =0x021D5300
	mov r1, #0xc
	mla r1, r0, r1, r2
	ldrb r0, [r1, #0x8]
	add r0, r0, #0x1
	strb r0, [r1, #0x8]
	bx lr
	.balign 4
_020CF55C: .word 0x021D5300

	arm_func_start SND_AlarmInit
SND_AlarmInit: ; 0x020CF560
	ldr r1, _020CF58C ; =0x021D5300
	mov r2, #0x0
	mov r0, r2
_020CF56C:
	str r0, [r1, #0x0]
	str r0, [r1, #0x4]
	add r2, r2, #0x1
	strb r0, [r1, #0x8]
	cmp r2, #0x8
	add r1, r1, #0xc
	blt _020CF56C
	bx lr
	.balign 4
_020CF58C: .word 0x021D5300

	arm_func_start SNDi_InitSharedWork
SNDi_InitSharedWork: ; 0x020CF590
	stmdb sp!, {r4,lr}
	mov r4, #0x0
	str r4, [r0, #0x4]
	strh r4, [r0, #0x8]
	strh r4, [r0, #0xa]
	mov r12, r0
	str r4, [r0, #0x0]
	mov r3, r4
	mvn r2, #0x0
_020CF5B4:
	mov lr, r3
	str r3, [r12, #0x40]
_020CF5BC:
	add r1, r12, lr, lsl #0x1
	add lr, lr, #0x1
	strh r2, [r1, #0x20]
	cmp lr, #0x10
	blt _020CF5BC
	add r4, r4, #0x1
	cmp r4, #0x10
	add r12, r12, #0x24
	blt _020CF5B4
	mov r3, #0x0
	mvn r2, #0x0
_020CF5E8:
	add r1, r0, r3, lsl #0x1
	add r1, r1, #0x200
	add r3, r3, #0x1
	strh r2, [r1, #0x60]
	cmp r3, #0x10
	blt _020CF5E8
	mov r1, #0x280
	bl DC_FlushRange
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SNDi_GetFinishedCommandTag
SNDi_GetFinishedCommandTag: ; 0x020CF610
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020CF640 ; =0x021D5360
	mov r1, #0x4
	ldr r0, [r0, #0x0]
	bl DC_InvalidateRange
	ldr r0, _020CF640 ; =0x021D5360
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CF640: .word 0x021D5360

	arm_func_start SND_GetPlayerTickCounter
SND_GetPlayerTickCounter: ; 0x020CF644
	stmdb sp!, {r4,lr}
	mov r1, #0x24
	mul r4, r0, r1
	ldr r0, _020CF680 ; =0x021D5360
	mov r1, #0x4
	ldr r0, [r0, #0x0]
	add r0, r0, #0x40
	add r0, r0, r4
	bl DC_InvalidateRange
	ldr r0, _020CF680 ; =0x021D5360
	ldr r0, [r0, #0x0]
	add r0, r0, r4
	ldr r0, [r0, #0x40]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020CF680: .word 0x021D5360

	arm_func_start SND_GetChannelStatus
SND_GetChannelStatus: ; 0x020CF684
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020CF6B8 ; =0x021D5360
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	add r0, r0, #0x8
	bl DC_InvalidateRange
	ldr r0, _020CF6B8 ; =0x021D5360
	ldr r0, [r0, #0x0]
	ldrh r0, [r0, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CF6B8: .word 0x021D5360

	arm_func_start SND_GetPlayerStatus
SND_GetPlayerStatus: ; 0x020CF6BC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020CF6F0 ; =0x021D5360
	mov r1, #0x4
	ldr r0, [r0, #0x0]
	add r0, r0, #0x4
	bl DC_InvalidateRange
	ldr r0, _020CF6F0 ; =0x021D5360
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020CF6F0: .word 0x021D5360

	arm_func_start SND_CalcChannelVolume
SND_CalcChannelVolume: ; 0x020CF6F4
	ldr r1, _020CF75C ; =0xFFFFFD2D
	cmp r0, r1
	movlt r0, r1
	blt _020CF70C
	cmp r0, #0x0
	movgt r0, #0x0
_020CF70C:
	ldr r1, _020CF760 ; =0x000002D3
	ldr r2, _020CF764 ; =0x02103CAC
	add r3, r0, r1
	mvn r1, #0xef
	cmp r0, r1
	ldrb r2, [r2, r3]
	movlt r0, #0x3
	blt _020CF74C
	mvn r1, #0x77
	cmp r0, r1
	movlt r0, #0x2
	blt _020CF74C
	mvn r1, #0x3b
	cmp r0, r1
	movlt r0, #0x1
	movge r0, #0x0
_020CF74C:
	orr r0, r2, r0, lsl #0x8
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bx lr
	.balign 4
_020CF75C: .word 0xFFFFFD2D
_020CF760: .word 0x000002D3
_020CF764: .word 0x02103CAC

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

	arm_func_start PXI_Init
PXI_Init: ; 0x020CFBB0
	ldr ip, _020CFBB8 ; =PXI_InitFifo
	bx r12
	.balign 4
_020CFBB8: .word PXI_InitFifo

	arm_func_start PXIi_HandlerRecvFifoNotEmpty
PXIi_HandlerRecvFifoNotEmpty: ; 0x020CFBBC
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x8
	ldr sl, _020CFCD4 ; =0x04000184
	ldr r5, _020CFCD8 ; =0x021D5368
	ldr r4, _020CFCDC ; =0x04000188
	mov r7, #0x4100000
	mov r6, #0x0
	mvn r8, #0x3
	mvn r9, #0x2
_020CFBE0:
	ldrh r0, [r10, #0x0]
	ands r0, r0, #0x4000
	ldrneh r0, [r10, #0x0]
	movne r1, r9
	orrne r0, r0, #0xc000
	strneh r0, [r10, #0x0]
	bne _020CFC28
	bl OS_DisableInterrupts
	ldrh r1, [r10, #0x0]
	ands r1, r1, #0x100
	beq _020CFC18
	bl OS_RestoreInterrupts
	mov r1, r8
	b _020CFC28
_020CFC18:
	ldr r1, [r7, #0x0]
	str r1, [sp, #0x0]
	bl OS_RestoreInterrupts
	mov r1, r6
_020CFC28:
	cmp r1, r8
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r10,lr}
	bxeq lr
	mvn r0, #0x2
	cmp r1, r0
	beq _020CFBE0
	ldr r1, [sp, #0x0]
	mov r0, r1, lsl #0x1b
	movs r0, r0, lsr #0x1b
	beq _020CFBE0
	ldr r3, [r5, r0, lsl #0x2]
	cmp r3, #0x0
	beq _020CFC74
	mov r2, r1, lsl #0x1a
	mov r1, r1, lsr #0x6
	mov r2, r2, lsr #0x1f
	blx r3
	b _020CFBE0
_020CFC74:
	mov r0, r1, lsl #0x1a
	movs r0, r0, lsr #0x1f
	bne _020CFBE0
	orr r0, r1, #0x20
	str r0, [sp, #0x0]
	ldrh r0, [r10, #0x0]
	ands r0, r0, #0x4000
	ldrneh r0, [r10, #0x0]
	orrne r0, r0, #0xc000
	strneh r0, [r10, #0x0]
	bne _020CFBE0
	bl OS_DisableInterrupts
	ldrh r1, [r10, #0x0]
	ands r1, r1, #0x2
	beq _020CFCB8
	bl OS_RestoreInterrupts
	b _020CFBE0
_020CFCB8:
	ldr r1, [sp, #0x0]
	str r1, [r4, #0x0]
	bl OS_RestoreInterrupts
	b _020CFBE0
_020CFCC8:
	add sp, sp, #0x8
	ldmia sp!, {r4-r10, lr}
	bx lr
_020CFCD4: .word 0x04000184
_020CFCD8: .word 0x021D5368
_020CFCDC: .word 0x04000188

	arm_func_start PXI_SendWordByFifo
PXI_SendWordByFifo:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r3, [sp, #0x0]
	and r0, r0, #0x1f
	bic r3, r3, #0x1f
	orr r12, r3, r0
	bic r3, r12, #0x20
	and r0, r2, #0x1
	orr r3, r3, r0, lsl #0x5
	str r12, [sp, #0x0]
	and r2, r3, #0x3f
	bic r0, r1, #0xfc000000
	orr r0, r2, r0, lsl #0x6
	str r3, [sp, #0x0]
	ldr r2, _020CFD8C ; =0x04000184
	str r0, [sp, #0x0]
	ldrh r0, [r2, #0x0]
	ands r0, r0, #0x4000
	ldrneh r1, [r2, #0x0]
	addne sp, sp, #0x4
	mvnne r0, #0x0
	orrne r1, r1, #0xc000
	strneh r1, [r2, #0x0]
	ldmneia sp!, {lr}
	bxne lr
	bl OS_DisableInterrupts
	ldr r1, _020CFD8C ; =0x04000184
	ldrh r1, [r1, #0x0]
	ands r1, r1, #0x2
	beq _020CFD6C
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mvn r0, #0x1
	ldmia sp!, {lr}
	bx lr
_020CFD6C:
	ldr r2, [sp, #0x0]
	ldr r1, _020CFD90 ; =0x04000188
	str r2, [r1, #0x0]
	bl OS_RestoreInterrupts
_020CFD7C:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr
_020CFD8C: .word 0x04000184
_020CFD90: .word 0x04000188

	arm_func_start PXI_IsCallbackReady
PXI_IsCallbackReady:
	ldr r2, _020CFDB8 ; =0x027FFC00
	mov r3, #0x1
	add r1, r2, r1, lsl #0x2
	mov r2, r3, lsl r0
	ldr r0, [r1, #0x388]
	ands r0, r2, r0
	moveq r3, #0x0
	mov r0, r3
	bx lr
	.balign 4
_020CFDB8: .word 0x027FFC00

	arm_func_start PXI_SetFifoRecvCallback
PXI_SetFifoRecvCallback: ; 0x020CFDBC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	mov r5, r1
	bl OS_DisableInterrupts
	ldr r1, _020CFE20 ; =0x021D5368
	cmp r5, #0x0
	str r5, [r1, r4, lsl #0x2]
	beq _020CFDF8
	ldr r3, _020CFE24 ; =0x027FFC00
	mov r1, #0x1
	ldr r2, [r3, #0x388]
	orr r1, r2, r1, lsl r4
	str r1, [r3, #0x388]
	b _020CFE10
_020CFDF8:
	ldr r3, _020CFE24 ; =0x027FFC00
	mov r1, #0x1
	mvn r1, r1, lsl r4
	ldr r2, [r3, #0x388]
	and r1, r2, r1
	str r1, [r3, #0x388]
_020CFE10:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CFE20: .word 0x021D5368
_020CFE24: .word 0x027FFC00

	arm_func_start PXI_InitFifo
PXI_InitFifo: ; 0x020CFE28
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r1, _020CFF18 ; =0x021D5364
	mov r4, r0
	ldrh r0, [r1, #0x0]
	cmp r0, #0x0
	bne _020CFF04
	mov r2, #0x1
	ldr r0, _020CFF1C ; =0x027FFC00
	strh r2, [r1, #0x0]
	mov r2, #0x0
	str r2, [r0, #0x388]
	ldr r0, _020CFF20 ; =0x021D5368
	mov r1, r2
_020CFE64:
	str r1, [r0, r2, lsl #0x2]
	add r2, r2, #0x1
	cmp r2, #0x20
	blt _020CFE64
	ldr r2, _020CFF24 ; =0x0000C408
	ldr r1, _020CFF28 ; =0x04000184
	mov r0, #0x40000
	strh r2, [r1, #0x0]
	bl OS_ResetRequestIrqMask
	ldr r1, _020CFF2C ; =PXIi_HandlerRecvFifoNotEmpty
	mov r0, #0x40000
	bl OS_SetIrqFunction
	mov r0, #0x40000
	bl OS_EnableIrqMask
	mov r12, #0x0
	ldr r3, _020CFF30 ; =0x04000180
	mov r1, r12
	mov r2, #0x3e8
_020CFEAC:
	ldrh r0, [r3, #0x0]
	ands lr, r0, #0xf
	mov r0, lr, lsl #0x8
	strh r0, [r3, #0x0]
	bne _020CFEC8
	cmp r12, #0x4
	bgt _020CFF04
_020CFEC8:
	ldrh r0, [r3, #0x0]
	mov r5, r2
	and r0, r0, #0xf
	cmp r0, lr
	bne _020CFEFC
_020CFEDC:
	cmp r5, #0x0
	movle r12, r1
	ble _020CFEFC
	ldrh r0, [r3, #0x0]
	sub r5, r5, #0x1
	and r0, r0, #0xf
	cmp r0, lr
	beq _020CFEDC
_020CFEFC:
	add r12, r12, #0x1
	b _020CFEAC
_020CFF04:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020CFF18: .word 0x021D5364
_020CFF1C: .word 0x027FFC00
_020CFF20: .word 0x021D5368
_020CFF24: .word 0x0000C408
_020CFF28: .word 0x04000184
_020CFF2C: .word PXIi_HandlerRecvFifoNotEmpty
_020CFF30: .word 0x04000180

	arm_func_start FSi_TranslateCommand
FSi_TranslateCommand:
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	ldr r0, [r8, #0xc]
	mov r7, r1
	mov r1, #0x1
	ldr r5, [r8, #0x8]
	mov r4, r1, lsl r7
	ands r0, r0, #0x4
	moveq r1, #0x0
	cmp r1, #0x0
	ldrne r0, [r5, #0x1c]
	orrne r0, r0, #0x200
	strne r0, [r5, #0x1c]
	ldreq r0, [r5, #0x1c]
	orreq r0, r0, #0x100
	streq r0, [r5, #0x1c]
	ldr r0, [r5, #0x58]
	ands r0, r0, r4
	beq _020CFFE4
	ldr r2, [r5, #0x54]
	mov r0, r8
	mov r1, r7
	blx r2
	mov r6, r0
	cmp r6, #0x8
	addls pc, pc, r6, lsl #0x2
	b _020CFFE8
_020CFFA0:
	b _020CFFC4
	b _020CFFC4
	b _020CFFE8
	b _020CFFE8
	b _020CFFC4
	b _020CFFE8
	b _020CFFE8
	b _020CFFE8
	b _020CFFCC
_020CFFC4:
	str r6, [r8, #0x14]
	b _020CFFE8
_020CFFCC:
	ldr r1, [r5, #0x58]
	mvn r0, r4
	and r0, r1, r0
	str r0, [r5, #0x58]
	mov r6, #0x7
	b _020CFFE8
_020CFFE4:
	mov r6, #0x7
_020CFFE8:
	cmp r6, #0x7
	bne _020D0004
	ldr r1, _020D00AC ; =0x02103F80
	mov r0, r8
	ldr r1, [r1, r7, lsl #0x2]
	blx r1
	mov r6, r0
_020D0004:
	cmp r6, #0x6
	bne _020D0060
	ldr r0, [r8, #0xc]
	ands r0, r0, #0x4
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020D00A0
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x1c]
	mov r4, r0
	ands r0, r1, #0x200
	beq _020D0050
	add r6, r5, #0xc
_020D003C:
	mov r0, r6
	bl OS_SleepThread
	ldr r0, [r5, #0x1c]
	ands r0, r0, #0x200
	bne _020D003C
_020D0050:
	mov r0, r4
	ldr r6, [r8, #0x14]
	bl OS_RestoreInterrupts
	b _020D00A0
_020D0060:
	ldr r0, [r8, #0xc]
	ands r0, r0, #0x4
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	ldrne r0, [r5, #0x1c]
	bicne r0, r0, #0x200
	strne r0, [r5, #0x1c]
	strne r6, [r8, #0x14]
	bne _020D00A0
	ldr r1, [r5, #0x1c]
	mov r0, r8
	bic r2, r1, #0x100
	mov r1, r6
	str r2, [r5, #0x1c]
	bl FSi_ReleaseCommand
_020D00A0:
	mov r0, r6
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020D00AC: .word 0x02103F80

	arm_func_start FSi_ReleaseCommand
FSi_ReleaseCommand:
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x0]
	mov r4, r0
	ldr r0, [r6, #0x4]
	cmp r1, #0x0
	strne r0, [r1, #0x4]
	cmp r0, #0x0
	strne r1, [r0, #0x0]
	mov r0, #0x0
	str r0, [r6, #0x0]
	ldr r1, [r6, #0x0]
	add r0, r6, #0x18
	str r1, [r6, #0x4]
	ldr r1, [r6, #0xc]
	bic r1, r1, #0x4f
	str r1, [r6, #0xc]
	str r5, [r6, #0x14]
	bl OS_WakeupThread
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FSi_CloseFileCommand
FSi_CloseFileCommand: ; 0x020D0114
	mov r0, #0x0
	bx lr

	arm_func_start FSi_OpenFileDirectCommand
FSi_OpenFileDirectCommand: ; 0x020D011C
	ldr r1, [r0, #0x30]
	str r1, [r0, #0x24]
	ldr r1, [r0, #0x30]
	str r1, [r0, #0x2c]
	ldr r1, [r0, #0x34]
	str r1, [r0, #0x28]
	ldr r1, [r0, #0x38]
	str r1, [r0, #0x20]
	mov r0, #0x0
	bx lr

	arm_func_start FSi_OpenFileFastCommand
FSi_OpenFileFastCommand: ; 0x020D0144
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x14
	mov r5, r0
	ldr r1, [r5, #0x8]
	ldr r4, [r5, #0x34]
	ldr r0, [r1, #0x30]
	mov r2, r4, lsl #0x3
	cmp r2, r0
	addcs sp, sp, #0x14
	movcs r0, #0x1
	ldmcsia sp!, {r4-r5,lr}
	bxcs lr
	str r1, [sp, #0x8]
	ldr r1, [r1, #0x2c]
	add r0, sp, #0x8
	add r3, r1, r2
	add r1, sp, #0x0
	mov r2, #0x8
	str r3, [sp, #0xc]
	bl FSi_ReadTable
_020D0194:
	cmp r0, #0
	addne sp, sp, #0x14
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r1, [sp]
	mov r0, r5
	str r1, [r5, #0x30]
	ldr r2, [sp, #0x4]
	mov r1, #7
	str r2, [r5, #0x34]
	str r4, [r5, #0x38]
	bl FSi_TranslateCommand
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FSi_GetPathCommand
FSi_GetPathCommand: ; 0x020D01D0
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xe4
	mov r4, r0
	ldr r1, [r4, #0x8]
	add r0, sp, #0x98
	add r11, r4, #0x30
	str r1, [sp, #0x0]
	bl FS_InitFile
	ldr r0, [r4, #0x8]
	str r0, [sp, #0xa0]
	ldr r0, [r4, #0xc]
	ands r0, r0, #0x20
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	ldrneh r5, [r4, #0x24]
	movne r4, #0x10000
	bne _020D02BC
	ldrh r0, [r11, #0x8]
	ldr r4, [r4, #0x20]
	cmp r0, #0x0
	ldrneh r5, [r11, #0xa]
	bne _020D02BC
	mov r10, #0x0
	mov r9, r10
	mov r5, #0x10000
	add r8, sp, #0x98
	mov r6, #0x3
	mov r7, #0x1
_020D0244:
	mov r0, r8
	mov r1, r10
	bl FSi_SeekDirDirect
	add r2, sp, #0x4
	cmp r10, #0x0
	mov r0, r8
	mov r1, r6
	ldreq r9, [sp, #0xc4]
	str r2, [sp, #0xc8]
	str r7, [sp, #0xcc]
	bl FSi_TranslateCommand
_020D0270:
	cmp r0, #0x0
	bne _020D02A8
_020D0278:
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	bne _020D0294
	ldr r0, [sp, #0x8]
	cmp r0, r4
	ldreqh r5, [sp, #0xbc]
	beq _020D02A8
_020D0294:
	mov r0, r8
	mov r1, r6
	bl FSi_TranslateCommand
	cmp r0, #0x0
	beq _020D0278
_020D02A8:
	cmp r5, #0x10000
	bne _020D02BC
	add sl, sl, #0x1
	cmp sl, r9
	bcc _020D0244
_020D02BC:
	cmp r5, #0x10000
	moveq r0, #0x0
	streqh r0, [r11, #0x8]
	addeq sp, sp, #0xe4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldrh r0, [r11, #0x8]
	cmp r0, #0x0
	bne _020D03B8
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0xff
	addls r9, r1, #0x1
	bls _020D0308
	cmp r0, #0xff00
	addls r9, r1, #0x2
	addhi r9, r1, #0x3
_020D0308:
	cmp r4, #0x10000
	ldrne r0, [sp, #0x14]
	add r9, r9, #0x2
	addne r9, r9, r0
	mov r10, r5
	cmp r5, #0x0
	beq _020D03AC
	add r0, sp, #0x98
	mov r1, r5
	bl FSi_SeekDirDirect
	add r8, sp, #0x98
	mov r6, #0x3
	mov r7, #0x1
_020D033C:
	ldr r1, [sp, #0xc4]
	mov r0, r8
	bl FSi_SeekDirDirect
	add r2, sp, #0x4
	mov r0, r8
	mov r1, r6
	str r2, [sp, #0xc8]
	str r7, [sp, #0xcc]
	bl FSi_TranslateCommand
_020D0360:
	cmp r0, #0x0
	bne _020D03A0
_020D0368:
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	beq _020D038C
	ldrh r0, [sp, #0x8]
	cmp r0, sl
	ldreq r0, [sp, #0x14]
	addeq r0, r0, #0x1
	addeq r9, r9, r0
	beq _020D03A0
_020D038C:
	mov r0, r8
	mov r1, r6
	bl FSi_TranslateCommand
	cmp r0, #0x0
	beq _020D0368
_020D03A0:
	ldrh sl, [sp, #0xbc]
	cmp sl, #0x0
	bne _020D033C
_020D03AC:
	add r0, r9, #0x1
	strh r0, [r11, #0x8]
	strh r5, [r11, #0xa]
_020D03B8:
	ldr r7, [r11, #0x0]
	cmp r7, #0x0
	addeq sp, sp, #0xe4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldrh r6, [r11, #0x8]
	ldr r0, [r11, #0x4]
	cmp r0, r6
	addcc sp, sp, #0xe4
	movcc r0, #0x1
	ldmccia sp!, {r4-r11,lr}
	bxcc lr
	ldr r0, [sp, #0x0]
	mov r9, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0xff
	movls r8, #0x1
	bls _020D0410
	cmp r0, #0xff00
	movls r8, #0x2
	movhi r8, #0x3
_020D0410:
	ldr r0, [sp, #0x0]
	mov r1, r7
	mov r2, r8
	bl MI_CpuCopy8
	add r1, r9, r8
	ldr r0, _020D058C ; =0x0210682C
	add r1, r7, r1
	mov r2, #0x2
	bl MI_CpuCopy8
	add r0, sp, #0x98
	mov r1, r5
	bl FSi_SeekDirDirect
	cmp r4, #0x10000
	beq _020D04C4
	add r3, sp, #0x4
	mov r2, #0x0
	add r0, sp, #0x98
	mov r1, #0x3
	str r3, [sp, #0xc8]
	str r2, [sp, #0xcc]
	bl FSi_TranslateCommand
_020D0464:
	cmp r0, #0x0
	bne _020D04A0
	add r9, sp, #0x98
	mov r8, #0x3
_020D0474:
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	bne _020D048C
	ldr r0, [sp, #0x8]
	cmp r0, r4
	beq _020D04A0
_020D048C:
	mov r0, r9
	mov r1, r8
	bl FSi_TranslateCommand
	cmp r0, #0x0
	beq _020D0474
_020D04A0:
	ldr r0, [sp, #0x14]
	add r1, r7, r6
	add r4, r0, #0x1
	add r0, sp, #0x18
	mov r2, r4
	sub r1, r1, r4
	bl MI_CpuCopy8
	sub r6, r6, r4
	b _020D04D4
_020D04C4:
	add r0, r7, r6
	mov r1, #0x0
	strb r1, [r0, #-0x1]
	sub r6, r6, #0x1
_020D04D4:
	cmp r5, #0x0
	beq _020D057C
	add r10, sp, #0x98
	add r11, sp, #0x4
	mov r4, #0x3
	mov r9, #0x0
	mov r8, #0x2f
_020D04F0:
	ldr r1, [sp, #0xc4]
	mov r0, r10
	bl FSi_SeekDirDirect
	add r2, r7, r6
	mov r0, r10
	mov r1, r4
	str r11, [sp, #0xc8]
	str r9, [sp, #0xcc]
	strb r8, [r2, #-0x1]
	sub r6, r6, #0x1
	bl FSi_TranslateCommand
_020D051C:
	cmp r0, #0x0
	bne _020D0570
_020D0524:
	ldr r0, [sp, #0x10]
	cmp r0, #0x0
	beq _020D055C
	ldrh r0, [sp, #0x8]
	cmp r0, r5
	bne _020D055C
	ldr r5, [sp, #0x14]
	add r1, r7, r6
	add r0, sp, #0x18
	mov r2, r5
	sub r1, r1, r5
	bl MI_CpuCopy8
	sub r6, r6, r5
	b _020D0570
_020D055C:
	mov r0, sl
	mov r1, r4
	bl FSi_TranslateCommand
	cmp r0, #0x0
	beq _020D0524
_020D0570:
	ldrh r5, [sp, #0xbc]
	cmp r5, #0x0
	bne _020D04F0
_020D057C:
	mov r0, #0x0
	add sp, sp, #0xe4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020D058C: .word 0x0210682C

	arm_func_start FSi_FindPathCommand
FSi_FindPathCommand: ; 0x020D0590
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x9c
	mov r10, r0
	ldr r2, [r10, #0x40]
	ldr r9, [r10, #0x3c]
	mov r1, #0x2
	str r2, [sp, #0x0]
	bl FSi_TranslateCommand
	ldrb r1, [r9, #0x0]
	cmp r1, #0x0
	beq _020D0780
	mov r0, #0x2
	add r11, sp, #0x1c
	mov r4, #0x3
	mov r5, #0x1
	mov r6, #0x0
	str r0, [sp, #0x4]
_020D05D4:
	mov r7, r6
	b _020D05E0
_020D05DC:
	add r7, r7, #0x1
_020D05E0:
	ldrb r8, [r9, r7]
	mov r0, r6
	cmp r8, #0x0
	beq _020D0600
	cmp r8, #0x2f
	beq _020D0600
	cmp r8, #0x5c
	movne r0, r5
_020D0600:
	cmp r0, #0x0
	bne _020D05DC
	cmp r8, #0x0
	bne _020D061C
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _020D0620
_020D061C:
	mov r8, r5
_020D0620:
	cmp r7, #0x0
	addeq sp, sp, #0x9c
	moveq r0, #0x1
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	cmp r1, #0x2e
	bne _020D068C
	cmp r7, #0x1
	addeq r9, r9, #0x1
	beq _020D0764
	ldrb r0, [r9, #0x1]
	cmp r7, #0x2
	moveq r1, r5
	movne r1, r6
	cmp r0, #0x2e
	moveq r0, r5
	movne r0, r6
	ands r0, r1, r0
	beq _020D068C
	ldrh r0, [r10, #0x24]
	cmp r0, #0x0
	beq _020D0684
	ldr r1, [r10, #0x2c]
	mov r0, r10
	bl FSi_SeekDirDirect
_020D0684:
	add r9, r9, #0x2
	b _020D0764
_020D068C:
	cmp r7, #0x7f
	addgt sp, sp, #0x9c
	movgt r0, #0x1
	ldmgtia sp!, {r4-r11,lr}
	bxgt lr
	add r0, sp, #0x8
	str r0, [r10, #0x30]
	str r6, [r10, #0x34]
_020D06AC:
	mov r0, r10
	mov r1, r4
	bl FSi_TranslateCommand
_020D06B8:
	cmp r0, #0x0
	addne sp, sp, #0x9c
	movne r0, #0x1
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	ldr r0, [sp, #0x14]
	cmp r8, r0
	bne _020D06AC
	ldr r0, [sp, #0x18]
	cmp r7, r0
	bne _020D06AC
	mov r0, r9
	mov r1, fp
	mov r2, r7
	bl FSi_StrNICmp
	cmp r0, #0x0
	bne _020D06AC
	cmp r8, #0x0
	beq _020D0728
	add r0, sp, #0x8
	add r3, sl, #0x30
	ldmia r0, {r0, r1, r2}
	stmia r3, {r0, r1, r2}
	ldr r1, [sp, #0x4]
	mov r0, sl
	add r9, r9, r7
	bl FSi_TranslateCommand
	b _020D0764
_020D0728:
	ldr r0, [sp]
	cmp r0, #0x0
	addne sp, sp, #0x9c
	movne r0, #0x1
	ldmneia sp!, {r4-r11,lr}
	bxne lr
	ldr r3, [sl, #0x44]
	ldr r2, [sp, #0x8]
	ldr r1, [sp, #0xC]
	add sp, sp, #0x9c
	str r2, [r3]
	str r1, [r3, #0x4]
	mov r0, #0x0
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D0764:
	ldrb r0, [r9, #0x0]
	cmp r0, #0x0
	movne r0, r5
	moveq r0, r6
	ldrb r1, [r9, r0]!
	cmp r1, #0x0
	bne _020D05D4
_020D0780:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	moveq r0, #0x1
	addne r0, r10, #0x20
	ldrne r3, [r10, #0x44]
	ldmneia r0, {r0-r2}
	stmneia r3, {r0-r2}
	movne r0, #0x0
	add sp, sp, #0x9c
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start FSi_ReadDirCommand
FSi_ReadDirCommand: ; 0x020D07AC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r5, r0
	ldr r4, [r5, #0x30]
	ldr r1, [r5, #0x8]
	add r0, sp, #0x4
	str r1, [sp, #0x4]
	ldr r3, [r5, #0x28]
	add r1, sp, #0x0
	mov r2, #0x1
	str r3, [sp, #0x8]
	bl FSi_ReadTable
_020D07DC:
	cmp r0, #0x0
	addne sp, sp, #0xC
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldrb r1, [sp]
	and r2, r1, #0x7F
	mov r1, r1, asr #0x7
	str r2, [r4, #0x10]
	and r1, r1, #0x1
	str r1, [r4, #0xC]
	ldr r2, [r4, #0x10]
	cmp r2, #0x0
	addeq sp, sp, #0xC
	moveq r0, #0x1
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, [r5, #0x34]
	cmp r1, #0x0
	bne _020D0858
	add r0, sp, #0x4
	add r1, r4, #0x14
	bl FSi_ReadTable
	cmp r0, #0x0
	addne sp, sp, #0xC
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r1, [r4, #0x10]
	mov r2, #0x0
	add r1, r4, r1
	strb r2, [r1, #0x14]
	b _020D0864
_020D0858:
	ldr r1, [sp, #0x8]
	add r1, r1, r2
	str r1, [sp, #0x8]
_020D0864:
	ldr r1, [r4, #0xC]
	cmp r1, #0x0
	beq _020D08B8
	add r0, sp, #0x4
	add r1, sp, #0x2
	mov r2, #0x2
	bl FSi_ReadTable
	cmp r0, #0x0
	addne sp, sp, #0xC
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r2, [r5, #0x8]
	ldr r1, _020D08E8
	str r2, [r4]
	ldrh r3, [sp, #0x2]
	mov r2, #0x0
	and r1, r3, r1
	strh r1, [r4, #0x4]
	strh r2, [r4, #0x6]
	str r2, [r4, #0x8]
	b _020D08D4
_020D08B8:
	ldr r1, [r5, #0x8]
	str r1, [r4]
	ldrh r1, [r5, #0x26]
	str r1, [r4, #0x4]
	ldrh r1, [r5, #0x26]
	add r1, r1, #0x1
	strh r1, [r5, #0x26]
_020D08D4:
	ldr r1, [sp, #0x8]
	str r1, [r5, #0x28]
	add sp, sp, #0xC
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D08E8: .word 0x00000FFF

	arm_func_start FSi_SeekDirCommand
FSi_SeekDirCommand: ; 0x020D08EC
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x10
	mov r6, r0
	ldr r5, [r6, #0x8]
	add r4, r6, #0x30
	str r5, [sp, #0x8]
	ldrh r1, [r4, #0x4]
	ldr r2, [r5, #0x34]
	add r0, sp, #0x8
	add r3, r2, r1, lsl #0x3
	add r1, sp, #0x0
	mov r2, #0x8
	str r3, [sp, #0xc]
	bl FSi_ReadTable
	movs r3, r0
	bne _020D0978
	add r12, r6, #0x20
	ldmia r4, {r0-r2}
	stmia r12, {r0-r2}
	ldrh r0, [r4, #0x6]
	cmp r0, #0x0
	bne _020D0968
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	bne _020D0968
	ldrh r0, [sp, #0x4]
	strh r0, [r6, #0x26]
	ldr r1, [r5, #0x34]
	ldr r0, [sp, #0x0]
	add r0, r1, r0
	str r0, [r6, #0x28]
_020D0968:
	ldrh r1, [sp, #0x6]
	ldr r0, _020D0988 ; =0x00000FFF
	and r0, r1, r0
	str r0, [r6, #0x2c]
_020D0978:
	mov r0, r3
	add sp, sp, #0x10
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D0988: .word 0x00000FFF

	arm_func_start FSi_WriteFileCommand
FSi_WriteFileCommand: ; 0x020D098C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x2c]
	ldr r3, [r0, #0x38]
	ldr lr, [r0, #0x8]
	ldr r1, [r0, #0x30]
	add r12, r2, r3
	str r12, [r0, #0x2c]
	ldr r12, [lr, #0x4c]
	mov r0, lr
	blx r12
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FSi_ReadFileCommand
FSi_ReadFileCommand: ; 0x020D09C4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x2c]
	ldr r3, [r0, #0x38]
	ldr lr, [r0, #0x8]
	ldr r1, [r0, #0x30]
	add r12, r2, r3
	str r12, [r0, #0x2c]
	ldr r12, [lr, #0x48]
	mov r0, lr
	blx r12
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FSi_SeekDirDirect
FSi_SeekDirDirect: ; 0x020D09FC
	ldr r3, [r0, #0xc]
	mov r2, #0x0
	orr r3, r3, #0x4
	str r3, [r0, #0xc]
	ldr r3, [r0, #0x8]
	ldr ip, _020D0A2C ; =FSi_TranslateCommand
	str r3, [r0, #0x30]
	str r2, [r0, #0x38]
	strh r2, [r0, #0x36]
	strh r1, [r0, #0x34]
	mov r1, #0x2
	bx r12
	.balign 4
_020D0A2C: .word FSi_TranslateCommand

	arm_func_start FSi_ReadTable
FSi_ReadTable:
	stmdb sp!, {r4-r8,lr}
	mov r7, r0
	ldr r5, [r7, #0x0]
	mov r6, r2
	ldr r2, [r5, #0x1c]
	mov r0, r5
	orr r2, r2, #0x200
	str r2, [r5, #0x1c]
	ldr r2, [r7, #0x4]
	ldr r4, [r5, #0x50]
	mov r3, r6
	blx r4
	cmp r0, #0x0
	beq _020D0A7C
	cmp r0, #0x1
	beq _020D0A7C
	cmp r0, #0x6
	beq _020D0A8C
	b _020D0AC8
_020D0A7C:
	ldr r1, [r5, #0x1c]
	bic r1, r1, #0x200
	str r1, [r5, #0x1c]
	b _020D0AC8
_020D0A8C:
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x1c]
	mov r4, r0
	ands r0, r1, #0x200
	beq _020D0AB8
	add r8, r5, #0xc
_020D0AA4:
	mov r0, r8
	bl OS_SleepThread
	ldr r0, [r5, #0x1c]
	ands r0, r0, #0x200
	bne _020D0AA4
_020D0AB8:
	mov r0, r4
	bl OS_RestoreInterrupts
	ldr r0, [r5, #0x24]
	ldr r0, [r0, #0x14]
_020D0AC8:
	ldr r1, [r7, #0x4]
	add r1, r1, r6
	str r1, [r7, #0x4]
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FSi_StrNICmp
FSi_StrNICmp: ; 0x020D0ADC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r2, #0x0
	mov lr, #0x0
	bls _020D0B30
_020D0AF0:
	ldrb r12, [r0, lr]
	ldrb r3, [r1, lr]
	sub r12, r12, #0x41
	cmp r12, #0x19
	sub r3, r3, #0x41
	addls r12, r12, #0x20
	cmp r3, #0x19
	addls r3, r3, #0x20
	cmp r12, r3
	addne sp, sp, #0x4
	subne r0, r12, r3
	ldmneia sp!, {lr}
	bxne lr
	add lr, lr, #0x1
	cmp lr, r2
	blo _020D0AF0
_020D0B30:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FS_NotifyArchiveAsyncEnd
FS_NotifyArchiveAsyncEnd: ; 0x020D0B40
	stmdb sp!, {r4-r6,lr}
	mov r4, r0
	ldr r0, [r4, #0x1c]
	mov r6, r1
	ands r0, r0, #0x100
	beq _020D0B8C
	ldr r2, [r4, #0x1c]
	ldr r0, [r4, #0x24]
	bic r2, r2, #0x100
	str r2, [r4, #0x1c]
	bl FSi_ReleaseCommand
	mov r0, r4
	bl FSi_NextCommand
_020D0B74:
	cmp r0, #0x0
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	bl FSi_ExecuteAsyncCommand
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D0B8C:
	ldr r5, [r4, #0x24]
	bl OS_DisableInterrupts
	str r6, [r5, #0x14]
	ldr r1, [r4, #0x1c]
	mov r5, r0
	bic r1, r1, #0x200
	add r0, r4, #0xc
	str r1, [r4, #0x1c]
	bl OS_WakeupThread
	mov r0, r5
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FS_SetArchiveProc
FS_SetArchiveProc: ; 0x020D0BC0
	cmp r2, #0x0
	moveq r1, #0x0
	beq _020D0BD4
	cmp r1, #0x0
	moveq r2, #0x0
_020D0BD4:
	str r1, [r0, #0x54]
	str r2, [r0, #0x58]
	bx lr

	arm_func_start FS_ResumeArchive
FS_ResumeArchive:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r4, r0
	mov r6, #0x0
	bl OS_DisableInterrupts
	ldr r1, [r4, #0x1c]
	mov r5, r0
	ands r0, r1, #0x8
	movne r0, #0x1
	moveq r0, r6
	cmp r0, #0x0
	moveq r7, #0x1
	movne r7, #0x0
	cmp r7, #0x0
	bne _020D0C34
	ldr r1, [r4, #0x1c]
	mov r0, r4
	bic r1, r1, #0x8
	str r1, [r4, #0x1c]
	bl FSi_NextCommand
	mov r6, r0
_020D0C34:
	mov r0, r5
	bl OS_RestoreInterrupts
_020D0C3C:
	cmp r6, #0x0
	beq _020D0C4C
	mov r0, r6
	bl FSi_ExecuteAsyncCommand
_020D0C4C:
	mov r0, r7
	add sp, sp, #0x4
	ldmia sp!, {r4-r7, lr}
	bx lr

	arm_func_start FS_SuspendArchive
FS_SuspendArchive: ; 0x020D0C5C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x1c]
	mov r4, r0
	ands r0, r1, #0x8
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	moveq r5, #0x1
	movne r5, #0x0
	cmp r5, #0x0
	beq _020D0CD4
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x10
	beq _020D0CC8
	ldr r0, [r6, #0x1c]
	orr r0, r0, #0x40
	str r0, [r6, #0x1c]
	add r7, r6, #0x14
_020D0CB0:
	mov r0, r7
	bl OS_SleepThread
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x40
	bne _020D0CB0
	b _020D0CD4
_020D0CC8:
	ldr r0, [r6, #0x1c]
	orr r0, r0, #0x8
	str r0, [r6, #0x1c]
_020D0CD4:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FS_UnloadArchiveTables
FS_UnloadArchiveTables: ; 0x020D0CEC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	ldr r0, [r5, #0x1c]
	mov r4, #0x0
	ands r0, r0, #0x2
	movne r0, #0x1
	moveq r0, r4
	cmp r0, #0x0
	beq _020D0D74
	mov r0, r5
	bl FS_SuspendArchive
	ldr r1, [r5, #0x1c]
	ands r1, r1, #0x4
	movne r1, #0x1
	moveq r1, #0x0
	cmp r1, #0x0
	beq _020D0D64
	ldr r2, [r5, #0x1c]
	mov r1, #0x0
	bic r2, r2, #0x4
	str r2, [r5, #0x1c]
	ldr r4, [r5, #0x44]
	str r1, [r5, #0x44]
	ldr r1, [r5, #0x3c]
	str r1, [r5, #0x2c]
	ldr r1, [r5, #0x40]
	str r1, [r5, #0x34]
	ldr r1, [r5, #0x48]
	str r1, [r5, #0x50]
_020D0D64:
	cmp r0, #0x0
	beq _020D0D74
	mov r0, r5
	bl FS_ResumeArchive
_020D0D74:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020D0D84
FUN_020D0D84: ; 0x020D0D84
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4c
	mov r7, r0
	ldr r3, [r7, #0x30]
	ldr r0, [r7, #0x38]
	mov r6, r1
	add r0, r3, r0
	add r0, r0, #0x20
	add r0, r0, #0x1f
	bic r5, r0, #0x1f
	cmp r5, r2
	bhi _020D0E9C
	add r1, r6, #0x1f
	add r0, sp, #0x4
	bic r4, r1, #0x1f
	bl FS_InitFile
	ldr r2, [r7, #0x2c]
	mvn r0, #0x0
	str r0, [sp, #0x0]
	ldr r3, [r7, #0x30]
	add r0, sp, #0x4
	mov r1, r7
	add r3, r2, r3
	bl FS_OpenFileDirect
_020D0DE4:
	cmp r0, #0x0
	beq _020D0E1C
	ldr r2, [r7, #0x30]
	add r0, sp, #0x4
	mov r1, r4
	bl FS_ReadFile
	cmp r0, #0x0
	bge _020D0E14
	ldr r2, [r7, #0x30]
	mov r0, r4
	mov r1, #0x0
	bl MI_CpuFill8
_020D0E14:
	add r0, sp, #0x4
	bl FS_CloseFile
_020D0E1C:
	str r4, [r7, #0x2C]
	ldr ip, [r7, #0x30]
	ldr r2, [r7, #0x34]
	mvn r0, #0x0
	str r0, [sp]
	ldr r3, [r7, #0x38]
	add r0, sp, #0x4
	mov r1, r7
	add r3, r2, r3
	add r4, r4, ip
	bl FS_OpenFileDirect
	cmp r0, #0x0
	beq _020D0E80
	ldr r2, [r7, #0x38]
	add r0, sp, #0x4
	mov r1, r4
	bl FS_ReadFile
	cmp r0, #0x0
	bge _020D0E78
	ldr r2, [r7, #0x38]
	mov r0, r4
	mov r1, #0x0
	bl MI_CpuFill8
_020D0E78:
	add r0, sp, #0x4
	bl FS_CloseFile
_020D0E80:
	str r4, [r7, #0x34]
	ldr r0, _020D0EAC
	str r6, [r7, #0x44]
	str r0, [r7, #0x50]
	ldr r0, [r7, #0x1C]
	orr r0, r0, #0x4
	str r0, [r7, #0x1C]
_020D0E9C:
	mov r0, r5
	add sp, sp, #0x4C
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D0EAC:
	.word FSi_ReadMemoryCore 

	arm_func_start FUN_020D0EB0
FUN_020D0EB0: ; 0x020D0EB0
	stmdb sp!, {r4-r8,lr}
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, [r5, #0x1c]
	mov r4, r0
	ands r0, r1, #0x2
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020D0F64
	mov r0, r5
	ldr r1, [r5, #0x1c]
	bl FS_SuspendArchive
	ldr r1, [r5, #0x1c]
	mov r7, r0
	orr r0, r1, #0x80
	str r0, [r5, #0x1c]
	ldr r0, [r5, #0x24]
	cmp r0, #0x0
	beq _020D0F1C
	mov r6, #0x3
_020D0F04:
	ldr r8, [r0, #0x4]
	mov r1, r6
	bl FSi_ReleaseCommand
	mov r0, r8
	cmp r8, #0x0
	bne _020D0F04
_020D0F1C:
	mov r0, #0x0
	str r0, [r5, #0x24]
	cmp r7, #0x0
	beq _020D0F34
	mov r0, r5
	bl FS_ResumeArchive
_020D0F34:
	mov r0, #0x0
	str r0, [r5, #0x28]
	str r0, [r5, #0x2c]
	str r0, [r5, #0x30]
	str r0, [r5, #0x34]
	str r0, [r5, #0x38]
	str r0, [r5, #0x40]
	ldr r0, [r5, #0x40]
	str r0, [r5, #0x3c]
	ldr r0, [r5, #0x1c]
	bic r0, r0, #0xa2
	str r0, [r5, #0x1c]
_020D0F64:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FS_LoadArchive
FS_LoadArchive: ; 0x020D0F78
	str r1, [r0, #0x28]
	str r3, [r0, #0x30]
	str r2, [r0, #0x3c]
	ldr r1, [r0, #0x3c]
	ldr r2, [sp, #0x4]
	str r1, [r0, #0x2c]
	str r2, [r0, #0x38]
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x8]
	str r1, [r0, #0x40]
	ldr r1, [r0, #0x40]
	cmp r2, #0x0
	str r1, [r0, #0x34]
	ldreq r2, _020D0FE8 ; =FSi_ReadMemCallback
	ldr r1, [sp, #0xc]
	str r2, [r0, #0x48]
	cmp r1, #0x0
	ldreq r1, _020D0FEC ; =FSi_WriteMemCallback
	str r1, [r0, #0x4c]
	ldr r2, [r0, #0x48]
	mov r1, #0x0
	str r2, [r0, #0x50]
	str r1, [r0, #0x44]
	ldr r1, [r0, #0x1c]
	orr r1, r1, #0x2
	str r1, [r0, #0x1c]
	mov r0, #0x1
	bx lr
	.balign 4
_020D0FE8: .word FSi_ReadMemCallback
_020D0FEC: .word FSi_WriteMemCallback

	arm_func_start FUN_020D0FF0
FUN_020D0FF0: ; 0x020D0FF0
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	bl OS_DisableInterrupts
	ldr r2, [r4, #0x4]
	mov r3, #0x0
	cmp r2, #0x0
	ldrne r1, [r4, #0x8]
	strne r1, [r2, #0x8]
	ldr r2, [r4, #0x8]
	cmp r2, #0x0
	ldrne r1, [r4, #0x4]
	strne r1, [r2, #0x4]
	str r3, [r4, #0x0]
	str r3, [r4, #0x8]
	ldr r1, [r4, #0x8]
	ldr r2, _020D1080 ; =0x021D53EC
	str r1, [r4, #0x4]
	ldr r1, [r4, #0x1c]
	bic r1, r1, #0x1
	str r1, [r4, #0x1c]
	ldr r1, [r2, #0x0]
	cmp r1, r4
	bne _020D1074
	ldr r1, _020D1084 ; =0x021D53E8
	str r3, [r2, #0x8]
	ldr r1, [r1, #0x0]
	strh r3, [r2, #0x6]
	str r1, [r2, #0x0]
	strh r3, [r2, #0x4]
_020D1074:
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D1080: .word 0x021D53EC
_020D1084: .word 0x021D53E8

	arm_func_start FS_RegisterArchiveName
FS_RegisterArchiveName: ; 0x020D1088
	stmdb sp!, {r4-r8,lr}
	mov r6, r1
	mov r5, r2
	mov r7, r0
	mov r8, #0x0
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, r6
	mov r1, r5
	bl FS_FindArchive
_020D10B0:
	cmp r0, #0x0
	bne _020D112C
	ldr r1, _020D1140
	ldr r2, [r1]
	cmp r2, #0x0
	bne _020D10E8
	ldr r0, _020D1144
	mov r2, r8
	str r7, [r1]
	str r7, [r0]
	str r2, [r0, #0x8]
	strh r2, [r0, #0x6]
	strh r2, [r0, #0x4]
	b _020D110C
_020D10E8:
	ldr r0, [r2, #0x4]
	cmp r0, #0x0
	beq _020D1104
_020D10F4:
	mov r2, r0
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	bne _020D10F4
_020D1104:
	str r7, [r2, #0x4]
	str r2, [r7, #0x8]
_020D110C:
	mov r0, r6
	mov r1, r5
	bl FSi_GetPackedName
	str r0, [r7]
	ldr r0, [r7, #0x1C]
	mov r8, #0x1
	orr r0, r0, #0x1
	str r0, [r7, #0x1C]
_020D112C:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020D1140: .word 0x021D53E8
_020D1144: .word 0x021D53EC

	arm_func_start FS_FindArchive
FS_FindArchive:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl FSi_GetPackedName
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020D1194 ; =0x021D53E8
	ldr r4, [r1, #0x0]
	b _020D116C
_020D1168:
	ldr r4, [r4, #0x4]
_020D116C:
	cmp r4, #0x0
	beq _020D1180
	ldr r1, [r4, #0x0]
	cmp r1, r5
	bne _020D1168
_020D1180:
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D1194: .word 0x021D53E8

	arm_func_start FS_InitArchive
FS_InitArchive: ; 0x020D1198
	stmdb sp!, {r4,lr}
	mov r1, #0x0
	mov r2, #0x5c
	mov r4, r0
	bl MI_CpuFill8
	mov r1, #0x0
	str r1, [r4, #0x10]
	ldr r0, [r4, #0x10]
	str r0, [r4, #0xc]
	str r1, [r4, #0x18]
	ldr r0, [r4, #0x18]
	str r0, [r4, #0x14]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FSi_SendCommand
FSi_SendCommand:
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r6, [r7, #0x8]
	mov r2, #0x1
	str r1, [r7, #0x10]
	mov r0, #0x2
	str r0, [r7, #0x14]
	ldr r0, [r7, #0xc]
	mov r5, r2, lsl r1
	orr r0, r0, #0x1
	str r0, [r7, #0xc]
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x1c]
	mov r4, r0
	ands r0, r1, #0x80
	beq _020D1238
	mov r0, r7
	mov r1, #0x3
	bl FSi_ReleaseCommand
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D1238:
	ands r0, r5, #0x1fc
	ldrne r0, [r7, #0xc]
	add r2, r6, #0x20
	orrne r0, r0, #0x4
	strne r0, [r7, #0xc]
	ldr r1, [r7, #0x0]
	ldr r0, [r7, #0x4]
	cmp r1, #0x0
	strne r0, [r1, #0x4]
	cmp r0, #0x0
	strne r1, [r0, #0x0]
	ldr r0, [r2, #0x4]
	cmp r0, #0x0
	beq _020D1280
_020D1270:
	mov r2, r0
	ldr r0, [r0, #0x4]
	cmp r0, #0x0
	bne _020D1270
_020D1280:
	str r7, [r2, #0x4]
	str r2, [r7, #0x0]
	mov r1, #0x0
	str r1, [r7, #0x4]
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x8
	movne r1, #0x1
	cmp r1, #0x0
	bne _020D132C
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x10
	bne _020D132C
	ldr r1, [r6, #0x1c]
	mov r0, r4
	orr r1, r1, #0x10
	str r1, [r6, #0x1c]
	bl OS_RestoreInterrupts
	ldr r0, [r6, #0x58]
	ands r0, r0, #0x200
	beq _020D12E0
	ldr r2, [r6, #0x54]
	mov r0, r7
	mov r1, #0x9
	blx r2
_020D12E0:
	bl OS_DisableInterrupts
	ldr r1, [r7, #0xc]
	orr r1, r1, #0x40
	str r1, [r7, #0xc]
	ldr r1, [r7, #0xc]
	ands r1, r1, #0x4
	movne r1, #0x1
	moveq r1, #0x0
	cmp r1, #0x0
	bne _020D1324
	bl OS_RestoreInterrupts
	mov r0, r7
	bl FSi_ExecuteAsyncCommand
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D1324:
	bl OS_RestoreInterrupts
	b _020D1378
_020D132C:
	ldr r0, [r7, #0xc]
	ands r0, r0, #0x4
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	bne _020D135C
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D135C:
	add r0, r7, #0x18
	bl OS_SleepThread
	ldr r0, [r7, #0xc]
	ands r0, r0, #0x40
	beq _020D135C
	mov r0, r4
	bl OS_RestoreInterrupts
_020D1378:
	mov r0, r7
	bl FSi_ExecuteSyncCommand
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FSi_ExecuteSyncCommand
FSi_ExecuteSyncCommand: ; 0x020D138C
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0x10]
	bl FSi_TranslateCommand
	mov r1, r0
	mov r0, r4
	bl FSi_ReleaseCommand
	ldr r0, [r4, #0x8]
	bl FSi_NextCommand
_020D13B0:
	cmp r0, #0x0
	beq _020D13BC
	bl FSi_ExecuteAsyncCommand
_020D13BC:
	ldr r0, [r4, #0x14]
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FSi_ExecuteAsyncCommand
FSi_ExecuteAsyncCommand: ; 0x020D13D4
	stmdb sp!, {r4-r8,lr}
	movs r6, r0
	ldr r5, [r6, #0x8]
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r7, #0x0
	mov r8, #0x1
_020D13F0:
	bl OS_DisableInterrupts
	ldr r1, [r6, #0xc]
	mov r4, r0
	orr r0, r1, #0x40
	str r0, [r6, #0xc]
	ldr r0, [r6, #0xc]
	ands r0, r0, #0x4
	movne r0, r8
	moveq r0, r7
	cmp r0, #0x0
	beq _020D1434
	add r0, r6, #0x18
	bl OS_WakeupThread
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r8,lr}
	bx lr
_020D1434:
	ldr r1, [r6, #0xc]
	mov r0, r4
	orr r1, r1, #0x8
	str r1, [r6, #0xc]
	bl OS_RestoreInterrupts
	ldr r1, [r6, #0x10]
	mov r0, r6
	bl FSi_TranslateCommand
	cmp r0, #0x6
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r0, r5
	bl FSi_NextCommand
	movs r6, r0
	bne _020D13F0
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start FSi_NextCommand
FSi_NextCommand:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4c
	mov r6, r0
	bl OS_DisableInterrupts
	ldr r1, [r6, #0x1c]
	mov r5, r0
	ands r0, r1, #0x20
	beq _020D1500
	ldr r0, [r6, #0x1c]
	bic r0, r0, #0x20
	str r0, [r6, #0x1c]
	ldr r0, [r6, #0x24]
	cmp r0, #0x0
	beq _020D1500
	mov r8, #0x0
	mov r9, #0x1
	mov r7, #0x3
_020D14BC:
	ldr r1, [r0, #0xc]
	ldr r4, [r0, #0x4]
	ands r1, r1, #0x2
	movne r1, r9
	moveq r1, r8
	cmp r1, #0x0
	beq _020D14F4
	ldr r1, [r6, #0x24]
	cmp r1, r0
	mov r1, r7
	streq r4, [r6, #0x24]
	bl FSi_ReleaseCommand
_020D14EC:
	cmp r4, #0x0
	ldreq r4, [r6, #0x24]
_020D14F4:
	mov r0, r4
	cmp r4, #0x0
	bne _020D14BC
_020D1500:
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x40
	bne _020D15EC
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x8
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	bne _020D15EC
	ldr r4, [r6, #0x24]
	cmp r4, #0x0
	beq _020D15EC
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x10
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	moveq r7, #0x1
	movne r7, #0x0
	cmp r7, #0x0
	ldrne r0, [r6, #0x1c]
	orrne r0, r0, #0x10
	strne r0, [r6, #0x1c]
	mov r0, r5
	bl OS_RestoreInterrupts
_020D1564:
	cmp r7, #0x0
	beq _020D1588
	ldr r0, [r6, #0x58]
	ands r0, r0, #0x200
	beq _020D1588
	ldr r2, [r6, #0x54]
	mov r0, r4
	mov r1, #0x9
	blx r2
_020D1588:
	bl OS_DisableInterrupts
	ldr r1, [r4, #0xC]
	mov r5, r0
	orr r0, r1, #0x40
	str r0, [r4, #0xC]
	ldr r0, [r4, #0xC]
	ands r0, r0, #0x4
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	beq _020D15D4
	add r0, r4, #0x18
	bl OS_WakeupThread
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4c
	mov r0, #0x0
	ldmia sp!, {r4-r9, lr}
	bx lr
_020D15D4:
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4c
	mov r0, r4
	ldmia sp!, {r4-r9, lr}
	bx lr
_020D15EC:
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x10
	beq _020D162C
	ldr r0, [r6, #0x1c]
	bic r0, r0, #0x10
	str r0, [r6, #0x1c]
	ldr r0, [r6, #0x58]
	ands r0, r0, #0x400
	beq _020D162C
	add r0, sp, #0x0
	bl FS_InitFile
	str r6, [sp, #0x8]
	ldr r2, [r6, #0x54]
	add r0, sp, #0x0
	mov r1, #0xa
	blx r2
_020D162C:
	ldr r0, [r6, #0x1c]
	ands r0, r0, #0x40
	beq _020D1658
	ldr r1, [r6, #0x1c]
	add r0, r6, #0x14
	bic r1, r1, #0x40
	str r1, [r6, #0x1c]
	ldr r1, [r6, #0x1c]
	orr r1, r1, #0x8
	str r1, [r6, #0x1c]
	bl OS_WakeupThread
_020D1658:
	mov r0, r5
	bl OS_RestoreInterrupts
_020D1660:
	mov r0, #0x0
	add sp, sp, #0x4c
	ldmia sp!, {r4-r9, lr}
	bx lr

	arm_func_start FSi_ReadMemoryCore
FSi_ReadMemoryCore: ; 0x020D1670
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r0, r2
	mov r2, r3
	bl MI_CpuCopy8
_020D1684:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr

	arm_func_start FSi_WriteMemCallback
FSi_WriteMemCallback: ; 0x020D1694
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r12, [r0, #0x28]
	mov r0, r1
	add r1, r12, r2
	mov r2, r3
	bl MI_CpuCopy8
_020D16B0:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr

	arm_func_start FSi_ReadMemCallback
FSi_ReadMemCallback: ; 0x020D16C0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x28]
	add r0, r0, r2
	mov r2, r3
	bl MI_CpuCopy8
_020D16D8:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr

	arm_func_start FSi_GetPackedName
FSi_GetPackedName: ; 0x020D16E8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0x3
	mov lr, #0x0
	bgt _020D173C
	mov r12, lr
	cmp r1, #0x0
	ble _020D173C
	mov r3, lr
_020D170C:
	ldrb r2, [r0, r12]
	cmp r2, #0x0
	beq _020D173C
	sub r2, r2, #0x41
	cmp r2, #0x19
	addls r2, r2, #0x61
	addhi r2, r2, #0x41
	add r12, r12, #0x1
	orr lr, lr, r2, lsl r3
	cmp r12, r1
	add r3, r3, #0x8
	blt _020D170C
_020D173C:
	mov r0, lr
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FS_ChangeDir
FS_ChangeDir: ; 0x020D174C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x58
	mov r4, r0
	add r0, sp, #0xc
	bl FS_InitFile
	add r0, sp, #0xc
	add r3, sp, #0x0
	mov r1, r4
	mov r2, #0x0
	bl FSi_FindPath
_020D1774:
	cmp r0, #0x0
	moveq r0, #0x0
	addne r0, sp, #0x0
	ldrne r3, _020D179C
	ldmneia r0, {r0, r1, r2}
	stmneia r3, {r0, r1, r2}
	movne r0, #0x1
	add sp, sp, #0x58
	ldmia sp!, {r4, lr}
	bx lr
_020D179C: .word 0x021D53EC

	arm_func_start FS_SeekFile
FS_SeekFile: ; 0x020D17A0
	cmp r2, #0x0
	beq _020D17BC
	cmp r2, #0x1
	beq _020D17C8
	cmp r2, #0x2
	beq _020D17D4
	b _020D17E0
_020D17BC:
	ldr r2, [r0, #0x24]
	add r1, r1, r2
	b _020D17E8
_020D17C8:
	ldr r2, [r0, #0x2c]
	add r1, r1, r2
	b _020D17E8
_020D17D4:
	ldr r2, [r0, #0x28]
	add r1, r1, r2
	b _020D17E8
_020D17E0:
	mov r0, #0x0
	bx lr
_020D17E8:
	ldr r2, [r0, #0x24]
	cmp r1, r2
	movlt r1, r2
	ldr r2, [r0, #0x28]
	cmp r1, r2
	movgt r1, r2
	str r1, [r0, #0x2c]
	mov r0, #0x1
	bx lr

	arm_func_start FS_ReadFile
FS_ReadFile: ; 0x020D180C
	ldr ip, _020D1818 ; =FUN_020D1AAC
	mov r3, #0x0
	bx r12
	.balign 4
_020D1818: .word FUN_020D1AAC

	arm_func_start FS_ReadFileAsync
FS_ReadFileAsync: ; 0x020D181C
	ldr ip, _020D1828 ; =FUN_020D1AAC
	mov r3, #0x1
	bx r12
	.balign 4
_020D1828: .word FUN_020D1AAC

	arm_func_start FS_WaitAsync
FS_WaitAsync: ; 0x020D182C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, #0x0
	bl OS_DisableInterrupts
	ldr r1, [r6, #0xc]
	mov r4, r0
	ands r0, r1, #0x1
	movne r0, #0x1
	moveq r0, r5
	cmp r0, #0x0
	beq _020D18BC
	ldr r0, [r6, #0xc]
	ands r0, r0, #0x44
	moveq r5, #0x1
	movne r5, #0x0
	cmp r5, #0x0
	beq _020D189C
	ldr r0, [r6, #0xc]
	orr r0, r0, #0x4
	str r0, [r6, #0xc]
	add r7, r6, #0x18
_020D1884:
	mov r0, r7
	bl OS_SleepThread
	ldr r0, [r6, #0xc]
	ands r0, r0, #0x40
	beq _020D1884
	b _020D18BC
_020D189C:
	add r0, r6, #0x18
	bl OS_SleepThread
	ldr r0, [r6, #0xc]
	ands r0, r0, #0x1
	movne r0, #0x1
	moveq r0, #0x0
	cmp r0, #0x0
	bne _020D189C
_020D18BC:
	mov r0, r4
	bl OS_RestoreInterrupts
_020D18C4:
	cmp r5, #0x0
	beq _020D18E0
	mov r0, r6
	bl FSi_ExecuteSyncCommand
	add sp, sp, #4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D18E0:
	ldr r0, [r6, #0x14]
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FS_CloseFile
FS_CloseFile: ; 0x020D18FC
	stmdb sp!, {r4,lr}
	mov r1, #0x8
	mov r4, r0
	bl FSi_SendCommand
_020D190C:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, #0x0
	str r0, [r4, #0x8]
	mov r0, #0xE
	str r0, [r4, #0x10]
	ldr r1, [r4, #0xC]
	mov r0, #0x1
	bic r1, r1, #0x30
	str r1, [r4, #0xC]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FS_OpenFile
FS_OpenFile: ; 0x020D1944
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r4, r0
	add r0, sp, #0x0
	bl FS_ConvertPathToFileID
_020D1958:
	cmp r0, #0x0
	beq _020D1984
	add r1, sp, #0x0
	mov r0, r4
	ldmia r1, {r1, r2}
	bl FS_OpenFileFast
	cmp r0, #0x0
	addne sp, sp, #0x8
	movne r0, #0x1
	ldmneia sp!, {r4, lr}
	bxne lr
_020D1984:
	mov r0, #0x0
	add sp, sp, #0x8
	ldmia sp!, {r4, lr}
	bx lr

	arm_func_start FS_OpenFileFast
FS_OpenFileFast:
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4,lr}
	ldr r1, [sp, #0xc]
	mov r4, r0
	cmp r1, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	addeq sp, sp, #0x10
	bxeq lr
	str r1, [r4, #0x8]
	ldr r3, [sp, #0xc]
	ldr r2, [sp, #0x10]
	mov r1, #0x6
	str r3, [r4, #0x30]
	str r2, [r4, #0x34]
	bl FSi_SendCommand
_020D19D4:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4, lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r1, [r4, #0xC]
	mov r0, #0x1
	orr r1, r1, #0x10
	str r1, [r4, #0xC]
	ldr r1, [r4, #0xC]
	bic r1, r1, #0x20
	str r1, [r4, #0xC]
	ldmia sp!, {r4, lr}
	add sp, sp, #0x10
	bx lr

	arm_func_start FS_OpenFileDirect
FS_OpenFileDirect:
	stmdb sp!, {r4,lr}
	mov r4, r0
	str r1, [r4, #0x8]
	ldr r12, [sp, #0x8]
	mov r1, #0x7
	str r12, [r4, #0x38]
	str r2, [r4, #0x30]
	str r3, [r4, #0x34]
	bl FSi_SendCommand
_020D1A34:
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4, lr}
	bxeq lr
	ldr r1, [r4, #0xC]
	mov r0, #0x1
	orr r1, r1, #0x10
	str r1, [r4, #0xC]
	ldr r1, [r4, #0xC]
	bic r1, r1, #0x20
	str r1, [r4, #0xC]
	ldmia sp!, {r4, lr}
	bx lr

	arm_func_start FS_ConvertPathToFileID
FS_ConvertPathToFileID:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4c
	mov r5, r0
	add r0, sp, #0x0
	mov r4, r1
	bl FS_InitFile
_020D1A80:
	add r0, sp, #0x0
	mov r1, r4
	mov r2, r5
	mov r3, #0x0
	bl FSi_FindPath
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4C
	ldmia sp!, {r4-r5, lr}
	bx lr

	arm_func_start FUN_020D1AAC
FUN_020D1AAC: ; 0x020D1AAC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r4, [r7, #0x2c]
	ldr r0, [r7, #0x28]
	mov r6, r2
	str r1, [r7, #0x30]
	sub r0, r0, r4
	cmp r6, r0
	movgt r6, r0
	cmp r6, #0x0
	movlt r6, #0x0
	str r2, [r7, #0x34]
	mov r5, r3
	str r6, [r7, #0x38]
	cmp r5, #0x0
	ldreq r0, [r7, #0xc]
	mov r1, #0x0
	orreq r0, r0, #0x4
	streq r0, [r7, #0xc]
	mov r0, r7
	bl FSi_SendCommand
_020D1B04:
	cmp r5, #0x0
	bne _020D1B24
	mov r0, r7
	bl FS_WaitAsync
	cmp r0, #0x0
	ldrne r0, [r7, #0x2C]
	subne r6, r0, r4
	mvneq r6, #0x0
_020D1B24:
	mov r0, r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r7, lr}
	bx lr

	arm_func_start FSi_FindPath
FSi_FindPath:
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	mov r7, r1
	ldrb r1, [r7, #0x0]
	mov r8, r0
	mov r6, r2
	mov r5, r3
	cmp r1, #0x2f
	beq _020D1B60
	cmp r1, #0x5c
	bne _020D1B84
_020D1B60:
	ldr r0, _020D1C90 ; =0x021D53EC
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	strh r1, [sp, #0x4]
	str r0, [sp, #0x0]
	str r1, [sp, #0x8]
	strh r1, [sp, #0x6]
	add r7, r7, #0x1
	b _020D1C40
_020D1B84:
	ldr r0, _020D1C90 ; =0x021D53EC
	add r3, sp, #0x0
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	mov r4, #0x0
_020D1B98:
	ldrb r0, [r7, r4]
	cmp r0, #0x0
	beq _020D1C40
	cmp r0, #0x2f
	beq _020D1C40
	cmp r0, #0x5c
	beq _020D1C40
	cmp r0, #0x3a
	bne _020D1C34
	mov r0, r7
	mov r1, r4
	bl FS_FindArchive
_020D1BC8:
	cmp r0, #0x0
	addeq sp, sp, #0x10
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r1, [r0, #0x1C]
	ands r1, r1, #0x2
	movne r1, #0x1
	moveq r1, #0x0
	cmp r1, #0x0
	addeq sp, sp, #0x10
	moveq r0, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r1, #0x0
	str r0, [sp]
	str r1, [sp, #0x8]
	strh r1, [sp, #0x6]
	strh r1, [sp, #0x4]
	add r0, r4, #0x1
	ldrb r0, [r7, r0]!
	cmp r0, #0x2f
	beq _020D1C2C
	cmp r0, #0x5c
	bne _020D1C40
_020D1C2C:
	add r7, r7, #0x1
	b _020D1C40
_020D1C34:
	add r4, r4, #0x1
	cmp r4, #0x3
	ble _020D1B98
_020D1C40:
	ldr r1, [sp, #0x0]
	add r0, sp, #0x0
	str r1, [r8, #0x8]
	str r7, [r8, #0x3c]
	add r3, r8, #0x30
	ldmia r0, {r0-r2}
	stmia r3, {r0-r2}
	cmp r5, #0x0
	movne r0, #0x1
	strne r0, [r8, #0x40]
	strne r5, [r8, #0x44]
	moveq r0, #0x0
	streq r0, [r8, #0x40]
	mov r0, r8
	mov r1, #0x4
	streq r6, [r8, #0x44]
	bl FSi_SendCommand
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020D1C90: .word 0x021D53EC

	arm_func_start FS_InitFile
FS_InitFile:
	mov r3, #0x0
	str r3, [r0, #0x0]
	ldr r2, [r0, #0x0]
	mov r1, #0xe
	str r2, [r0, #0x4]
	str r3, [r0, #0x1c]
	ldr r2, [r0, #0x1c]
	str r2, [r0, #0x18]
	str r3, [r0, #0x8]
	str r1, [r0, #0x10]
	str r3, [r0, #0xc]
	bx lr

	arm_func_start FS_IsAvailable
FS_IsAvailable: ; 0x020D1CC4
	ldr r0, _020D1CD0 ; =0x021D53F8
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020D1CD0: .word 0x021D53F8

	arm_func_start FS_Init
FS_Init: ; 0x020D1CD4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D1D0C ; =0x021D53F8
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl FSi_InitRom
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D1D0C: .word 0x021D53F8

	arm_func_start FS_TryLoadTable
FS_TryLoadTable: ; 0x020D1D10
	ldr ip, _020D1D28 ; =FUN_020D0D84
	mov r3, r0
	mov r2, r1
	ldr r0, _020D1D2C ; =0x021D5414
	mov r1, r3
	bx r12
	.balign 4
_020D1D28: .word FUN_020D0D84
_020D1D2C: .word 0x021D5414

	arm_func_start FS_SetDefaultDMA
FS_SetDefaultDMA: ; 0x020D1D30
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	bl OS_DisableInterrupts
	mov r5, r0
	ldr r1, _020D1D7C ; =0x021D5400
	ldr r0, _020D1D80 ; =0x021D5414
	ldr r4, [r1, #0x0]
	bl FS_SuspendArchive
	ldr r1, _020D1D7C ; =0x021D5400
	cmp r0, #0x0
	str r6, [r1, #0x0]
	beq _020D1D68
	ldr r0, _020D1D80 ; =0x021D5414
	bl FS_ResumeArchive
_020D1D68:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D1D7C: .word 0x021D5400
_020D1D80: .word 0x021D5414

	arm_func_start FSi_InitRom
FSi_InitRom: ; 0x020D1D84
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x14
	ldr r1, _020D1EE8 ; =0x021D5400
	str r0, [r1, #0x0]
	bl OS_GetLockID
	ldr r3, _020D1EEC ; =0x021D53FC
	ldr r2, _020D1EF0 ; =0x021D5404
	mov r12, #0x0
	ldr r1, _020D1EF4 ; =0x021D540C
	str r0, [r3, #0x0]
	str r12, [r2, #0x0]
	str r12, [r2, #0x4]
	str r12, [r1, #0x0]
	str r12, [r1, #0x4]
	bl CARD_Init
	ldr r0, _020D1EF8 ; =0x021D5414
	bl FS_InitArchive
	ldr r0, _020D1EF8 ; =0x021D5414
	ldr r1, _020D1EFC ; =0x02106830
	mov r2, #0x3
	bl FS_RegisterArchiveName
	ldr r0, _020D1F00 ; =0x027FFC40
	ldrh r0, [r0, #0x0]
	cmp r0, #0x2
	bne _020D1E4C
	ldr ip, _020D1EF0 ; =0x021D5404
	mvn r2, #0x0
	ldr r3, _020D1EF4 ; =0x021D540C
	mov lr, #0x0
	ldr r0, _020D1EF8 ; =0x021D5414
	ldr r1, _020D1F04 ; =FSi_EmptyArchiveProc
	str r2, [r12, #0x0]
	str lr, [r12, #0x4]
	str r2, [r3, #0x0]
	str lr, [r3, #0x4]
	bl FS_SetArchiveProc
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, _020D1F08 ; =FSi_ReadDummyCallback
	str r1, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr ip, _020D1F0C ; =FSi_WriteDummyCallback
	ldr r0, _020D1EF8 ; =0x021D5414
	mov r2, r1
	mov r3, r1
	str r12, [sp, #0xc]
	bl FS_LoadArchive
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D1E4C:
	ldr r5, _020D1F10 ; =0x027FFE40
	ldr r0, _020D1EF8 ; =0x021D5414
	ldr r1, _020D1F14 ; =FSi_RomArchiveProc
	ldr r2, _020D1F18 ; =0x00000602
	ldr r4, _020D1F1C ; =0x027FFE48
	bl FS_SetArchiveProc
	ldr r1, [r5, #0x0]
	mvn r0, #0x0
	cmp r1, r0
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r1, #0x0
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r2, [r4, #0x0]
	cmp r2, r0
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r2, #0x0
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	str r1, [sp, #0x0]
	ldr r0, [r5, #0x4]
	ldr r1, _020D1F20 ; =FSi_ReadRomCallback
	str r0, [sp, #0x4]
	ldr r0, _020D1F0C ; =FSi_WriteDummyCallback
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	ldr r3, [r4, #0x4]
	ldr r0, _020D1EF8 ; =0x021D5414
	mov r1, #0x0
	bl FS_LoadArchive
	add sp, sp, #0x14
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D1EE8: .word 0x021D5400
_020D1EEC: .word 0x021D53FC
_020D1EF0: .word 0x021D5404
_020D1EF4: .word 0x021D540C
_020D1EF8: .word 0x021D5414
_020D1EFC: .word 0x02106830
_020D1F00: .word 0x027FFC40
_020D1F04: .word FSi_EmptyArchiveProc
_020D1F08: .word FSi_ReadDummyCallback
_020D1F0C: .word FSi_WriteDummyCallback
_020D1F10: .word 0x027FFE40
_020D1F14: .word FSi_RomArchiveProc
_020D1F18: .word 0x00000602
_020D1F1C: .word 0x027FFE48
_020D1F20: .word FSi_ReadRomCallback

	arm_func_start FSi_EmptyArchiveProc
FSi_EmptyArchiveProc: ; 0x020D1F24
	mov r0, #0x4
	bx lr

	arm_func_start FSi_ReadDummyCallback
FSi_ReadDummyCallback: ; 0x020D1F2C
	mov r0, #0x1
	bx lr

	arm_func_start FSi_RomArchiveProc
FSi_RomArchiveProc: ; 0x020D1F34
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0x1
	beq _020D1FA0
	cmp r1, #0x9
	beq _020D1F58
	cmp r1, #0xa
	beq _020D1F7C
	b _020D1FB0
_020D1F58:
	ldr r0, _020D1FC0 ; =0x021D53FC
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl CARD_LockRom
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {lr}
	bx lr
_020D1F7C:
	ldr r0, _020D1FC0 ; =0x021D53FC
	ldr r0, [r0, #0x0]
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl CARD_UnlockRom
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {lr}
	bx lr
_020D1FA0:
	add sp, sp, #0x4
	mov r0, #0x4
	ldmia sp!, {lr}
	bx lr
_020D1FB0:
	mov r0, #0x8
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D1FC0: .word 0x021D53FC

	arm_func_start FSi_WriteDummyCallback
FSi_WriteDummyCallback: ; 0x020D1FC4
	mov r0, #0x1
	bx lr

	arm_func_start FSi_ReadRomCallback
FSi_ReadRomCallback: ; 0x020D1FCC
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr ip, _020D2010 ; =FSi_OnRomReadDone
	mov lr, r1
	str r12, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r1, #0x1
	ldr r0, _020D2014 ; =0x021D5400
	str r1, [sp, #0x8]
	mov r1, r2
	ldr r0, [r0, #0x0]
	mov r2, lr
	bl CARDi_ReadRom
	mov r0, #0x6
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D2010: .word FSi_OnRomReadDone
_020D2014: .word 0x021D5400

	arm_func_start FSi_OnRomReadDone
FSi_OnRomReadDone: ; 0x020D2018
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl CARD_IsPulledOut
_020D2024:
	cmp r0, #0x0
	movne r1, #0x5
	moveq r1, #0x0
	mov r0, r4
	bl FS_NotifyArchiveAsyncEnd
	ldmia sp!, {r4,lr}
	bx lr


	arm_func_start FS_UnloadOverlay
FS_UnloadOverlay: ; 0x020D2040
	stmdb sp!, {lr}
	sub sp, sp, #0x2c
	mov r3, r0
	mov r2, r1
	add r0, sp, #0x0
	mov r1, r3
	bl FS_LoadOverlayInfo
_020D205C:
	cmp r0, #0x0
	beq _020D2074
	add r0, sp, #0x0
	bl FS_UnloadOverlayImage
	cmp r0, #0x0
	bne _020D2084
_020D2074:
	add sp, sp, #0x2c
	mov r0, #0x0
	ldmfd sp!, {lr}
	bx lr
_020D2084:
	mov r0, #0x1
	add sp, sp, #0x2c
	ldmfd sp!, {lr}
	bx lr

	arm_func_start FS_LoadOverlay
FS_LoadOverlay: ; 0x020D2094
	stmdb sp!, {lr}
	sub sp, sp, #0x2c
	mov r3, r0
	mov r2, r1
	add r0, sp, #0x0
	mov r1, r3
	bl FS_LoadOverlayInfo
_020D20B0:
	cmp r0, #0x0
	beq _020D20C8
	add r0, sp, #0x0
	bl FS_LoadOverlayImage
	cmp r0, #0x0
	bne _020D20D8
_020D20C8:
	add sp, sp, #0x2c
	mov r0, #0x0
	ldmfd sp!, {lr}
	bx lr
_020D20D8:
	add r0, sp, #0x0
	bl FS_StartOverlay
	mov r0, #0x1
	add sp, sp, #0x2c
	ldmfd sp!, {lr}
	bx lr

	arm_func_start FS_UnloadOverlayImage
FS_UnloadOverlayImage: ; 0x020D20F0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FS_EndOverlay
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FS_EndOverlay
FS_EndOverlay: ; 0x020D210C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r8, _020D220C ; =0x021D74C8
	mov r11, r0
	mov r9, #0x0
_020D2120:
	ldr r1, [r11, #0x8]
	ldr r0, [r11, #0xc]
	ldr r5, [r11, #0x4]
	add r0, r1, r0
	mov r7, r9
	mov r6, r9
	add r4, r5, r0
	bl OS_DisableInterrupts
	ldr lr, [r8, #0x0]
	mov r10, r9
	mov r12, lr
	cmp lr, #0x0
	beq _020D21C4
_020D2154:
	ldr r2, [r12, #0x8]
	ldr r3, [r12, #0x0]
	cmp r2, #0x0
	ldr r1, [r12, #0x4]
	bne _020D2178
	cmp r1, r5
	blo _020D2178
	cmp r1, r4
	blo _020D2188
_020D2178:
	cmp r2, r5
	blo _020D21B4
	cmp r2, r4
	bhs _020D21B4
_020D2188:
	cmp r6, #0x0
	strne r12, [r6, #0x0]
	moveq r7, r12
	cmp lr, r12
	streq r3, [r8, #0x0]
	moveq lr, r3
	str r9, [r12, #0x0]
	cmp r10, #0x0
	mov r6, r12
	strne r3, [r10, #0x0]
	b _020D21B8
_020D21B4:
	mov r10, r12
_020D21B8:
	mov r12, r3
	cmp r3, #0x0
	bne _020D2154
_020D21C4:
	bl OS_RestoreInterrupts
_020D21C8:
	cmp r7, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r11, lr}
	bxeq lr
_020D21D8:
	ldr r1, [r7, #0x4]
	ldr r4, [r7]
	cmp r1, #0x0
	beq _020D21F0
	ldr r0, [r7, #0x8]
	blx r1
_020D21F0:
	mov r7, r4
	cmp r4, #0x0
	bne _020D21D8
	b _020D2120
	add sp, sp, #0x4
	ldmia sp!, {r4-r11, lr}
	bx lr
_020D220C: .word 0x021D74C8

	arm_func_start FS_StartOverlay
FS_StartOverlay: ; 0x020D2210
	stmdb sp!, {r4-r6,lr}
	mov r5, r0
	bl FSi_GetOverlayBinarySize
	ldr r1, _020D2300 ; =0x027FFC40
	mov r4, r0
	ldrh r0, [r1, #0x0]
	cmp r0, #0x2
	bne _020D22A4
	ldrb r1, [r5, #0x1f]
	mov r0, #0x0
	ands r1, r1, #0x2
	beq _020D2280
	ldr r1, _020D2304 ; =0x02106F84
	ldr r3, _020D2308 ; =0x02106F84
	ldr r2, _020D230C ; =0x66666667
	sub r12, r1, r3
	smull r1, lr, r2, r12
	mov lr, lr, asr #0x3
	mov r1, r12, lsr #0x1f
	ldr r2, [r5, #0x0]
	add lr, r1, lr
	cmp r2, lr
	bhs _020D2280
	mov r0, #0x14
	mla r0, r2, r0, r3
	ldr r1, [r5, #0x4]
	mov r2, r4
	bl FSi_CompareDigest
_020D2280:
	cmp r0, #0x0
	bne _020D22A4
	ldr r0, [r5, #0x4]
	mov r2, r4
	mov r1, #0x0
	bl MI_CpuFill8
	bl OS_Terminate
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D22A4:
	ldrb r0, [r5, #0x1f]
	ands r0, r0, #0x1
	beq _020D22BC
	ldr r0, [r5, #0x4]
	add r0, r0, r4
	bl MIi_UncompressBackward
_020D22BC:
	ldr r0, [r5, #0x4]
	ldr r1, [r5, #0x8]
	bl DC_FlushRange
	ldr r6, [r5, #0x10]
	ldr r4, [r5, #0x14]
	cmp r6, r4
	ldmcsia sp!, {r4-r6,lr}
	bxcs lr
_020D22DC:
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	beq _020D22EC
	blx r0
_020D22EC:
	add r6, r6, #0x4
	cmp r6, r4
	blo _020D22DC
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D2300: .word 0x027FFC40
_020D2304: .word 0x02106F84
_020D2308: .word 0x02106F84
_020D230C: .word 0x66666667

	arm_func_start FSi_CompareDigest
FSi_CompareDigest:
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x58
	mov r4, r0
	mov r6, r1
	mov r5, r2
	add r0, sp, #0x4
	mov r1, #0x0
	mov r2, #0x14
	bl MI_CpuFill8
	ldr r0, _020D23AC ; =0x02106834
	ldr r1, _020D23B0 ; =0x02106838
	ldr r0, [r0, #0x0]
	ldr r2, [r1, #0x0]
	add r1, sp, #0x18
	bl MI_CpuCopy8
	ldr r3, _020D23B0 ; =0x02106838
	mov r1, r6
	ldr r12, [r3, #0x0]
	mov r2, r5
	add r0, sp, #0x4
	add r3, sp, #0x18
	str r12, [sp, #0x0]
	bl MATH_CalcHMACSHA1
	add r2, sp, #0x4
	mov r3, #0x0
_020D2374:
	ldr r1, [r2, #0x0]
	ldr r0, [r4, r3]
	cmp r1, r0
	bne _020D2394
	add r3, r3, #0x4
	cmp r3, #0x14
	add r2, r2, #0x4
	blo _020D2374
_020D2394:
	cmp r3, #0x14
	moveq r0, #0x1
	movne r0, #0x0
	add sp, sp, #0x58
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D23AC: .word 0x02106834
_020D23B0: .word 0x02106838

	arm_func_start FS_LoadOverlayImage
FS_LoadOverlayImage: ; 0x020D23B4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x54
	mov r5, r0
	add r0, sp, #0x8
	bl FS_InitFile
_020D23C8:
	add r0, sp, #0x0
	mov r1, r5
	bl FS_GetOverlayFileID
	add r1, sp, #0x0
	add r0, sp, #0x8
	ldmia r1, {r1, r2}
	bl FS_OpenFileFast
	cmp r0, #0x0
	addeq sp, sp, #0x54
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5, lr}
	bxeq lr
	mov r0, r5
	bl FSi_GetOverlayBinarySize
	mov r4, r0
	mov r0, r5
	bl FS_ClearOverlayImage
	ldr r1, [r5, #0x4]
	add r0, sp, #0x8
	mov r2, r4
	bl FS_ReadFile
	cmp r4, r0
	beq _020D243C
	add r0, sp, #0x8
	bl FS_CloseFile
	add sp, sp, #0x54
	mov r0, #0x0
	ldmia sp!, {r4-r5, lr}
	bx lr
_020D243C:
	add r0, sp, #0x8
	bl FS_CloseFile
	mov r0, #0x1
	add sp, sp, #0x54
	ldmia sp!, {r4-r5, lr}
	bx lr

	arm_func_start FS_LoadOverlayImageAsync
FS_LoadOverlayImageAsync: ; 0x020D2454
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x8
	mov r5, r1
	mov r6, r0
	mov r0, r5
	bl FS_InitFile
_020D246C:
	add r0, sp, #0x0
	mov r1, r6
	bl FS_GetOverlayFileID
	add r1, sp, #0x0
	mov r0, r5
	ldmia r1, {r1, r2}
	bl FS_OpenFileFast
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6, lr}
	bxeq lr
	mov r0, r6
	bl FSi_GetOverlayBinarySize
	mov r4, r0
	mov r0, r6
	bl FS_ClearOverlayImage
	ldr r1, [r6, #0x4]
	mov r0, r5
	mov r2, r4
	bl FS_ReadFileAsync
	cmp r4, r0
	addeq sp, sp, #0x8
	moveq r0, #0x1
	ldmeqia sp!, {r4-r6, lr}
	bxeq lr
	mov r0, r5
	bl FS_CloseFile
	mov r0, #0x0
	add sp, sp, #0x8
	ldmia sp!, {r4-r6, lr}
	bx lr

	arm_func_start FS_LoadOverlayInfo
FS_LoadOverlayInfo:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x64
	movs r4, r1
	mov r5, r0
	ldreq r0, _020D25EC ; =0x021D5404
	ldrne r0, _020D25F0 ; =0x021D540C
	ldr r3, [r0, #0x0]
	cmp r3, #0x0
	beq _020D25A8
	ldr r0, [r0, #0x4]
	mov r2, r2, lsl #0x5
	cmp r2, r0
	addcs sp, sp, #0x64
	movcs r0, #0x0
	ldmcsia sp!, {r4-r5,lr}
	bxcs lr
	add r0, r3, r2
	mov r1, r5
	mov r2, #0x20
	bl MI_CpuCopy8
	add r0, sp, #0x18
	str r4, [r5, #0x20]
	bl FS_InitFile
	add r0, sp, #0x10
	mov r1, r5
	bl FS_GetOverlayFileID
	add r1, sp, #0x10
	add r0, sp, #0x18
	ldmia r1, {r1-r2}
	bl FS_OpenFileFast
_020D2564:
	cmp r0, #0x0
	addeq sp, sp, #0x64
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r1, [sp, #0x3c]
	add r0, sp, #0x18
	str r1, [r5, #0x24]
	ldr r2, [sp, #0x40]
	ldr r1, [sp, #0x3c]
	sub r1, r2, r1
	str r1, [r5, #0x28]
	bl FS_CloseFile
	add sp, sp, #0x64
	mov r0, #0x1
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D25A8:
	ldr r1, _020D25F4 ; =0x027FFE50
	ldr ip, _020D25F8 ; =0x027FFE58
	ldr r0, [r1, #0x0]
	ldr r3, _020D25FC ; =0x021D5414
	str r0, [sp, #0x0]
	ldr r1, [r1, #0x4]
	mov r0, r5
	str r1, [sp, #0x4]
	ldr r5, [r12, #0x0]
	mov r1, r4
	str r5, [sp, #0x8]
	ldr r4, [r12, #0x4]
	str r4, [sp, #0xc]
	bl FSi_LoadOverlayInfoCore
	add sp, sp, #0x64
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D25EC: .word 0x021D5404
_020D25F0: .word 0x021D540C
_020D25F4: .word 0x027FFE50
_020D25F8: .word 0x027FFE58
_020D25FC: .word 0x021D5414

	arm_func_start FSi_LoadOverlayInfoCore
FSi_LoadOverlayInfoCore: ; 0x020D2600
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x54
	movs r9, r1
	ldreq r5, [sp, #0x74]
	ldreq r6, [sp, #0x70]
	ldrne r5, [sp, #0x7c]
	ldrne r6, [sp, #0x78]
	mov r7, r2, lsl #0x5
	cmp r7, r5
	mov r4, r0
	mov r8, r3
	addcs sp, sp, #0x54
	movcs r0, #0x0
	ldmcsia sp!, {r4-r9,lr}
	bxcs lr
	add r0, sp, #0xc
	bl FS_InitFile
	mvn r12, #0x0
	add r0, sp, #0xc
	mov r1, r8
	add r2, r6, r7
	add r3, r6, r5
	str r12, [sp, #0x0]
	bl FS_OpenFileDirect
_020D2660:
	cmp r0, #0
	addeq sp, sp, #0x54
	moveq r0, #0
	ldmeqia sp!, {r4-r9, lr}
	bxeq lr
	add r0, sp, #12
	mov r1, r4
	mov r2, #32
	bl FS_ReadFile
	cmp r0, #32
	beq _020D26A4
	add r0, sp, #12
	bl FS_CloseFile
	add sp, sp, #0x54
	mov r0, #0x0
	ldmia sp!, {r4-r9, lr}
	bx lr
_020D26A4:
	add r0, sp, #0xC
	bl FS_CloseFile
	add r0, sp, #0x4
	mov r1, r4
	str r9, [r4, #0x20]
	bl FS_GetOverlayFileID
	add r1, sp, #0x4
	add r0, sp, #0xC
	ldmia r1, {r1, r2}
	bl FS_OpenFileFast
	cmp r0, #0x0
	addeq sp, sp, #0x54
	moveq r0, #0x0
	ldmeqia sp!, {r4-r9, lr}
	bxeq lr
	ldr r1, [sp, #0x30]
	add r0, sp, #0xC
	str r1, [r4, #0x24]
	ldr r2, [sp, #0x34]
	ldr r1, [sp, #0x30]
	sub r1, r2, r1
	str r1, [r4, #0x28]
	bl FS_CloseFile
	mov r0, #0x1
	add sp, sp, #0x54
	ldmia sp!, {r4-r9, lr}
	bx lr

	arm_func_start FS_GetOverlayFileID
FS_GetOverlayFileID: ; 0x020D2710
	sub sp, sp, #0x8
	ldr r2, _020D2734 ; =0x021D5414
	str r2, [sp, #0x0]
	ldr r1, [r1, #0x18]
	str r1, [sp, #0x4]
	str r2, [r0, #0x0]
	str r1, [r0, #0x4]
	add sp, sp, #0x8
	bx lr
	.balign 4
_020D2734: .word 0x021D5414

	arm_func_start FS_ClearOverlayImage
FS_ClearOverlayImage: ; 0x020D2738
	stmdb sp!, {r4-r6,lr}
	ldr r5, [r0, #0x8]
	ldr r1, [r0, #0xc]
	ldr r6, [r0, #0x4]
	add r4, r5, r1
	mov r0, r6
	mov r1, r4
	bl IC_InvalidateRange
	mov r0, r6
	mov r1, r4
	bl DC_InvalidateRange
	add r0, r6, r5
	sub r2, r4, r5
	mov r1, #0x0
	bl MI_CpuFill8
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start FSi_GetOverlayBinarySize
FSi_GetOverlayBinarySize: ; 0x020D277C
	ldrb r1, [r0, #0x1f]
	ands r1, r1, #0x1
	ldrne r0, [r0, #0x1c]
	movne r0, r0, lsl #0x8
	movne r0, r0, lsr #0x8
	ldreq r0, [r0, #0x8]
	bx lr

	arm_func_start ProcessBlock
ProcessBlock: ; 0x020D2798
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	add r3, r0, #0x18
	ldr r5, [r0, #0x0]
	ldr r4, [r0, #0x4]
	ldr lr, [r0, #0x8]
	ldr r12, [r0, #0xc]
	ldr r2, _020D2B78 ; =0x02106900
	mov r8, r3
	mov r7, #0x0
_020D27C0:
	mvn r1, r4
	and r6, r4, lr
	and r1, r1, r12
	orr r1, r6, r1
	ldr r6, [r8, #0x0]
	add r1, r5, r1
	ldr r5, [r2, #0x0]
	add r1, r6, r1
	add r5, r5, r1
	mov r1, r5, lsl #0x7
	orr r1, r1, r5, lsr #0x19
	add r5, r4, r1
	mvn r1, r5
	and r6, r5, r4
	and r1, r1, lr
	orr r1, r6, r1
	ldr r6, [r8, #0x4]
	add r1, r12, r1
	ldr r9, [r2, #0x4]
	add r1, r6, r1
	add r6, r9, r1
	mov r1, r6, lsl #0xc
	orr r1, r1, r6, lsr #0x14
	add r12, r5, r1
	mvn r1, r12
	and r6, r12, r5
	and r1, r1, r4
	orr r6, r6, r1
	add r1, r8, #0xc
	ldr r9, [r8, #0x8]
	add r6, lr, r6
	add r6, r9, r6
	ldr r9, [r2, #0x8]
	ldr r1, [r1, #0x0]
	add r10, r9, r6
	add r6, r2, #0xc
	ldr r6, [r6, #0x0]
	mov r9, r10, lsl #0x11
	orr r9, r9, r10, lsr #0xf
	add lr, r12, r9
	add r2, r2, #0x10
	add r8, r8, #0x10
	and r10, lr, r12
	mvn r9, lr
	and r9, r9, r5
	orr r9, r10, r9
	add r4, r4, r9
	add r1, r1, r4
	add r4, r6, r1
	mov r1, r4, lsl #0x16
	orr r1, r1, r4, lsr #0xa
	add r4, lr, r1
	add r7, r7, #0x1
	cmp r7, #0x4
	blt _020D27C0
	ldr r6, _020D2B7C ; =0x02106840
	mov r1, #0x0
_020D28A4:
	mvn r7, r12
	ldr r9, [r6, #0x0]
	and r8, r4, r12
	and r7, lr, r7
	orr r7, r8, r7
	ldr r8, [r3, r9, lsl #0x2]
	add r5, r5, r7
	ldr r7, [r2, #0x0]
	add r5, r8, r5
	add r7, r7, r5
	mov r5, r7, lsl #0x5
	orr r5, r5, r7, lsr #0x1b
	add r5, r4, r5
	mvn r8, lr
	ldr r7, [r6, #0x4]
	and r9, r5, lr
	and r8, r4, r8
	orr r10, r9, r8
	mvn r8, r4
	ldr r9, [r6, #0x8]
	ldr r11, [r3, r7, lsl #0x2]
	add r7, r12, r10
	add r10, r11, r7
	add r7, r6, #0xc
	ldr r9, [r3, r9, lsl #0x2]
	and r8, r5, r8
	ldr r7, [r7, #0x0]
	ldr r11, [r2, #0x4]
	ldr r7, [r3, r7, lsl #0x2]
	add r11, r11, r10
	mov r10, r11, lsl #0x9
	orr r10, r10, r11, lsr #0x17
	add r12, r5, r10
	ldr r10, [r2, #0x8]
	and r11, r12, r4
	orr r8, r11, r8
	add r8, lr, r8
	add r8, r9, r8
	add r10, r10, r8
	add r8, r2, #0xc
	ldr r8, [r8, #0x0]
	mov r9, r10, lsl #0xe
	orr r9, r9, r10, lsr #0x12
	add lr, r12, r9
	add r2, r2, #0x10
	add r6, r6, #0x10
	and r10, lr, r5
	mvn r9, r5
	and r9, r12, r9
	orr r9, r10, r9
	add r4, r4, r9
	add r4, r7, r4
	add r7, r8, r4
	mov r4, r7, lsl #0x14
	orr r4, r4, r7, lsr #0xc
	add r4, lr, r4
	add r1, r1, #0x1
	cmp r1, #0x4
	blt _020D28A4
	mov r7, #0x0
_020D2994:
	ldr r8, [r6, #0x0]
	eor r1, r4, lr
	eor r1, r12, r1
	add r1, r5, r1
	ldr r8, [r3, r8, lsl #0x2]
	ldr r5, [r2, #0x0]
	add r1, r8, r1
	add r5, r5, r1
	mov r1, r5, lsl #0x4
	orr r1, r1, r5, lsr #0x1c
	add r5, r4, r1
	ldr r8, [r6, #0x4]
	eor r1, r5, r4
	eor r1, lr, r1
	ldr r8, [r3, r8, lsl #0x2]
	add r1, r12, r1
	ldr r9, [r6, #0x8]
	ldr r10, [r2, #0x4]
	add r1, r8, r1
	add r8, r10, r1
	mov r1, r8, lsl #0xb
	orr r1, r1, r8, lsr #0x15
	add r12, r5, r1
	eor r8, r12, r5
	eor r8, r4, r8
	ldr r9, [r3, r9, lsl #0x2]
	add r8, lr, r8
	add r9, r9, r8
	ldr r10, [r2, #0x8]
	add r1, r2, #0xc
	ldr r8, [r6, #0xc]
	add r10, r10, r9
	ldr r9, [r3, r8, lsl #0x2]
	mov r8, r10, lsl #0x10
	orr r8, r8, r10, lsr #0x10
	add lr, r12, r8
	eor r8, lr, r12
	eor r8, r5, r8
	add r4, r4, r8
	add r7, r7, #0x1
	ldr r1, [r1, #0x0]
	add r4, r9, r4
	add r4, r1, r4
	mov r1, r4, lsl #0x17
	orr r1, r1, r4, lsr #0x9
	add r2, r2, #0x10
	add r6, r6, #0x10
	add r4, lr, r1
	cmp r7, #0x4
	blt _020D2994
	mov r10, #0x0
_020D2A60:
	mvn r1, r12
	ldr r7, [r6, #0x0]
	orr r1, r4, r1
	eor r1, lr, r1
	ldr r7, [r3, r7, lsl #0x2]
	add r1, r5, r1
	ldr r5, [r2, #0x0]
	add r1, r7, r1
	add r5, r5, r1
	mov r1, r5, lsl #0x6
	orr r1, r1, r5, lsr #0x1a
	add r5, r4, r1
	mvn r1, lr
	ldr r7, [r6, #0x4]
	orr r1, r5, r1
	eor r1, r4, r1
	ldr r8, [r6, #0x8]
	ldr r7, [r3, r7, lsl #0x2]
	add r1, r12, r1
	ldr r9, [r2, #0x4]
	add r1, r7, r1
	add r9, r9, r1
	mov r7, r9, lsl #0xa
	add r1, r6, #0xc
	orr r9, r7, r9, lsr #0x16
	ldr r1, [r1, #0x0]
	add r7, r2, #0xc
	add r12, r5, r9
	ldr r8, [r3, r8, lsl #0x2]
	ldr r7, [r7, #0x0]
	ldr r1, [r3, r1, lsl #0x2]
	ldr r9, [r2, #0x8]
	mvn r11, r4
	orr r11, r12, r11
	eor r11, r5, r11
	add r11, lr, r11
	add r8, r8, r11
	add r9, r9, r8
	mov r8, r9, lsl #0xf
	orr r8, r8, r9, lsr #0x11
	add lr, r12, r8
	add r2, r2, #0x10
	add r6, r6, #0x10
	mvn r8, r5
	orr r8, lr, r8
	eor r8, r12, r8
	add r4, r4, r8
	add r1, r1, r4
	add r4, r7, r1
	mov r1, r4, lsl #0x15
	orr r1, r1, r4, lsr #0xb
	add r4, lr, r1
	add r10, r10, #0x1
	cmp r10, #0x4
	blt _020D2A60
	ldr r1, [r0, #0x0]
	add r1, r1, r5
	str r1, [r0, #0x0]
	ldr r1, [r0, #0x4]
	add r1, r1, r4
	str r1, [r0, #0x4]
	ldr r1, [r0, #0x8]
	add r1, r1, lr
	str r1, [r0, #0x8]
	ldr r1, [r0, #0xc]
	add r1, r1, r12
	str r1, [r0, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020D2B78: .word 0x02106900
_020D2B7C: .word 0x02106840

	arm_func_start MATH_MD5GetHash
MATH_MD5GetHash: ; 0x020D2B80
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r1
	ldr r1, [r6, #0x14]
	ldr r3, [r6, #0x10]
	mov r7, r0
	mov r4, r1, lsl #0x3
	ldr r1, _020D2C40 ; =0x0210683C
	mov r0, r6
	mov r2, #0x1
	orr r4, r4, r3, lsr #0x1d
	mov r5, r3, lsl #0x3
	bl MATH_MD5Update
	ldr r0, [r6, #0x10]
	mov r1, #0x0
	and r3, r0, #0x3f
	rsb r2, r3, #0x40
	cmp r2, #0x8
	bhs _020D2BE8
	add r0, r6, #0x18
	add r0, r0, r3
	bl MI_CpuFill8
	mov r0, r6
	bl ProcessBlock
	mov r3, #0x0
	mov r2, #0x40
_020D2BE8:
	cmp r2, #0x8
	bls _020D2C04
	add r0, r6, #0x18
	add r0, r0, r3
	sub r2, r2, #0x8
	mov r1, #0x0
	bl MI_CpuFill8
_020D2C04:
	str r5, [r6, #0x50]
	mov r0, r6
	str r4, [r6, #0x54]
	bl ProcessBlock
	mov r0, r6
	mov r1, r7
	mov r2, #0x10
	bl MI_CpuCopy8
	mov r0, r6
	mov r1, #0x0
	mov r2, #0x58
	bl MI_CpuFill8
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020D2C40: .word 0x0210683C

	arm_func_start MATH_MD5Update
MATH_MD5Update: ; 0x020D2C44
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r0
	add r12, r8, #0x10
	ldr r4, [r8, #0x10]
	mov r6, r2
	and r3, r4, #0x3f
	ldr r0, [r12, #0x4]
	adds r4, r4, r6
	str r4, [r8, #0x10]
	adc r0, r0, #0x0
	rsb r5, r3, #0x40
	mov r7, r1
	str r0, [r12, #0x4]
	cmp r5, r6
	bls _020D2CB0
	cmp r6, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	add r1, r8, #0x18
	mov r0, r7
	add r1, r1, r3
	bl MI_CpuCopy8
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
_020D2CB0:
	add r1, r8, #0x18
	mov r0, r7
	mov r2, r5
	add r1, r1, r3
	bl MI_CpuCopy8
	mov r0, r8
	bl ProcessBlock
	sub r6, r6, r5
	mov r4, r6, lsr #0x6
	cmp r4, #0x0
	add r9, r7, r5
	ble _020D2D10
	add r7, r8, #0x18
	mov r5, #0x40
_020D2CE8:
	mov r0, r9
	mov r1, r7
	mov r2, r5
	bl MI_CpuCopy8
	mov r0, r8
	add r9, r9, #0x40
	bl ProcessBlock
	sub r4, r4, #0x1
	cmp r4, #0x0
	bgt _020D2CE8
_020D2D10:
	ands r2, r6, #0x3f
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r0, r9
	add r1, r8, #0x18
	bl MI_CpuCopy8
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start MATH_MD5Init
MATH_MD5Init: ; 0x020D2D38
	ldr r2, _020D2D68 ; =0x67452301
	ldr r1, _020D2D6C ; =0xEFCDAB89
	str r2, [r0, #0x0]
	ldr r2, _020D2D70 ; =0x98BADCFE
	str r1, [r0, #0x4]
	ldr r1, _020D2D74 ; =0x10325476
	str r2, [r0, #0x8]
	str r1, [r0, #0xc]
	mov r1, #0x0
	str r1, [r0, #0x10]
	str r1, [r0, #0x14]
	bx lr
	.balign 4
_020D2D68: .word 0x67452301
_020D2D6C: .word 0xEFCDAB89
_020D2D70: .word 0x98BADCFE
_020D2D74: .word 0x10325476

	arm_func_start MATH_CalcHMACSHA1
MATH_CalcHMACSHA1: ; 0x020D2D78
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0xa0
	ldr lr, _020D2E00 ; =0x02106A04
	add r12, sp, #0x1c
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, r3
	mov r4, r12
	ldmia lr!, {r0-r3}
	stmia r12!, {r0-r3}
	ldmia lr, {r0-r2}
	stmia r12, {r0-r2}
	add lr, sp, #0x38
	add r12, sp, #0x8
	str lr, [sp, #0x24]
	ldr lr, _020D2E04 ; =MATH_SHA1Init
	str r12, [sp, #0x28]
	ldr ip, _020D2E08 ; =MATH_SHA1Update
	str lr, [sp, #0x2c]
	ldr lr, _020D2E0C ; =MATH_SHA1GetHash
	str r12, [sp, #0x30]
	ldr r12, [sp, #0xb8]
	str lr, [sp, #0x34]
	str r12, [sp, #0x0]
	mov r3, r5
	mov r0, r8
	mov r1, r7
	mov r2, r6
	str r4, [sp, #0x4]
	bl MATHi_CalcHMAC
	add sp, sp, #0xa0
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020D2E00: .word 0x02106A04
_020D2E04: .word MATH_SHA1Init
_020D2E08: .word MATH_SHA1Update
_020D2E0C: .word MATH_SHA1GetHash

	arm_func_start MATH_SHA1GetHash
MATH_SHA1GetHash: ; 0x020D2E10
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4-r6,lr}
	ldr r0, [sp, #0x10]
	mov r6, r1
	ldr r3, [r0, #0x1c]
	add r5, r0, #0x20
	ands r1, r3, #0x3
	mov r0, r3, asr #0x2
	moveq r1, #0x0
	streq r1, [r5, r0, lsl #0x2]
	ldr r2, [sp, #0x10]
	mov r1, #0x80
	add r4, r2, #0x20
	strb r1, [r4, r3]
	add r3, r3, #0x1
	ands r1, r3, #0x3
	beq _020D2E68
	mov r2, #0x0
_020D2E58:
	strb r2, [r4, r3]
	add r3, r3, #0x1
	ands r1, r3, #0x3
	bne _020D2E58
_020D2E68:
	ldr r1, [sp, #0x10]
	add r0, r0, #0x1
	ldr r1, [r1, #0x1c]
	cmp r1, #0x38
	blt _020D2EB4
	cmp r0, #0x10
	bge _020D2E98
	mov r1, #0x0
_020D2E88:
	str r1, [r5, r0, lsl #0x2]
	add r0, r0, #0x1
	cmp r0, #0x10
	blt _020D2E88
_020D2E98:
	ldr r1, _020D3008 ; =0x02106A00
	ldr r0, [sp, #0x10]
	ldr r3, [r1, #0x0]
	mov r1, r5
	mov r2, #0x40
	blx r3
	mov r0, #0x0
_020D2EB4:
	cmp r0, #0xe
	bge _020D2ED0
	mov r1, #0x0
_020D2EC0:
	str r1, [r5, r0, lsl #0x2]
	add r0, r0, #0x1
	cmp r0, #0xe
	blt _020D2EC0
_020D2ED0:
	ldr r0, [sp, #0x10]
	mov r1, r5
	ldr r2, [r0, #0x14]
	ldr r3, _020D3008 ; =0x02106A00
	strb r2, [r4, #0x3f]
	mov r0, r2, lsr #0x8
	strb r0, [r4, #0x3e]
	mov r0, r2, lsr #0x10
	strb r0, [r4, #0x3d]
	mov r0, r2, lsr #0x18
	strb r0, [r4, #0x3c]
	ldr r0, [sp, #0x10]
	mov r2, #0x40
	ldr r5, [r0, #0x18]
	strb r5, [r4, #0x3b]
	mov r0, r5, lsr #0x8
	strb r0, [r4, #0x3a]
	mov r0, r5, lsr #0x10
	strb r0, [r4, #0x39]
	mov r0, r5, lsr #0x18
	strb r0, [r4, #0x38]
	ldr r0, [sp, #0x10]
	ldr r3, [r3, #0x0]
	blx r3
	ldr r0, [sp, #0x10]
	add r1, sp, #0x10
	ldr r3, [r0, #0x0]
	mov r0, #0x0
	mov r2, r3, lsr #0x18
	strb r2, [r6, #0x0]
	mov r2, r3, lsr #0x10
	strb r2, [r6, #0x1]
	mov r2, r3, lsr #0x8
	strb r2, [r6, #0x2]
	strb r3, [r6, #0x3]
	ldr r3, [sp, #0x10]
	mov r2, #0x4
	ldr r4, [r3, #0x4]
	mov r3, r4, lsr #0x18
	strb r3, [r6, #0x4]
	mov r3, r4, lsr #0x10
	strb r3, [r6, #0x5]
	mov r3, r4, lsr #0x8
	strb r3, [r6, #0x6]
	strb r4, [r6, #0x7]
	ldr r3, [sp, #0x10]
	ldr r4, [r3, #0x8]
	mov r3, r4, lsr #0x18
	strb r3, [r6, #0x8]
	mov r3, r4, lsr #0x10
	strb r3, [r6, #0x9]
	mov r3, r4, lsr #0x8
	strb r3, [r6, #0xa]
	strb r4, [r6, #0xb]
	ldr r3, [sp, #0x10]
	ldr r4, [r3, #0xc]
	mov r3, r4, lsr #0x18
	strb r3, [r6, #0xc]
	mov r3, r4, lsr #0x10
	strb r3, [r6, #0xd]
	mov r3, r4, lsr #0x8
	strb r3, [r6, #0xe]
	strb r4, [r6, #0xf]
	ldr r3, [sp, #0x10]
	ldr r4, [r3, #0x10]
	mov r3, r4, lsr #0x18
	strb r3, [r6, #0x10]
	mov r3, r4, lsr #0x10
	strb r3, [r6, #0x11]
	mov r3, r4, lsr #0x8
	strb r3, [r6, #0x12]
	strb r4, [r6, #0x13]
	ldr r3, [sp, #0x10]
	str r0, [r3, #0x1c]
	bl MIi_CpuClear32
	ldmia sp!, {r4-r6,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020D3008: .word 0x02106A00

	arm_func_start MATH_SHA1Update
MATH_SHA1Update: ; 0x020D300C
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	movs r6, r2
	mov r7, r1
	add r5, r8, #0x20
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldr r0, [r8, #0x14]
	add r1, r0, r6, lsl #0x3
	cmp r1, r0
	ldrcc r0, [r8, #0x18]
	addcc r0, r0, #0x1
	strcc r0, [r8, #0x18]
	ldr r0, [r8, #0x18]
	add r0, r0, r6, lsr #0x1d
	str r0, [r8, #0x18]
	str r1, [r8, #0x14]
	ldr r1, [r8, #0x1c]
	cmp r1, #0x0
	beq _020D30CC
	add r0, r1, r6
	cmp r0, #0x40
	blo _020D30A8
	rsb r4, r1, #0x40
	mov r0, r7
	mov r2, r4
	add r1, r5, r1
	bl MI_CpuCopy8
	ldr r1, _020D3164 ; =0x02106A00
	mov r0, r8
	ldr r3, [r1, #0x0]
	mov r1, r5
	mov r2, #0x40
	sub r6, r6, r4
	add r7, r7, r4
	blx r3
	mov r0, #0x0
	str r0, [r8, #0x1c]
	b _020D30CC
_020D30A8:
	mov r0, r7
	mov r2, r6
	add r1, r5, r1
	bl MI_CpuCopy8
	ldr r0, [r8, #0x1c]
	add r0, r0, r6
	str r0, [r8, #0x1c]
	ldmia sp!, {r4-r8,lr}
	bx lr
_020D30CC:
	cmp r6, #0x40
	blo _020D313C
	bic r4, r6, #0x3f
	sub r6, r6, r4
	ands r0, r7, #0x3
	bne _020D3104
	ldr r1, _020D3164 ; =0x02106A00
	mov r0, r8
	ldr r3, [r1, #0x0]
	mov r1, r7
	mov r2, r4
	blx r3
	add r7, r7, r4
	b _020D313C
_020D3104:
	mov r0, r7
	mov r1, r5
	mov r2, #0x40
	bl MI_CpuCopy8
	ldr r1, _020D3164 ; =0x02106A00
	mov r0, r8
	ldr r3, [r1, #0x0]
	mov r1, r5
	mov r2, #0x40
	add r7, r7, #0x40
	blx r3
	sub r4, r4, #0x40
	cmp r4, #0x0
	bgt _020D3104
_020D313C:
	str r6, [r8, #0x1c]
	cmp r6, #0x0
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r0, r7
	mov r1, r5
	mov r2, r6
	bl MI_CpuCopy8
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020D3164: .word 0x02106A00

	arm_func_start MATH_SHA1Init
MATH_SHA1Init: ; 0x020D3168
	ldr r1, _020D31A4 ; =0x67452301
	ldr r2, _020D31A8 ; =0xEFCDAB89
	str r1, [r0, #0x0]
	ldr r1, _020D31AC ; =0x98BADCFE
	str r2, [r0, #0x4]
	ldr r2, _020D31B0 ; =0x10325476
	str r1, [r0, #0x8]
	ldr r1, _020D31B4 ; =0xC3D2E1F0
	str r2, [r0, #0xc]
	str r1, [r0, #0x10]
	mov r1, #0x0
	str r1, [r0, #0x14]
	str r1, [r0, #0x18]
	str r1, [r0, #0x1c]
	bx lr
	.balign 4
_020D31A4: .word 0x67452301
_020D31A8: .word 0xEFCDAB89
_020D31AC: .word 0x98BADCFE
_020D31B0: .word 0x10325476
_020D31B4: .word 0xC3D2E1F0

	arm_func_start MATHi_CalcHMAC
MATHi_CalcHMAC: ; 0x020D31B8
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0xc4
	ldr r5, [sp, #0xe0]
	ldr r4, [sp, #0xe4]
	movs r9, r0
	mov r8, r1
	mov r7, r2
	mov r6, r3
	addeq sp, sp, #0xc4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	cmp r8, #0x0
	addeq sp, sp, #0xc4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	cmp r7, #0x0
	addeq sp, sp, #0xc4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	cmp r6, #0x0
	addeq sp, sp, #0xc4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	cmp r5, #0x0
	addeq sp, sp, #0xc4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	cmp r4, #0x0
	addeq sp, sp, #0xc4
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r0, [r4, #0x4]
	cmp r5, r0
	ble _020D3278
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0x10]
	blx r1
	ldr r0, [r4, #0x8]
	ldr r3, [r4, #0x14]
	mov r1, r6
	mov r2, r5
	blx r3
	ldr r0, [r4, #0x8]
	ldr r2, [r4, #0x18]
	add r1, sp, #0x0
	blx r2
	ldr r5, [r4, #0x0]
	add r6, sp, #0x0
_020D3278:
	cmp r5, #0x0
	mov r0, #0x0
	ble _020D32A0
	add r2, sp, #0x40
_020D3288:
	ldrb r1, [r6, r0]
	add r0, r0, #0x1
	cmp r0, r5
	eor r1, r1, #0x36
	strb r1, [r2], #0x1
	blt _020D3288
_020D32A0:
	ldr r1, [r4, #0x4]
	cmp r0, r1
	bge _020D32CC
	add r1, sp, #0x40
	add r3, r1, r0
	mov r2, #0x36
_020D32B8:
	strb r2, [r3], #0x1
	ldr r1, [r4, #0x4]
	add r0, r0, #0x1
	cmp r0, r1
	blt _020D32B8
_020D32CC:
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0x10]
	blx r1
	ldr r0, [r4, #0x8]
	ldr r2, [r4, #0x4]
	ldr r3, [r4, #0x14]
	add r1, sp, #0x40
	blx r3
	ldr r0, [r4, #0x8]
	ldr r3, [r4, #0x14]
	mov r1, r8
	mov r2, r7
	blx r3
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x18]
	blx r2
	cmp r5, #0x0
	mov r2, #0x0
	ble _020D3338
	add r1, sp, #0x80
_020D3320:
	ldrb r0, [r6, r2]
	add r2, r2, #0x1
	cmp r2, r5
	eor r0, r0, #0x5c
	strb r0, [r1], #0x1
	blt _020D3320
_020D3338:
	ldr r0, [r4, #0x4]
	cmp r2, r0
	bge _020D3364
	add r0, sp, #0x80
	add r3, r0, r2
	mov r1, #0x5c
_020D3350:
	strb r1, [r3], #0x1
	ldr r0, [r4, #0x4]
	add r2, r2, #0x1
	cmp r2, r0
	blt _020D3350
_020D3364:
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0x10]
	blx r1
	ldr r0, [r4, #0x8]
	ldr r2, [r4, #0x4]
	ldr r3, [r4, #0x14]
	add r1, sp, #0x80
	blx r3
	ldr r0, [r4, #0x8]
	ldr r1, [r4, #0xc]
	ldr r2, [r4, #0x0]
	ldr r3, [r4, #0x14]
	blx r3
	ldr r0, [r4, #0x8]
	ldr r2, [r4, #0x18]
	mov r1, r9
	blx r2
	add sp, sp, #0xc4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020D33B4: .word 0x00FF00FF
_020D33B8: .word 0x5A827999
_020D33BC: .word 0x6ED9EBA1
_020D33C0: .word 0x8F1BBCDC
_020D33C4: .word 0xCA62C1D6

	arm_func_start MATHi_SHA1ProcessBlock
MATHi_SHA1ProcessBlock: ; 0x020D33C8
	stmdb sp!, {r4-r12,lr}
	ldmia r0, {r3,r9-r12}
	sub sp, sp, #0x84
	str r2, [sp, #0x80]
_020D33D8:
	ldr r8, _020D33B8 ; =0x5A827999
	ldr r7, _020D33B4 ; =0x00FF00FF
	mov r6, sp
	mov r5, #0x0
_020D33E8:
	ldr r4, [r1], #0x4
	add r2, r8, r12
	add r2, r2, r3, ror #0x1B
	and lr, r4, r7
	and r4, r7, r4, ror #0x18
	orr r4, r4, lr, ror #0x8
	str r4, [r6, #0x40]
	str r4, [r6], #0x4
	add r2, r2, r4
	eor r4, r10, r11
	and r4, r4, r9
	eor r4, r4, r11
	add r2, r2, r4
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r5, r5, #0x4
	cmp r5, #0x40
	blt _020D33E8
	mov r7, #0x0
	mov r6, sp
_020D3448:
	ldr r2, [r6, #0x0]
	ldr r5, [r6, #0x8]
	ldr r4, [r6, #0x20]
	ldr lr, [r6, #0x34]
	eor r2, r2, r5
	eor r4, r4, lr
	eor r2, r2, r4
	mov r2, r2, ror #0x1F
	str r2, [r6, #0x40]
	str r2, [r6], #0x4
	add r2, r2, r12
	add r2, r2, r8
	add r2, r2, r3, ror #0x1B
	eor r4, r10, r11
	and r4, r4, r9
	eor r4, r4, r11
	add r2, r2, r4
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r7, r7, #0x4
	cmp r7, #0x10
	blt _020D3448
	ldr r8, _020D33BC ; =0x6ED9EBA1
	mov r7, #0x0
_020D34B8:
	ldr r2, [r6, #0x0]
	ldr r4, [r6, #0x8]
	ldr lr, [r6, #0x20]
	ldr r5, [r6, #0x34]
	eor r2, r2, r4
	eor lr, lr, r5
	eor r2, r2, lr
	mov r2, r2, ror #0x1F
	str r2, [r6, #0x40]
	str r2, [r6], #0x4
	add r2, r2, r12
	add r2, r2, r8
	add r2, r2, r3, ror #0x1B
	eor lr, r9, r10
	eor lr, lr, r11
	add r2, r2, lr
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r7, r7, #0x1
	cmp r7, #0xc
	moveq r6, sp
	cmp r7, #0x14
	blt _020D34B8
	ldr r8, _020D33C0 ; =0x8F1BBCDC
	mov r7, #0x0
_020D352C:
	ldr r2, [r6, #0x0]
	ldr lr, [r6, #0x8]
	ldr r5, [r6, #0x20]
	ldr r4, [r6, #0x34]
	eor r2, r2, lr
	eor r5, r5, r4
	eor r2, r2, r5
	mov r2, r2, ror #0x1F
	str r2, [r6, #0x40]
	str r2, [r6], #0x4
	add r2, r2, r12
	add r2, r2, r8
	add r2, r2, r3, ror #0x1B
	orr r5, r9, r10
	and r5, r5, r11
	and r4, r9, r10
	orr r5, r5, r4
	add r2, r2, r5
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r7, r7, #0x1
	cmp r7, #0x8
	moveq r6, sp
	cmp r7, #0x14
	blt _020D352C
	ldr r8, _020D33C4 ; =0xCA62C1D6
	mov r7, #0x0
_020D35A8:
	ldr r2, [r6, #0x0]
	ldr r5, [r6, #0x8]
	ldr r4, [r6, #0x20]
	ldr lr, [r6, #0x34]
	eor r2, r2, r5
	eor r4, r4, lr
	eor r2, r2, r4
	mov r2, r2, ror #0x1F
	str r2, [r6, #0x40]
	str r2, [r6], #0x4
	add r2, r2, r12
	add r2, r2, r8
	add r2, r2, r3, ror #0x1B
	eor r4, r9, r10
	eor r4, r4, r11
	add r2, r2, r4
	mov r9, r9, ror #0x2
	mov r12, r11
	mov r11, r10
	mov r10, r9
	mov r9, r3
	mov r3, r2
	add r7, r7, #0x1
	cmp r7, #0x4
	moveq r6, sp
	cmp r7, #0x14
	blt _020D35A8
	ldmia r0, {r2,r4,r6-r7,lr}
	add r3, r3, r2
	add r9, r9, r4
	add r10, r10, r6
	add r11, r11, r7
	add r12, r12, lr
	stmia r0, {r3,r9-r12}
	ldr lr, [sp, #0x80]
	subs lr, lr, #0x40
	str lr, [sp, #0x80]
	bgt _020D33D8
	add sp, sp, #0x84
	ldmia sp!, {r4-r12,pc}

	arm_func_start CP_SaveContext
CP_SaveContext: ; 0x020D3648
	ldr r1, _020D3684 ; =0x04000290
	stmdb sp!, {r4}
	ldmia r1, {r2-r4,r12}
	stmia r0!, {r2-r4,r12}
	ldrh r12, [r1, #-0x10]
	add r1, r1, #0x28
	ldmia r1, {r2-r3}
	stmia r0!, {r2-r3}
	and r12, r12, #0x3
	ldrh r2, [r1, #-0x8]
	strh r12, [r0, #0x0]
	and r2, r2, #0x1
	strh r2, [r0, #0x2]
	ldmia sp!, {r4}
	bx lr
	.balign 4
_020D3684: .word 0x04000290

	arm_func_start CP_RestoreContext
CP_RestoreContext: ; 0x020D3688
	stmdb sp!, {r4}
	ldr r1, _020D36C0 ; =0x04000290
	ldmia r0, {r2-r4,r12}
	stmia r1, {r2-r4,r12}
	ldrh r2, [r0, #0x18]
	ldrh r3, [r0, #0x1a]
	strh r2, [r1, #-0x10]
	strh r3, [r1, #0x20]
	add r0, r0, #0x10
	add r1, r1, #0x28
	ldmia r0, {r2-r3}
	stmia r1, {r2-r3}
	ldmia sp!, {r4}
	bx lr
	.balign 4
_020D36C0: .word 0x04000290

	arm_func_start TP_CheckError
TP_CheckError: ; 0x020D36C4
	ldr r1, _020D36D4 ; =0x021D5474
	ldrh r1, [r1, #0x34]
	and r0, r1, r0
	bx lr
	.balign 4
_020D36D4: .word 0x021D5474

	arm_func_start TP_WaitBusy
TP_WaitBusy: ; 0x020D36D8
	ldr r1, _020D36EC ; =0x021D5474
_020D36DC:
	ldrh r2, [r1, #0x36]
	ands r2, r2, r0
	bne _020D36DC
	bx lr
	.balign 4
_020D36EC: .word 0x021D5474

	arm_func_start TP_GetCalibratedPoint
TP_GetCalibratedPoint: ; 0x020D36F0
	stmdb sp!, {r4-r6,lr}
	ldr r2, _020D3818 ; =0x021D5474
	ldrh r2, [r2, #0x30]
	cmp r2, #0x0
	bne _020D372C
	ldrh r3, [r1, #0x0]
	ldrh r2, [r1, #0x2]
	strh r3, [r0, #0x0]
	strh r2, [r0, #0x2]
	ldrh r2, [r1, #0x4]
	ldrh r1, [r1, #0x6]
	strh r2, [r0, #0x4]
	strh r1, [r0, #0x6]
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D372C:
	ldrh r3, [r1, #0x4]
	ldr r2, _020D381C ; =0x021D548C
	strh r3, [r0, #0x4]
	ldrh r3, [r1, #0x6]
	strh r3, [r0, #0x6]
	ldrh r3, [r1, #0x4]
	cmp r3, #0x0
	moveq r1, #0x0
	streqh r1, [r0, #0x0]
	streqh r1, [r0, #0x2]
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrh r4, [r1, #0x0]
	ldr r3, [r2, #0x0]
	ldr lr, [r2, #0x8]
	mov r12, r4, lsl #0x2
	mov r4, r12, asr #0x1f
	subs r12, r12, r3
	sbc r3, r4, r3, asr #0x1f
	umull r6, r5, lr, r12
	mla r5, lr, r3, r5
	mov r3, lr, asr #0x1f
	mla r5, r3, r12, r5
	mov r3, r6, lsr #0x16
	orr r3, r3, r5, lsl #0xa
	strh r3, [r0, #0x0]
	ldrsh r3, [r0, #0x0]
	cmp r3, #0x0
	movlt r3, #0x0
	strlth r3, [r0, #0x0]
	blt _020D37B4
	cmp r3, #0xff
	movgt r3, #0xff
	strgth r3, [r0, #0x0]
_020D37B4:
	ldrh r3, [r1, #0x2]
	ldr r1, [r2, #0xc]
	ldr r12, [r2, #0x14]
	mov r3, r3, lsl #0x2
	mov r2, r3, asr #0x1f
	subs r3, r3, r1
	sbc r1, r2, r1, asr #0x1f
	umull r4, lr, r12, r3
	mla lr, r12, r1, lr
	mov r1, r12, asr #0x1f
	mla lr, r1, r3, lr
	mov r1, r4, lsr #0x16
	orr r1, r1, lr, lsl #0xa
	strh r1, [r0, #0x2]
	ldrsh r1, [r0, #0x2]
	cmp r1, #0x0
	movlt r1, #0x0
	strlth r1, [r0, #0x2]
	ldmltia sp!, {r4-r6,lr}
	bxlt lr
	cmp r1, #0xbf
	movgt r1, #0xbf
	strgth r1, [r0, #0x2]
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020D3818: .word 0x021D5474
_020D381C: .word 0x021D548C

	arm_func_start TP_CalcCalibrateParam
TP_CalcCalibrateParam:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r6, r1
	mov r7, r0
	mov r5, r2
	mov r4, r3
	cmp r6, #0x1000
	bhs _020D3860
	cmp r5, #0x1000
	bhs _020D3860
	ldrh r8, [sp, #0x2c]
	cmp r8, #0x1000
	bhs _020D3860
	ldrh r3, [sp, #0x30]
	cmp r3, #0x1000
	blo _020D3870
_020D3860:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D3870:
	cmp r4, #0x100
	bhs _020D389C
	ldrh r2, [sp, #0x34]
	cmp r2, #0x100
	bhs _020D389C
	ldrh r1, [sp, #0x28]
	cmp r1, #0xc0
	bhs _020D389C
	ldrh r0, [sp, #0x38]
	cmp r0, #0xc0
	blo _020D38AC
_020D389C:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D38AC:
	cmp r4, r2
	beq _020D38CC
	cmp r1, r0
	beq _020D38CC
	cmp r6, r8
	beq _020D38CC
	cmp r5, r3
	bne _020D38DC
_020D38CC:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D38DC:
	bl OS_DisableInterrupts
	ldrh r1, [sp, #0x2c]
	ldr r3, _020D3A80 ; =0x04000280
	ldr fp, _020D3A84 ; =0x04000290
	str r1, [sp, #0x0]
	ldr r2, [sp, #0x0]
	ldrh r1, [sp, #0x34]
	sub r9, r6, r2
	mov r2, #0x0
	mov r12, r9, lsl #0x8
	strh r2, [r3, #0x0]
	str r12, [r11, #0x0]
	ldrh r8, [sp, #0x30]
	ldrh r10, [sp, #0x38]
	ldrh r9, [sp, #0x28]
	ldr fp, _020D3A88 ; =0x04000298
	sub r12, r4, r1
	str r12, [r11, #0x0]
	str r2, [r11, #0x4]
	sub r11, r5, r8
	sub r2, r9, r10
_020D3930:
	ldrh r12, [r3, #0x0]
	ands r12, r12, #0x8000
	bne _020D3930
	ldr ip, _020D3A8C ; =0x040002A0
	mov r11, r11, lsl #0x8
	ldr lr, [r12, #0x0]
	mov r12, #0x0
	strh r12, [r3, #0x0]
	ldr r3, _020D3A84 ; =0x04000290
	cmp lr, #0x8000
	str r11, [r3, #0x0]
	ldr r3, _020D3A88 ; =0x04000298
	str r2, [r3, #0x0]
	mov r2, r3
	str r12, [r2, #0x4]
	bge _020D3980
	mov r2, #0x8000
	rsb r2, r2, #0x0
	cmp lr, r2
	bge _020D3994
_020D3980:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D3994:
	strh lr, [r7, #0x4]
	ldrsh r11, [r7, #0x4]
	add r3, r4, r1
	ldr r1, [sp, #0x0]
	add r4, r6, r1
	mul r1, r11, r3
	mov r3, r4, lsl #0x8
	sub r1, r3, r1
	mov r1, r1, lsl #0x9
	mov r1, r1, asr #0x10
	cmp r1, #0x8000
	bge _020D39CC
	cmp r1, r2
	bge _020D39E0
_020D39CC:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D39E0:
	ldr r2, _020D3A80 ; =0x04000280
	strh r1, [r7, #0x0]
_020D39E8:
	ldrh r1, [r2, #0x0]
	ands r1, r1, #0x8000
	bne _020D39E8
	ldr r1, _020D3A8C ; =0x040002A0
	ldr r4, [r1, #0x0]
	bl OS_RestoreInterrupts
	cmp r4, #0x8000
	bge _020D3A18
	mov r0, #0x8000
	rsb r1, r0, #0x0
	cmp r4, r1
	bge _020D3A28
_020D3A18:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D3A28:
	strh r4, [r7, #0x6]
	ldrsh r2, [r7, #0x6]
	add r0, r9, r10
	add r3, r5, r8
	mul r0, r2, r0
	mov r2, r3, lsl #0x8
	sub r0, r2, r0
	mov r0, r0, lsl #0x9
	mov r0, r0, asr #0x10
	cmp r0, #0x8000
	bge _020D3A5C
	cmp r0, r1
	bge _020D3A6C
_020D3A5C:
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r11,lr}
	bx lr
_020D3A6C:
	strh r0, [r7, #0x2]
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020D3A80: .word 0x04000280
_020D3A84: .word 0x04000290
_020D3A88: .word 0x04000298
_020D3A8C: .word 0x040002A0

	arm_func_start TP_GetLatestIndexInAuto
TP_GetLatestIndexInAuto: ; 0x020D3A90
	ldr r0, _020D3A9C ; =0x021D5474
	ldrh r0, [r0, #0xc]
	bx lr
	.balign 4
_020D3A9C: .word 0x021D5474

	arm_func_start TP_GetLatestRawPointInAuto
TP_GetLatestRawPointInAuto: ; 0x020D3AA0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r1, #0x3
	ldr lr, _020D3C10 ; =0x021D5474
	strh r1, [r0, #0x6]
	ldrh r1, [lr, #0xe]
	ldrh r3, [lr, #0xc]
	cmp r1, #0x1
	beq _020D3AD0
	ldrh r1, [lr, #0x14]
	cmp r1, #0x1
	bne _020D3B0C
_020D3AD0:
	ldr r1, _020D3C10 ; =0x021D5474
	mov r2, r3, lsl #0x3
	ldr r1, [r1, #0x10]
	add sp, sp, #0x4
	add r3, r1, r3, lsl #0x3
	ldrh r2, [r1, r2]
	ldrh r1, [r3, #0x2]
	strh r2, [r0, #0x0]
	strh r1, [r0, #0x2]
	ldrh r2, [r3, #0x4]
	ldrh r1, [r3, #0x6]
	strh r2, [r0, #0x4]
	strh r1, [r0, #0x6]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D3B0C:
	add r1, r0, #0x6
	mov r12, #0x0
	b _020D3BE0
_020D3B18:
	subs r5, r3, r12
	ldr r2, [lr, #0x10]
	addmi r5, r5, r4
	add r2, r2, r5, lsl #0x3
	ldrh r4, [r2, #0x4]
	cmp r4, #0x0
	bne _020D3B60
	ldrh r3, [r2, #0x0]
	ldrh r1, [r2, #0x2]
	add sp, sp, #0x4
	strh r3, [r0, #0x0]
	strh r1, [r0, #0x2]
	ldrh r3, [r2, #0x4]
	ldrh r1, [r2, #0x6]
	strh r3, [r0, #0x4]
	strh r1, [r0, #0x6]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D3B60:
	ldrh r4, [r0, #0x6]
	ands r4, r4, #0x1
	beq _020D3B90
	ldrh r4, [r2, #0x6]
	ands r4, r4, #0x1
	bne _020D3B90
	ldrh r4, [r2, #0x0]
	cmp r12, #0x0
	strh r4, [r0, #0x0]
	ldrneh r4, [r1, #0x0]
	bicne r4, r4, #0x1
	strneh r4, [r1, #0x0]
_020D3B90:
	ldrh r4, [r0, #0x6]
	ands r4, r4, #0x2
	beq _020D3BC0
	ldrh r4, [r2, #0x6]
	ands r4, r4, #0x2
	bne _020D3BC0
	ldrh r2, [r2, #0x2]
	cmp r12, #0x0
	strh r2, [r0, #0x2]
	ldrneh r2, [r1, #0x0]
	bicne r2, r2, #0x2
	strneh r2, [r1, #0x0]
_020D3BC0:
	ldrh r2, [r0, #0x6]
	cmp r2, #0x0
	moveq r1, #0x1
	streqh r1, [r0, #0x4]
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	add r12, r12, #0x1
_020D3BE0:
	ldrh r2, [lr, #0xe]
	cmp r12, r2
	bge _020D3BFC
	ldrh r4, [lr, #0x14]
	sub r2, r4, #0x1
	cmp r12, r2
	blt _020D3B18
_020D3BFC:
	mov r1, #0x1
	strh r1, [r0, #0x4]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D3C10: .word 0x021D5474

	arm_func_start TP_RequestAutoSamplingStopAsync
TP_RequestAutoSamplingStopAsync: ; 0x020D3C14
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	mov r4, r0
	ldr r1, _020D3CB0 ; =0x03000200
	mov r0, #0x6
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020D3C30:
	cmp r0, #0x0
	movge r0, #0x1
	movlt r0, #0x0
	cmp r0, #0x0
	bne _020D3C84
	mov r0, r4
	bl OS_RestoreInterrupts
	ldr r0, _020D3CB4
	ldrh r1, [r0, #0x34]
	ldr r3, [r0]
	orr r1, r1, #0x4
	strh r1, [r0, #0x34]
	cmp r3, #0x0
	ldmeqia sp!, {r4, lr}
	bxeq lr
	mov r0, #0x2
	mov r1, #0x4
	mov r2, #0x0
	blx r3
	ldmia sp!, {r4, lr}
	bx lr
_020D3C84:
	ldr r1, _020D3CB4
	mov r0, r4
	ldrh r2, [r1, #0x36]
	orr r2, r2, #0x4
	strh r2, [r1, #0x36]
	ldrh r2, [r1, #0x34]
	bic r2, r2, #0x4
	strh r2, [r1, #0x34]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4, lr}
	bx lr
_020D3CB0: .word 0x03000200
_020D3CB4: .word 0x021D5474

	arm_func_start TP_RequestAutoSamplingStartAsync
TP_RequestAutoSamplingStartAsync: ; 0x020D3CB8
	stmdb sp!, {r4-r6,lr}
	ldr r4, _020D3DC0 ; =0x021D5474
	mov r5, r1
	mov r12, #0x0
	mov r6, r0
	str r2, [r4, #0x10]
	strh r12, [r4, #0xc]
	strh r5, [r4, #0xe]
	strh r3, [r4, #0x14]
	cmp r3, #0x0
	bls _020D3D00
	mov r1, r12
_020D3CE8:
	ldr r0, [r4, #0x10]
	add r0, r0, r12, lsl #0x3
	add r12, r12, #0x1
	strh r1, [r0, #0x4]
	cmp r12, r3
	blo _020D3CE8
_020D3D00:
	bl OS_DisableInterrupts
	mov r4, r0
	ldr r0, _020D3DC4 ; =0x02000100
	and r1, r5, #0xff
	orr r1, r1, r0
	mov r0, #0x6
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020D3D20:
	cmp r0, #0x0
	movlt r0, #0x0
	blt _020D3D4C
	ldr r1, _020D3DC8
	mov r0, #0x6
	orr r1, r6, r1
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movlt r0, #0x0
	movge r0, #0x1
_020D3D4C:
	ands r0, r0, #0xFF
	bne _020D3D94
	mov r0, r4
	bl OS_RestoreInterrupts
	ldr r0, _020D3DC0
	ldrh r1, [r0, #0x34]
	ldr r3, [r0]
	orr r1, r1, #0x2
	strh r1, [r0, #0x34]
	cmp r3, #0x0
	ldmeqia sp!, {r4-r6, lr}
	bxeq lr
	mov r0, #0x1
	mov r1, #0x4
	mov r2, #0x0
	blx r3
	ldmia sp!, {r4-r6, lr}
	bx lr
_020D3D94:
	ldr r1, _020D3DC0
	mov r0, r4
	ldrh r2, [r1, #0x36]
	orr r2, r2, #0x2
	strh r2, [r1, #0x36]
	ldrh r2, [r1, #0x34]
	bic r2, r2, #0x2
	strh r2, [r1, #0x34]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r6, lr}
	bx lr
_020D3DC0: .word 0x021D5474
_020D3DC4: .word 0x02000100
_020D3DC8: .word 0x01010000

	arm_func_start TP_WaitRawResult
TP_WaitRawResult: ; 0x020D3DCC
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x1
	bl TP_WaitBusy
	ldr r1, _020D3E20 ; =0x021D5474
	ldrh r0, [r1, #0x34]
	ands r0, r0, #0x1
	movne r0, #0x1
	ldmneia sp!, {r4,lr}
	bxne lr
	ldrh r3, [r1, #0x4]
	ldrh r2, [r1, #0x6]
	mov r0, #0x0
	strh r3, [r4, #0x0]
	strh r2, [r4, #0x2]
	ldrh r2, [r1, #0x8]
	ldrh r1, [r1, #0xa]
	strh r2, [r4, #0x4]
	strh r1, [r4, #0x6]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D3E20: .word 0x021D5474

	arm_func_start TP_RequestSamplingAsync
TP_RequestSamplingAsync: ; 0x020D3E24
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	mov r4, r0
	mov r0, #0x6
	mov r1, #0x3000000
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020D3E40:
	cmp r0, #0x0
	movge r0, #0x1
	movlt r0, #0x0
	cmp r0, #0x0
	bne _020D3E94
	mov r0, r4
	bl OS_RestoreInterrupts
	ldr r0, _20D3EC0
	ldrh r1, [r0, #0x34]
	ldr r3, [r0]
	orr r1, r1, #0x1
	strh r1, [r0, #0x34]
	cmp r3, #0x0
	ldmeqia sp!, {r4, lr}
	bxeq lr
	mov r0, #0x0
	mov r2, r0
	mov r1, #0x4
	blx r3
	ldmia sp!, {r4, lr}
	bx lr
_020D3E94:
	ldr r1, _20D3EC0
	mov r0, r4
	ldrh r2, [r1, #0x36]
	orr r2, r2, #0x1
	strh r2, [r1, #0x36]
	ldrh r2, [r1, #0x34]
	bic r2, r2, #0x1
	strh r2, [r1, #0x34]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4, lr}
	bx lr
_20D3EC0: .word 0x021D5474

	arm_func_start TP_SetCalibrateParam
TP_SetCalibrateParam: ; 0x020D3EC4
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r4, r0
	ldreq r0, _020D3FF8 ; =0x021D5474
	moveq r1, #0x0
	streqh r1, [r0, #0x30]
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	bl OS_DisableInterrupts
	ldrsh lr, [r4, #0x4]
	cmp lr, #0x0
	beq _020D3F50
	ldr r5, _020D3FFC ; =0x04000280
	mov r12, #0x0
	ldr r2, _020D4000 ; =0x04000290
	strh r12, [r5, #0x0]
	mov r3, #0x10000000
	ldr r1, _020D4004 ; =0x04000298
	str r3, [r2, #0x0]
	str lr, [r1, #0x0]
	str r12, [r1, #0x4]
	ldrsh r2, [r4, #0x0]
	ldr r1, _020D3FF8 ; =0x021D5474
	str r2, [r1, #0x18]
	ldrsh r2, [r4, #0x4]
	str r2, [r1, #0x1c]
_020D3F30:
	ldrh r1, [r5, #0x0]
	ands r1, r1, #0x8000
	bne _020D3F30
	ldr r2, _020D4008 ; =0x040002A0
	ldr r1, _020D3FF8 ; =0x021D5474
	ldr r2, [r2, #0x0]
	str r2, [r1, #0x20]
	b _020D3F64
_020D3F50:
	ldr r1, _020D3FF8 ; =0x021D5474
	mov r2, #0x0
	str r2, [r1, #0x18]
	str r2, [r1, #0x1c]
	str r2, [r1, #0x20]
_020D3F64:
	ldrsh r5, [r4, #0x6]
	cmp r5, #0x0
	beq _020D3FC8
	ldr ip, _020D3FFC ; =0x04000280
	mov lr, #0x0
	ldr r2, _020D4000 ; =0x04000290
	strh lr, [r12, #0x0]
	mov r3, #0x10000000
	ldr r1, _020D4004 ; =0x04000298
	str r3, [r2, #0x0]
	str r5, [r1, #0x0]
	str lr, [r1, #0x4]
	ldrsh r2, [r4, #0x2]
	ldr r1, _020D3FF8 ; =0x021D5474
	str r2, [r1, #0x24]
	ldrsh r2, [r4, #0x6]
	str r2, [r1, #0x28]
_020D3FA8:
	ldrh r1, [r12, #0x0]
	ands r1, r1, #0x8000
	bne _020D3FA8
	ldr r2, _020D4008 ; =0x040002A0
	ldr r1, _020D3FF8 ; =0x021D5474
	ldr r2, [r2, #0x0]
	str r2, [r1, #0x2c]
	b _020D3FDC
_020D3FC8:
	ldr r1, _020D3FF8 ; =0x021D5474
	mov r2, #0x0
	str r2, [r1, #0x24]
	str r2, [r1, #0x28]
	str r2, [r1, #0x2c]
_020D3FDC:
	bl OS_RestoreInterrupts
	ldr r0, _020D3FF8 ; =0x021D5474
	mov r1, #0x1
	strh r1, [r0, #0x30]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D3FF8: .word 0x021D5474
_020D3FFC: .word 0x04000280
_020D4000: .word 0x04000290
_020D4004: .word 0x04000298
_020D4008: .word 0x040002A0

	arm_func_start TP_GetUserInfo
TP_GetUserInfo: ; 0x020D400C
	stmdb sp!, {r4-r6,lr}
	sub sp, sp, #0x18
	ldr ip, _020D40B4 ; =0x027FFC80
	mov r4, r0
	ldrh r1, [r12, #0x58]
	ldrh r2, [r12, #0x5a]
	ldrb r3, [r12, #0x5c]
	cmp r1, #0x0
	ldrb lr, [r12, #0x5d]
	ldrh r6, [r12, #0x5e]
	ldrh r5, [r12, #0x60]
	ldrb r0, [r12, #0x62]
	ldrb r12, [r12, #0x63]
	bne _020D405C
	cmp r6, #0x0
	bne _020D405C
	cmp r2, #0x0
	bne _020D405C
	cmp r5, #0x0
	beq _020D4080
_020D405C:
	str lr, [sp, #0x0]
	str r6, [sp, #0x4]
	str r5, [sp, #0x8]
	str r0, [sp, #0xc]
	mov r0, r4
	str r12, [sp, #0x10]
	bl TP_CalcCalibrateParam
_020D4078:
	cmp r0, #0
	beq _020D40A4
_020D4080:
	mov r0, #0x0
	strh r0, [r4, #0x0]
	strh r0, [r4, #0x2]
	strh r0, [r4, #0x4]
	strh r0, [r4, #0x6]
	add sp, sp, #0x18
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D40A4:
	mov r0, #0x1
	add sp, sp, #0x18
	ldmia sp!, {r4-r6,lr}
	bx lr
_020D40B4: .word 0x027FFC80

	arm_func_start TP_Init
TP_Init: ; 0x020D40B8
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, _020D413C ; =0x021D5470
	ldrh r1, [r0, #0x0]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r1, #0x1
	strh r1, [r0, #0x0]
	bl PXI_Init
	ldr r0, _020D4140 ; =0x021D5474
	mov r1, #0x0
	strh r1, [r0, #0x32]
	strh r1, [r0, #0x36]
	strh r1, [r0, #0xc]
	str r1, [r0, #0x0]
	str r1, [r0, #0x10]
	strh r1, [r0, #0x30]
	strh r1, [r0, #0x34]
	mov r5, #0x6
	mov r4, #0x1
_020D4110:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
_020D411C:
	cmp r0, #0x0
	beq _020D4110
	ldr r1, _020D4144
	mov r0, #0x6
	bl PXI_SetFifoRecvCallback
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D413C: .word 0x021D5470
_020D4140: .word 0x021D5474
_020D4144: .word FUN_020D4148

	arm_func_start FUN_020D4148
FUN_020D4148: ; 0x020D4148
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r0, r1, lsl #0x10
	mov r3, r0, lsr #0x10
	and r0, r3, #0x7f00
	mov r0, r0, lsl #0x8
	cmp r2, #0x0
	mov r0, r0, lsr #0x10
	beq _020D41AC
	ldr r1, _020D43FC ; =0x021D5474
	mov r2, #0x1
	ldrh r4, [r1, #0x34]
	ldr r3, [r1, #0x0]
	orr r2, r4, r2, lsl r0
	cmp r3, #0x0
	strh r2, [r1, #0x34]
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r1, #0x4
	mov r2, #0x0
	blx r3
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020D41AC:
	cmp r0, #0x10
	bne _020D427C
	ldr r1, _020D43FC ; =0x021D5474
	ldrh r3, [r1, #0xc]
	ldrh r2, [r1, #0x14]
	add r3, r3, #0x1
	strh r3, [r1, #0xc]
	ldrh r3, [r1, #0xc]
	cmp r3, r2
	movcs r2, #0x0
	strcsh r2, [r1, #0xc]
	ldr r1, _020D4400 ; =0x027FFFAA
	ldr r2, _020D43FC ; =0x021D5474
	ldrh r3, [r1, #0x0]
	ldr r1, _020D4404 ; =0x027FFFAC
	ldrh r12, [r2, #0xc]
	strh r3, [sp, #0x0]
	ldrh r1, [r1, #0x0]
	ldr r4, [r2, #0x10]
	mov lr, r12, lsl #0x3
	strh r1, [sp, #0x2]
	ldr r3, [sp, #0x0]
	add r1, r4, r12, lsl #0x3
	mov r3, r3, lsl #0x14
	mov r3, r3, lsr #0x14
	strh r3, [r4, lr]
	ldr r3, [sp, #0x0]
	mov r3, r3, lsl #0x8
	mov r3, r3, lsr #0x14
	strh r3, [r1, #0x2]
	ldr r3, [sp, #0x0]
	mov r3, r3, lsl #0x7
	mov r3, r3, lsr #0x1f
	and r3, r3, #0xff
	strh r3, [r1, #0x4]
	ldr r3, [sp, #0x0]
	mov r3, r3, lsl #0x5
	mov r3, r3, lsr #0x1e
	and r3, r3, #0xff
	strh r3, [r1, #0x6]
	ldr r3, [r2, #0x0]
	cmp r3, #0x0
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrh r2, [r2, #0xc]
	mov r1, #0x0
	and r2, r2, #0xff
	blx r3
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020D427C:
	ands r1, r1, #0x1000000
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	and r1, r3, #0xff
	cmp r1, #0x4
	addls pc, pc, r1, lsl #0x2
	b _020D43EC
_020D429C:
	b _020D42B0
	b _020D43EC
	b _020D4390
	b _020D4398
	b _020D4388
_020D42B0:
	cmp r0, #0x0
	beq _020D42D4
	cmp r0, #0x1
	beq _020D4338
	cmp r0, #0x2
	ldreq r1, _020D43FC
	moveq r2, #0x0
	streqh r2, [r1, #0x32]
	b _020D4344
_020D42D4:
	ldr r1, _020D4400
	ldr r3, _020D4404
	ldrh ip, [r1]
	ldr r1, _020D43FC
	mov r2, #0x0
	strh ip, [sp, #0x4]
	ldrh r3, [r3]
	strh r3, [sp, #0x6]
	ldr ip, [sp, #0x4]
	strh r2, [r1, #0x32]
	mov r3, ip, lsl #0x7
	mov r2, ip, lsl #0x5
	mov lr, ip, lsl #0x14
	mov ip, ip, lsl #0x8
	mov r3, r3, lsr #0x1F
	mov r2, r2, lsr #0x1E
	mov lr, lr, lsr #0x14
	mov ip, ip, lsr #0x14
	and r3, r3, #0xFF
	and r2, r2, #0xFF
	strh lr, [r1, #0x4]
	strh ip, [r1, #0x6]
	strh r3, [r1, #0x8]
	strh r2, [r1, #0xA]
	b _020D4344
_020D4338:
	ldr r1, _020D43FC
	mov r2, #0x2
	strh r2, [r1, #0x32]
_020D4344:
	ldr r1, _020D43FC
	mov r2, #0x1
	ldrh ip, [r1, #0x36]
	mvn r2, r2, lsl r0
	ldr r3, [r1]
	and r2, ip, r2
	cmp r3, #0x0
	strh r2, [r1, #0x36]
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4, lr}
	bxeq lr
	mov r1, #0x0
	mov r2, r1
	blx r3
	add sp, sp, #0x8
	ldmia sp!, {r4, lr}
	bx lr
_020D4388:
	mov r4, #0x3
	b _020D439C
_020D4390:
	mov r4, #0x1
	b _020D439C
_020D4398:
	mov r4, #0x2
_020D439C:
	ldr r1, _020D43FC
	mov lr, #0x1
	ldrh ip, [r1, #0x34]
	ldr r3, [r1]
	mvn r2, lr, lsl r0
	orr ip, ip, lr, lsl r0
	strh ip, [r1, #0x34]
	ldrh ip, [r1, #0x36]
	cmp r3, #0x0
	addeq sp, sp, #0x8
	and r2, ip, r2
	strh r2, [r1, #0x36]
	ldmeqia sp!, {r4, lr}
	bxeq lr
	and r1, r4, #0xff
	mov r2, #0x0
	blx r3
	add sp, sp, #0x8
	ldmia sp!, {r4, lr}
	bx lr
_020D43EC:
	bl OS_Terminate
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D43FC: .word 0x021D5474
_020D4400: .word 0x027FFFAA
_020D4404: .word 0x027FFFAC

	arm_func_start MicWaitBusy
MicWaitBusy: ; 0x020D4408
	ldr ip, _020D441C ; =0x021D54B0
_020D440C:
	ldr r0, [r12, #0x0]
	cmp r0, #0x1
	beq _020D440C
	bx lr
	.balign 4
_020D441C: .word 0x021D54B0

	arm_func_start MicGetResultCallback
MicGetResultCallback: ; 0x020D4420
	ldr r1, _020D442C ; =0x021D54B0
	str r0, [r1, #0xc]
	bx lr
	.balign 4
_020D442C: .word 0x021D54B0

	arm_func_start MicStopAutoSampling
MicStopAutoSampling:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D4460 ; =0x03004200
	mov r0, #0x9
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020D4448:
	cmp r0, #0x0
	movge r0, #0x1
	movlt r0, #0x0
	add sp, sp, #4
	ldmfd sp!, {lr}
	bx lr
_020D4460: .word 0x03004200

	arm_func_start MicStartAutoSampling
MicStartAutoSampling: ; 0x020D4464
	stmdb sp!, {r4-r6,lr}
	ldr ip, _020D4584 ; =0x02004100
	mov r6, r0
	mov r5, r1
	mov r4, r2
	orr r1, r3, r12
	mov r0, #0x9
	mov r2, #0x0
	bl PXI_SendWordByFifo
_020D4488:
	cmp r0, #0x0
	movlt r0, #0x0
	ldmltia sp!, {r4-r6, lr}
	bxlt lr
	mov r0, r6, lsr #0x10
	orr r1, r0, #0x10000
	mov r0, #0x9
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movlt r0, #0x0
	ldmltia sp!, {r4-r6, lr}
	bxlt lr
	ldr r1, _020D4588
	mov r0, #0x9
	and r1, r6, r1
	orr r1, r1, #0x20000
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movlt r0, #0x0
	ldmltia sp!, {r4-r6, lr}
	bxlt lr
	mov r0, r5, lsr #0x10
	orr r1, r0, #0x30000
	mov r0, #0x9
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movlt r0, #0x0
	ldmltia sp!, {r4-r6, lr}
	bxlt lr
	ldr r1, _020D4588
	mov r0, #0x9
	and r1, r5, r1
	orr r1, r1, #0x40000
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movlt r0, #0x0
	ldmltia sp!, {r4-r6, lr}
	bxlt lr
	mov r0, r4, lsr #0x10
	orr r1, r0, #0x50000
	mov r0, #0x9
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movlt r0, #0x0
	ldmltia sp!, {r4-r6, lr}
	bxlt lr
	ldr r0, _020D4588
	ldr r1, _020D458C
	and r0, r4, r0
	orr r1, r0, r1
	mov r0, #0x9
	mov r2, #0x0
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movge r0, #0x1
	movlt r0, #0x0
	ldmia sp!, {r4-r6, lr}
	bx lr
_020D4584: .word 0x02004100
_020D4588: .word 0x0000FFFF
_020D458C: .word 0x01060000

	arm_func_start MicDoSampling
MicDoSampling: ; 0x020D4590
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D45C4 ; =0x03004000
	mov r2, #0x0
	orr r1, r0, r1
	mov r0, #0x9
	bl PXI_SendWordByFifo
_020D45AC:
	cmp r0, #0x0
	movge r0, #0x1
	movlt r0, #0x0
	add sp, sp, #0x4
	ldmfd sp!, {lr}
	bx lr
_020D45C4: .word 0x03004000

	arm_func_start MicCommonCallback
MicCommonCallback: ; 0x020D45C8
	stmdb sp!, {r4,lr}
	mov r4, r1
	cmp r2, #0x0
	beq _020D4610
	ldr r0, _020D4700 ; =0x021D54B0
	ldr r2, _020D4700 ; =0x021D54B0
	ldr r1, [r0, #0x0]
	ldr r12, [r2, #0x4]
	cmp r1, #0x0
	movne r1, #0x0
	strne r1, [r0, #0x0]
	cmp r12, #0x0
	beq _020D4610
	ldr r1, [r2, #0x8]
	mov r3, #0x0
	mov r0, #0x6
	str r3, [r2, #0x4]
	blx r12
_020D4610:
	and r0, r4, #0xff
	mov r1, r0, lsl #0x10
	and r2, r4, #0x7f00
	mov r0, r2, lsl #0x8
	mov r1, r1, lsr #0x10
	cmp r1, #0x4
	mov r2, r0, lsr #0x10
	addls pc, pc, r1, lsl #0x2
	b _020D4670
_020D4634:
	b _020D4648
	b _020D4650
	b _020D4658
	b _020D4660
	b _020D4668
_020D4648:
	mov r0, #0x0
	b _020D4674
_020D4650:
	mov r0, #0x4
	b _020D4674
_020D4658:
	mov r0, #0x2
	b _020D4674
_020D4660:
	mov r0, #0x5
	b _020D4674
_020D4668:
	mov r0, #0x1
	b _020D4674
_020D4670:
	mov r0, #0x6
_020D4674:
	cmp r2, #0x51
	bne _020D46A0
	ldr r1, _020D4700 ; =0x021D54B0
	ldr r2, [r1, #0x10]
	cmp r2, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, [r1, #0x14]
	blx r2
	ldmia sp!, {r4,lr}
	bx lr
_020D46A0:
	cmp r2, #0x40
	bne _020D46C0
	ldr r1, _020D4700 ; =0x021D54B0
	ldr r2, [r1, #0x18]
	cmp r2, #0x0
	ldrne r1, _020D4704 ; =0x027FFF94
	ldrneh r1, [r1, #0x0]
	strneh r1, [r2, #0x0]
_020D46C0:
	ldr r1, _020D4700 ; =0x021D54B0
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	movne r2, #0x0
	strne r2, [r1, #0x0]
	ldr r2, _020D4700 ; =0x021D54B0
	ldr r4, [r2, #0x4]
	cmp r4, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, [r2, #0x8]
	mov r3, #0x0
	str r3, [r2, #0x4]
	blx r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020D4700: .word 0x021D54B0
_020D4704: .word 0x027FFF94

	arm_func_start MIC_GetLastSamplingAddress
MIC_GetLastSamplingAddress: ; 0x020D4708
	ldr r0, _020D4714 ; =0x027FFF90
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020D4714: .word 0x027FFF90

	arm_func_start MIC_StopAutoSampling
MIC_StopAutoSampling: ; 0x020D4718
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020D4754 ; =MicGetResultCallback
	mov r1, #0x0
	bl MIC_StopAutoSamplingAsync
	ldr r1, _020D4758 ; =0x021D54B0
	cmp r0, #0x0
	str r0, [r1, #0xc]
	bne _020D4740
	bl MicWaitBusy
_020D4740:
	ldr r0, _020D4758 ; =0x021D54B0
	ldr r0, [r0, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D4754: .word MicGetResultCallback
_020D4758: .word 0x021D54B0

	arm_func_start MIC_StopAutoSamplingAsync
MIC_StopAutoSamplingAsync: ; 0x020D475C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl OS_DisableInterrupts
	ldr r1, _020D47C8 ; =0x021D54B0
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	beq _020D4794
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D4794:
	mov r2, #0x1
	str r2, [r1, #0x0]
	bl OS_RestoreInterrupts
	ldr r0, _020D47C8 ; =0x021D54B0
	str r5, [r0, #0x4]
	str r4, [r0, #0x8]
	bl MicStopAutoSampling
_020D47B0:
	cmp r0, #0x0
	movne r0, #0x0
	moveq r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r5, lr}
	bx lr
_020D47C8: .word 0x021D54B0

	arm_func_start MIC_StartAutoSampling
MIC_StartAutoSampling: ; 0x020D47CC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020D4808 ; =MicGetResultCallback
	mov r2, #0x0
	bl MIC_StartAutoSamplingAsync
	ldr r1, _020D480C ; =0x021D54B0
	cmp r0, #0x0
	str r0, [r1, #0xc]
	bne _020D47F4
	bl MicWaitBusy
_020D47F4:
	ldr r0, _020D480C ; =0x021D54B0
	ldr r0, [r0, #0xc]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020D4808: .word MicGetResultCallback
_020D480C: .word 0x021D54B0

	arm_func_start MIC_StartAutoSamplingAsync
MIC_StartAutoSamplingAsync: ; 0x020D4810
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r0, [r7, #0x4]
	mov r6, r1
	ands r0, r0, #0x1f
	mov r5, r2
	addne sp, sp, #0x4
	movne r0, #0x2
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldr r1, [r7, #0x8]
	ands r0, r1, #0x1f
	addne sp, sp, #0x4
	movne r0, #0x2
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	cmp r1, #0x0
	addeq sp, sp, #0x4
	moveq r0, #0x2
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r0, [r7, #0xc]
	cmp r0, #0x400
	addcc sp, sp, #0x4
	movcc r0, #0x2
	ldmccia sp!, {r4-r7,lr}
	bxcc lr
	ldr r0, [r7, #0x0]
	cmp r0, #0x5
	addls pc, pc, r0, lsl #0x2
	b _020D48D8
_020D4890:
	b _020D48A8
	b _020D48B0
	b _020D48B8
	b _020D48C0
	b _020D48C8
	b _020D48D0
_020D48A8:
	mov r1, #0x0
	b _020D48E8
_020D48B0:
	mov r1, #0x1
	b _020D48E8
_020D48B8:
	mov r1, #0x2
	b _020D48E8
_020D48C0:
	mov r1, #0x3
	b _020D48E8
_020D48C8:
	mov r1, #0x5
	b _020D48E8
_020D48D0:
	mov r1, #0x7
	b _020D48E8
_020D48D8:
	add sp, sp, #0x4
	mov r0, #0x2
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D48E8:
	ldr r0, [r7, #0x10]
	cmp r0, #0x0
	orrne r0, r1, #0x10
	andne r0, r0, #0xff
	andeq r0, r1, #0xff
	and r4, r0, #0xff
	bl OS_DisableInterrupts
	ldr r1, _020D497C
	ldr r2, [r1]
	cmp r2, #0x0
	beq _020D4928
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D4928:
	mov r2, #0x1
	str r2, [r1]
	bl OS_RestoreInterrupts
	ldr r0, _020D497C
	mov r3, r4
	str r6, [r0, #0x4]
	str r5, [r0, #0x8]
	ldr r1, [r7, #0x14]
	str r1, [r0, #0x10]
	ldr r1, [r7, #0x18]
	str r1, [r0, #0x14]
	ldr r0, [r7, #0x4]
	ldr r1, [r7, #0x8]
	ldr r2, [r7, #0xC]
	bl MicStartAutoSampling
	cmp r0, #0x0
	movne r0, #0x0
	moveq r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D497C: .word 0x021D54B0

	arm_func_start MIC_DoSamplingAsync
MIC_DoSamplingAsync: ; 0x020D4980
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	cmp r0, #0x6
	mov r7, r1
	mov r6, r2
	mov r5, r3
	addge sp, sp, #0x4
	movge r0, #0x2
	ldmgeia sp!, {r4-r7,lr}
	bxge lr
	cmp r0, #0x3
	addls pc, pc, r0, lsl #0x2
	b _020D49E4
_020D49B4:
	b _020D49C4
	b _020D49CC
	b _020D49D4
	b _020D49DC
_020D49C4:	
	mov r4, #0x0
	b _020D49F4
_020D49CC:	
	mov r4, #0x1
	b _020D49F4
_020D49D4:	
	mov r4, #0x2
	b _020D49F4
_020D49DC:	
	mov r4, #0x3
	b _020D49F4
_020D49E4:
	add sp, sp, #0x4
	mov r0, #0x2
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D49F4:
	bl OS_DisableInterrupts
	ldr r1, _020D4A58
	ldr r2, [r1]
	cmp r2, #0x0
	beq _020D4A1C
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D4A1C:
	mov r2, #0x1
	str r2, [r1]
	bl OS_RestoreInterrupts
	ldr r1, _020D4A58
	mov r0, r4
	str r6, [r1, #0x4]
	str r5, [r1, #0x8]
	str r7, [r1, #0x18]
	bl MicDoSampling
	cmp r0, #0x0
	movne r0, #0x0
	moveq r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020D4A58: .word 0x021D54B0

	arm_func_start MIC_Init
MIC_Init: ; 0x020D4A5C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _020D4AD8 ; =0x021D54AC
	ldrh r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldr r0, _020D4ADC ; =0x021D54B0
	mov r2, #0x0
	mov r3, #0x1
	strh r3, [r1, #0x0]
	str r2, [r0, #0x0]
	str r2, [r0, #0x4]
	bl PXI_Init
	mov r5, #0x9
	mov r4, #0x1
_020D4AA0:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
_020D4AAC:
	cmp r0, #0x0
	beq _020D4AA0
	ldr r2, _020D4AE0
	mov r3, #0x0
	ldr r1, _020D4AE4
	mov r0, #0x9
	str r3, [r2]
	bl PXI_SetFifoRecvCallback
	add sp, sp, #0x4
	ldmia sp!, {r4-r5, lr}
	bx lr
_020D4AD8: .word 0x021D54AC
_020D4ADC: .word 0x021D54B0
_020D4AE0: .word 0x027FFF90
_020D4AE4: .word MicCommonCallback
