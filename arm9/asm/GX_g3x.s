    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start GXi_NopClearFifo128_
GXi_NopClearFifo128_: ; 0x020C7970
	mov r1, #0x0
	mov r2, #0x0
	mov r3, #0x0
	mov r12, #0x0
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	stmia r0, {r1-r3,r12}
	bx lr

	arm_func_start G3X_SetHOffset
G3X_SetHOffset: ; 0x020C7A04
	ldr r1, _020C7A10 ; =0x04000010
	str r0, [r1, #0x0]
	bx lr
	.balign 4
_020C7A10: .word 0x04000010

	arm_func_start G3X_GetBoxTestResult
G3X_GetBoxTestResult: ; 0x020C7A14
	ldr r2, _020C7A38 ; =0x04000600
	ldr r1, [r2, #0x0]
	ands r1, r1, #0x1
	ldreq r1, [r2, #0x0]
	mvnne r0, #0x0
	andeq r1, r1, #0x2
	streq r1, [r0, #0x0]
	moveq r0, #0x0
	bx lr
	.balign 4
_020C7A38: .word 0x04000600

	arm_func_start G3X_GetMtxStackLevelPJ
G3X_GetMtxStackLevelPJ:
	ldr r2, _020C7A64 ; =0x04000600
	ldr r1, [r2, #0x0]
	ands r1, r1, #0x4000
	ldreq r1, [r2, #0x0]
	mvnne r0, #0x0
	andeq r1, r1, #0x2000
	moveq r1, r1, lsr #0xd
	streq r1, [r0, #0x0]
	moveq r0, #0x0
	bx lr
	.balign 4
_020C7A64: .word 0x04000600

	arm_func_start G3X_GetMtxStackLevelPV
G3X_GetMtxStackLevelPV:
	ldr r2, _020C7A90 ; =0x04000600
	ldr r1, [r2, #0x0]
	ands r1, r1, #0x4000
	ldreq r1, [r2, #0x0]
	mvnne r0, #0x0
	andeq r1, r1, #0x1f00
	moveq r1, r1, lsr #0x8
	streq r1, [r0, #0x0]
	moveq r0, #0x0
	bx lr
	.balign 4
_020C7A90: .word 0x04000600

	arm_func_start G3X_InitTable
G3X_InitTable: ; 0x020C7A94
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r0, _020C7B2C ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C7AE4
	mov r2, #0x0
	str r2, [sp, #0x0]
	ldr r1, _020C7B30 ; =0x04000330
	mov r3, #0x10
	str r2, [sp, #0x4]
	bl MI_DmaFill32Async
	ldr r0, _020C7B2C ; =0x02106814
	ldr r1, _020C7B34 ; =0x04000360
	ldr r0, [r0, #0x0]
	mov r2, #0x0
	mov r3, #0x60
	bl MI_DmaFill32
	b _020C7B04
_020C7AE4:
	ldr r1, _020C7B30 ; =0x04000330
	mov r0, #0x0
	mov r2, #0x10
	bl MIi_CpuClear32
	ldr r1, _020C7B34 ; =0x04000360
	mov r0, #0x0
	mov r2, #0x60
	bl MIi_CpuClear32
_020C7B04:
	mov r2, #0x0
	ldr r0, _020C7B38 ; =0x040004D0
	mov r1, r2
_020C7B10:
	add r2, r2, #0x1
	str r1, [r0, #0x0]
	cmp r2, #0x20
	blt _020C7B10
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C7B2C: .word 0x02106814
_020C7B30: .word 0x04000330
_020C7B34: .word 0x04000360
_020C7B38: .word 0x040004D0

	arm_func_start G3X_SetClearColor
G3X_SetClearColor: ; 0x020C7B3C
	orr r0, r0, r1, lsl #0x10
	ldr r12, [sp, #0x0]
	orr r3, r0, r3, lsl #0x18
	cmp r12, #0x0
	ldr r1, _020C7B64 ; =0x04000350
	orrne r3, r3, #0x8000
	ldr r0, _020C7B68 ; =0x04000354
	str r3, [r1, #0x0]
	strh r2, [r0, #0x0]
	bx lr
	.balign 4
_020C7B64: .word 0x04000350
_020C7B68: .word 0x04000354

	arm_func_start G3X_SetFogTable
G3X_SetFogTable: ; 0x020C7B6C
	ldr ip, _020C7B78 ; =0x020CE2C4
	ldr r1, _020C7B7C ; =0x04000360
	bx r12
	.balign 4
_020C7B78: .word 0x020CE2C4
_020C7B7C: .word 0x04000360

	arm_func_start G3X_SetEdgeColorTable
G3X_SetEdgeColorTable: ; 0x020C7B80
	ldr ip, _020C7B90 ; =MIi_CpuCopy16
	ldr r1, _020C7B94 ; =0x04000330
	mov r2, #0x10
	bx r12
	.balign 4
_020C7B90: .word MIi_CpuCopy16
_020C7B94: .word 0x04000330

	arm_func_start G3X_GetVectorMtx
G3X_GetVectorMtx:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020C7BD8 ; =0x04000600
	mov r1, r0
	ldr r0, [r2, #0x0]
	ands r0, r0, #0x8000000
	addne sp, sp, #0x4
	mvnne r0, #0x0
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020C7BDC ; =0x04000680
	bl MI_Copy36B
_020C7BC8: ; 0x020C7BC8
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C7BD8: .word 0x04000600
_020C7BDC: .word 0x04000680

	arm_func_start G3X_GetClipMtx
G3X_GetClipMtx:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020C7C20 ; =0x04000600
	mov r1, r0
	ldr r0, [r2, #0x0]
	ands r0, r0, #0x8000000
	addne sp, sp, #0x4
	mvnne r0, #0x0
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020C7C24 ; =0x04000640
	bl MI_Copy64B
_020C7C10: ; 0x020C7C10
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C7C20: .word 0x04000600
_020C7C24: .word 0x04000640

	arm_func_start G3X_SetFog
G3X_SetFog: ; 0x020C7C28
	cmp r0, #0x0
	ldreq r2, _020C7C70 ; =0x04000060
	ldreq r0, _020C7C74 ; =0x0000CF7F
	ldreqh r1, [r2, #0x0]
	andeq r0, r1, r0
	streqh r0, [r2, #0x0]
	bxeq lr
	ldr r0, _020C7C78 ; =0x0400035C
	ldr ip, _020C7C70 ; =0x04000060
	strh r3, [r0, #0x0]
	mov r0, r2, lsl #0x8
	orr r0, r0, r1, lsl #0x6
	ldrh r3, [r12, #0x0]
	orr r0, r0, #0x80
	bic r1, r3, #0x3f40
	orr r0, r1, r0
	strh r0, [r12, #0x0]
	bx lr
	.balign 4
_020C7C70: .word 0x04000060
_020C7C74: .word 0x0000CF7F
_020C7C78: .word 0x0400035C

	arm_func_start G3X_ResetMtxStack_2
G3X_ResetMtxStack_2: ; 0x020C7C7C
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r1, _020C7D18 ; =0x04000600
	ldr r0, [r1, #0x0]
	orr r0, r0, #0x8000
	str r0, [r1, #0x0]
	add r4, sp, #0x0
_020C7C98:
	mov r0, r4
	bl G3X_GetMtxStackLevelPV
_020C7CA0: ; 0x020C7CA0
	cmp r0, #0x0
	bne _020C7C98
	add r4, sp, #0x4
_020C7CAC:
	mov r0, r4
	bl G3X_GetMtxStackLevelPJ
_020C7CB4: ; 0x020C7CB4
	cmp r0, #0x0
	bne _020C7CAC
	ldr r2, _020C7D1C ; =0x04000440
	mov r1, #0x3
	str r1, [r2, #0x0]
	ldr r0, _020C7D20 ; =0x04000454
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r2, #0x0]
	ldr r1, [sp, #0x4]
	cmp r1, #0x0
	ldrne r0, _020C7D24 ; =0x04000448
	strne r1, [r0, #0x0]
	ldr r0, _020C7D1C ; =0x04000440
	mov r1, #0x2
	str r1, [r0, #0x0]
	ldr r2, [sp, #0x0]
	ldr r1, _020C7D24 ; =0x04000448
	ldr r0, _020C7D20 ; =0x04000454
	str r2, [r1, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C7D18: .word 0x04000600
_020C7D1C: .word 0x04000440
_020C7D20: .word 0x04000454
_020C7D24: .word 0x04000448

	arm_func_start G3X_InitMtxStack
G3X_InitMtxStack: ; 0x020C7D28
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r1, _020C7DC8 ; =0x04000600
	ldr r0, [r1, #0x0]
	orr r0, r0, #0x8000
	str r0, [r1, #0x0]
	add r4, sp, #0x0
_020C7D44:
	mov r0, r4
	bl G3X_GetMtxStackLevelPV
_020C7D4C: ; 0x020C7D4C
	cmp r0, #0x0
	bne _020C7D44
	add r4, sp, #0x4
_020C7D58:
	mov r0, r4
	bl G3X_GetMtxStackLevelPJ
_020C7D60: ; 0x020C7D60
	cmp r0, #0x0
	bne _020C7D58
	ldr r2, _020C7DCC ; =0x04000440
	mov r1, #0x3
	str r1, [r2, #0x0]
	ldr r0, _020C7DD0 ; =0x04000454
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r2, #0x0]
	ldr r1, [sp, #0x4]
	ldr r2, _020C7DD0 ; =0x04000454
	cmp r1, #0x0
	ldrne r0, _020C7DD4 ; =0x04000448
	mov r3, #0x0
	strne r1, [r0, #0x0]
	ldr r0, _020C7DCC ; =0x04000440
	str r3, [r2, #0x0]
	mov r1, #0x2
	str r1, [r0, #0x0]
	ldr r1, [sp, #0x0]
	ldr r0, _020C7DD4 ; =0x04000448
	str r1, [r0, #0x0]
	str r3, [r2, #0x0]
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C7DC8: .word 0x04000600
_020C7DCC: .word 0x04000440
_020C7DD0: .word 0x04000454
_020C7DD4: .word 0x04000448

	arm_func_start G3X_ClearFifo
G3X_ClearFifo: ; 0x020C7DD8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C7E04 ; =0x04000400
	bl GXi_NopClearFifo128_
	ldr r1, _020C7E08 ; =0x04000600
_020C7DEC:
	ldr r0, [r1, #0x0]
	ands r0, r0, #0x8000000
	bne _020C7DEC
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C7E04: .word 0x04000400
_020C7E08: .word 0x04000600

	arm_func_start G3X_ResetMtxStack
G3X_ResetMtxStack: ; 0x020C7E0C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020C7E7C ; =0x04000600
_020C7E18:
	ldr r0, [r2, #0x0]
	ands r0, r0, #0x8000000
	bne _020C7E18
	ldr r0, [r2, #0x0]
	ldr r1, _020C7E80 ; =0x04000060
	orr r0, r0, #0x8000
	str r0, [r2, #0x0]
	ldrh r0, [r1, #0x0]
	orr r0, r0, #0x2000
	strh r0, [r1, #0x0]
	ldrh r0, [r1, #0x0]
	orr r0, r0, #0x1000
	strh r0, [r1, #0x0]
	bl G3X_ResetMtxStack_2
	ldr r2, _020C7E84 ; =0x001F0080
	ldr r0, _020C7E88 ; =0x040004A4
	ldr r1, _020C7E8C ; =0x040004A8
	str r2, [r0, #0x0]
	mov r2, #0x0
	ldr r0, _020C7E90 ; =0x040004AC
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C7E7C: .word 0x04000600
_020C7E80: .word 0x04000060
_020C7E84: .word 0x001F0080
_020C7E88: .word 0x040004A4
_020C7E8C: .word 0x040004A8
_020C7E90: .word 0x040004AC

	arm_func_start G3X_Init
G3X_Init: ; 0x020C7E94
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl G3X_ClearFifo
	ldr r0, _020C7FAC ; =0x04000504
	mov r1, #0x0
	str r1, [r0, #0x0]
	ldr r1, _020C7FB0 ; =0x04000600
_020C7EB0:
	ldr r0, [r1, #0x0]
	ands r0, r0, #0x8000000
	bne _020C7EB0
	ldr r0, _020C7FB4 ; =0x04000060
	mov r3, #0x0
	strh r3, [r0, #0x0]
	ldr r2, _020C7FB8 ; =0x04000010
	str r3, [r1, #0x0]
	str r3, [r2, #0x0]
	ldrh r12, [r0, #0x0]
	ldr r2, _020C7FBC ; =0xFFFFCFFD
	ldr r3, _020C7FC0 ; =0x0000CFFB
	orr r12, r12, #0x2000
	strh r12, [r0, #0x0]
	ldrh r12, [r0, #0x0]
	orr r12, r12, #0x1000
	strh r12, [r0, #0x0]
	ldrh r12, [r0, #0x0]
	and r2, r12, r2
	strh r2, [r0, #0x0]
	ldrh r2, [r0, #0x0]
	bic r2, r2, #0x3000
	orr r2, r2, #0x10
	strh r2, [r0, #0x0]
	ldrh r2, [r0, #0x0]
	and r2, r2, r3
	strh r2, [r0, #0x0]
	ldr r0, [r1, #0x0]
	orr r0, r0, #0x8000
	str r0, [r1, #0x0]
	ldr r0, [r1, #0x0]
	bic r0, r0, #0xc0000000
	orr r0, r0, #0x80000000
	str r0, [r1, #0x0]
	bl G3X_InitMtxStack
	ldr r0, _020C7FC4 ; =0x04000350
	mov r3, #0x0
	ldr r2, _020C7FC8 ; =0x00007FFF
	ldr r1, _020C7FCC ; =0x04000354
	str r3, [r0, #0x0]
	ldr r0, _020C7FD0 ; =0x04000356
	strh r2, [r1, #0x0]
	ldr r1, _020C7FD4 ; =0x04000358
	strh r3, [r0, #0x0]
	ldr r0, _020C7FD8 ; =0x0400035C
	str r3, [r1, #0x0]
	ldr r1, _020C7FDC ; =0x04000008
	strh r3, [r0, #0x0]
	ldrh r0, [r1, #0x0]
	bic r0, r0, #0x3
	strh r0, [r1, #0x0]
	bl G3X_InitTable
	ldr r2, _020C7FE0 ; =0x001F0080
	ldr r0, _020C7FE4 ; =0x040004A4
	ldr r1, _020C7FE8 ; =0x040004A8
	str r2, [r0, #0x0]
	mov r2, #0x0
	ldr r0, _020C7FEC ; =0x040004AC
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C7FAC: .word 0x04000504
_020C7FB0: .word 0x04000600
_020C7FB4: .word 0x04000060
_020C7FB8: .word 0x04000010
_020C7FBC: .word 0xFFFFCFFD
_020C7FC0: .word 0x0000CFFB
_020C7FC4: .word 0x04000350
_020C7FC8: .word 0x00007FFF
_020C7FCC: .word 0x04000354
_020C7FD0: .word 0x04000356
_020C7FD4: .word 0x04000358
_020C7FD8: .word 0x0400035C
_020C7FDC: .word 0x04000008
_020C7FE0: .word 0x001F0080
_020C7FE4: .word 0x040004A4
_020C7FE8: .word 0x040004A8
_020C7FEC: .word 0x040004AC
