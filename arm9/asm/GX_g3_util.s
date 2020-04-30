    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start G3_RotZ
G3_RotZ: ; 0x020C7FF0
	ldr r3, _020C8028 ; =0x04000468
	mov r2, #0x0
	str r1, [r3, #0x0]
	str r0, [r3, #0x0]
	str r2, [r3, #0x0]
	rsb r0, r0, #0x0
	str r0, [r3, #0x0]
	str r1, [r3, #0x0]
	str r2, [r3, #0x0]
	str r2, [r3, #0x0]
	str r2, [r3, #0x0]
	mov r0, #0x1000
	str r0, [r3, #0x0]
	bx lr
	.balign 4
_020C8028: .word 0x04000468

	arm_func_start G3_RotY
G3_RotY: ; 0x020C802C
	ldr ip, _020C8064 ; =0x04000468
	mov r3, #0x0
	str r1, [r12, #0x0]
	str r3, [r12, #0x0]
	rsb r2, r0, #0x0
	str r2, [r12, #0x0]
	str r3, [r12, #0x0]
	mov r2, #0x1000
	str r2, [r12, #0x0]
	str r3, [r12, #0x0]
	str r0, [r12, #0x0]
	str r3, [r12, #0x0]
	str r1, [r12, #0x0]
	bx lr
	.balign 4
_020C8064: .word 0x04000468

	arm_func_start G3_RotX
G3_RotX: ; 0x020C8068
	ldr r3, _020C80A0 ; =0x04000468
	mov r2, #0x1000
	str r2, [r3, #0x0]
	mov r2, #0x0
	str r2, [r3, #0x0]
	str r2, [r3, #0x0]
	str r2, [r3, #0x0]
	str r1, [r3, #0x0]
	str r0, [r3, #0x0]
	str r2, [r3, #0x0]
	rsb r0, r0, #0x0
	str r0, [r3, #0x0]
	str r1, [r3, #0x0]
	bx lr
	.balign 4
_020C80A0: .word 0x04000468

	arm_func_start G3i_LookAt_
G3i_LookAt_: ; 0x020C80A4
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x24
	mov r9, r0
	ldr r6, [r9, #0x0]
	ldr r5, [r2, #0x0]
	add r0, sp, #0x0
	sub r5, r6, r5
	str r5, [sp, #0x0]
	ldr r7, [r9, #0x4]
	ldr r6, [r2, #0x4]
	mov r5, r1
	sub r1, r7, r6
	str r1, [sp, #0x4]
	ldr r6, [r9, #0x8]
	ldr r2, [r2, #0x8]
	mov r1, r0
	sub r2, r6, r2
	mov r8, r3
	str r2, [sp, #0x8]
	ldr r7, [sp, #0x40]
	bl VEC_Normalize
	add r1, sp, #0x0
	add r2, sp, #0xc
	mov r0, r5
	bl VEC_CrossProduct
	add r0, sp, #0xc
	mov r1, r0
	bl VEC_Normalize
_020C8114: ; 0x020C8114
	add r0, sp, #0x0
	add r1, sp, #0xc
	add r2, sp, #0x18
	bl VEC_CrossProduct
_020C8124: ; 0x020C8124
	cmp r8, #0x0
	beq _020C8184
	ldr r0, _020C8234 ; =0x04000440
	mov r1, #0x2
	str r1, [r0, #0x0]
	ldr r0, [sp, #0xc]
	ldr r4, _020C8238 ; =0x0400045C
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x18]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x0]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x10]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x1c]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x4]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x14]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x20]
	str r0, [r4, #0x0]
	ldr r0, [sp, #0x8]
	str r0, [r4, #0x0]
_020C8184:
	add r1, sp, #0xc
	mov r0, r9
	bl VEC_DotProduct
	rsb r6, r0, #0x0
	add r1, sp, #0x18
	mov r0, r9
	bl VEC_DotProduct
	rsb r5, r0, #0x0
	add r1, sp, #0x0
	mov r0, r9
	bl VEC_DotProduct
_020C81B0: ; 0x020C81B0
	cmp r8, #0x0
	strne r6, [r4, #0x0]
	rsb r0, r0, #0x0
	strne r5, [r4, #0x0]
	strne r0, [r4, #0x0]
	cmp r7, #0x0
	addeq sp, sp, #0x24
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r1, [sp, #0xc]
	str r1, [r7, #0x0]
	ldr r1, [sp, #0x18]
	str r1, [r7, #0x4]
	ldr r1, [sp, #0x0]
	str r1, [r7, #0x8]
	ldr r1, [sp, #0x10]
	str r1, [r7, #0xc]
	ldr r1, [sp, #0x1c]
	str r1, [r7, #0x10]
	ldr r1, [sp, #0x4]
	str r1, [r7, #0x14]
	ldr r1, [sp, #0x14]
	str r1, [r7, #0x18]
	ldr r1, [sp, #0x20]
	str r1, [r7, #0x1c]
	ldr r1, [sp, #0x8]
	str r1, [r7, #0x20]
	str r6, [r7, #0x24]
	str r5, [r7, #0x28]
	str r0, [r7, #0x2c]
	add sp, sp, #0x24
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020C8234: .word 0x04000440
_020C8238: .word 0x0400045C

	arm_func_start G3i_OrthoW_
G3i_OrthoW_: ; 0x020C823C
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x34
	str r2, [sp, #0x8]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x8]
	mov r2, r3
	ldr r7, [sp, #0x64]
	sub r0, r2, r0
	str r3, [sp, #0xc]
	str r1, [sp, #0x4]
	ldr r8, [sp, #0x60]
	ldr r6, [sp, #0x68]
	bl FX_InvAsync
_020C8270: ; 0x020C8270
	cmp r7, #0x0
	ldrne r0, _020C8528 ; =0x04000440
	movne r1, #0x0
	ldrne r4, _020C852C ; =0x04000458
	strne r1, [r0, #0x0]
	cmp r6, #0x0
	beq _020C82B8
	mov r0, #0x0
	str r0, [r6, #0x4]
	str r0, [r6, #0x8]
	str r0, [r6, #0xc]
	str r0, [r6, #0x10]
	str r0, [r6, #0x18]
	str r0, [r6, #0x1c]
	str r0, [r6, #0x20]
	str r0, [r6, #0x24]
	str r0, [r6, #0x2c]
	str r8, [r6, #0x3c]
_020C82B8:
	bl FX_GetDivResultFx64c
	mov r5, r0
	str r1, [sp, #0x14]
	ldr sb, _020C8530 ; =0x04000290
	mov r3, #0x0
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	str r3, [r9, #0x0]
	mov r2, #0x1000
	sub r1, r1, r0
	ldr r0, _020C8534 ; =0x04000298
	str r2, [r9, #0x4]
	str r1, [r0, #0x0]
	cmp r8, #0x1000
	str r3, [r0, #0x4]
	beq _020C8318
	mov r9, r8, asr #0x1f
	umull r0, r1, r5, r8
	mla r1, r5, r9, r1
	ldr r5, [sp, #0x14]
	mla r1, r5, r8, r1
	bl _ll_sdiv
	mov r5, r0
	str r1, [sp, #0x14]
_020C8318:
	ldr r0, [sp, #0x14]
	mov r2, r5, lsl #0xd
	mov r1, r0, lsl #0xd
	mov r0, #0x80000000
	adds r0, r2, r0
	orr r1, r1, r5, lsr #0x13
	adc r1, r1, #0x0
	cmp r7, #0x0
	mov r0, #0x0
	strne r1, [r4, #0x0]
	strne r0, [r4, #0x0]
	strne r0, [r4, #0x0]
	strne r0, [r4, #0x0]
	strne r0, [r4, #0x0]
	cmp r6, #0x0
	strne r1, [r6, #0x0]
	bl FX_GetDivResultFx64c
	mov r11, r0
	str r1, [sp, #0x2c]
	ldr r0, _020C8530 ; =0x04000290
	mov r3, #0x0
	mov r2, #0x1000
	str r3, [r0, #0x0]
	str r2, [r0, #0x4]
	ldr r9, [sp, #0x58]
	ldr r1, [sp, #0x5c]
	ldr r0, _020C8534 ; =0x04000298
	sub r1, r9, r1
	str r1, [r0, #0x0]
	cmp r8, #0x1000
	str r3, [r0, #0x4]
	beq _020C83B8
	mov r9, r8, asr #0x1f
	umull r0, r1, r11, r8
	mla r1, r11, r9, r1
	ldr r9, [sp, #0x2c]
	mla r1, r9, r8, r1
	bl _ll_sdiv
	mov r11, r0
	str r1, [sp, #0x2c]
_020C83B8:
	ldr r0, [sp, #0x2c]
	mov r3, r11, lsl #0xd
	mov r2, r0, lsl #0xd
	mov r0, #0x80000000
	orr r2, r2, r11, lsr #0x13
	adds r0, r3, r0
	adc r0, r2, #0x0
	cmp r7, #0x0
	mov r1, #0x0
	strne r0, [r4, #0x0]
	strne r1, [r4, #0x0]
	strne r1, [r4, #0x0]
	strne r1, [r4, #0x0]
	strne r1, [r4, #0x0]
	cmp r6, #0x0
	strne r0, [r6, #0x14]
	bl FX_GetDivResultFx64c
	cmp r8, #0x1000
	beq _020C8428
	mov r9, r8, asr #0x1f
	mov r2, #0x1000
	mov r3, #0x0
	umull r12, r10, r0, r8
	mla r10, r0, r9, r10
	mov r0, r12
	mla r10, r1, r8, r10
	mov r1, r10
	bl _ll_sdiv
_020C8428:
	mov r9, r1, lsl #0xd
	mov r10, r0, lsl #0xd
	mov r2, #0x80000000
	orr r9, r9, r0, lsr #0x13
	adds r2, r10, r2
	adc r2, r9, #0x0
	cmp r7, #0x0
	mov r3, #0x0
	strne r2, [r4, #0x0]
	strne r3, [r4, #0x0]
	cmp r6, #0x0
	strne r2, [r6, #0x28]
	ldr r3, [sp, #0xc]
	ldr r2, [sp, #0x8]
	add r9, r3, r2
	rsb lr, r9, #0x0
	ldr r3, [sp, #0x0]
	ldr r2, [sp, #0x4]
	ldr r9, [sp, #0x5c]
	add r2, r3, r2
	ldr r3, [sp, #0x58]
	rsb r12, r2, #0x0
	add r3, r9, r3
	mov r9, r12, asr #0x1f
	str r9, [sp, #0x20]
	mov r9, r3, asr #0x1f
	str r9, [sp, #0x24]
	umull r10, r9, r5, lr
	mov r2, lr, asr #0x1f
	str r2, [sp, #0x1c]
	str r10, [sp, #0x18]
	ldr r10, [sp, #0x1c]
	mov r2, #0x80000000
	mla r9, r5, r10, r9
	ldr r5, [sp, #0x14]
	mla r9, r5, lr, r9
	ldr r5, [sp, #0x18]
	adds r5, r5, r2
	adc r10, r9, #0x0
	ldr r5, [sp, #0x20]
	umull lr, r9, r11, r12
	mla r9, r11, r5, r9
	ldr r5, [sp, #0x2c]
	mla r9, r5, r12, r9
	adds r5, lr, r2
	adc r5, r9, #0x0
	umull r11, r9, r0, r3
	adds r2, r11, r2
	ldr r2, [sp, #0x24]
	mla r9, r0, r2, r9
	mla r9, r1, r3, r9
	adc r0, r9, #0x0
	cmp r7, #0x0
	strne r10, [r4, #0x0]
	strne r5, [r4, #0x0]
	strne r0, [r4, #0x0]
	strne r8, [r4, #0x0]
	cmp r6, #0x0
	strne r10, [r6, #0x30]
	strne r5, [r6, #0x34]
	strne r0, [r6, #0x38]
	add sp, sp, #0x34
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020C8528: .word 0x04000440
_020C852C: .word 0x04000458
_020C8530: .word 0x04000290
_020C8534: .word 0x04000298

	arm_func_start G3i_PerspectiveW_
G3i_PerspectiveW_: ; 0x020C8538
	stmdb sp!, {r4-r10,lr}
	mov r5, r0
	mov r0, r1
	mov r1, r5
	ldr r6, [sp, #0x24]
	mov r9, r2
	mov r8, r3
	ldr r5, [sp, #0x2c]
	bl FX_Div
	mov r7, r0
	cmp r6, #0x1000
	mulne r1, r7, r6
	movne r0, r1, asr #0xb
	addne r0, r1, r0, lsr #0x14
	movne r7, r0, asr #0xc
	ldr r0, [sp, #0x28]
	ldr r2, _020C8718 ; =0x04000290
	cmp r0, #0x0
	mov r3, #0x0
	str r3, [r2, #0x0]
	ldr r1, _020C871C ; =0x04000298
	str r7, [r2, #0x4]
	str r9, [r1, #0x0]
	ldrne r0, _020C8720 ; =0x04000440
	str r3, [r1, #0x4]
	ldrne r4, _020C8724 ; =0x04000458
	strne r3, [r0, #0x0]
	cmp r5, #0x0
	beq _020C85E4
	mov r1, #0x0
	str r1, [r5, #0x4]
	str r1, [r5, #0x8]
	str r1, [r5, #0xc]
	str r1, [r5, #0x10]
	str r1, [r5, #0x18]
	str r1, [r5, #0x1c]
	str r1, [r5, #0x20]
	str r1, [r5, #0x24]
	rsb r0, r6, #0x0
	str r0, [r5, #0x2c]
	str r1, [r5, #0x30]
	str r1, [r5, #0x34]
	str r1, [r5, #0x3c]
_020C85E4:
	bl FX_GetDivResult
	ldr r3, [sp, #0x20]
	ldr r1, [sp, #0x28]
	ldr sb, _020C8718 ; =0x04000290
	mov r12, #0x0
	str r12, [r9, #0x0]
	mov r10, #0x1000
	ldr r2, _020C871C ; =0x04000298
	str r10, [r9, #0x4]
	sub r3, r8, r3
	str r3, [r2, #0x0]
	str r12, [r2, #0x4]
	cmp r1, #0x0
	beq _020C8644
	str r0, [r4, #0x0]
	str r12, [r4, #0x0]
	str r12, [r4, #0x0]
	str r12, [r4, #0x0]
	str r12, [r4, #0x0]
	str r7, [r4, #0x0]
	str r12, [r4, #0x0]
	str r12, [r4, #0x0]
	str r12, [r4, #0x0]
	str r12, [r4, #0x0]
_020C8644:
	cmp r5, #0x0
	strne r0, [r5, #0x0]
	strne r7, [r5, #0x14]
	bl FX_GetDivResultFx64c
	cmp r6, #0x1000
	beq _020C8680
	mov r2, r6, asr #0x1f
	umull r7, r3, r0, r6
	mla r3, r0, r2, r3
	mla r3, r1, r6, r3
	mov r0, r7
	mov r1, r3
	mov r2, #0x1000
	mov r3, #0x0
	bl _ll_sdiv
_020C8680:
	ldr r3, [sp, #0x20]
	mov r10, r8, lsl #0x1
	add r12, r3, r8
	mov r2, r12, asr #0x1f
	umull r7, lr, r0, r12
	mla lr, r0, r2, lr
	mov r9, #0x80000000
	smull r3, r2, r10, r3
	mla lr, r1, r12, lr
	adds r7, r7, r9
	mov r8, #0x800
	adc r7, lr, #0x0
	adds r3, r3, r8
	adc r2, r2, #0x0
	mov r3, r3, lsr #0xc
	orr r3, r3, r2, lsl #0x14
	umull r10, r8, r0, r3
	mov r2, r3, asr #0x1f
	adds r9, r10, r9
	mla r8, r0, r2, r8
	mla r8, r1, r3, r8
	ldr r0, [sp, #0x28]
	adc r2, r8, #0x0
	cmp r0, #0x0
	mov r0, #0x0
	beq _020C8704
	str r7, [r4, #0x0]
	rsb r1, r6, #0x0
	str r1, [r4, #0x0]
	str r0, [r4, #0x0]
	str r0, [r4, #0x0]
	str r2, [r4, #0x0]
	str r0, [r4, #0x0]
_020C8704:
	cmp r5, #0x0
	strne r7, [r5, #0x28]
	strne r2, [r5, #0x38]
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_020C8718: .word 0x04000290
_020C871C: .word 0x04000298
_020C8720: .word 0x04000440
_020C8724: .word 0x04000458
