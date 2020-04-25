	.include "asm/macros.inc"
	.include "global.inc"

	.section .dtcm
	.balign 16, 0
	.global OS_IRQTable
OS_IRQTable: ; 027E0000 ;10b6a0
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OSi_IrqTimer0 ; 020c9cbc
	.word OSi_IrqTimer1 ; 020c9cac
	.word OSi_IrqTimer2 ; 020c9c9c
	.word OSi_IrqTimer3 ; 020c9c8c
	.word OS_IrqDummy ; 020c9da8
	.word OSi_IrqDma0 ; 020c9cfc
	.word OSi_IrqDma1 ; 020c9cec
	.word OSi_IrqDma2 ; 020c9cdc
	.word OSi_IrqDma3 ; 020c9ccc
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.word OS_IrqDummy ; 020c9da8
	.balign 16, 0
OSi_IrqThreadQueue: ; 027E0060

	.section .text

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
	ldr r0, _020CC3F8 ; =0x01FF7780
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
	bl OSi_DoResetSystem
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
