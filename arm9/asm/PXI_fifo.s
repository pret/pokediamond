	.include "asm/macros.inc"
	.include "global.inc"

	.extern UNK_021D5364
	.extern UNK_021D5368

	.text

	arm_func_start PXIi_HandlerRecvFifoNotEmpty
PXIi_HandlerRecvFifoNotEmpty: ; 0x020CFBBC
	stmdb sp!, {r4-r10,lr}
	sub sp, sp, #0x8
	ldr sl, _020CFCD4 ; =0x04000184
	ldr r5, _020CFCD8 ; =UNK_021D5368
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
_020CFCD8: .word UNK_021D5368
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
	ldr r1, _020CFE20 ; =UNK_021D5368
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
_020CFE20: .word UNK_021D5368
_020CFE24: .word 0x027FFC00

	arm_func_start PXI_InitFifo
PXI_InitFifo: ; 0x020CFE28
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r1, _020CFF18 ; =UNK_021D5364
	mov r4, r0
	ldrh r0, [r1, #0x0]
	cmp r0, #0x0
	bne _020CFF04
	mov r2, #0x1
	ldr r0, _020CFF1C ; =0x027FFC00
	strh r2, [r1, #0x0]
	mov r2, #0x0
	str r2, [r0, #0x388]
	ldr r0, _020CFF20 ; =UNK_021D5368
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
_020CFF18: .word UNK_021D5364
_020CFF1C: .word 0x027FFC00
_020CFF20: .word UNK_021D5368
_020CFF24: .word 0x0000C408
_020CFF28: .word 0x04000184
_020CFF2C: .word PXIi_HandlerRecvFifoNotEmpty
_020CFF30: .word 0x04000180
