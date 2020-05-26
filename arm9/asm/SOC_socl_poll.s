	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start SOCLi_GetReadBufferOccpiedSize
SOCLi_GetReadBufferOccpiedSize:
	ldr r2, [r0, #0x64]
	mov r3, #0x0
	cmp r2, #0x0
	beq _02099E88
	ldrsb r1, [r0, #0x73]
	cmp r1, #0x1
	bne _02099E6C
	ldr r0, [r2, #0x104]
	cmp r0, #0x0
	ldrneh r3, [r0, #0x4]
	b _02099E88
_02099E6C:
	cmp r1, #0x0
	beq _02099E7C
	cmp r1, #0x4
	bne _02099E88
_02099E7C:
	ldr r1, [r0, #0x44]
	ldr r0, [r2, #0xf8]
	sub r3, r1, r0
_02099E88:
	mov r0, r3
	bx lr

	arm_func_start SOCL_GetStatus
SOCL_GetStatus:
	stmdb sp!, {r4-r6,lr}
	mov r4, #0x0
	mov r5, r0
	bl SOCL_SocketIsInvalid
	cmp r0, #0x0
	orrne r4, r4, #0x80
	bne _02099F60
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x40
	ldrsb r0, [r5, #0x73]
	orrne r4, r4, #0x20
	cmp r0, #0x1
	beq _02099ED0
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x4
	beq _02099F00
_02099ED0:
	bl OS_DisableInterrupts
	mov r6, r0
	mov r0, r5
	bl SOCLi_GetReadBufferOccpiedSize
	cmp r0, #0x0
	mov r0, r5
	orrgt r4, r4, #0x1
	bl SOCLi_GetWriteBufferFreeSize
	cmp r0, #0x0
	mov r0, r6
	orrgt r4, r4, #0x8
	bl OS_RestoreInterrupts
_02099F00:
	ldrsb r0, [r5, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _02099F18
	cmp r0, #0x4
	movne r1, #0x0
_02099F18:
	cmp r1, #0x0
	beq _02099F60
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x4
	beq _02099F48
	ldrb r0, [r5, #0x8]
	cmp r0, #0x4
	beq _02099F48
	ands r0, r4, #0x1
	ldreqsh r0, [r5, #0x70]
	biceq r0, r0, #0x6
	streqh r0, [r5, #0x70]
_02099F48:
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x2
	bne _02099F60
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x4
	orreq r4, r4, #0x40
_02099F60:
	mov r0, r4
	ldmia sp!, {r4-r6,lr}
	bx lr
