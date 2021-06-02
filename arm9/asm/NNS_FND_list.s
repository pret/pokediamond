	.include "asm/macros.inc"
	.include "global.inc"
	.text

	arm_func_start NNS_FndGetPrevListObject
NNS_FndGetPrevListObject: ; 0x020ADA84
	cmp r1, #0x0
	ldreq r0, [r0, #0x4]
	ldrneh r0, [r0, #0xa]
	ldrne r0, [r1, r0]
	bx lr
	arm_func_end NNS_FndGetPrevListObject

	arm_func_start NNS_FndGetNextListObject
NNS_FndGetNextListObject: ; 0x020ADA98
	cmp r1, #0x0
	ldreq r0, [r0, #0x0]
	ldrneh r0, [r0, #0xa]
	addne r0, r1, r0
	ldrne r0, [r0, #0x4]
	bx lr
	arm_func_end NNS_FndGetNextListObject

	arm_func_start NNS_FndRemoveListObject
NNS_FndRemoveListObject: ; 0x020ADAB0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r12, [r0, #0xa]
	ldr r3, [r1, r12]
	add lr, r1, r12
	cmp r3, #0x0
	ldreq r1, [lr, #0x4]
	streq r1, [r0, #0x0]
	ldrne r2, [lr, #0x4]
	addne r1, r3, r12
	strne r2, [r1, #0x4]
	ldr r3, [lr, #0x4]
	cmp r3, #0x0
	ldreq r1, [lr, #0x0]
	streq r1, [r0, #0x4]
	ldrneh r1, [r0, #0xa]
	ldrne r2, [lr, #0x0]
	strne r2, [r3, r1]
	mov r1, #0x0
	str r1, [lr, #0x0]
	str r1, [lr, #0x4]
	ldrh r1, [r0, #0x8]
	sub r1, r1, #0x1
	strh r1, [r0, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_FndRemoveListObject

	arm_func_start NNS_FndInsertListObject
NNS_FndInsertListObject: ; 0x020ADB18
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0x0
	bne _020ADB38
	mov r1, r2
	bl NNS_FndAppendListObject
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020ADB38:
	ldr r3, [r0, #0x0]
	cmp r1, r3
	bne _020ADB54
	mov r1, r2
	bl NNS_FndPrependListObject
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020ADB54:
	ldrh lr, [r0, #0xa]
	ldr r3, [r1, lr]
	add r12, r2, lr
	str r3, [r2, lr]
	str r1, [r12, #0x4]
	add r3, r3, lr
	str r2, [r3, #0x4]
	ldrh r3, [r0, #0xa]
	str r2, [r1, r3]
	ldrh r1, [r0, #0x8]
	add r1, r1, #0x1
	strh r1, [r0, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_FndInsertListObject

	arm_func_start NNS_FndPrependListObject
NNS_FndPrependListObject: ; 0x020ADB8C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	bne _020ADBAC
	bl SetFirstObject
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020ADBAC:
	ldrh r3, [r0, #0xa]
	mov r2, #0x0
	str r2, [r1, r3]
	ldr r2, [r0, #0x0]
	add r3, r1, r3
	str r2, [r3, #0x4]
	ldrh r2, [r0, #0xa]
	ldr r3, [r0, #0x0]
	str r1, [r3, r2]
	str r1, [r0, #0x0]
	ldrh r1, [r0, #0x8]
	add r1, r1, #0x1
	strh r1, [r0, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_FndPrependListObject

	arm_func_start NNS_FndAppendListObject
NNS_FndAppendListObject: ; 0x020ADBE8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x0]
	cmp r2, #0x0
	bne _020ADC08
	bl SetFirstObject
	add sp, sp, #0x4
	ldmia sp!, {pc}
_020ADC08:
	ldrh r12, [r0, #0xa]
	ldr r3, [r0, #0x4]
	mov r2, #0x0
	str r3, [r1, r12]
	add r3, r1, r12
	str r2, [r3, #0x4]
	ldrh r2, [r0, #0xa]
	ldr r3, [r0, #0x4]
	add r2, r3, r2
	str r1, [r2, #0x4]
	str r1, [r0, #0x4]
	ldrh r1, [r0, #0x8]
	add r1, r1, #0x1
	strh r1, [r0, #0x8]
	add sp, sp, #0x4
	ldmia sp!, {pc}
	arm_func_end NNS_FndAppendListObject

	arm_func_start SetFirstObject
SetFirstObject: ; 0x020ADC48
	ldrh r3, [r0, #0xa]
	mov r2, #0x0
	add r12, r1, r3
	str r2, [r12, #0x4]
	str r2, [r1, r3]
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	ldrh r1, [r0, #0x8]
	add r1, r1, #0x1
	strh r1, [r0, #0x8]
	bx lr
	arm_func_end SetFirstObject

	arm_func_start NNS_FndInitList
NNS_FndInitList: ; 0x020ADC74
	mov r2, #0x0
	str r2, [r0, #0x0]
	str r2, [r0, #0x4]
	strh r2, [r0, #0x8]
	strh r1, [r0, #0xa]
	bx lr
	arm_func_end NNS_FndInitList
